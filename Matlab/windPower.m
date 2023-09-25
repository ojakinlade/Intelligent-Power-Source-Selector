% Generate simulated wind speed data
num_samples = 365 * 24;  % Number of samples for one year (assuming hourly data)
shape_parameter = 2;    % Adjust as needed
scale_parameter = 6;   % Adjust as needed

simulated_wind_speed = wblrnd(scale_parameter, shape_parameter, [num_samples, 1]);

% Define a wind turbine power curve function
turbine_power_curve = @(wind_speed) (0.5 * wind_speed.^3);  % power curve
% Assuming simulated_wind_speed is the generated wind speed data

% Define the number of hours in a day
hours_per_day = 24;

% Initialize an array to store hourly power generation
hourly_power = zeros(hours_per_day, 1);

% Calculate hourly power generation and create a table
power_table = table('Size', [hours_per_day, 2], 'VariableTypes', {'double', 'double'});
power_table.Properties.VariableNames = {'Hour', 'WindPower'};

% Calculate hourly power generation
for hour = 1:hours_per_day
    % Filter wind speeds for the current hour
    wind_speed_hourly = simulated_wind_speed((hour - 1) * num_samples / hours_per_day + 1 : hour * num_samples / hours_per_day);

    % Calculate power for each wind speed using the power curve
    power_hourly = turbine_power_curve(wind_speed_hourly);

    % Sum the hourly power generation
    hourly_power(hour) = sum(power_hourly);

    % Add data to the table
    power_table.Hour(hour) = hour;
    power_table.WindPower(hour) = hourly_power(hour);
end

% Display the table
disp(power_table);

% Plot the hourly power generation
plot(1:hours_per_day, hourly_power);
xlabel('Hour of the Day');
ylabel('Wind Power (Watts)');
title('Hourly Wind Power Generation');

% Plot the hourly power generation
subplot(2, 1, 1);
plot(1:hours_per_day, hourly_power);
xlabel('Hour of the Day');
ylabel('Wind Power (Watts)');
title('Hourly Wind Power Generation');

% Plot the wind speed distribution
subplot(2, 1, 2);
histogram(simulated_wind_speed, 'Normalization', 'pdf');  % 'pdf' for probability density
xlabel('Wind Speed (m/s)');
ylabel('Probability Density');
title('Wind Speed Distribution');

% Adjust the subplot layout
sgtitle('Hourly Wind Power and Wind Speed Distribution');
