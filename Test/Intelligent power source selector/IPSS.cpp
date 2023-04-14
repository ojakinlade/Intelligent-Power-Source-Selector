#include <iostream>
#include "IPSS.h"

using namespace std;

IPSS::IPSS(const uint16_t* solarOutput,const uint16_t* windOutput,
           uint16_t generatorOutput)
{
    _solarOutput = solarOutput;
    _windOutput = windOutput;
    _generatorOutput = generatorOutput;
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

bool IPSS::IsGeneratorSuitable(float powerDemand)
{
   return _generatorOutput >= powerDemand;
}

void IPSS::SelectPowerSource(uint8_t currHour,float powerDemand)
{
    if(IPSS::IsSolarSuitable(currHour,powerDemand))
    {
        cout << "Solar Selected!" << endl;
    }
    else if(IPSS::IsWindSuitable(currHour,powerDemand))
    {
        cout << "Wind Selected!" << endl;
    }
    else if(IPSS::IsSolarAndWindSuitable(currHour,powerDemand))
    {
        cout << "Solar and Wind Selected!" << endl;
    }
    else if(IPSS::IsSolarAndGeneratorSuitable(currHour,powerDemand))
    {
        cout << "Solar and Generator Selected!" << endl;
    }
    else if(IPSS::IsWindAndGeneratorSuitable(currHour,powerDemand))
    {
        cout << "Wind and Generator Selected!" << endl;
    }
    else if(IPSS::IsSolarWindAndGeneratorSuitable(currHour,powerDemand))
    {
        cout << "Solar, Wind and Generator Selected!" << endl;
    }
}
