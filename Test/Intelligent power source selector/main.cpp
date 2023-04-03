#include <iostream>
#include <stdint.h>
#include "IPSS.h"

#define SOLAR_OUTPUT        20
#define WIND_OUTPUT         30
#define GENERATOR_OUTPUT    50


using namespace std;

IPSS ipss(SOLAR_OUTPUT,WIND_OUTPUT,GENERATOR_OUTPUT);
const uint32_t totalPower = 15;

int main()
{
    ipss.SelectPowerSource(20,totalPower);
    return 0;
}
