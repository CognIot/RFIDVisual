/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfid.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 13 April 2019, 16:12
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/rfid_parameters.h"
#include "../inc/rfid.h"
#include "../inc/rfidPrivate.h"

/* ToDo: Resolve this.
 * Both of these are responses to the z command, but in different modes. The version info is not everything
 * after the initial letter as I firth thought, but only the bits in brackets
 * The rest is the mode info
 *  Device Response in Main() : c IDE MTRW MC200/EM400X (MTRW125-87LP V1.01 20/05/15)
 *  Device Response in Main() : b IDE MTRW H1 (MTRW125-87LP V1.01 02/06/15)
 * 
 * I can no longer use a fixed size for the array, I need to realloc on the fly!
 */

//Note: This contains the functions for the user functions.
/*
 * The functions below are public functions and should be called from outside.
 * 
 */
int readVersion(int conn, char *answer, int max_length) {
    
	int				j = 0;
	char			*result = malloc (sizeof(char*));		//The firmware info is held here
	int				*arr_length = malloc (sizeof(int*));	//The length of the resulting array
	int				status = EXIT_FAILURE;

    printf("Reading version\n");
	
	prv_getFirmwareInfo(conn, &result, arr_length);
	printf("Returned wth data\n");
	printf("response:%s\n", result);
	printf(".\n");
	//printf("length of response:%d", arr_length);
	j=0;
    while (result[j] != '\0')
    {
		printf(".\n");
		printf("j:%d\n", j);
        //printf("%d : %s", j, result[j]);
		j++;
    }
	printf("..\n");
	
	if (*arr_length > MIN_FIRMWARE_LENGTH) {
		// sufficient size of length, now extract from the start onwards.
		printf("extracting the version info\n");
		
		strncpy(answer, result+START_OF_VERSION_INFO,max_length-1);
		printf("answer:%s\n", answer);
		status = EXIT_SUCCESS;
	}
    return status;
}

int readMode(int conn, char *answer) {
    
    int				length = 0;
	char			*valid;
    char			reply[MODE_LENGTH];
	int				status = EXIT_FAILURE;
    
	memset(reply,'\0', sizeof(reply));
	
    printf("Reading Mode\n");
	
	prv_getFirmwareInfo(conn, reply, MAX_FIRMWARE_LENGTH);
	printf("version info received:%s\n", reply);
	
	length = strlen(reply);
	if (length > MIN_FIRMWARE_LENGTH) {
		// sufficient size of length, now extract the first character only.
		strncpy(answer, reply, MODE_LENGTH);
		
		// check for valid mode, if not set it back to empty!
		valid = strchr(VALID_MODES, answer[0]);
		if (valid == NULL) {
			answer[0] = '\0';
			status = EXIT_FAILURE;
		}
		else
		{
			status = EXIT_SUCCESS;
		}
	}

    return status;
}

int setReaderMode(int conn, char mode) {
	
	int			mode_setting = 0x00;
	int			status = 1;
	
	// write mode
	switch (mode) {
		case 'a':
		case 'A':
			printf("Mode A being set\n");
			mode_setting = 0x01;
			break;
		case 'b':
		case 'B':
			printf("Mode B being set\n");
			mode_setting = 0x02;
			break;
		case 'c':
		case 'C':
			printf("Mode C being set\n");
			mode_setting = 0x03;
			break;
		default:
			printf("invalid mode received\n");
			mode_setting = 0x00;
			break;
	}
	
	if (mode_setting > 0) {
		status = prv_modeSetting(conn, mode_setting);
	}

	return status;
}

int resetReader(int conn) {
	
	int			status = 1;
	
	prv_waitForCTS(conn);
	
	status = prv_sendResetCommand(conn);
		
	return status;
}

int setupComms(int *conn){
	
	int			status = 0;
	
	prv_setupWiringPi(); 
	
	status = prv_openCommsPort(conn);
	if (status == 0) {

		// We have opened communications with the onboard Serial device
		int antennaOK = 0;

		printf("Opened communications with PirFix.\n");  // Communications opened successfully

		antennaOK = prv_getAntennaStatus(conn);  // Check status of the antenna.

		if (antennaOK != 0) {
			status = 1;
		}		
	}

	return status;
}

int readTagStatus(int conn) {
	int		noTag = 1;

	printf("\nWaiting for a tag ....\n");

	while (noTag == 1)
	{
		prv_waitForCTS(conn);

		noTag = prv_checkTagPresent(conn);
	}
	// Returns 0 if tag found, 1 if not.
	return noTag;
}

int setPollingDelay(int conn, int pollDelay) {
	
	int		status = 1;

	// Set the polling delay
	prv_waitForCTS(conn);

	status = prv_setPollingDelay(conn, pollDelay);
	
	//Return value based on sub function response
	return status;
}
			
int readTagPage(int fd, int page, int *pg, int page_size) {

	int			response = EXIT_FAILURE;

	response = prv_readPage(fd, page, pg, page_size);
	
	return response;
}

int * readTagBlock(int fd, int blk) {
	
	int		* data;
	
	prv_waitForCTS(fd);

	data = prv_readBlock(fd, blk);

	return data;
}