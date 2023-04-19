/*
 * hw_timers.c
 *
 *  Created on: Jun 22, 2021
 *      Author: Joe Krachey
 */

#include "hw_timers.h"


volatile bool ALERT_1_SECOND = false;
volatile bool ALERT_2_MILLISECOND = false;

/*****************************************************
 * Configures Timer32_1 to generate a periodic interrupt
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void hw_timer_init_1S_irq(void)
{
    // Stop the timer
    TIMER32_1->CONTROL = 0;

    // Set the load register
    TIMER32_1->LOAD = TICKS_SECOND_1;

    // Enable the Timer32 interrupt in NVIC
    NVIC_EnableIRQ(T32_INT1_IRQn);
    NVIC_SetPriority(T32_INT1_IRQn, 1);

    // Start Timer32 and enable interrupt
    TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE |   // turn timer on
                         TIMER32_CONTROL_MODE |     // periodic mode
                         TIMER32_CONTROL_SIZE |     // 32 bit timer
                         TIMER32_CONTROL_IE;        // enable interrupts
}

/*****************************************************
 * Configures Timer32_2 to generate a periodic interrupt
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void hw_timer_init_2ms_irq(void)
{
    // Stop the timer
    TIMER32_2->CONTROL = 0;

    // Set the load register
    TIMER32_2->LOAD = TICKS_MILLISECOND_2;

    // Enable the Timer32 interrupt in NVIC
    NVIC_EnableIRQ(T32_INT2_IRQn);
    NVIC_SetPriority(T32_INT2_IRQn, 1);

    // Start Timer32 and enable interrupt
    TIMER32_2->CONTROL = TIMER32_CONTROL_ENABLE |   // turn timer on
                         TIMER32_CONTROL_MODE |     // periodic mode
                         TIMER32_CONTROL_SIZE |     // 32 bit timer
                         TIMER32_CONTROL_IE;        // enable interrupts
}



/*****************************************************
 * ISR used to time 1 second.
 *****************************************************/
void T32_INT1_IRQHandler()
{

    ALERT_1_SECOND = true;
    // clear the interrupt
    TIMER32_1->INTCLR = BIT0;

}

/*****************************************************
 * ISR used to time 2 milliseconds.
 *****************************************************/
void T32_INT2_IRQHandler()
{

    ALERT_2_MILLISECOND = true;
    // clear the interrupt
    TIMER32_2->INTCLR = BIT0;

}





