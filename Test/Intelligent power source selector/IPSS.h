#ifndef IPSS_H_INCLUDED
#define IPSS_H_INCLUDED

#include <stdint.h>

class IPSS
{
   private:
       uint16_t _generatorOutput;
       const uint16_t* _solarOutput;
       const uint16_t* _windOutput;
       uint16_t _solarCost;
       uint16_t _windCost;
       uint16_t _generatorCost;
       bool IsSolarAvailable(uint8_t currHour);
       bool IsWindAvailable(uint8_t currHour);
       bool IsGeneratorAvailable(void);
       bool IsSolarSuitable(uint8_t currHour,float powerDemand);
       bool IsWindSuitable(uint8_t currHour,float powerDemand);
       bool IsSolarAndWindSuitable(uint8_t currHour,float powerDemand);
       bool IsSolarAndGeneratorSuitable(uint8_t currHour,float powerDemand);
       bool IsWindAndGeneratorSuitable(uint8_t currHour,float powerDemand);
       bool IsSolarWindAndGeneratorSuitable(uint8_t currHour,float powerDemand);
       bool IsGeneratorSuitable(float powerDemand);

   public:
       IPSS(const uint16_t* solarOutput,const uint16_t* windOutput,uint16_t generatorOutput,
            const uint16_t solarCost,const uint16_t windCost,const uint16_t generatorCost);
       void SelectPowerSource(uint8_t currHour,float powerDemand);
};

#endif // IPSS_H_INCLUDED
