//////////////////////////////////////////////////////////////////////////
//			SAM D - Cortex M0+ SERCOM Source Code
//	Author: Andres Vasquez
//	Purpose: THis code is in charge of the necessary transactions that
//				are to take place between any main code and the code 
//				necessary to send data through the SERCOM peripherals
//////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bastian_sercom.h"

#define LED_DEBUG	PIN_PA24

void bastian_SPI_configuration (void);
void bastian_IrDA_configuration (void);

static void spi_slave_callback_transmitted(const struct spi_module *const module);
static void spi_slave_callback_received(const struct spi_module *const module);
static void spi_slave_callback_transceived(const struct spi_module *const module);

static void irda_master_callback_received(const struct usart_module *const module);
static void irda_master_callback_transmitted(const struct usart_module *const module);

////////////////////  BASTIAN SERCOM  ////////////////////////////////////
//		MODULE: Slave Module -> spi_slave
//		module handler for the SPI interaction with GREEN
struct spi_module spi_slave;
//		MODULE: IrDA Module -> irda_master
//		module handler for the IR interaction with RED-SLAT
struct usart_module irda_master;

////////////////////  BASTIAN SERCOM  ////////////////////////////////////
//		Perform complete SERCOM module setup for the application
//		Takes no arguments
void bastian_complete_sercom_setup(void) {
	// Configure the SPI
	bastian_SPI_configuration();
	
	// Configure the IrDA
	bastian_IrDA_configuration();
}

//////////////////////////////////////////////////////////////////////////
// SPI Port Configuration
void bastian_SPI_configuration (void) {
	//////////////////////////////////////////////////////////////////////////
	// "SHIELD" communication module Setup for Red
	// Declare our configuration parameters
	struct spi_config spi_conf;

	// Initialize them to default values
	spi_get_config_defaults(&spi_conf);
	
	spi_conf.mode = SPI_MODE_SLAVE;
	spi_conf.mode_specific.slave.preload_enable = true;
	//spi_conf.
	spi_conf.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
	spi_conf.mux_setting = SPI_SIGNAL_MUX_SETTING_I;
	// Pad Configuration
	spi_conf.pinmux_pad0 = PINMUX_PA14D_SERCOM2_PAD0;
	spi_conf.pinmux_pad1 = PINMUX_PA15D_SERCOM2_PAD1;
	spi_conf.pinmux_pad2 = PINMUX_PA16D_SERCOM2_PAD2;
	spi_conf.pinmux_pad3 = PINMUX_PA25D_SERCOM2_PAD3;
	

	// Initialize the previous settings
	spi_init(&spi_slave, SERCOM2, &spi_conf);

	// Enable the module
	spi_enable(&spi_slave);

	// ******** Callback setup
	spi_register_callback(&spi_slave, spi_slave_callback_received, SPI_CALLBACK_BUFFER_RECEIVED);
	spi_enable_callback(&spi_slave, SPI_CALLBACK_BUFFER_RECEIVED);

	spi_register_callback(&spi_slave, spi_slave_callback_transmitted, SPI_CALLBACK_BUFFER_TRANSMITTED);
	spi_enable_callback(&spi_slave, SPI_CALLBACK_BUFFER_TRANSMITTED);
	
	spi_register_callback(&spi_slave, spi_slave_callback_transceived, SPI_CALLBACK_BUFFER_TRANSCEIVED);
	spi_enable_callback(&spi_slave, SPI_CALLBACK_BUFFER_TRANSCEIVED);
}

//////////////////////////////////////////////////////////////////////////
// IrDA Port COnfiguration
void bastian_IrDA_configuration (void){
	// USART Configuration Structure
	struct usart_config irda_conf;
	
	// Get defaults for this protocol
	usart_get_config_defaults(&irda_conf);
	
	// Port Configuration
	irda_conf.transfer_mode = USART_TRANSFER_ASYNCHRONOUSLY;	// Asynchronous Communication Mode
	irda_conf.generator_source = GCLK_GENERATOR_0;				// Use the Generic Clock 0 as source
	irda_conf.baudrate = 115200;								// IrDA Baudrate
	irda_conf.character_size = USART_CHARACTER_SIZE_8BIT;
	irda_conf.stopbits = USART_STOPBITS_1;
	irda_conf.parity = USART_PARITY_EVEN;
	irda_conf.encoding_format_enable = true;	// Enable IrDA Encoding 
	
	// Pin Multiplexer Settings
	irda_conf.mux_setting = USART_RX_1_TX_0_XCK_1;
	irda_conf.pinmux_pad0 = PINMUX_PA22C_SERCOM1_PAD0;
	irda_conf.pinmux_pad1 = PINMUX_PA23C_SERCOM1_PAD1;
	irda_conf.pinmux_pad2 = PINMUX_UNUSED;
	irda_conf.pinmux_pad3 = PINMUX_UNUSED;

	// Initialize the previous settings
	usart_init(&irda_master, SERCOM1, &irda_conf);

	// Enable the module
	usart_enable(&irda_master);

	// ******** Callback setup
	usart_register_callback(&irda_master, irda_master_callback_received, SPI_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&irda_master, SPI_CALLBACK_BUFFER_RECEIVED);

	usart_register_callback(&irda_master, irda_master_callback_transmitted, SPI_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&irda_master, SPI_CALLBACK_BUFFER_TRANSMITTED);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////// SPI CALLBACK FUNCTIONS ////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// SPI RX Callback Function
static void spi_slave_callback_received(const struct spi_module *const module) {
	
}
// SPI RX Callback Function
static void spi_slave_callback_transmitted(const struct spi_module *const module) {
	
}

// SPI RX Callback Function
static void spi_slave_callback_transceived(const struct spi_module *const module) {
	
	
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////// IrDA CALLBACK FUNCTIONS ////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// IrDA Rx Callback Function
static void irda_master_callback_received(const struct usart_module *const module) {
// 	if ( slave_rx_buffer[0] == 0xBA ) {
// 		port_pin_toggle_output_level(LED_DEBUG);	// Toggle LED
// 	}
}
// IrDA Tx Callback Function
static void irda_master_callback_transmitted(const struct usart_module *const module) {
	
}