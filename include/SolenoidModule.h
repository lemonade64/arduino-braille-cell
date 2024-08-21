
#ifndef SOLENOID_MODULE_H
#define SOLENOID_MODULE_H

#include <Arduino.h>
#include <Adafruit_MCP23X17.h>
#include <Wire.h>
#include <string>

class SolenoidModule {
public:
    /**
     * @brief Initialises the Braille display hardware.
     *
     * Sets up the MCP23017 I2C port expander and configures
     * the control pins for the Braille cell.
     */
    static void setup();

    /**
     * @brief Displays the given text in Braille.
     *
     * Converts each character of the input text to its Braille 
     * representation and activates the corresponding solenoids.
     * Each character is displayed for 1 second.
     *
     * @param text The string to be displayed in Braille.
     */
    static void displayBraille(const std::string& text);

private:
    /** @brief Braille patterns for the alphabet. */
    static const int braille[26][6];

    /** @brief Control pin numbers for the Braille cell. */
    static const int controlPins[6];

    /** @brief The alphabet used for Braille conversion. */
    static const char alphabet[];

    /**
     * @brief Sets up the MCP23017 I2C port expander.
     *
     * Initialises I2C communication and configures the MCP23017.
     */
    static void setupMCP23017();

    /**
     * @brief Configures the Braille cell.
     *
     * Sets up the control pins on the MCP23017 as outputs.
     */
    static void setupBraille();
};

#endif
