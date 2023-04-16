#ifndef IPSS_H_INCLUDED
#define IPSS_H_INCLUDED

#include <stdint.h>

class IPSS
{
   private:
       uint32_t _generatorOutput;
       uint32_t _solarOutput;
       uint32_t _windOutput;
       bool IsSolarAvailable(uint8_t currHour);
       bool IsWindAvailable(uint8_t currHour);
       bool IsGeneratorAvailable(uint8_t currHour);
       bool IsSolarSuitable(float powerDemand);
       bool IsWindSuitable(float powerDemand);
       bool IsGeneratorSuitable(float powerDemand);

   public:
       IPSS(uint32_t solarOutput,uint32_t windOutput,uint32_t generatorOutput);
       void SelectPowerSource(uint8_t currHour,float powerDemand);
};

#endif // IPSS_H_INCLUDED
