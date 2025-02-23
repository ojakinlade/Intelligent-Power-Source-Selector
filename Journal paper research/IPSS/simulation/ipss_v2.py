import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Constants
HOURS = 24
LCOE_SOLAR = 100  # Cost per kWh
LCOE_WIND = 200   # Cost per kWh
GENERATOR_COST = 0.15  # Cost per kWh

# Wind Power Data for each hour (given in the problem)
wind_power_data = [
    634.6, 733.76, 818.39, 654.97, 613.94, 587.47, 678.97, 719.86, 642.3,
    595.1, 643.84, 695.86, 648.41, 651.23, 636.94, 696.95, 610.48, 728.35,
    692.31, 620.21, 645.61, 704.21, 727.39, 662.95
]

solar_power_data = [
    0.10064, 0.36116, 1.1598, 3.3327, 8.5697, 19.719, 40.601, 74.806, 123.33, 181.96,
    240.22, 283.79, 300, 283.79, 240.22, 181.96, 123.33, 74.806, 40.601, 19.719,
    8.5697, 3.3327, 1.1598, 0.36116
]

# Load profile in Watts
load_profile = [
    2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300,  # 00:00 - 12:00 (lower load in morning)
    3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500,  # 12:00 - 18:00 (moderate load in afternoon)
    4600, 4700, 4800, 4900, 5000, 5100, 5200, 5300, 5400, 5500, 5600, 5700   # 18:00 - 23:00 (peak load in evening)
]

# Load profile in Watts
load_profile = [
    220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330,  # 00:00 - 12:00 (lower load in morning)
    1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2200, 2300, 2400,  # 12:00 - 18:00 (moderate load in afternoon)
    2300, 2200, 2200, 2100, 2100, 2100, 2000, 1500, 1400, 1300, 600, 400   # 18:00 - 23:00 (peak load in evening)
]

# Create a DataFrame to store the Hourly Wind Power data
wind_data = pd.DataFrame({
    'Hour': np.arange(24),  # Hours from 0 to 23
    'WindPower': wind_power_data
})

solar_data = pd.DataFrame({
    'Hour': np.arange(24),
    'SolarPower': solar_power_data
})

# Decision Algorithm
def select_power_sources(load, solar, wind):
    """
    Determines which sources are used to meet the power demand.

    Args:
        load (list): List of power demands at each time step.
        solar (list): List of available solar power at each time step.
        wind (list): List of available wind power at each time step.

    Returns:
        list: A list of sets, where each set contains the sources used to meet the demand.
    """

    selected_sources = []
    for i in range(1):
        demand = load[i]
        solar_avail = solar[i]
        wind_avail = wind[i]

        sources_used = set()
        
        # Check if solar can cover the demand
        if solar_avail >= demand:
            sources_used.add('solar')
        
        # Check if wind alone can cover the demand (even if solar can't)
        elif wind_avail >= demand:
            sources_used.add('wind')
        
        # If neither solar nor wind alone can cover the demand, use both
        elif solar_avail + wind_avail >= demand:
            sources_used.add('solar')
            sources_used.add('wind')
        
        # If both solar and wind together still can't cover the demand, use generator
        else:
            if solar_avail > 0:
                sources_used.add('solar')
            if wind_avail > 0:
                sources_used.add('wind')
            sources_used.add('generator')
        selected_sources.append(sources_used)
    return selected_sources

selected_sources = select_power_sources(load_profile, solar_power_data, wind_power_data)
print(selected_sources)