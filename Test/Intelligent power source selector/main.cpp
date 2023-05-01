#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include "IPSS.h"

#define GENERATOR_OUTPUT    50

const uint16_t SOLAR_OUTPUT[24] = {0,0,0,0,0,0,
                                   20,30,35,40,40,45,
                                   50,50,50,50,40,30,
                                   20,0,0,0,0,0};
const uint16_t WIND_OUTPUT[24] = {20,20,25,35,40,45,
                                 50,50,50,50,45,40,
                                 35,30,30,35,40,50,
                                 50,50,50,45,30,20};

const uint16_t GENERATOR_COST = 100;
const uint16_t SOLAR_COST = 40;
const uint16_t WIND_COST = 60;
//uint8_t currHour = 11;
using namespace std;

IPSS ipss(SOLAR_OUTPUT,WIND_OUTPUT,GENERATOR_OUTPUT,
          SOLAR_COST,WIND_COST,GENERATOR_COST);
uint32_t totalPower[24] = {10,15,10,20,20,20,
                           80,80,80,30,30,30,
                           40,35,30,35,40,70,
                           80,80,90,90,50,30};


int main()
{
    //srand(20);
    cout << "TIME" <<'\t'<< "Total Demand" <<'\t' << "Solar Output" <<'\t'<< "Wind Output"<<'\t'<<"Gen Output"<<'\t'<<"IPSS Selection"<<'\t' <<'\t'<<"Cost"<<endl;
    for(int i = 0; i < 24; i++)
    {
        //totalPower = 1 + (rand() % 100);
        cout<< i <<'\t' << totalPower[i] <<'\t' << '\t' << '\t' << SOLAR_OUTPUT[i] << '\t' << '\t' << WIND_OUTPUT[i] << '\t' << GENERATOR_OUTPUT;
        ipss.SelectPowerSource(i,totalPower[i]);
    }

    return 0;
}
