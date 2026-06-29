/**
 * @file digitalSwitch.h
 * @author G. Hulsbos
 * @date June 29, 2026
 * @brief Hardware abstraction layer for a digital output pin using libgpiod.
 */

#ifndef digitalSwitch_HPP
#define digitalSwitch_HPP

#include <gpiod.h>
#include <string>

/**
 * @class digitalSwitch
 * @brief Encapsulates a GPIO output line via the Linux libgpiod API.
 */
class digitalSwitch
{
public:
    digitalSwitch(const char* chipname = "/dev/gpiochip0");
    ~digitalSwitch();

    /**
     * @brief Opens the GPIO chip and configures pin index 16 as output.
     * @return true if successful, false otherwise.
     */
    bool init();

    /**
     * @brief Sets the logic state of the GPIO pin.
     * @param value true for active-high, false for inactive-low.
     */
    void setValue(bool value);

private:
    const char* chipname;
    gpiod_chip *chip;
    gpiod_line_request* request;
};

#endif // digitalSwitch_HPP
