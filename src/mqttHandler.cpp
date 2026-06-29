#include "mqttHandler.h"
#include <iostream>

MqttHandler::MqttHandler(std::string address, std::string client, digitalSwitch* gpio) : _client(address, client)
{
    _client.set_callback(*this);
    this->led = gpio;
}

bool MqttHandler::connect()
{
    try
    {
        _client.connect();
        std::cout << "Connected to MQTT broker successfully." << std::endl;
        return true;
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error connecting to MQTT broker: " << exc.what() << std::endl;
        return false;
    }
}

void MqttHandler::disconnect()
{
    try
    {
        _client.disconnect();
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error disconnecting from MQTT broker: " << exc.what() << std::endl;
    }
}

void MqttHandler::publish(std::string topic, std::string payload)
{
    try
    {
        mqtt::message_ptr msg = mqtt::make_message(topic, payload);
        _client.publish(msg);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error publishing message: " << exc.what() << std::endl;
    }
}

void MqttHandler::subscribe(std::string topic)
{
    try
    {
        _client.subscribe(topic);
    }
    catch (const mqtt::exception& exc)
    {
        std::cerr << "Error subscribing to topic: " << exc.what() << std::endl;
    }
}

void MqttHandler::message_arrived(mqtt::const_message_ptr msg)
{
    std::string topic = msg->get_topic();
    std::string payload = msg->to_string();

    std::cout << "Message arrived on topic: " << topic << std::endl;
    std::cout << "Payload: " << payload << std::endl;

    if (topic == "topic/led")
    {
        // Note: The physical hardware mapping logic is inverted on this circuit
        if (payload == "true")
        {
            led->setValue(false);
            std::cout << "LED on" << std::endl;
        }
        else if (payload == "false")
        {
            led->setValue(true);
            std::cout << "LED off" << std::endl;
        }
    }
}
