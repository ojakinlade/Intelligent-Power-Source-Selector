#include <iostream>
#include <algorithm>
#include "IPSS.h"

#define INFINITY    65535

using namespace std;

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

bool IPSS::IsGeneratorSuitable(uint8_t currHour,float powerDemand)
{
   bool isSuitable = false;
   if(IPSS::IsGeneratorAvailable() && _generatorOutput >= powerDemand)
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

void IPSS::SelectPowerSource(uint8_t currHour,float powerDemand)
{
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
    uint16_t minCost = (min({solarCost,windCost,solarWindCost,solarGeneratorCost,windGeneratorCost,solarWindGeneratorCost}));
    if (minCost == INFINITY)
    {
        cout << "No suitable power source available!" << endl;
    }
    else if (minCost == solarCost)
    {
        cout << '\t' << '\t'  << "Solar" << '\t' << '\t' <<'\t' << solarCost << endl;
    }
    else if (minCost == windCost)
    {
        cout << '\t' << '\t'  << "Wind" << '\t' << '\t' <<'\t'<< windCost << endl;
    }
    else if (minCost == solarWindCost)
    {
        cout << '\t' << '\t'  <<"Solar+Wind" << '\t' <<'\t' << solarWindCost << endl;
    }
    else if (minCost == solarGeneratorCost)
    {
        cout << '\t' << '\t'  <<"Solar+Generator" << '\t' <<'\t' << solarGeneratorCost << endl;
    }
    else if (minCost == windGeneratorCost)
    {
        cout << '\t' << '\t'  <<"Wind+Generator" << '\t' <<'\t' << windGeneratorCost << endl;
    }
    else if (minCost == solarWindGeneratorCost)
    {
        cout << '\t' << '\t'  <<"Solar+Wind+Generator" << '\t' <<'\t'<< solarWindGeneratorCost <<endl;
    }
}
