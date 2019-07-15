/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidPrivate.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 04 May 2019, 14:01
 */

/*
 * T H I S   I S   P R I V A T E   F U N C T I O N S   O N L Y
 * 
 * Do not call these directly, use rfid.c/h instead
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "../inc/rfid_parameters.h"
#include "../inc/rfidPrivate.h"

//Note: This contains the functions to do all the comms etc. Formatting is done
//		as part of rfid, not this

//ToDo: Need to implement a check of the response to validate success

//ToDo: Need to identify and change all the functions that return strings to use pointers instead

//ToDo:  All calls that require the GPIO pin, should have it passed in and not use the global GPIO_PIN.

//ToDo: waitForCTS should be at the prv level and not the user level.

// conn is the serial connection, **response is the array that the reply is in, *length is the size of the array
int prv_getFirmwareInfo(int conn, char **response, int *length) {
    
	int				i = 0;
	char				*firmware_response = malloc (sizeof(char));
    
    printf("Getting firmware information.\n");
	
	prv_waitForCTS(conn);
	serialPuts(conn,"z");
    delay(100);
	// get data and fill the buffer, less the last which needs to be \0
	while (serialDataAvail (conn) )
	{
		firmware_response = serialGetchar (conn) ;
		*response = (char*)realloc(*response, (i+1) * sizeof(char));
		//printf("Char Received:%i", text_result[i]);
		(*response)[i] = (char) firmware_response;

		i++;
	}
	printf("out of get data loop\n");
	//*response = (char*)realloc(firmware_response, (i+1) * sizeof(char));
	response[i] = '\0';
	printf("length:%d\n", i+1);
	*length = i+1;			// Set one higher as it is the length, not the last entry.
	
	serialFlush(conn);

    
    return 0;
}

int prv_modeSetting(int fd, int mode) {
	
	int		success = 1;
	
	
	serialPutchar(fd, mode);

	delay(100);
	while ( serialDataAvail(fd) )
	{
		char result;
		result = serialGetchar(fd);
		if (result == 0xC0)
		{
			//printf("\n\nReader Operating Tag Mode changed .......\n\n");
			success = 0;
		}
		else
		{
			//printf("\n\nUnexpected reply >%X< \n\n", result);
			success = 1;
		}
	}
	return success;
}

int prv_sendResetCommand(int fd) {
	
	serialPutchar(fd, 0x46);	// this command sequence is
	serialPutchar(fd, 0x55);	//
	serialPutchar(fd, 0xAA);	// required to force a factory reset.

	delay(100);

	// There is no way to validate receipt of the reset command, comms is ended immediately.
	return 0;
}

int prv_waitForCTS(int fd) {
	
	serialFlush(fd);	
	while (digitalRead(GPIO_PIN) == HIGH)
	{
		// Do Nothing
		// printf(".");
	}
	return 0;
}

int prv_getAntennaStatus(int *fd) {
	// Perform a firmware read to check the status of the antenna

	prv_waitForCTS(*fd);
    serialPutchar(*fd, 0x53);  // Send any command - this happens to be the one to check if a tag is present
	delay(100);

	if ((serialGetchar(*fd) & 0x20) == 0x20 )  // Checking bit 5.  If set, indicates antenna fault
	{
		printf("ERROR : ANTENNA or EPROM fault. Please check the antenna is correctly installed.\n\n");
		return 1;  // return value set to indicate error
	}
	else
	{
		return 0;
	}
	return 1;
}

int prv_setupWiringPi(void) {


 if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  pinMode(GPIO_PIN,INPUT);	// We are using GPIO_PIN as the pin to identify the "CTS" function
  
  return 0;

}

int prv_openCommsPort(int *fd) {
	
	if ((*fd = serialOpen (SERIAL_PORT, SERIAL_BAUD_RATE) ) < 0)  // Try to open a connection to the serial port
	{
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		return 1 ;
	}

	return 0;
}

int prv_readPage(int fd, int page, int *page_contents, int page_size) {
	
	//ToDo: This needs to return the page size, not get it!!
	
	int			noTag = 1;
	int			pagedata[page_size];
	int			counter = 0;
	int			status = EXIT_FAILURE;
	
	//ToDo: Convert the '100' above to be dynamically allocated and not fixed.
	
	memset(pagedata, '\0' , sizeof(pagedata));
	
	while (noTag == 1) {
		prv_waitForCTS(fd);
        serialPutchar(fd, 0x52);
 		serialPutchar(fd, page); // Tag Page 00 - both H1/S and H2 should work here

		delay(100); //  Need to wait otherwise the command does not work

		while ( serialDataAvail(fd) )
		{
			char result;
			result = serialGetchar(fd);
			if (result == 0xD6)
			{
				// Tag present
				noTag = 0;
				counter=0;
				while (serialDataAvail(fd) && (counter < page_size))
				{
					pagedata[counter] = serialGetchar(fd);
					counter ++;
				}
				pagedata[counter] = '\0';
				memcpy(page_contents, pagedata, counter);
				status = EXIT_SUCCESS;
			}
			else
			{
				// first character is garbage, start again
				serialFlush(fd);
			}
		}
	}
	return status;
}

int * prv_readBlock(int fd, int block) {
	
	int		noTag = 1;
	int			maxBlockSize = 100;
	static int	blockdata[100]; //maxBlockSize]; //Bug: This should be set to maxBlockSize, not a number
	int			counter = 0;
	
	memset(blockdata, '\0' , sizeof(blockdata));
		
	while (noTag ==1) {
		serialPutchar(fd, 0x72);
		serialPutchar(fd, 0x04); // Tag blocks 00-003 - only H1/S should work here

		delay(100); // ??? Need to wait otherwise the command does not work

		while ( serialDataAvail(fd) )
		{
			char result;
			result = serialGetchar(fd);
			if (result == 0xD6)
			{
				noTag = 0;
				counter=0;
				while (serialDataAvail(fd) && (counter < maxBlockSize))
				{
					blockdata[counter] = serialGetchar(fd);
					counter ++;
				}
			}
			else
			{
			}
		}
	}

	return blockdata;
}

int prv_checkTagPresent(int fd) {
	int			noTag = 1;
	serialPutchar(fd, 0x53); // Send 'S' to the PirFix

	delay(100); 

	while ( serialDataAvail(fd))  // Whilst data is being sent back from the device
	{
		char result;
		result = serialGetchar(fd);	// Get each character
		if (result == 0xD6)  // confirm that the tag is present, valid and no errors
		{
			noTag = 0;		// set this so the outer while loop can terminate
			// printf ("\nTag present.\n\n");
		}
	}
	return noTag;
}

int prv_setPollingDelay(int fd, int polling_delay) {
	
	char		result;
	int			success = 1;
	
	serialPutchar(fd, 0x50);
	serialPutchar(fd, 0x00);
	serialPutchar(fd, polling_delay);

	delay(100);

	while ( serialDataAvail(fd) )
	{
		
		result = serialGetchar(fd);
		if (result == 0xC0)
		{
			//printf("\n\nPolling delay changed .......\n\n");
			success = 0;
		}
		else
		{
			//printf("\n\nUnexpected reply >%X< \n\n", result);
			success = 1;
		}
	}
	
	return success;

}

//old functions prior to latest change
int prv_getFirmwareInfo_old(int conn, char *response, int response_size) {
    
	int				i = 0;
    char			firmware_response[response_size];
	firmware_response[0]= '\0';
    
    printf("Getting firmware information.\n");
	
	prv_waitForCTS(conn);
	serialPuts(conn,"z");
    delay(100);
	// get data and fill the buffer, less the last which needs to be \0
	while (serialDataAvail (conn) && i < (response_size-1))
	{
		firmware_response[i] = serialGetchar (conn) ;
		//printf("Char Received:%i", text_result[i]);
		i++;
	}
	firmware_response[i] = '\0';
	serialFlush(conn);

    strcpy(response, firmware_response);
    return 0;
}
