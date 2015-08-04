/*
 * main.h
 *
 * Created: 7/13/2015 2:53:10 PM
 *  Author: avasquez
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <asf.h>

#define SYSTEM_MODE_START	( ( uint8_t ) 100 )
#define SYSTEM_MODE_IDLE	( ( uint8_t ) 0 )
	// Slave Modes
#define SYSTEM_MODE_DISCOVERY_RESPONSE	( ( uint8_t ) 1 )
#define SYSTEM_MODE_DO_JOB				( ( uint8_t ) 2 )
#define SYSTEM_MODE_TX_JOB_CONFIRMATION	( ( uint8_t ) 3 )
#define SYSTEM_MODE_WAIT_FOR_ACK_REQ	( ( uint8_t ) 4 )
#define SYSTEM_MODE_INT_PROCESS_START	( ( uint8_t ) 10 )

#define SYSTEM_MODE_IS_DISCOVERED		( ( uint8_t ) 11 )
#define SYSTEM_MODE_JOB_DONE			( ( uint8_t ) 22 )

#define SYSTEM_SLAVE_TX_SINGLE_BYTE	1
#define SYSTEM_SLAVE_RX_BYTES_TO_RECEIVE	1

#define SYSTEM_SLAVE_TX_BUFFER_SIZE		2
#define SYSTEM_SLAVE_RX_BUFFER_SIZE		2
#define SYSTEM_SLAVE_TX_DISCOVERY	0
#define SYSTEM_SLAVE_TX_JOB_DONE	1

#define COM_RX_DISCOVERY	( ( uint8_t ) 0xAA )
#define COM_RX_JOB_REQUEST	( ( uint8_t ) 0xAB )
#define COM_RX_JOB_CONFIRM	( ( uint8_t ) 0xAC )

extern volatile uint8_t system_mode;
extern volatile uint8_t slave_rx_buffer[SYSTEM_SLAVE_RX_BUFFER_SIZE];
extern volatile uint8_t slave_tx_buffer[SYSTEM_SLAVE_TX_BUFFER_SIZE];
extern volatile uint8_t slave_empty_response_buffer[SYSTEM_SLAVE_TX_BUFFER_SIZE];

extern volatile bool isInTransaction;
extern volatile bool isListening;

#endif /* MAIN_H_ */