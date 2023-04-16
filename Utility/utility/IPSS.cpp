#include "IPSS.h"

#define INFINITY 65535

uint16_t IPSS::GetMinimum(uint16_t num1,uint16_t num2,uint16_t num3,
                 uint16_t num4,uint16_t num5,uint16_t num6)
{
  uint16_t minimum = num1;
  if(num2 < minimum)
  {
    minimum = num2;
  }
  if(num3 < minimum)
  {
    minimum = num3;
  }
  if(num4 < minimum)
  {
    minimum = num4;
  }
  if(num5 < minimum)
  {
    minimum = num5;
  }
  if(num6 < minimum)
  {
    minimum = num6;
  }
  return minimum;
}

IPSS::IPSS(const uint16_t* solarOutput,const uint16_t* windOutput,uint16_t generatorOutput,
           const uint16_t solarCost, const uint16_t windCost,const uint16_t generatorCost)
{
  _solarOutput = solarOutput;
  _windOutput = windOutput;
  _generatorOutput = generatorOutput;
  _solarCost = solarCost;
  _windCost = windCost;
  _generatorCost = generatorCost;
}

bool IPSS::IsSolarAvailable(uint8_t currHour)
{
  return _solarOutput[currHour] > 0;
}

bool IPSS::IsWindAvailable(uint8_t currHour)
{
  return _windOutput[currHour] > 0;
}

bool IPSS::IsGeneratorAvailable(void)
{
  return _generatorOutput > 0;
}

bool IPSS::IsSolarSuitable(uint8_t currHour,float powerDemand)
{
  bool isSuitable = false;
  if(IPSS::IsSolarAvailable(currHour) && _solarOutput[currHour] >= powerDemand)
  {
      isSuitable = true;
  }
  return isSuitable;
}

bool IPSS::IsWindSuitable(uint8_t currHour,float powerDemand)
{
  bool isSuitable = false;
  if(IPSS::IsWindAvailable(currHour) && _windOutput[currHour] >= powerDemand)
  {
      isSuitable = true;
  }
  return isSuitable;
}

bool IPSS::IsSolarAndWindSuitable(uint8_t currHour,float powerDemand)
{
  bool isSuitable = false;
  if(IPSS::IsSolarAvailable(currHour) && IPSS::IsWindAvailable(currHour))
  {
    if((_solarOutput[currHour] + _windOutput[currHour]) >= powerDemand)
    {
        isSuitable = true;
    }
  }
  return isSuitable;
}

bool IPSS::IsSolarAndGeneratorSuitable(uint8_t currHour,float powerDemand)
{
  bool isSuitable = false;
  if(IPSS::IsSolarAvailable(currHour) && IPSS::IsGeneratorAvailable())
  {
    if((_solarOutput[currHour] + _generatorOutput) >= powerDemand)
    {
        isSuitable = true;
    }
  }
  return isSuitable;
}

bool IPSS::IsWindAndGeneratorSuitable(uint8_t currHour,float powerDemand)
{
  bool isSuitable = false;
  if(IPSS::IsWindAvailable(currHour) && IPSS::IsGeneratorAvailable())
  {
    if((_windOutput[currHour] + _generatorOutput) >= powerDemand)
    {
        isSuitable = true;
    }
  }
  return isSuitable;
}

bool IPSS::IsSolarWindAndGeneratorSuitable(uint8_t currHour,float powerDemand)
{
  bool isSuitable = false;
  if(IPSS::IsSolarAvailable(currHour) && IPSS::IsWindAvailable(currHour) && IPSS::IsGeneratorAvailable())
  {
    if((_solarOutput[currHour] + _windOutput[currHour] + _generatorOutput) >= powerDemand)
    {
        isSuitable = true;
    }
  }
  return isSuitable;
}

powerSource IPSS::SelectPowerSource(uint8_t currHour,float powerDemand)
{
  powerSource selectedSource;
  //Calculate the cost of each source
  uint16_t solarCost = IPSS::IsSolarSuitable(currHour,powerDemand) ?
                       _solarCost  : INFINITY;
  uint16_t windCost = IPSS::IsWindSuitable(currHour,powerDemand) ?
                       _windCost : INFINITY;
  uint16_t solarWindCost = IPSS::IsSolarAndWindSuitable(currHour,powerDemand) ?
                           (_solarCost + _windCost) : INFINITY;
  uint16_t solarGeneratorCost = IPSS::IsSolarAndGeneratorSuitable(currHour,powerDemand) ?
                                (_solarCost + _generatorCost) : INFINITY;
  uint16_t windGeneratorCost = IPSS::IsWindAndGeneratorSuitable(currHour,powerDemand) ?
                               (_windCost + _generatorCost) : INFINITY;
  uint16_t solarWindGeneratorCost = IPSS::IsSolarWindAndGeneratorSuitable(currHour,powerDemand) ?
                                  (_solarCost + _windCost + _generatorCost) : INFINITY;
  //Select the power source with the least cost
  uint16_t minCost = IPSS::GetMinimum(solarCost,windCost,solarWindCost,solarGeneratorCost,windGeneratorCost,solarWindGeneratorCost);
  if (minCost == INFINITY)
  {
    selectedSource = INVALID;
  }
  else if (minCost == solarCost)
  {
    selectedSource = SOLAR;
  }
  else if (minCost == windCost)
  {
    selectedSource = WIND;
  }
  else if (minCost == solarWindCost)
  {
    selectedSource = SOLAR_WIND;
  }
  else if (minCost == solarGeneratorCost)
  {
    selectedSource = SOLAR_GEN;
  }
  else if (minCost == windGeneratorCost)
  {
    selectedSource = WIND_GEN;
  }
  else if (minCost == solarWindGeneratorCost)
  {
    selectedSource = SOLAR_WIND_GEN;
  }
  return selectedSource;
}
