#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include "numeric_lib.h"
#include "hc12.h"
#include "IPSS.h"

#define NO_OF_NODES         2
#define GENERATOR_OUTPUT    50

const uint16_t SOLAR_OUTPUT[24] = {0,0,0,0,0,0,
                                   10,15,20,25,30,35,
                                   40,40,35,30,20,
                                   10,0,0,0,0,0};
const uint16_t WIND_OUTPUT[24] = {32,34,38,51,53,52,
                                  50,36,35,34,32,33,
                                  36,31,35,58,59,51,
                                  52,50,56,53,38,34};

const uint16_t GENERATOR_COST = 80;
const uint16_t SOLAR_COST = 60;
const uint16_t WIND_COST = 100;

namespace Pin
{
  const uint8_t setPin = 15;
  const uint8_t ioPin = 4;
  const uint8_t sclkPin = 5;
  const uint8_t cePin = 2;
};

typedef  struct
{
  uint16_t node1Pwr;
  uint16_t node2Pwr;
}pwr_t;

typedef struct
{
  uint8_t hour;
  uint8_t minute;
}tim_t;

typedef struct
{
  char hour[3];
  char minute[3];
}timeChar_t;

//RTOS Handle(s)
TaskHandle_t appTaskHandle;
TaskHandle_t nodeTaskHandle;
TaskHandle_t webServerTaskHandle;
QueueHandle_t nodeToAppQueue;
QueueHandle_t webServerToAppQueue;

AsyncWebServer server(80);

const char* ssid = "AkJoe";
const char* pword = "spacetek";

const char* PARAM_INPUT_1 = "HOUR";
const char* PARAM_INPUT_2 = "MINUTE";

// HTML web page to handle  input fields (Hour, minute)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Hour: <input type="text" name="HOUR">
    <input type="submit" value="Submit">
  </form><br>
  
  <form action="/get">
    Minute: <input type="text" name="MINUTE">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void DisplayAlignedTwoDigits(LiquidCrystal_I2C& lcd,uint8_t digit)
{
  if(digit < 10)
  {
    lcd.print('0');
    lcd.print(digit);
  }
  else
  {
    lcd.print(digit);
  }
}

void setup() {
  // put your setup code here, to run once:
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  Serial.println("Energy monitor");
  nodeToAppQueue = xQueueCreate(1,sizeof(pwr_t));
  webServerToAppQueue = xQueueCreate(1,sizeof(tim_t));
  if(nodeToAppQueue != NULL)
  {
    Serial.println("Node-Application Queue successfully created");
  }
  else
  {
    Serial.println("Node-Application Queue creation failed");
  }
  if(webServerToAppQueue != NULL)
  {
    Serial.println("WebServer-Application Queue successfully created");
  }
  else
  {
    Serial.println("WebServer-Application Queue creation failed");
  }
  //Tasks
  xTaskCreatePinnedToCore(NodeTask,"",20000,NULL,1,&nodeTaskHandle,1);
  xTaskCreatePinnedToCore(ApplicationTask,"",20000,NULL,1,&appTaskHandle,1);  
  xTaskCreatePinnedToCore(WebServerTask,"",10000,NULL,1,&webServerTaskHandle,1);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void WebServerTask(void* pvParameter)
{
  static tim_t Time;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pword);

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  //Send webpage with required fields to client
  server.on("/",HTTP_GET,[](AsyncWebServerRequest* request)
  {
    request->send_P(200,"text/html",index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request)
  {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) 
    {
      inputMessage = "";
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      Time.hour = inputMessage.toInt();
      if(xQueueSend(webServerToAppQueue,&Time,0) == pdPASS)
      {
        Serial.println("WebServer task sent data to Application Task successfully");
      }
      else
      {
        Serial.println("WebServer task failed to send data to Application Task");
      }
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2))
    {
      inputMessage = "";
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      Time.minute = inputMessage.toInt();
      if(xQueueSend(webServerToAppQueue,&Time,0) == pdPASS)
      {
        Serial.println("WebServer task sent data to Application Task successfully");
      }
      else
      {
        Serial.println("WebServer task failed to send data to Application Task");
      }
      inputParam = PARAM_INPUT_2;
    }
    else 
    {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    Serial.println(inputMessage);
    Serial.print("Hour: ");
    Serial.println(Time.hour);
    Serial.print("Minute: ");
    Serial.println(Time.minute);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();

  while(1)
  {
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void ApplicationTask(void* pvParameters)
{
  LiquidCrystal_I2C lcd(0x27,20,4);
  ThreeWire myWire(Pin::ioPin,Pin::sclkPin,Pin::cePin);
  IPSS ipss(SOLAR_OUTPUT,WIND_OUTPUT,GENERATOR_OUTPUT,
          SOLAR_COST,WIND_COST,GENERATOR_COST);
  RtcDS1302<ThreeWire> Rtc(myWire);

  static pwr_t pwr;
  static tim_t tim;
  static timeChar_t timChar;
  char timeRecvd[20] = {0};

  //[RTC Initialization]
  Rtc.Begin();
  //Set the current time
//  RtcDateTime initialTime = RtcDateTime(__DATE__,"16:52:00");
//  Rtc.SetDateTime(initialTime);

  //[LCD Inititalization]
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("INTELLIGENT");
  lcd.setCursor(4,1);
  lcd.print("POWER SOURCE");
  lcd.setCursor(6,2);
  lcd.print("SELECTOR");
  lcd.setCursor(7,3);
  lcd.print("(IPSS)");
  vTaskDelay(pdMS_TO_TICKS(1500));
  lcd.clear();
  lcd.print("INITIALIZING...");
  vTaskDelay(pdMS_TO_TICKS(1500));
  lcd.clear();
  vTaskResume(nodeTaskHandle);

  const uint8_t displayState1 = 0;
  const uint8_t displayState2 = 1;
  uint8_t displayState = displayState1;
  uint32_t prevTime = millis();

  while(1)
  {
    RtcDateTime timeNow = Rtc.GetDateTime();
    //Receive sensor Data from Node-Application Queue.
    if(xQueueReceive(nodeToAppQueue,&pwr,0) == pdPASS)
    {
      Serial.println("--Application task received data from Node task\n");
    }
    //Receive time setting for RTC from WebServer-Application Queue.
    if(xQueueReceive(webServerToAppQueue,&tim,0) == pdPASS)
    {
      Serial.println("--Application Task received data from Web Server task\n");
      memset(timeRecvd,'\0',strlen(timeRecvd));
      memset(timChar.hour,'\0',strlen(timChar.hour));
      memset(timChar.minute,'\0',strlen(timChar.minute));
      IntegerToString(tim.hour,timChar.hour);
      IntegerToString(tim.minute,timChar.minute);
      
      strcat(timeRecvd,timChar.hour);
      strcat(timeRecvd,":");
      strcat(timeRecvd,timChar.minute);
      strcat(timeRecvd,":00");
      //Set the RTC with the received time
      RtcDateTime receivedTime = RtcDateTime(__DATE__,timeRecvd);
      Rtc.SetDateTime(receivedTime);  
    }
    float totalPwr = pwr.node1Pwr + pwr.node2Pwr;
    powerSource selectedSource = ipss.SelectPowerSource(timeNow.Hour(),totalPwr);
    switch(displayState)
    {
      case displayState1:
        lcd.setCursor(0,0);
        lcd.print("Time: ");
        DisplayAlignedTwoDigits(lcd,timeNow.Hour());
        lcd.print(":");
        DisplayAlignedTwoDigits(lcd,timeNow.Minute());
        lcd.setCursor(0,1);
        lcd.print("Node 1: ");
        lcd.print(pwr.node1Pwr / 100.0,2);
        lcd.print(" W");
        lcd.setCursor(0,2);
        lcd.print("Node 2: ");
        lcd.print(pwr.node2Pwr / 100.0,2);
        lcd.print(" W");
        lcd.setCursor(0,3);
        lcd.print("Total PWR: ");
        lcd.print(totalPwr / 100.0);
        lcd.print(" W");
        if(millis() - prevTime >= 4000)
        {
          displayState = displayState2;
          prevTime = millis();
          lcd.clear(); 
        }
        break;

      case displayState2:
        lcd.setCursor(0,0);
        lcd.print("SOLAR:");
        lcd.print(SOLAR_OUTPUT[timeNow.Hour()]);
        lcd.print("W");
        lcd.setCursor(10,0);
        lcd.print("Cost:");
        lcd.print("N");
        lcd.print(SOLAR_COST);
        lcd.setCursor(0,1);
        lcd.print("WIND:");
        lcd.print(WIND_OUTPUT[timeNow.Hour()]);
        lcd.print("W");
        lcd.setCursor(10,1);
        lcd.print("Cost:");
        lcd.print("N");
        lcd.print(WIND_COST);
        lcd.setCursor(0,2);
        lcd.print("GEN:");
        lcd.print(GENERATOR_OUTPUT);
        lcd.print("W");
        lcd.setCursor(10,2);
        lcd.print("Cost:");
        lcd.print("N");
        lcd.print(GENERATOR_COST);
        lcd.setCursor(0,3);
        lcd.print("SELECTED:");
        switch(selectedSource)
        {
          case SOLAR:
            lcd.print("SOLAR");
          break;
          case WIND:
            lcd.print("WIND");
          break;
          case SOLAR_WIND:
            lcd.print("SLR+WND");
          break;
          case SOLAR_GEN:
            lcd.print("SLR+GEN");
            break;
          case WIND_GEN:
            lcd.print("WND+GEN");
            break;
          case SOLAR_WIND_GEN:
            lcd.print("SLR+WND+GEN");
            break;
          case INVALID:
            lcd.print("INVALID");
            break;
        }
        if(millis() - prevTime >= 4000)
        {
          displayState = displayState1;
          prevTime = millis();
          lcd.clear(); 
        }
        break;
    }
  }
}

/**
 * @brief Handles communication between the master and the node via a 
 * serial interface (i.e. MNI).
 * MNI is an acronym for 'Master-Node-Interface'.
*/
void NodeTask(void* pvParameters)
{
  vTaskSuspend(NULL);
  Serial.println("IPSS!!!!!");
  static HC12 hc12(&Serial2,Pin::setPin);
  static pwr_t pwr; 
  static uint8_t Node[NO_OF_NODES] = {HC12::Node1Addr,HC12::Node2Addr};
  enum Nodes
  {
    NODE1 = 0,
    NODE2
  };
  uint8_t node = (uint8_t)NODE1;
  uint32_t nodeTime = millis();
  hc12.SetChannel(CHANNEL_18);
  
  while(1)
  {
    if(millis() - nodeTime >= 1000)
    {
      hc12.EncodeData(HC12::QUERY,HC12::TxDataId::DATA_QUERY);
      hc12.EncodeData(Node[node],HC12::TxDataId::DEST_ADDR);
      hc12.TransmitData();
      node = (node + 1) % 2;
      nodeTime = millis();
    }
    
    if(hc12.ReceivedData())
    {
      if(hc12.DecodeData(HC12::RxDataId::DATA_ACK) == HC12::ACK)
      {
        if(hc12.DecodeData(HC12::RxDataId::SRC_ADDR) == HC12::Node1Addr)
        {
          Serial.println("Data Received from node 1");
          pwr.node1Pwr = hc12.DecodeData(HC12::RxDataId::POWER);
          Serial.println(pwr.node1Pwr);
          if(xQueueSend(nodeToAppQueue,&pwr,0) == pdPASS)
          {
            Serial.println("--Data from Node 1 successfully sent to Application task");
          }
          else
          {
            Serial.println("--Failed to send data from Node 1 to Application Task");
          }
        }
        else if(hc12.DecodeData(HC12::RxDataId::SRC_ADDR) == HC12::Node2Addr)
        {
          Serial.println("Data Received from node 2");
          pwr.node2Pwr = hc12.DecodeData(HC12::RxDataId::POWER);
          Serial.println(pwr.node2Pwr);
          if(xQueueSend(nodeToAppQueue,&pwr,0) == pdPASS)
          {
            Serial.println("--Data from Node 2 successfully sent to Application task");
          }
          else
          {
            Serial.println("--Failed to send data from Node 2 to Application Task");
          }
        }
      }   
    }
  }
}
