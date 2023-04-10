#include <iostream>
#include "IPSS.h"

using namespace std;

IPSS::IPSS(uint32_t solarOutput,uint32_t windOutput,
           uint32_t generatorOutput)
{
  _solarOutput = solarOutput;
  _windOutput = windOutput;
  _generatorOutput = generatorOutput;
}

bool IPSS::IsSolarAvailable(uint8_t currHour)
{
  return (currHour >= 13 && currHour <= 16);
}

bool IPSS::IsWindAvailable(uint8_t currHour)
{
  bool isAvailable = false;
  if((currHour >= 17 && currHour <= 23) || (currHour >= 0 && currHour <= 6))
  {
      isAvailable = true;
  }
  return isAvailable;
}

bool IPSS::IsGeneratorAvailable(uint8_t currHour)
{
  return (currHour >= 7 && currHour <= 12);
}

bool IPSS::IsSolarSuitable(float powerDemand)
{
  return _solarOutput >= powerDemand;
}

bool IPSS::IsWindSuitable(float powerDemand)
{
  return _windOutput >= powerDemand;
}

bool IPSS::IsGeneratorSuitable(float powerDemand)
{
  return _generatorOutput >= powerDemand;
}

powerSource IPSS::SelectPowerSource(uint8_t currHour,float powerDemand)
{
  powerSource selectedSource;
  if(IPSS::IsSolarAvailable(currHour) && IPSS::IsSolarSuitable(powerDemand))
  {
      selectedSource = SOLAR;
  }
  else if(IPSS::IsWindAvailable(currHour) && IPSS::IsWindSuitable(powerDemand))
  {
      selectedSource = WIND;
  }
  else if(IPSS::IsGeneratorAvailable(currHour) && IPSS::IsGeneratorSuitable(powerDemand))
  {
      selectedSource = GENERATOR;
  }
  return selectedSource;
}
