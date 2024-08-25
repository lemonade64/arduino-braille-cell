#include "SolenoidModule.h"
#include "HapticModule.h"

Adafruit_MCP23X17 mcp;

const int SolenoidModule::braille[26][6] = {
    {1,0,0,0,0,0},
    {1,1,0,0,0,0},
    {1,0,0,1,0,0},
    {1,0,0,1,1,0},
    {1,0,0,0,1,0},
    {1,1,0,1,0,0},
    {1,1,0,1,1,0},
    {1,1,0,0,1,0},
    {0,1,0,1,0,0},
    {0,1,0,1,1,0},
    {1,0,1,0,0,0},
    {1,1,1,0,0,0},
    {1,0,1,1,0,0},
    {1,0,1,1,1,0},
    {1,0,1,0,1,0},
    {1,1,1,1,0,0},
    {1,1,1,1,1,0},
    {1,1,1,0,1,0},
    {0,1,1,1,0,0},
    {0,1,1,1,1,0},
    {1,0,1,0,0,1},
    {1,1,1,0,0,1},
    {0,1,0,1,1,1},
    {1,0,1,1,0,1},
    {1,0,1,1,1,1},
    {1,0,1,0,1,1},
};

const int SolenoidModule::controlPins[6] = {1, 2, 3, 4, 5, 6};

const char SolenoidModule::alphabet[] = "abcdefghijklmnopqrstuvwxyz";

void SolenoidModule::setup() {
    HapticModule::playEffect(HapticEffect::SOLENOID_ON);
    setupMCP23017();
    setupBraille();
}

void SolenoidModule::setupMCP23017() {
    Wire.begin(15, 14);
    if (!mcp.begin_I2C()) {
        log_e("MCP23017 Error");
        while (1);
    }
    for (int i = 1; i < 6; i++) {
        mcp.pinMode(i, OUTPUT);
    }
}

void SolenoidModule::setupBraille() {
    for (int i = 0; i < 6; i++) {
        mcp.pinMode(controlPins[i], OUTPUT);
    }
}

void SolenoidModule::displayBraille(const std::string& text) {
    int length = text.length();
    char letter;
    int index;

    for (int i = 0; i < length; i++) {
        letter = text[i];
        for (int j = 0; j < 26; j++) {
            if (letter == alphabet[j]) {
                index = j;
                break;
            }
        }

        for (int k = 0; k <= 5; k++) {
            mcp.digitalWrite(controlPins[k], braille[index][k]);
        }

        delay(1000);
    }
    HapticModule::playEffect(HapticEffect::SOLENOID_OFF);
}