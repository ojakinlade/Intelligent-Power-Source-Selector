#include <iostream>
#include <stdint.h>
#include "IPSS.h"

#define GENERATOR_OUTPUT    50

const uint16_t SOLAR_OUTPUT[24] = {0,0,0,0,0,0,
                                   10,15,20,25,30,35,
                                   40,40,35,30,20,
                                   10,0,0,0,0,0};
const uint16_t WIND_OUTPUT[24] = {32,34,38,51,53,52,
                                 50,36,35,34,32,33,
                                 36,31,35,58,59,51,
                                 52,50,56,53,38,34};
uint8_t currHour = 7;
using namespace std;

IPSS ipss(SOLAR_OUTPUT,WIND_OUTPUT,GENERATOR_OUTPUT);
const uint32_t totalPower = 89;

int main()
{
    cout <<"Solar output: "<<SOLAR_OUTPUT[currHour]<<endl;
    cout <<"Wind output: "<<WIND_OUTPUT[currHour]<<endl;
    ipss.SelectPowerSource(currHour,totalPower);
    return 0;
}
