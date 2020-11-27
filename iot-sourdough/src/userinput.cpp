#include <Arduino.h>

#include <pushbutton.h>
#include <EasyButton.h>
#include "userinput.h"

#define BUTTON_PIN 9
#define LONG_PRESS_THRESHOLD_MS 500

int userState = STATE_DEFAULT;

EasyButton button(BUTTON_PIN, 35, true, false);

void onPressed() {
    Serial.println("Pressed");
}

void onLongPressed() {
    Serial.println("Long press");
}

void onDoublePressed() {
    Serial.println("Double press");
}

void initializeButton() {
    // button.setDebounceDelay(100);
    button.begin();
    button.onPressed(onPressed);
    button.onPressedFor(LONG_PRESS_THRESHOLD_MS, onLongPressed);
    button.onSequence(2, 500, onDoublePressed);
}

void tUserInputCallback() {
    static int buttonState = 0;
    static int prevButtonState = 0;
    static long pressTimeStart = millis();
    static long pressDuration;
    static bool stateChangeInProgress = false;

    // buttonState = button.isPressed();

    // if (prevButtonState != buttonState) {
    //     if (buttonState == HIGH) {
    //         // Start of button press
    //         Serial.println("Pressed");
    //         pressTimeStart = millis();
    //     }
    //     else {
    //         // End of button press
    //         pressDuration = millis() - pressTimeStart;
    //         Serial.print(pressDuration);
    //         Serial.println(" ms pressed");

    //         if (!stateChangeInProgress) {
    //             switch (userState) {
    //                 case STATE_CALIBRATION:
    //                     // Short button press exits calibration mode
    //                     userState = STATE_DEFAULT;
    //                     break;
    //                 case STATE_DEFAULT:
    //                     // Start monitoring
    //                     userState = STATE_MONITOR;
    //                     break;
    //                 case STATE_MONITOR:
    //                     // Stop monitoring
    //                     userState = STATE_DEFAULT;
    //                     break;
    //             }
    //         }

    //         stateChangeInProgress = false;
    //     }
    // }
    // else if (buttonState == HIGH) {
    //     // While button is being pressed
    //     pressDuration = millis() - pressTimeStart;
    //     Serial.print(pressDuration);
    //     Serial.println(" ms pressing");

    //     if (pressDuration >= LONG_PRESS_THRESHOLD_MS) {
    //         if (userState != STATE_CALIBRATION) {
    //             Serial.println("Entering calibration");
    //             userState = STATE_CALIBRATION;
    //             stateChangeInProgress = true;
    //         }
    //     }
    // }
    // prevButtonState = buttonState;
    button.read();
}

int getState() {
    return userState;
}

void setState(int state) {
    userState = state;
}
