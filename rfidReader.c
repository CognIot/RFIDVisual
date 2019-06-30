/* 
 * File:   rfidReader.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 30 March 2019, 09:34
 * 
 *	Example code on accessing the RFID Reader and reading data from tags
 *
 *
 *
 * The code here is experimental, and is not intended to be used
 * in a production environment. It demonstrates the basics of what is
 * required to get the Raspberry Pi receiving RFID data and configuring
 * the RFID Reader parameters.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.cogniot.eu
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "rfidReader.h"
#include "lib_rfid/inc/rfid.h"

void helpText(void) {
	printf("**************************************************************************\n");
	printf("Available commands: -\n\n");
	printf("z - Display firmware version information\n");
	printf("S - Acknowledge presence of Tag\n");
	printf("F - Perform a Factory Reset \n");
	printf("P - Program EEPROM Polling delay \n");
	printf("v - Select reader operating mode \n");
	printf("R - Read Tag and PAGE 00 data \n");
	printf("r - Read Tag and BLOCK 00-03 data \n");
	printf("e - Exit program \n");
	printf("\n 	Press h for this help\n");
}

void setOperatingMode(int conn) {
	
	char			tagOption;
	
	printf("\n\nSetting Reader Operating Tag Mode.......\n\n");
	printf("\n\t*********************************************\n");
	printf("\ta - Hitag H2\n");
	printf("\tb - Hitag H1/S (factory default)\n");
	printf("\tc - EM/MC2000\n\n");

	printf("\tPlease select tag type .....>");

	tagOption = getchar();
	getchar(); // Needed to consume the carriage return.

	switch (tagOption)
	{
		case 'a':
			setReaderMode(conn, 'a');
			break;

		case 'b':
			setReaderMode(conn, 'b');
			break;

		case 'c':
			setReaderMode(conn, 'c');
			break;

		default:
			printf("\n\tInvalid option.  returning to main menu...\n\n");
	}
	return;
}

int main () {
//
    char            version[100];
	char			option;
	int				conn;
	int				status;
	int				* data;
	int				i = 0;

	helpText();

	printf("Bostin Technology Ltd\n");
	printf("Cogniot Products\n");
	printf("PirFlx\n");
	printf("\n");
	
	conn = setupComms();

	do {

		printf("\n");
		printf("Please select command -> ");

		option = getchar();
		getchar();  // have to press enter and this consumes the enter character

		switch (option)
		{
			case 'z': // Read the firmware version

				printf("\nRead Firmware Details - Reading device..>\n\n");
				strcpy(version,readVersion(conn));
				printf("Version Information: >>%s<<\n", version);
				break;

			case 'S': // Read the status of the RFID device

				status = readTagStatus(conn);
				if (status ==0) {
					printf("Tag Found\n");
				}
				else {
					printf("No tag found\n");
				}
				break;

			case 'F': // Perform a factory reset
				
				printf("\nPerforming a factory reset ....\n");
				status = resetReader(conn);
				if (status == 0) {
					printf("\n\nFACTORY RESET COMPLETE \n\n");
				}
				else {
					printf("Factory Reset failed\n");
				}
				break;

			case 'P': // Program the internal EEPROM Polling delay

				printf("\n\nSetting Polling delay .......\n\n");
				setPollingDelay(conn, 0x60);

				break;

			case 'v': // Select the reader operating mode

				setOperatingMode(conn);
				break;

			case 'R': // Read a page of data from the Tag

				printf("\n\nReading Tag Data Page 00.......\n\n");
				printf("\nWaiting for a tag ....\n");

				data = readTagPage(conn, 0x00);
				
				//ToDo: This needs to be changed so that I read back the data and the size of it.
				//		Put it into a structure maybe??
				for ( i = 0; i < 100; i++ ) {
					printf( "*(data + %d) : %d\n", i, *(data + i));
				 }

				break;

			case 'r': // Read data tag block data

				printf("\n\nReading Tag Data Block 00, 01, 02 & 03.......\n\n");
				printf("\nWaiting for a tag ....\n");

				//ToDo: It is currently only reading block zero!!
				data = readTagBlock(conn, 0x00);
				
				//ToDo: This needs to be changed so that I read back the data and the size of it.
				//		Put it into a structure maybe??
				for ( i = 0; i < 100; i++ ) {
					printf( "*(data + %d) : %d\n", i, *(data + i));
				 }

				 break;


			case 'e':
				 printf("Exiting.......\n");
				 option = 'e';
				 break;

			case 'h':
				 helpText();
				 break;

			default:
				 printf("Unrecognised command!\n");
		}

	//ToDo: where do these bits belong??
		fflush (stdout) ;

		} while(option != 'e');

		// serialClose(conn); //Bug: This doesn't work here and needs to be somewhere.

		return(0);

	}
