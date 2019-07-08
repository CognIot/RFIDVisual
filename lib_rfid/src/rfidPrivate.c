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


char *prv_getFirmwareInfo(int conn) {
    
    static char     firmware_response[100];		// ToDo: need to set this size parameter to a #define rather than fixed.
	firmware_response[0]= '\0';
    
    printf("Getting firmware information.\n");
	
	prv_waitForCTS(conn);
	serialPuts(conn,"z");
    delay(100);
    strcpy(firmware_response,prv_getTextResult(conn));

	//int             number;
    //number = rand();
    //sprintf(firmware_response, "c IDE MTRW EM400X/MC200 (MTRW_LP  V%d) DD/MM/YY) Copyright IB Technology Ltd", number);
    //printf("firmware Info is: >>%s<<\n", firmware_response);
    
    return firmware_response;
}


int prv_modeSetting(int fd, int mode) {
	
	//ToDo: Set the mode, code below was copied from rfidReader.c
	
				switch (mode)
				{
					case 'a':
						prv_waitForCTS(fd);

						serialPutchar(fd, 0x76);
						serialPutchar(fd, 0x01);  // 0x01 = H2
						break;


					case 'b':
						prv_waitForCTS(fd);

						serialPutchar(fd, 0x76);
						serialPutchar(fd, 0x02);  // 0x02 = H1/S
						break;

					case 'c':
						prv_waitForCTS(fd);

						serialPutchar(fd, 0x76);
						serialPutchar(fd, 0x03);// 0x03 = EM/MC2000
						break;

					default:
						printf("\n\tInvalid option.  Please try again...\n\n");
						// wait until a valid entry has been selected.
						//ToDo: Change this to no action taken and return failure

				}

				delay(100);
				while ( serialDataAvail(fd) )
				{
					char result;
					result = serialGetchar(fd);
					if (result == 0xC0)
					{
						printf("\n\nReader Operating Tag Mode changed .......\n\n");
					}
					else
					{
						printf("\n\nUnexpected reply >%X< \n\n", result);
						while (serialDataAvail (fd))
						{
							printf (" %X", serialGetchar (fd)) ;
							fflush (stdout) ;
						}
						printf("\n\n");
					}
				}
	
	
	return 0;
}

int prv_sendResetCommand(int fd) {
	
	//ToDo: Need to implement this via serial comms.
	
	//wiringpi2.serialPutchar(fd, 0x46)
    //wiringpi2.serialPutchar(fd, 0x55)
    //wiringpi2.serialPutchar(fd, 0xAA)
    //time.sleep(0.1)

	//ToDo: Tidy up and add checking
	
	//wait for CTS
	
			serialPutchar(fd, 0x46);	// this command sequence is
			serialPutchar(fd, 0x55);	//
			serialPutchar(fd, 0xAA);	// required to force a factory reset.

			delay(100);

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

char * prv_getTextResult(int conn) {
	
	static char		text_result[100];				//ToDo: This needs to be changed from a fixed number to something better
	int				i = 0;
	text_result[0] = '\0';
	
	while (serialDataAvail (conn))
	{
		text_result[i] = serialGetchar (conn) ;
		printf("Char Received:%i", text_result[i]);
		i++;
	}
	text_result[i]='\0';
	printf("length of text response:%d\n", i);
	return text_result;
}

int prv_getAntennaStatus(int fd) {
	// Perform a firmware read to check the status of the antenna

	prv_waitForCTS(fd);
    serialPutchar(fd, 0x53);  // Send any command - this happens to be the one to check if a tag is present
	delay(100);

	if ((serialGetchar(fd) & 0x20) == 0x20 )  // Checking bit 5.  If set, indicates antenna fault
	{
		printf("ERROR : ANTENNA or Eprom fault. Please check the antenna is correctly installed.\n\n");
		return 1;  // return value set to indicate error
	}
	else
	{
		return 0;
	}

}

int prv_setupWiringPi(void) {


 if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  pinMode(GPIO_PIN,INPUT);	// We are using GPIO_PIN as the pin to identify the "CTS" function
  //ToDo: What happens if the command above fails??
  
  return 0;

}

int prv_openCommsPort(void) {
	
	int			fd = 0;
	
  if ((fd = serialOpen (SERIAL_PORT, SERIAL_BAUD_RATE)) < 0)  // Try to open a connection to the serial port
  {
	  fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
	  return 0 ;
  }

  return fd;
}


int *prv_readPage(int fd, int page) {
	
	int			noTag = 1;
	int			maxPageSize = 100;
	static int	pagedata[100]; //maxPageSize]; //Bug: This should be set to maxPageSize, not a number
	int			counter = 0;
	
	memset(pagedata, 0 , maxPageSize);
	
	//ToDo: lots to do here to get it to work and probably split it up a little.
	while (noTag == 1) {
		prv_waitForCTS(fd);
        serialPutchar(fd, 0x52);
 		serialPutchar(fd, 0x00); // Tag Page 00 - both H1/S and H2 should work here

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
				while (serialDataAvail(fd) && (counter < maxPageSize))
				{
					pagedata[counter] = serialGetchar(fd);
					counter ++;
				}
			}
			else
			{
				// first character is garbage, start again
				serialFlush(fd);
			}
		}
	}
	return pagedata;
}

int * prv_readBlock(int fd, int block) {
	
	int		noTag = 1;
	int			maxBlockSize = 100;
	static int	blockdata[100]; //maxBlockSize]; //Bug: This should be set to maxBlockSize, not a number
	int			counter = 0;
	
	memset(blockdata, 0 , maxBlockSize);
		
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
	//ToDo: Need to return the string / array
	return blockdata;
}

int prv_checkTagPresent(int fd) {
	int			noTag = 1;
	serialPutchar(fd, 0x53); // Send 'S' to the PirFix

	delay(100); // ??? Need to wait otherwise the command does not work

	while ( serialDataAvail(fd))  // Whilst data is being sent back from the device
	{
		char result;
		result = serialGetchar(fd);	// Get each character
		if (result == 0xD6)  // confirm that the tag is present, valid and no errors
		{
			noTag = 0;		// set this so the outer while loop can terminate
			printf ("\nTag present.\n\n");
		}
	}
	//ToDo: return 0 if tag found, 1 if not.
	return noTag;
}

int prv_setPollingDelay(int fd, int polling_delay) {
	serialPutchar(fd, 0x50);
	serialPutchar(fd, 0x00);
	//serialPutchar(fd, 0x00); // 0x00 is no delay
	//serialPutchar(fd, 0x20); // 0x20 is approx 20ms
	//serialPutchar(fd, 0x40); // 0x40 is approx 65ms
	serialPutchar(fd, 0x60); // 0x60 is approx 262ms
	//serialPutchar(fd, 0x80); // 0x60 is approx 1 Seconds
	//serialPutchar(fd, 0xA0); // 0x60 is approx 4 Seconds

	delay(100);

	while ( serialDataAvail(fd) )
	{
		char result;
		result = serialGetchar(fd);
		if (result == 0xC0)
		{
			printf("\n\nPolling delay changed .......\n\n");
		}
		else
		{
			printf("\n\nUnexpected reply >%X< \n\n", result);
			while (serialDataAvail (fd))
			{
				printf (" %X", serialGetchar (fd)) ;
				fflush (stdout) ;
			}
			printf("\n\n");
		}
	}
	
	return 0;

}