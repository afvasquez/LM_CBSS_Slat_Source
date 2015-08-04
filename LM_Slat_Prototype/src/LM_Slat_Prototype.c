/*
 * LM_Slat_Prototype.c
 *
 * Created: 6/22/2015 1:30:22 PM
 *  Author: avasquez
 */ 

#include "sam.h"

#define SW2_BUTTON	PIN_PA07
#define LED_DEBUG	PIN_PA24

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
    /* Initialize the SAM system */
    SystemInit();

	struct port_config sw_input;
	port_get_config_defaults(&sw_input);
	
	struct port_config led_out;
	port_get_config_defaults(&led_out);
	
	sw_input.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(SW2_BUTTON, &sw_input);
	
	led_out.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_DEBUG, &led_out);
	
    while (1) 
    {
		port_pin_set_output_level(LED_DEBUG, true);
    }
}
