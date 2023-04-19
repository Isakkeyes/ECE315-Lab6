/*
 * display.c
 *
 *  Created on: Jun 22, 2021
 *      Author: <Your Name>
 */

#include "display.h"

uint8_t SEVEN_SEG_LUT[] =
{
   0x00,  // 0   -- ADD VALUE
   0x00,  // 1   -- ADD VALUE
   0x00,  // 2   -- ADD VALUE
   0x00,  // 3   -- ADD VALUE
   0x00,  // 4   -- ADD VALUE
   0x00,  // 5   -- ADD VALUE
   0x00,  // 6   -- ADD VALUE
   0x00,  // 7   -- ADD VALUE
   0x00,  // 8   -- ADD VALUE
   0x00,  // 9   -- ADD VALUE
};

/******************************************************************************
 *
 *****************************************************************************/
void display_init(void)
{
    // Configure LEFT and RIGHT LEDs as outputs
    LED_LEFT_PORT->DIR |= LED_LEFT_PIN;
    LED_RIGHT_PORT->DIR |= LED_RIGHT_PIN;

    // turn the LEFT and RIGHT LEDs off.
    LED_LEFT_PORT->OUT &= ~LED_LEFT_PIN;
    LED_RIGHT_PORT->OUT &= ~LED_RIGHT_PIN;

    // Configure the IO pins that control the digits
    DIG_3_PORT->DIR |= DIG_3_PIN;
    DIG_2_PORT->DIR |= DIG_2_PIN;
    DIG_1_PORT->DIR |= DIG_1_PIN;
    DIG_0_PORT->DIR |= DIG_0_PIN;

    // turn the digits off
    DIG_3_PORT->OUT |= DIG_3_PIN;
    DIG_2_PORT->OUT |= DIG_2_PIN;
    DIG_1_PORT->OUT |= DIG_1_PIN;
    DIG_0_PORT->OUT |= DIG_0_PIN;

    // Initialize the segments
    SEG_A_PORT->DIR |= SEG_A_PIN;
    SEG_B_PORT->DIR |= SEG_B_PIN;
    SEG_C_PORT->DIR |= SEG_C_PIN;
    SEG_D_PORT->DIR |= SEG_D_PIN;
    SEG_E_PORT->DIR |= SEG_E_PIN;
    SEG_F_PORT->DIR |= SEG_F_PIN;
    SEG_G_PORT->DIR |= SEG_G_PIN;
    SEG_DP_PORT->DIR |= SEG_DP_PIN;

    SEG_A_PORT->OUT &= ~SEG_A_PIN;
    SEG_B_PORT->OUT &= ~SEG_B_PIN;
    SEG_C_PORT->OUT &= ~SEG_C_PIN;
    SEG_D_PORT->OUT &= ~SEG_D_PIN;
    SEG_E_PORT->OUT &= ~SEG_E_PIN;
    SEG_F_PORT->OUT &= ~SEG_F_PIN;
    SEG_G_PORT->OUT &= ~SEG_G_PIN;
    SEG_DP_PORT->OUT &= ~SEG_DP_PIN;
}

/******************************************************************************
 * This function is used to disable all 4 seven segment digits by turning off
 * the MOSFET that is connected to the Anode of each digit.
 *****************************************************************************/
void display_all_dig_off(void)
{
    // turn the digits off
    DIG_3_PORT->OUT |= DIG_3_PIN;
    DIG_2_PORT->OUT |= DIG_2_PIN;
    DIG_1_PORT->OUT |= DIG_1_PIN;
    DIG_0_PORT->OUT |= DIG_0_PIN;
}

/******************************************************************************
 * If "on" is true, turn on the LED used to control the left eye (D301)
 * If "on" is false, turn off the LED used to control the left eye (D301)
 *****************************************************************************/
void display_eye_left(bool on)
{
    if (on) {
        // turn on LED
        LED_LEFT_PORT->OUT |= LED_LEFT_PIN;
    } else {
        // turn off LED
        LED_LEFT_PORT->OUT &= ~LED_LEFT_PIN;
    }
}

/******************************************************************************
 * If "on" is true, turn on the LED used to control the right eye (D300)
 * If "on" is false, turn off the LED used to control the right eye (D300)
 *****************************************************************************/
void display_eye_right(bool on)
{
    if (on) {
        // turn on LED
        LED_RIGHT_PORT->OUT |= LED_RIGHT_PIN;
    } else {
        // turn off LED
        LED_RIGHT_PORT->OUT &= ~LED_RIGHT_PIN;
    }
}

/******************************************************************************
 * Used to output the a number in the range of 0-9 on the specified seven
 * segment LED.
 *
 * DO NOT determine how long the specified digit will be turned
 * on in this function.  Just turn on the required segments, enable the
 * requested digit, and return.
 *
 * The code you write in kitchen_timer.c will determine when and how
 * long an individual digit will be turned on for.
 *
 * Parameter:
 *  location        Used to identify which of the 7-segment LEDs are enabled.
 *                  0 - Rightmost digit
 *                  1 - 2nd to the right
 *                  2 - 3rd to the right
 *                  3 - 4th to the right
 *
 *  number          The value to be displayed
 *****************************************************************************/
void display_digit(uint8_t location, uint8_t number)
{
    // ADD CODE - fix the segments thing

    // turn on the required segments
    SEG_DP_PORT->OUT |= SEG_DP_PIN;

    switch(number) {
        case 0:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_E_PORT->OUT |= SEG_E_PIN;
            SEG_F_PORT->OUT |= SEG_F_PIN;
            break;
        case 1:
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            break;
        case 2:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_E_PORT->OUT |= SEG_E_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;
        case 3:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;
        case 4:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_F_PORT->OUT |= SEG_F_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;
        case 5:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_F_PORT->OUT |= SEG_F_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;
        case 6:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_E_PORT->OUT |= SEG_E_PIN;
            SEG_F_PORT->OUT |= SEG_F_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;
        case 7:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            break;
        case 8:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_E_PORT->OUT |= SEG_E_PIN;
            SEG_F_PORT->OUT |= SEG_F_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;
        case 9:
            SEG_A_PORT->OUT |= SEG_A_PIN;
            SEG_B_PORT->OUT |= SEG_B_PIN;
            SEG_C_PORT->OUT |= SEG_C_PIN;
            SEG_D_PORT->OUT |= SEG_D_PIN;
            SEG_F_PORT->OUT |= SEG_F_PIN;
            SEG_G_PORT->OUT |= SEG_G_PIN;
            break;

    }

    // enable the requested digit
    switch (location) {
        case 0:
            DIG_0_PORT->OUT &= ~DIG_0_PIN;
            break;
        case 1:
            DIG_1_PORT->OUT |= DIG_1_PIN;
            break;
        case 2:
            DIG_2_PORT->OUT |= DIG_2_PIN;
            break;
        case 3:
            DIG_3_PORT->OUT |= DIG_3_PIN;
            break;
    }

}




