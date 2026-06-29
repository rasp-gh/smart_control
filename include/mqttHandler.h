/**
 * @file mqttHandler.h
 * @author G. Hulsbos
 * @date June 29, 2026
 * @brief MQTT client wrapper implementing callbacks for hardware control.
 */

#pragma once
#include <mqtt/client.h>
#include <string.h>
#include "digitalSwitch.h"

/**
 * @class MqttHandler
 * @brief Handles MQTT publish/subscribe topics and maps events to hardware actions.
 */
class MqttHandler : public virtual mqtt::callback
{
public:
    MqttHandler(std::string address, std::string client, digitalSwitch* gpio);
    
    bool connect();
    void disconnect();
    void publish(std::string topic, std::string payload);
    void subscribe(std::string topic);
    
    // Override from mqtt::callback to intercept incoming broker messages
    void message_arrived(mqtt::const_message_ptr msg) override;
    
private:
    digitalSwitch* led;
    mqtt::client _client;
};
