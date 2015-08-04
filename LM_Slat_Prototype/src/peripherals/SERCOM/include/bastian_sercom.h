/*
 * bastian_sercom.h
 *
 * Created: 7/13/2015 2:29:39 PM
 *  Author: avasquez
 */ 

#ifndef BASTIAN_SERCOM_H_
#define BASTIAN_SERCOM_H_



////////////////////  BASTIAN SERCOM  ////////////////////////////////////
//		Perform complete SERCOM module setup for the application
//		Takes no arguments
void bastian_complete_sercom_setup(void);

////////////////////  BASTIAN SERCOM  ////////////////////////////////////
//		MODULE: Slave Module -> spi_slave
//		module handler for the SPI interaction with RED
extern struct spi_module spi_slave;
//		MODULE: IrDA Module -> irda_master
//		module handler for the IR interaction with RED-SLAT
extern struct usart_module irda_master;

#endif /* BASTIAN_SERCOM_H_ */