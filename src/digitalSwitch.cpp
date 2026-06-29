#include "digitalSwitch.h"
#include "mqttHandler.h"
#include <iostream>

digitalSwitch::digitalSwitch(const char *chipname) : chipname(chipname), chip(nullptr), request(nullptr)
{
}

digitalSwitch::~digitalSwitch()
{
    // Clean up hardware resources on destruction
    if (request)
    {
        gpiod_line_request_release(request);
    }
    if (chip)
    {
        gpiod_chip_close(chip);
    }
}

bool digitalSwitch::init()
{
    chip = gpiod_chip_open(chipname);
    if (!chip)
    {
        std::cerr << "Failed to open GPIO chip: " << chipname << std::endl;
        return false;
    }

    // Configure line settings for a standard output pin
    gpiod_line_settings *settings = gpiod_line_settings_new();
    gpiod_line_settings_set_direction(settings, GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_settings_set_output_value(settings, GPIOD_LINE_VALUE_INACTIVE);

    gpiod_line_config *line_cfg = gpiod_line_config_new();
    unsigned int offset = 16; // Hardcoded pin index for this application

    if (gpiod_line_config_add_line_settings(line_cfg, &offset, 1, settings) < 0)
    {
        std::cerr << "Failed in line configuration.\n" << std::endl; 
        return false;
    }

    gpiod_request_config* req_cfg = gpiod_request_config_new();
    gpiod_request_config_set_consumer(req_cfg, "digitalSwitch-output");

    // Request the line claim from the OS kernel
    request = gpiod_chip_request_lines(chip, req_cfg, line_cfg);
    if (!request)
    {
        std::cerr << "Line request failed.\n" << std::endl;
        return false;
    }
    
    gpiod_line_settings_free(settings);
    gpiod_line_config_free(line_cfg);
    gpiod_request_config_free(req_cfg);

    return true;
}

void digitalSwitch::setValue(bool value)
{
    if (!request) return;

    enum gpiod_line_value gpiod_val = value ? GPIOD_LINE_VALUE_ACTIVE : GPIOD_LINE_VALUE_INACTIVE;
    gpiod_line_request_set_value(request, 16, gpiod_val);
}
