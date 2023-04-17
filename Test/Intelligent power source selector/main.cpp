#include <iostream>
#include <stdint.h>
#include <cstdlib>
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

const uint16_t GENERATOR_COST = 80;
const uint16_t SOLAR_COST = 60;
const uint16_t WIND_COST = 100;
//uint8_t currHour = 11;
using namespace std;

IPSS ipss(SOLAR_OUTPUT,WIND_OUTPUT,GENERATOR_OUTPUT,
          SOLAR_COST,WIND_COST,GENERATOR_COST);
uint32_t totalPower;


int main()
{
    //srand(20);
    cout << "TIME" <<'\t'<< "Total Demand" <<'\t' << "Solar Output" <<'\t'<< "Wind Output"<<'\t'<<"Gen Output"<<'\t'<<"IPSS Selection"<<'\t' <<'\t'<<"Cost"<<endl;
    for(int i = 0; i < 24; i++)
    {
        totalPower = 1 + (rand() % 100);
        cout<< i <<'\t' << totalPower <<'\t' << '\t' << '\t' << SOLAR_OUTPUT[i] << '\t' << '\t' << WIND_OUTPUT[i] << '\t' << GENERATOR_OUTPUT;
        ipss.SelectPowerSource(i,totalPower);
    }

    return 0;
}
