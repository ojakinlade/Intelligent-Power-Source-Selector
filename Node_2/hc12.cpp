#include <Arduino.h>
#include <SoftwareSerial.h>
#include "hc12.h"

#define RX_DATA_EXPECTED_LEN 4 
/*
 * @brief Initializes HC12 transceiver
*/
HC12::HC12(SoftwareSerial* serial,uint8_t Pin,uint32_t baudRate)
{
  //Initialize private variables
  port = serial;
  this->setPin = Pin;
  port->begin(baudRate);
  pinMode(this->setPin, OUTPUT);
  digitalWrite(setPin, HIGH);
  rxDataCounter = 0;
  for(uint8_t i = 0; i < BufferSize::TX; i++)
  {
    txBuffer[i] = 0;
  }
  for(uint8_t i = 0; i < BufferSize::RX; i++)
  {
    rxBuffer[i] = 0;
  }
}

/**
 * @brief Encodes data into the "txBuffer" before
 * transmission to an HC12 receiver can occur.
 * @param dataToEncode: data to be encoded
 * @param id: location of specific data within "txBuffer".
*/
void HC12::EncodeData(uint16_t dataToEncode,TxDataId id)
{
  uint8_t dataID = (uint8_t)id;
  txBuffer[dataID] = (dataToEncode & 0xFF00) >> 8;
  txBuffer[dataID + 1] = (dataToEncode & 0x00FF);
}

/**
 * @brief Sets the HC12 transceiver to a particular channel
 * @param AT_Cmd: AT Command to set the HC12 to a particular channel
*/
void HC12::SetChannel(const char* AT_Cmd)
{
  digitalWrite(this->setPin, LOW);
  delay(40); //wait for command mode to engage
  port->print(AT_Cmd);
  while(port->available() == 0){} //wait for response
  while(port->available() > 0)
  {
    port->read();
  }
  digitalWrite(this->setPin,HIGH);
  delay(80);
}

/**
 * @brief Sends data to an HC12 receiver.
*/
void HC12::TransmitData(void)
{
  Serial.print("TX Buffer: ");
  for(uint8_t i = 0; i < BufferSize::TX; i++)
  {
    port->write(txBuffer[i]);
    //Debug
    Serial.print(txBuffer[i]);
    Serial.print(' ');
  }
  Serial.print("\n");
}

/**
 * @brief Receives data from an HC12 transmitter.
 * @reurn true: if total data expected is received completely
 *        false: if otherwise
*/
bool HC12::ReceivedData(void)
{
  bool rxDone = false;
  while(port->available())
  {
    rxBuffer[rxDataCounter] = port->read();
    Serial.print(rxBuffer[rxDataCounter]);
    rxDataCounter++;
  }
  //Check if the number of bytes received is that of AT command response or
  //if it is data sent from the other node (6 bytes)
  if(rxDataCounter == BufferSize::RX || rxDataCounter == 6)
  {
    Serial.println();
    rxDataCounter = 0;
    rxDone = false;
  }
  else if(rxDataCounter == RX_DATA_EXPECTED_LEN)
  {
    Serial.println();
    rxDataCounter = 0;
    rxDone = true;
  }
  
  return rxDone;
}

/**
 * @brief Decodes data received from an HC12 transmitter
 * @param id: location of specific data within "rxBuffer" to be decoded.
 * @return decoded data i.e actual value of desired parameter
*/
uint16_t HC12::DecodeData(RxDataId id)
{
  uint8_t dataID = (uint8_t)id;
  return rxBuffer[dataID] << 8 | rxBuffer[dataID + 1];
}
