#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include "hc12.h"

namespace Pin
{
  const uint8_t pzemTx = 8;
  const uint8_t pzemRx = 9;
  const uint8_t setPin = 5;
  const uint8_t hc12Tx = 2;
  const uint8_t hc12Rx = 3; 
};

//Objects
SoftwareSerial pzemSerial(Pin::pzemTx,Pin::pzemRx);
SoftwareSerial hc12Serial(Pin::hc12Tx,Pin::hc12Rx);
PZEM004Tv30 pzem(pzemSerial);
HC12 hc12(&hc12Serial,Pin::setPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Energy Monitor");
  hc12Serial.listen();
  hc12.SetChannel(CHANNEL_18);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(hc12.ReceivedData())
  {
    if(hc12.DecodeData(HC12::RxDataId::DATA_QUERY) == HC12::QUERY)
    {
      if(hc12.DecodeData(HC12::RxDataId::RX_ADDR) == HC12::deviceAddr)
      {
        Serial.println("Query Received");
        pzemSerial.listen();
        uint16_t pwr = pzem.power() * 100; 
        //Debug  
        Serial.print("power = ");
        Serial.println(pwr);   
  
        hc12.EncodeData(HC12::ACK,HC12::TxDataId::DATA_ACK);
        hc12.EncodeData(HC12::deviceAddr,HC12::TxDataId::SRC_ADDR);
        hc12.EncodeData(pwr,HC12::TxDataId::POWER);
        
        hc12.TransmitData();
        hc12Serial.listen();
      }   
    } 
  }
}
