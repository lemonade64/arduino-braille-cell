#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

class ButtonModule {
public:
    /**
     * @brief Initialises the button with the correct pin.
     * @param pin Arduino pin number to which the button is connected.
     */
    static void init(int pin);

    /**
     * @brief Checks if the button is currently pressed.
     * @return true if the button is pressed, false otherwise.
     */
    static bool isPressed();

    /**
     * @brief Updates the current state of the button.
     */
    static void update();

private:
    /// Arduino pin number for the button.
    static int buttonPin;

    /// Current state of the button (HIGH or LOW).
    static int buttonState;
};

#endif
