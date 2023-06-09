/*
 * kitchen_timer.c
 *
 *  Created on: April 19, 2023
 *      Authors: Isak Keyes
 *               Ian Lotus
 */

#include "kitchen_timer.h"

/******************************************************************************
 * Make sure you examine the functions that are made available to you in
 * the provided_code directory.  There are already functions provided that
 * configure timers for 1 second and 2mS.  The ISRs for these timers are
 * also provided.
 *
 * You should also make use of the functions you completed in display.c and
 * cap_sense.c
 *
 * You can add as many helper functions are you like to this file.
 *
 * DO NOT try to code all of this at once.  Break this into smaller steps.
 *
 *      -> Write  a small amount of code to accomplish a simple requirement.
 *      -> Verify your new code works.
 *      -> Verify that you did not break any of your earlier code.
 *      -> Continue to the next requirement.
 *
 * Use the debugger to verify your code!
 *
 * Suggested Development Strategy
 *
 * 1. Detect when the user presses one of the Cap Sense Buttons
 * 2. Determine which button has been pressed
 * 3. Print out a number to a single seven segment digit
 * 4. Print out a 4-digit number to the display (see video on POV)
 * 5. Blink the 4-digit number on/off at a rate of 1 second
 * 6. Modify the 4-digit number displayed using the Cap Sense Buttons
 * 6. Count down to 00:00
 * 7. Toggle the eyes/buzzer
 * 8. Complete remaining requirements.
 *****************************************************************************/

extern uint8_t set_time_min = 0;
extern uint8_t set_time_hour = 0;
extern uint8_t displayDig = 0x00;


/*****************************************************
 * Allows the user to set the duration of the timer
 *****************************************************/
void kitchen_timer_mode_init(void)
{
    // H (key 1) - modify hours (0-99)
    // M (key 0) - modify minutes (0-59)
    // ^ (key 3) - increment by 1 (loop 59/99 -> 0)
    // v (key 2) - decrement by 1 (loop 0 -> 59/99)
    // if H+M start countdown

    bool hours_sel = false;
    uint8_t capStatus = 0; // stores the values input by the buttons
    bool display_status = true;

    while (1) {

        capStatus = cap_sense_get_buttons();

        if ((capStatus & 0x02) == 0x02) {
            hours_sel = true;
        } else if ((capStatus & 0x01) == 0x01) {
            hours_sel = false;
        }

        if (ALERT_BUTTON_PRESSED) {

            if ((capStatus & 0x03) == 0x03) {
                ALERT_BUTTON_PRESSED = false;
                kitchen_timer_mode_count_down();
            } else if (((capStatus & 0x08) == 0x08) && hours_sel) {
                if (set_time_hour == 99) {
                    set_time_hour = 0;
                } else {
                    set_time_hour++;
                }
            } else if (((capStatus & 0x08) == 0x08) && !hours_sel) {
                if (set_time_min == 59) {
                    set_time_min = 0;
                } else {
                    set_time_min++;
                }
            } else if (((capStatus & 0x04) == 0x04) && hours_sel) {
                if (set_time_hour == 0) {
                    set_time_hour = 99;
                } else {
                    set_time_hour--;
                }
            } else if (((capStatus & 0x04) == 0x04) && !hours_sel) {
                if (set_time_min == 0) {
                    set_time_min = 59;
                } else {
                    set_time_min--;
                }
            }
            ALERT_BUTTON_PRESSED = false;
        }

        // every 1 second, toggle the state of the display between on/off
        if (ALERT_1_SECOND) {
            display_status = !display_status;
            ALERT_1_SECOND = false;
        }

        if (ALERT_2_MILLISECOND) {
            if (display_status) {
                display_4_digit(set_time_hour, set_time_min, false);
            } else {
                display_all_dig_off();
            }
            ALERT_2_MILLISECOND = false;
        }
    }
}

/*****************************************************
 * Starts the timer
 *****************************************************/
void kitchen_timer_mode_count_down(void)
{
    printf("In Countdown \x0A");
    int time_sec = set_time_min * 60 + set_time_hour * 3600;

    uint8_t capStatus = 0;

    // count down to zero
    // at 00:00 toggle eyes and buzzer every 1s
    // if H+M put back into initialization mode
    while (1) {
        capStatus = cap_sense_get_buttons();

        if ( (ALERT_BUTTON_PRESSED && ((capStatus & 0x03) == 0x03)) ) {
            ALERT_BUTTON_PRESSED = false;
            kitchen_timer_mode_init();
        }

        if (time_sec == 0) {
            toggle_eyes_buzzer();
        }
        if (ALERT_2_MILLISECOND) {
            if (time_sec < 60) {
                display_4_digit(0, time_sec, false);
            } else {
                uint8_t currHour = (time_sec - (time_sec % 3600)) / 3600;
                uint8_t currMin = ((time_sec % 3600) - (time_sec % 60)) / 60;
                display_4_digit(currHour, currMin, false);
            }
            ALERT_2_MILLISECOND = false;
        }
        if (ALERT_1_SECOND) {
            time_sec--;
            ALERT_1_SECOND = false;
        }
    }
}

/*****************************************************
 * Prints 4-digit number of time in seconds to display
 *****************************************************/
void display_4_digit(uint8_t time_hour, uint8_t time_min, bool done) {
    printf("In Display Digit \x0A");

    uint8_t time_hour_0 = 0;
    uint8_t time_hour_1 = 0;

    uint8_t time_min_0 = 0;
    uint8_t time_min_1 = 0;

    if (!done) {
        time_hour_0 = time_hour % 10;
        time_hour_1 = time_hour / 10;

        if ((time_min % 60) != 0) {
            time_min_0 = time_min % 10;
            time_min_1 = time_min / 10;
        }
    } else {
        time_hour_0 = 10;
        time_hour_1 = 10;
        time_min_0 = 10;
        time_min_1 = 10;
    }

    uint8_t capStatus = 0;

    switch (displayDig) {
        case 0:
            display_digit(0, time_min_0);
            displayDig = 0x01;
            break;
        case 1:
            display_digit(1, time_min_1);
            displayDig = 0x02;
            break;
        case 2:
            display_digit(2, time_hour_0);
            displayDig = 0x03;
            break;
        case 3:
            display_digit(3, time_hour_1);
            displayDig = 0x00;
            break;
    }

}

/*****************************************************
 * Toggles the eyes and the buzzer every one second
 *****************************************************/
void toggle_eyes_buzzer(void) {
    
    bool eye_state = false;
    bool buzzer_state = false;

    uint8_t capStatus = 0;

    while (1) {
        
        // check if H+M is pressed and go to initialization if so
        capStatus = cap_sense_get_buttons();
        if (ALERT_BUTTON_PRESSED && ((capStatus & 0x03) == 0x03)) {
            display_eye_left(false);
            display_eye_right(false);
            buzzer_off();
            ALERT_BUTTON_PRESSED = false;
            break;
        }

        // when 1 second is reached, toggle eyes & buzzer
        if (ALERT_1_SECOND) {
            display_eye_left(eye_state);
            display_eye_right(eye_state);
            if (buzzer_state) {
                buzzer_on();
            } else {
                buzzer_off();
            }

            eye_state = !eye_state;
            buzzer_state = !buzzer_state;
            
            ALERT_1_SECOND = false;
        }

        if (ALERT_2_MILLISECOND) {
            display_4_digit(1, 1, true);
            ALERT_2_MILLISECOND = false;
        }
    }

    // go to initialization
    kitchen_timer_mode_init();
}

