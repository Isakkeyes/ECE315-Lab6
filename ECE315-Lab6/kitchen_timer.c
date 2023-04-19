/*
 * kitchen_timer.c
 *
 *  Created on: Jun 18, 2021
 *      Author: <Your Name>
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

extern uint8_t current_min = 0;
extern uint8_t current_hour = 0;


/*****************************************************
 * Allows the user to set the duration of the timer
 *****************************************************/
void kitchen_timer_mode_init(void)
{
    // ADD CODE
    // H (key 1) - modify hours (0-99)
    // M (key 0) - modify minutes (0-59)
    // ^ (key 3) - increment by 1 (loop 59/99 -> 0)
    // v (key 2) - decrement by 1 (loop 0 -> 59/99)
    // if H+M start countdown

    bool hours_sel = true;

    while (1) {
        uint8_t capStatus = AT42QT2120_read_key_status_lo();

        if ((capStatus & 0x02) == 0x02) {
            hours_sel = true;
        } else if ((capStatus & 0x01) == 0x01) {
            hours_sel = false;
        } else if (((capStatus & 0x08) == 0x08) && hours_sel) {
            current_hour++;
        } else if (((capStatus & 0x08) == 0x08) && !hours_sel) {
            current_min++;
        } else if (((capStatus & 0x04) == 0x04) && hours_sel) {
            current_hour--;
        } else if (((capStatus & 0x04) == 0x04) && !hours_sel) {
            current_min--;
        }

        display_4_digit(trunc(current_hour/10), current_hour%10, trunc(current_hour/10), current_min%10);

        // start the count
        if ((capStatus & 0x03) == 0x03) {
            kitchen_timer_mode_count_down();
        }
    }
}

/*****************************************************
 * Starts the timer
 *****************************************************/
void kitchen_timer_mode_count_down(void)
{
    uint8_t time_sec = current_hour * 3600 + current_min * 60;


    // ADD CODE
    // count down to zero
    // at 00:00 toggle eyes and buzzer every 1s
    // if H+M put back into initialization mode

    // Start 1sec interrupt timer
    hw_timer_init_1S_irq();

    while (1) {
        if ((capStatus & 0x03) == 0x03) {
            kitchen_timer_mode_init();
        }
        if (time_sec == 0) {

        }
        if (ALERT_1_SECOND) {
            display_4_digit(trunc(current_hour/10), trunc(time_sec/3600), trunc(current_hour/10), current_min%10);
            time_sec--;
        }
    }


}


