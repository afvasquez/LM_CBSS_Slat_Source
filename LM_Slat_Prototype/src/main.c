/*
 * LM_Slat_Prototype.c
 *
 * Created: 6/22/2015 1:30:22 PM
 *  Author: avasquez
 */ 
#include "main.h"

// Include the library necessary to take advantage of SERCOM
#include "bastian_sercom.h"

#define SW2_BUTTON	PIN_PA07
#define LED_DEBUG	PIN_PA24

//////////////////////////////////////////////////////////////////////////
// Function Prototypes
void board_led_setup(void);			// LED Setup Function
static void tcc_callback_function( struct tcc_module *const module_instance );	// TCC Callback Function
static void tcc_configure_function(void);		// TCC Configuration Function
static void tcc_callback_configuration(void);	// TCC Callback Function

//////////////////////////////////////////////////////////////////////////
//	Global Module Declaration
struct tcc_module tcc_instance;

volatile uint8_t system_mode = SYSTEM_MODE_START;
volatile uint8_t slave_tx_buffer[SYSTEM_SLAVE_TX_BUFFER_SIZE] = { 0xBA , 0xBB };
volatile uint8_t slave_empty_response_buffer[SYSTEM_SLAVE_TX_BUFFER_SIZE] = { 0x00 , 0x00 };
volatile uint8_t slave_rx_buffer[SYSTEM_SLAVE_RX_BUFFER_SIZE] = { 0 };
volatile bool isInTransaction = false;
volatile bool isListening = true;

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	//SystemInit();
	
	// Set the registers for input and output
	board_led_setup();
	
	system_init();
	
	port_pin_set_output_level(LED_DEBUG, false);
	
	while ( !system_clock_source_is_ready(SYSTEM_CLOCK_SOURCE_DPLL) ) {
	}
	

	/* Initialize the SAM system */
	
	// TCC Configuration
	tcc_configure_function();		// Counter Configuration
	tcc_callback_configuration();	// Timer Callback Configuration
	
	// Run SERCOM Setup
	bastian_complete_sercom_setup();	

	system_interrupt_enable_global();	// Enable all sources of interrupt
	//spi_transceive_buffer_job(&spi_slave, slave_empty_response_buffer, slave_rx_buffer, SYSTEM_SLAVE_RX_BYTES_TO_RECEIVE);
	// Send IrDA data only once
	//
	//usart_read_buffer_job(&irda_master, slave_rx_buffer, 1);	// Read only one character
	
    while (1) {
		//usart_read_buffer_job(&irda_master, slave_rx_buffer, 1);	// Read only one character	
		
    }
}

//////////////////////////////////////////////////////////////////////////
//	TCC Callback Function
//		-> This function only toggles the LED when TCC is triggered
static void tcc_callback_function( struct tcc_module *const module_instance ) {
	usart_write_buffer_job(&irda_master, slave_tx_buffer, 1);	// Send only one character
	port_pin_toggle_output_level(LED_DEBUG);	// Toggle LED
}
//
//	TCC Configuration Function
static void tcc_configure_function(void){
	struct tcc_config config_tcc;	// Configuration structure
	
	tcc_get_config_defaults(&config_tcc, TCC0);	// Initialize with known values
	
		// Custom Counter Configuration
	config_tcc.counter.clock_source = GCLK_GENERATOR_0;
	config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV64;
	config_tcc.counter.period = 750000UL;
	
	tcc_init(&tcc_instance, TCC0, &config_tcc);	// Commit Counter Configuration
	tcc_enable(&tcc_instance);	// Enable this counter instance
}
//
//	TCC Callback Configuration
static void tcc_callback_configuration(void){
		// Register the address to the function that is to be used when counter overflows
	tcc_register_callback(&tcc_instance, tcc_callback_function, TCC_CALLBACK_OVERFLOW);
	
		// Enable this callback entry
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_OVERFLOW);
}

//////////////////////////////////////////////////////////////////////////
//	Board peripheral function
void board_led_setup(void) {
	struct port_config sw_input;
	port_get_config_defaults(&sw_input);
	
	struct port_config led_out;
	port_get_config_defaults(&led_out);
	
	sw_input.direction = PORT_PIN_DIR_INPUT;
	sw_input.input_pull = PORT_PIN_PULL_DOWN;
	port_pin_set_config(SW2_BUTTON, &sw_input);
	
	led_out.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(LED_DEBUG, &led_out);
}
