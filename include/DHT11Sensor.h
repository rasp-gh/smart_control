/**
 * @file DHT11Sensor.h
 * @author G. Hulsbos
 * @date June 29, 2026
 * @brief Interfaces with a DHT11 sensor via sysfs, tracking peak-hold statistics.
 */

#ifndef DHT11SENSOR_H
#define DHT11SENSOR_H

#include <string>
#include <optional>

/**
 * @class DHT11Sensor
 * @brief Manages DHT11 data collection, filtering, and historical min/max values.
 */
class DHT11Sensor
{
public:
    explicit DHT11Sensor(int device_index = 0);
    ~DHT11Sensor() = default;

    std::optional<float> getTemperature();
    std::optional<float> getHumidity();
    std::string makeString();

    // Getters for historical statistics
    float getMinTemp() const { return min_temp; }
    float getMaxTemp() const { return max_temp; }
    float getMinHum() const { return min_hum; }
    float getMaxHum() const { return max_hum; }

private:
    std::string base_path;

    /**
     * @brief Reads a raw float value from a specific sysfs attribute file.
     */
    std::optional<float> read_sysfs(const std::string& filename);

    // Peak-hold tracking variables
    float min_temp = 999.0f;
    float max_temp = -999.0f;
    int min_hum = 100;
    int max_hum = 0;

    // Validation boundaries for error filtering
    float const temp_error_low = 21.0f;
    float const temp_error_high = 50.0f;
    int const hum_error_low = 20;
    int const hum_error_high = 90;
};

#endif
