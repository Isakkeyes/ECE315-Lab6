/*
 * display.c
 *
 *  Created on: April 19, 2023
 *      Authors: Isak Keyes
 *               Ian Lotus
 */

#include "display.h"

uint8_t SEVEN_SEG_LUT[] =
{
   0xFC,  // 0   -- 11111100
   0x60,  // 1   -- 01100000
   0xDA,  // 2   -- 11011010
   0xF2,  // 3   -- 11110010
   0x66,  // 4   -- 01100110
   0xB6,  // 5   -- 10110110
   0xBE,  // 6   -- 10111110
   0xE0,  // 7   -- 11100000
   0xFE,  // 8   -- 11111110
   0xF6,  // 9   -- 11110110
   0x02   // 10  -- 00000010 // display line when timer done ("----")
};


/******************************************************************************
 * Initialize the 4-digit 7-segment dispay
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
    // the hex value of the number to be displayed
    uint8_t seg_Vals = SEVEN_SEG_LUT[number];

    // turn on the required segments
    if ((SEG_A_PIN & seg_Vals) != 0) {
        SEG_A_PORT->OUT |= SEG_A_PIN;
    } else {
        SEG_A_PORT->OUT &= ~SEG_A_PIN;
    }
    if ((SEG_B_PIN & seg_Vals) != 0) {
        SEG_B_PORT->OUT |= SEG_B_PIN;
    } else {
        SEG_B_PORT->OUT &= ~SEG_B_PIN;
    }
    if ((SEG_C_PIN & seg_Vals) != 0) {
        SEG_C_PORT->OUT |= SEG_C_PIN;
    } else {
        SEG_C_PORT->OUT &= ~SEG_C_PIN;
    }
    if ((SEG_D_PIN & seg_Vals) != 0) {
        SEG_D_PORT->OUT |= SEG_D_PIN;
    } else {
        SEG_D_PORT->OUT &= ~SEG_D_PIN;
    }
    if ((SEG_E_PIN & seg_Vals) != 0) {
        SEG_E_PORT->OUT |= SEG_E_PIN;
    } else {
        SEG_E_PORT->OUT &= ~SEG_E_PIN;
    }
    if ((SEG_F_PIN & seg_Vals) != 0) {
        SEG_F_PORT->OUT |= SEG_F_PIN;
    } else {
        SEG_F_PORT->OUT &= ~SEG_F_PIN;
    }
    if ((SEG_G_PIN & seg_Vals) != 0) {
        SEG_G_PORT->OUT |= SEG_G_PIN;
    } else {
        SEG_G_PORT->OUT &= ~SEG_G_PIN;
    }

    // enable the requested digit
    switch (location) {
        case 0:
            DIG_0_PORT->OUT &= ~DIG_0_PIN;
            DIG_1_PORT->OUT |= DIG_1_PIN;
            DIG_2_PORT->OUT |= DIG_2_PIN;
            DIG_3_PORT->OUT |= DIG_3_PIN;
            break;
        case 1:
            DIG_1_PORT->OUT &= ~DIG_1_PIN;
            DIG_0_PORT->OUT |= DIG_0_PIN;
            DIG_2_PORT->OUT |= DIG_2_PIN;
            DIG_3_PORT->OUT |= DIG_3_PIN;
            break;
        case 2:
            DIG_2_PORT->OUT &= ~DIG_2_PIN;
            DIG_1_PORT->OUT |= DIG_1_PIN;
            DIG_0_PORT->OUT |= DIG_0_PIN;
            DIG_3_PORT->OUT |= DIG_3_PIN;
            break;
        case 3:
            DIG_3_PORT->OUT &= ~DIG_3_PIN;
            DIG_0_PORT->OUT |= DIG_0_PIN;
            DIG_1_PORT->OUT |= DIG_1_PIN;
            DIG_2_PORT->OUT |= DIG_2_PIN;
            break;
    }

}





