/*
	FreeRTOS.org V4.2.1 - Copyright (C) 2003-2007 Richard Barry.

	This file is part of the FreeRTOS.org distribution.

	FreeRTOS.org is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	FreeRTOS.org is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeRTOS.org; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	A special exception to the GPL can be applied should you wish to distribute
	a combined work that includes FreeRTOS.org, without being obliged to provide
	the source code for any proprietary components.  See the licensing section
	of http://www.FreeRTOS.org for full details of how and when the exception
	can be applied.

	***************************************************************************
	See http://www.FreeRTOS.org for documentation, latest information, license
	and contact details.  Please ensure to read the configuration and relevant
	port sections of the online documentation.

	Also see http://www.SafeRTOS.com for an IEC 61508 compliant version along
	with commercial development and support options.
	***************************************************************************
*/

#ifndef USB_CDC_H
#define USB_CDC_H

#include "usb.h"
#include <usbshell.h>

#define USB_CDC_QUEUE_SIZE_TX		35
#define USB_CDC_QUEUE_SIZE_RX		35
#define USB_CDC_QUEUE_SIZE_FREE		72

#define USB_CDC_QUEUE_SIZE_PRI_TX	 4
#define USB_CDC_QUEUE_SIZE_PRI_RX	 2

#define USB_MAX_TRANSMIT_COUNT		64

#define MEMBLOCK_TYPE_NORMAL		1
#define MEMBLOCK_TYPE_DYNMEM		3
#define MEMBLOCK_TYPE_USE			5
#define MEMBLOCK_MAX_SIZE			100
#define ENCODING_PARAMETER			0x20

typedef struct {
	unsigned portCHAR type;         // wird verwendet oder ist frei
	unsigned portCHAR length;		// belegte grösse von pValue
	unsigned portCHAR pos;			// wird beim versenden verwendet
	portCHAR pValue[MEMBLOCK_MAX_SIZE];
} MemBlock;

#define USB_MONITOR_INPUT 		1 + ENCODING_PARAMETER
#define USB_TEST_DATA			2 + ENCODING_PARAMETER
#define USB_TEST_DATA_ECHO		3 + ENCODING_PARAMETER

typedef struct {
	  unsigned portCHAR  start;
	  unsigned portCHAR  length;
	  unsigned portCHAR  type;
	  unsigned portCHAR  reserved;
} USB_Chunk;

/* Structure used to take a snapshot of the USB status from within the ISR. */
typedef struct X_ISR_STATUS
{
  unsigned portLONG ulISR;
  unsigned portLONG ulCSR0;
  unsigned portCHAR ucFifoData[8];
} xISRStatus;

/* Structure used to hold the received requests. */
typedef struct
{
  unsigned portCHAR ucReqType;
  unsigned portCHAR ucRequest;
  unsigned portSHORT usValue;
  unsigned portSHORT usIndex;
  unsigned portSHORT usLength;
} xUSB_REQUEST;

typedef enum
{
  eNOTHING,
  eJUST_RESET,
  eJUST_GOT_CONFIG,
  eJUST_GOT_ADDRESS,
  eSENDING_EVEN_DESCRIPTOR,
  eREADY_TO_SEND
} eDRIVER_STATE;

/* Structure used to control the data being sent to the host. */
typedef struct
{
  unsigned portCHAR ucBuffer[usbMAX_CONTROL_MESSAGE_SIZE];
  unsigned portLONG ulNextCharIndex;
  unsigned portLONG ulTotalDataLength;
} xCONTROL_MESSAGE;

/*-----------------------------------------------------------*/
void vUSBCDCTask (void *pvParameters);

// queue: send and recive normal blocks
void vUSBSendPacket(MemBlock *daten, unsigned portBASE_TYPE length);
unsigned portBASE_TYPE vUSBRecivePacket(MemBlock **pq);

// queue: send and recive spezial blocks
void vUSBSendPriPacket(MemBlock *daten, unsigned portBASE_TYPE length);
unsigned portBASE_TYPE vUSBRecivePriPacket(MemBlock **pq);

MemBlock *pullFreeBlock(void);
void pushFreeBlock(MemBlock *b);

unsigned portBASE_TYPE getTXSize( void );
unsigned portBASE_TYPE getRXSize( void );
unsigned portBASE_TYPE getFreeSize( void );

#endif
