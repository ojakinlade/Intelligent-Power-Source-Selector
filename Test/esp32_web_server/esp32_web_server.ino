#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

typedef struct
{
  uint32_t hour;
  uint32_t minute;
}tim_t;

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

void ConvStrToInt(char* str, uint32_t* integer)
{
  for(uint32_t i = 0; str[i] != '\0'; i++)
  {
    *integer = *integer * 10 + (str[i] - 48);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

}

void loop() {
  // put your main code here, to run repeatedly:

}
