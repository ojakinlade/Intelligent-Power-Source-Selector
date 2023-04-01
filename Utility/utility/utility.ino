#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#include "hc12.h"

#define NO_OF_NODES 2

namespace Pin
{
  const uint8_t setPin = 15;
};

typedef  struct
{
  uint16_t node1Pwr;
  uint16_t node2Pwr;
}pwr_t;

typedef struct
{
  uint32_t hour;
  uint32_t minute;
}tim_t;

//RTOS Handle(s)
TaskHandle_t appTaskHandle;
TaskHandle_t nodeTaskHandle;
TaskHandle_t webServerTaskHandle;
QueueHandle_t nodeToAppQueue;

AsyncWebServer server(80);

const char* ssid = "AkJoe";
const char* pword = "spacetek";

const char* PARAM_INPUT_1 = "HOUR";
const char* PARAM_INPUT_2 = "MINUTE";

tim_t Time;

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

void setup() {
  // put your setup code here, to run once:
  setCpuFrequencyMhz(80);
  Serial.begin(115200);
  Serial.println("Energy monitor");
  nodeToAppQueue = xQueueCreate(1,sizeof(pwr_t));
  if(nodeToAppQueue != NULL)
  {
    Serial.println("Node-Application Queue successfully creeated");
  }
  else
  {
    Serial.println("Node-Application Queue creation failed");
  }
  //Tasks
  xTaskCreatePinnedToCore(NodeTask,"",30000,NULL,1,&nodeTaskHandle,1);
  xTaskCreatePinnedToCore(ApplicationTask,"",25000,NULL,1,&appTaskHandle,1);  
  xTaskCreatePinnedToCore(WebServerTask,"",3000,NULL,1,&webServerTaskHandle,1);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void WebServerTask(void* pvParameter)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pword);
  if(WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi connect Failed");
    return;
  }
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
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2))
    {
      inputMessage = "";
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      Time.minute = inputMessage.toInt();
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
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void ApplicationTask(void* pvParameters)
{
  LiquidCrystal_I2C lcd(0x27,20,4);
  static pwr_t pwr;

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
    //Receive sensor Data from Node-Application Queue.
    if(xQueueReceive(nodeToAppQueue,&pwr,0) == pdPASS)
    {
      Serial.println("--Application task received data from Node task\n");
    }
    float totalPwr = pwr.node1Pwr + pwr.node2Pwr;
    switch(displayState)
    {
      case displayState1:
        lcd.setCursor(0,0);
        lcd.print("Time: ");
        lcd.print(Time.hour);
        lcd.print(":");
        lcd.print(Time.minute);
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
        lcd.print("Source used: ");
        lcd.print("xxxx");
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
