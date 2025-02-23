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
    220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330,  # 00:00 - 12:00 (lower load in morning)
    1400, 1500, 1600, 1700, 1800, 1900,                          # 12:00 - 18:00 (moderate load in afternoon)
    2300, 2200, 2200, 2100, 2100, 2100                           # 18:00 - 23:00 (peak load in evening)
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

# Simulate Varying Load Profile (in Watts)
def generate_varying_load_profile():
    base_load = 3000  # Base load in watts
    # Create sinusoidal variation with peaks in the evening
    time_of_day = np.linspace(0, 2 * np.pi, HOURS)  # Time from 0 to 24 hours
    load_variation = 1000 * np.sin(time_of_day)  # Load variation between -1000 and +1000W
    load_profile = base_load + load_variation  # Add the variation to the base load
    return load_profile

# Decision Algorithm
def select_power_sources(load, solar, wind):
    selected_sources = {'solar': [], 'wind': [], 'generator': []}
    for i in range(HOURS):
        demand = load[i]
        solar_avail = solar[i]
        wind_avail = wind[i]
        
        # Check if solar can cover the demand
        if solar_avail >= demand:
            selected_sources['solar'].append(demand)
            selected_sources['wind'].append(0)
            selected_sources['generator'].append(0)
        
        # Check if wind alone can cover the demand (even if solar can't)
        elif wind_avail >= demand:
            selected_sources['solar'].append(0)
            selected_sources['wind'].append(demand)
            selected_sources['generator'].append(0)
        
        # If neither solar nor wind alone can cover the demand, use both
        elif solar_avail + wind_avail >= demand:
            selected_sources['solar'].append(solar_avail)
            selected_sources['wind'].append(demand - solar_avail)
            selected_sources['generator'].append(0)
        
        # If both solar and wind together still can't cover the demand, use generator
        else:
            selected_sources['solar'].append(solar_avail)
            selected_sources['wind'].append(wind_avail)
            selected_sources['generator'].append(demand - solar_avail - wind_avail)

    return selected_sources

def calculate_all_in_cost(selected_sources, solar_power_data, wind_power_data):
    """
    Calculates the hourly costs for solar, wind, and generator based on "all-in" costs.

    Args:
    - selected_sources (dict): Sources used and the power they supplied.
    - solar_power_data (list): Available solar power for each hour.
    - wind_power_data (list): Available wind power for each hour.

    Returns:
    - Tuple of lists: (solar_cost, wind_cost, generator_cost)
    """
    solar_cost = [
        LCOE_SOLAR if solar_used > 0 else 0
        for solar_used in selected_sources['solar']
    ]
    wind_cost = [
        LCOE_WIND if wind_used > 0 else 0
        for wind_used in selected_sources['wind']
    ]
    generator_cost = [
        GENERATOR_COST * gen_used
        for gen_used in selected_sources['generator']
    ]
    
    return solar_cost, wind_cost, generator_cost

# Cost Calculation
def calculate_cost(selected_sources):
    solar_cost = np.array(selected_sources['solar']) * LCOE_SOLAR
    wind_cost = np.array(selected_sources['wind']) * LCOE_WIND
    generator_cost = np.array(selected_sources['generator']) * GENERATOR_COST
    total_cost = solar_cost + wind_cost + generator_cost
    return total_cost, solar_cost, wind_cost, generator_cost

# Select power sources based on the varying load profile
selected_sources = select_power_sources(load_profile, solar_power_data, wind_power_data)

# Calculate total costs
total_cost, solar_cost, wind_cost, generator_cost = calculate_cost(selected_sources)

# Determine the selected sources in a readable format
def determine_selected_source(solar_used, wind_used, generator_used):
    sources = []
    if solar_used > 0:
        sources.append("Solar")
    if wind_used > 0:
        sources.append("Wind")
    if generator_used > 0:
        sources.append("Generator")
    return ', '.join(sources)

# Create a DataFrame to store the data
hourly_data = pd.DataFrame({
    'Hour': np.arange(24),
    'Load (W)': load_profile,
    'Solar Power (W)': solar_power_data,
    'Wind Power (W)': wind_power_data,
    'Solar Used (W)': selected_sources['solar'],
    'Wind Used (W)': selected_sources['wind'],
    'Generator Used (W)': selected_sources['generator'],
    'Solar Cost (N)': solar_cost,
    'Wind Cost (N)': wind_cost,
    'Generator Cost (N)': generator_cost,
    'Total Cost (N)': total_cost,
    'Selected Source': [
        determine_selected_source(solar_used, wind_used, generator_used)
        for solar_used, wind_used, generator_used in zip(
            selected_sources['solar'], selected_sources['wind'], selected_sources['generator']
        )
    ]
})

hourly_data.to_csv("hourly_power_profile.csv", index=False)

# Print the hourly data table
print("\nHourly Power Profile, Selected Energy Sources, and Usage:")
print(hourly_data)

# # Plotting the load profile and the energy usage
# plt.figure(figsize=(10, 6))
# plt.plot(np.arange(24), load_profile, label='Load (W)', color='blue', linestyle='-', marker='o')
# plt.plot(np.arange(24), solar_power_data, label='Solar Power (W)', color='orange', linestyle='--')
# plt.plot(np.arange(24), wind_power_data, label='Wind Power (W)', color='green', linestyle='--')
# plt.xlabel('Hour of the Day')
# plt.ylabel('Power (W)')
# plt.title('Load Profile and Available Power Sources')
# plt.legend()
# plt.grid(True)
# plt.show()

# Plot the data
# plt.figure(figsize=(12, 8))

# # Plot Load Profile
# plt.subplot(3, 1, 1)
# plt.plot(hourly_data['Hour'], hourly_data['Load (kW)'], label='Load (kW)', color='black')
# plt.title('Hourly Load Profile')
# plt.xlabel('Hour of Day')
# plt.ylabel('Load (kW)')
# plt.grid(True)

# # Plot Solar, Wind, and Generator Usage
# plt.subplot(3, 1, 2)
# plt.plot(hourly_data['Hour'], hourly_data['Solar Used (kW)'], label='Solar Power (kW)', color='yellow')
# plt.plot(hourly_data['Hour'], hourly_data['Wind Used (kW)'], label='Wind Power (kW)', color='blue')
# plt.plot(hourly_data['Hour'], hourly_data['Generator Used (kW)'], label='Generator Power (kW)', color='red')
# plt.title('Selected Energy Sources Usage')
# plt.xlabel('Hour of Day')
# plt.ylabel('Power (kW)')
# plt.legend()
# plt.grid(True)

# # Plot Costs
# plt.subplot(3, 1, 3)
# plt.bar(['Solar', 'Wind', 'Generator'], [solar_cost, wind_cost, generator_cost], color=['yellow', 'blue', 'red'])
# plt.title('Cost Breakdown')
# plt.ylabel('Cost ($)')
# plt.grid(True)

# plt.tight_layout()
# plt.show()