/**
 * @file main.cpp
 * @author G. Hulsbos
 * @date June 29, 2026
 * @brief Main entry point executing the telemetric loop for DHT11 and MQTT.
 */

#include <iostream>
#include <thread>
#include <chrono>

#include "mqttHandler.h"
#include "digitalSwitch.h"
#include "DHT11Sensor.h"

int main()
{
    digitalSwitch myLed;

    if (!myLed.init())
    {
        std::cerr << "Error: cannot open chip or pin.\n" << std::endl;
    }

    // Set up local MQTT infrastructure connection
    MqttHandler mqtt("tcp://localhost:1883", "GH", &myLed);
    mqtt.connect();
    mqtt.publish("test/topic", "Hello, MQTT!");
    mqtt.subscribe("topic/led");

    DHT11Sensor sensor(0);

    while (true)
    {
        auto temp = sensor.getTemperature();
        auto hum = sensor.getHumidity();

        if (temp.has_value() && hum.has_value())
        {
            mqtt.publish("sensor/air/temp", std::to_string(temp.value()));
            mqtt.publish("sensor/air/hum", std::to_string(hum.value()));

            std::string peakHoldText = sensor.makeString();
            mqtt.publish("sensor/air/peakhold", peakHoldText);

            std::cout << peakHoldText << std::endl;
            std::cout << "Temp and hum successfully sent" << std::endl;
        }
        else
        {
            std::cerr << "Error: could not read sysfs-file" << std::endl;
        }

        // 3-second sampling rate restriction to respect DHT11 hardware limits
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
