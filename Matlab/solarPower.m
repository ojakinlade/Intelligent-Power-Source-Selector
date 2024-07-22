% Number of hours in a day
hours_per_day = 24;

% Parameters for the normal distribution
mu = 12;  % Mean (peak at noon)
sigma = 3;  % Standard deviation (spread of the irradiance curve)

% Generate the hours of the day
hours = linspace(0, hours_per_day - 1, hours_per_day);

% Generate solar irradiance data following a normal distribution
irradiance = normpdf(hours, mu, sigma);

% Scale the irradiance data to a realistic range (e.g., 0 to 1000 W/m^2)
peak_irradiance = 1000;  % Peak irradiance in W/m^2
daily_irradiance = irradiance / max(irradiance) * peak_irradiance;

% Define solar panel efficiency and area
solar_panel_efficiency = 0.2;  % 20% efficiency
solar_panel_area = 10;  % Area in square meters

% Calculate hourly power generation (in Watts)
hourly_power = daily_irradiance * solar_panel_efficiency * solar_panel_area;

% Plot the solar irradiance over time
figure;
subplot(2, 1, 1);
plot(hours, daily_irradiance, '-o');
xlabel('Hour of the Day');
ylabel('Solar Irradiance (W/m^2)');
title('Solar Irradiance Over Time (Following a Normal Distribution)');

% Plot the hourly power generation over time
subplot(2, 1, 2);
plot(hours, hourly_power, '-o');
xlabel('Hour of the Day');
ylabel('Power Generation (Watts)');
title('Hourly Solar Power Generation');

% Display the irradiance and power data
disp(table(hours', daily_irradiance', hourly_power', 'VariableNames', {'Hour', 'SolarIrradiance', 'PowerGeneration'}));
