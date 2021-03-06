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

/*
	- DESCRIPTOR DEFINITIONS -
*/

/* String descriptors used during the enumeration process.
These take the form:

{
	Length of descriptor,
	Descriptor type,
	Data
}
*/

const portCHAR pxLanguageStringDescriptor[] = {
  4,
  usbDESCRIPTOR_TYPE_STRING,
  0x09, 0x04
};

const portCHAR pxManufacturerStringDescriptor[] = {
  28,
  usbDESCRIPTOR_TYPE_STRING,

  'b', 0x00, 'i', 0x00, 't', 0x00, 'm', 0x00,
  'a', 0x00, 'n', 0x00, 'u', 0x00, 'f', 0x00,
  'a', 0x00, 'k', 0x00, 't', 0x00, 'u', 0x00,
  'r', 0x00
};

const portCHAR pxProductStringDescriptor[] = {
  44,
  usbDESCRIPTOR_TYPE_STRING,
  
  'O', 0x00, 'p', 0x00, 'e', 0x00, 'n', 0x00,
  'B', 0x00, 'e', 0x00, 'a', 0x00, 'c', 0x00,
  'o', 0x00, 'n', 0x00, ' ', 0x00, 'U', 0x00,
  'S', 0x00, 'B', 0x00, ' ', 0x00, '2', 0x00,
  '.', 0x00, '4', 0x00, 'G', 0x00, 'H', 0x00,
  'z', 0x00
};

/* Device should properly be 0x134A:0x9001, using 0x05F9:0xFFFF for Linux testing */
const char pxDeviceDescriptor[] = {
  /* Device descriptor */
  0x12, // Size of this descriptor, 0x12
  1, // DEVICE Descriptor Type, 0x01
  0x10, 0x01, // USB 2.0 specification, 0x10, 0x01
  0x02, // USB Communication class code, 0x02
  0x00, // No device subclass code
  0x00, // No device protocol code
  0x08, // Maximum packet size for endpoint zero, 0x08
  0xC0, 0x16, // ATMEL Vendor ID, 0xC0, 0x16
  0x10, 0x01, // Product ID (6119), 0x10, 0x01
  0x00, 0x01, // Device release number 0.01
  usbMANUFACTURER_STRING, // Index of manufacturer description
  usbPRODUCT_STRING, // Index of product description
  0x00, // Index of serial number description
  0x01 // One possible configuration
};

const char pxConfigDescriptor[] = {

  /* Configuration 1 descriptor
     Here we define two interfaces (0 and 1) and a total of 3 endpoints.
     Interface 0 is a CDC Abstract Control Model interface with one interrupt-in endpoint.
     Interface 1 is a CDC Data Interface class, with a bulk-in and bulk-out endpoint.
     Endpoint 0 gets used as the CDC management element.
   */
  0x09,				/* CbLength                                                             */
  0x02,				/* CbDescriptorType                                             */
  0x43, 0x00,			/* CwTotalLength 2 EP + Control         ?       */
  0x02,				/* CbNumInterfaces                                              */
  0x01,				/* CbConfigurationValue                                 */
  0x00,				/* CiConfiguration                                      */
  usbBUS_POWERED,		/* CbmAttributes Bus powered + Remote Wakeup */
  0x32,				/* CMaxPower: 100mA                                             */

  /* Communication Class Interface Descriptor Requirement         */
  0x09,				/* bLength                                                              */
  0x04,				/* bDescriptorType                                              */
  0x00,				/* bInterfaceNumber                                             */
  0x00,				/* bAlternateSetting                                    */
  0x01,				/* bNumEndpoints                                                */
  0x02,				/* bInterfaceClass: Comm Interface Class */
  0x02,				/* bInterfaceSubclass: Abstract Control Model */
  0x01,				/* bInterfaceProtocol                                   */
  usbINTERFACE_STRING,		/* iInterface                                                       */

  /* Header Functional Descriptor                                                         */
  0x05,				/* bLength                                                              */
  0x24,				/* bDescriptor type: CS_INTERFACE               */
  0x00,				/* bDescriptor subtype: Header Func Desc */
  0x10, 0x01,			/* bcdCDC:1.1                                                   */

  /* ACM Functional Descriptor                                                            */
  0x04,				/* bFunctionLength                                              */
  0x24,				/* bDescriptor type: CS_INTERFACE               */
  0x02,				/* bDescriptor subtype: ACM Func Desc   */
  0x00,				/* bmCapabilities: We don't support squat */

  /* Union Functional Descriptor                                                          */
  0x05,				/* bFunctionLength                                              */
  0x24,				/* bDescriptor type: CS_INTERFACE               */
  0x06,				/* bDescriptor subtype: Union Func Desc */
  0x00,				/* bMasterInterface: CDC Interface              */
  0x01,				/* bSlaveInterface0: Data Class Interface */

  /* Call Management Functional Descriptor
     0 in D1 and D0 indicates that device does not handle call management */
  0x05,				/* bFunctionLength                                              */
  0x24,				/* bDescriptor type: CS_INTERFACE               */
  0x01,				/* bDescriptor subtype: Call Management Func */
  0x00,				/* bmCapabilities: D1 + D0                              */
  0x01,				/* bDataInterface: Data Class Interface 1 */

  /* CDC Control - Endpoint 3 descriptor
     This endpoint serves as a notification element.                              */

  0x07,				/* bLength                                                              */
  0x05,				/* bDescriptorType                                              */
  0x83,				/* bEndpointAddress, Endpoint 03 - IN   */
  0x03,				/* bmAttributes   INT                                   */
  0x08, 0x00,			/* wMaxPacketSize: 8 bytes                              */
  0xFF,				/* bInterval                                                    */

  /* Data Class Interface Descriptor Requirement                          */
  0x09,				/* bLength                                                              */
  0x04,				/* bDescriptorType                                              */
  0x01,				/* bInterfaceNumber                                             */
  0x00,				/* bAlternateSetting                                    */
  0x02,				/* bNumEndPoints                                                */
  0x0A,				/* bInterfaceClass                                              */
  0x00,				/* bInterfaceSubclass                                   */
  0x00,				/* bInterfaceProtocol                                   */
  0x00,				/* iInterface                                                   */

  /* CDC Data - Endpoint 1 descriptor */
  0x07,				/* bLenght                                                              */
  0x05,				/* bDescriptorType                                              */
  0x01,				/* bEndPointAddress, Endpoint 01 - OUT  */
  0x02,				/* bmAttributes BULK                                    */
  64,				/* wMaxPacketSize                                               */
  0x00,
  0x00,				/* bInterval                                                    */

  /* CDC Data - Endpoint 2 descriptor */
  0x07,				/* bLength                                                              */
  0x05,				/* bDescriptorType                                              */
  0x82,				/* bEndPointAddress, Endpoint 02 - IN   */
  0x02,				/* bmAttributes BULK                                    */
  64,				/* wMaxPacketSize                                               */
  0x00,
  0x00				/* bInterval                                                    */
};
