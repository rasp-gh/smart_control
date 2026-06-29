#include "DHT11Sensor.h"
#include <fstream>
#include <sstream>
#include <iostream>

DHT11Sensor::DHT11Sensor(int device_index)
{
    // Construct the standard Linux sysfs path for the industrial I/O device
    base_path = "/sys/bus/iio/devices/iio:device" + std::to_string(device_index) + "/";
}

std::optional<float> DHT11Sensor::getTemperature()
{
    auto raw_temp = read_sysfs("in_temp_input");
    if (!raw_temp.has_value()) return std::nullopt;

    // Convert millidegrees Celsius from sysfs to standard Celsius degrees
    float temp = raw_temp.value() / 1000.0f;

    // Filter out potential hardware read errors using boundaries
    if (temp < temp_error_low || temp > temp_error_high) return std::nullopt;

    // Update historical peak-hold temperature metrics
    if (temp < min_temp) min_temp = temp;
    if (temp > max_temp) max_temp = temp;

    return temp;
}

std::optional<float> DHT11Sensor::getHumidity()
{
    auto raw_hum = read_sysfs("in_humidityrelative_input");
    if (!raw_hum.has_value()) return std::nullopt;

    // Convert milli-percent humidity from sysfs to standard percentage
    float hum = raw_hum.value() / 1000.0f;

    // Filter out potential hardware read errors using boundaries
    if (hum < hum_error_low || hum > hum_error_high) return std::nullopt;

    // Update historical peak-hold humidity metrics
    if (hum < min_hum) min_hum = static_cast<int>(hum);
    if (hum > max_hum) max_hum = static_cast<int>(hum);

    return hum;
}

std::string DHT11Sensor::makeString()
{
    std::stringstream ss;
    ss << "Peak Hold Stats -> Temp: [" << min_temp << "C - " << max_temp 
       << "C] | Hum: [" << min_hum << "% - " << max_hum << "%]";
    return ss.str();
}

std::optional<float> DHT11Sensor::read_sysfs(const std::string& filename)
{
    std::ifstream file(base_path + filename);
    if (!file.is_open()) return std::nullopt;

    float value;
    if (file >> value)
    {
        return value;
    }
    return std::nullopt;
}
