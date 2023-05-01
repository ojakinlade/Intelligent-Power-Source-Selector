#pragma once

#define CHANNEL_18 "AT+C018\r\n"

class HC12
{
  private:
    enum BufferSize { TX = 6, RX = 8};
    SoftwareSerial* port;
    uint8_t setPin;
    uint8_t rxDataCounter;
    uint8_t txBuffer[BufferSize::TX];
    uint8_t rxBuffer[BufferSize::RX];

  public:
    enum {QUERY = 0xAA, ACK = 0xBB, deviceAddr = 0xDD};
    enum RxDataId
    {
      DATA_QUERY = 0,
      RX_ADDR = 2 //Destination address
    };
    enum TxDataId
    {
      DATA_ACK = 0,
      SRC_ADDR = 2,
      POWER = 4
    };
    HC12(SoftwareSerial* serial,uint8_t Pin,
         uint32_t baudRate = 9600);
    void EncodeData(uint16_t dataToEncode,TxDataId id);
    void SetChannel(const char* AT_Cmd);
    void TransmitData(void);
    bool ReceivedData(void);
    uint16_t DecodeData(RxDataId id);
};
  
