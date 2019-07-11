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


//Note: This contains the functions for the user functions.
/*
 * The functions below are public functions and should be called from outside.
 * 
 */
char *readVersion(int conn) {
    
    int				length = 0;
    char			reply[MAX_FIRMWARE_LENGTH];
	static char		answer[MAX_FIRMWARE_LENGTH];
    
	reply[0] = '\0';
	answer[0] = '\0';
	
    printf("Reading version\n");
	
	strcpy(reply,prv_getFirmwareInfo(conn));
	printf("version info received:%s\n", reply);
	
	length = strlen(reply);
	if (length > MIN_FIRMWARE_LENGTH) {
		// sufficient size of length, now extract from the start onwards.
		printf("extracting the version info\n");
		
		strcpy(answer, reply+START_OF_VERSION_INFO);
	}
    
    return answer;
}

char *readMode(int conn) {
    
    int				i = 0;
	char			*valid;
    char			reply[MAX_FIRMWARE_LENGTH];
	static char		answer[1];
    
	reply[0] = '\0';
	answer[0] = '\0';
	
    printf("Reading Mode\n");
	
	strcpy(reply,prv_getFirmwareInfo(conn));
	
	i = strlen(reply);
	if (i > MIN_FIRMWARE_LENGTH) {
		// sufficient size of length, now extract the first character only.
		strncpy(answer, reply, 1);
		
		// check for valid mode, if not set it back to empty!
		valid = strchr(VALID_MODES, answer[0]);
		if (valid == NULL) {
			answer[0] = '\0';
		}
	}

    return answer;
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
	// ToDo: check response
	
	// repeat if failed
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
	
	//ToDo: The bit below needs to have better failure handling... It should probably return a status and 
	//      separately a a pointer to the comms port  
	
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

int readTagStatus(int fd) {
	int		noTag = 1;

	printf("\nWaiting for a tag ....\n");

	// ToDo: Add a timeout loop on this one, else it will sit there for ever.
	while (noTag == 1)
	{
		prv_waitForCTS(fd);

		noTag = prv_checkTagPresent(fd);
	}
	// Returns 0 if tag found, 1 if not.
	return noTag;
}

int setPollingDelay(int fd, int pollDelay) {
	
	int		status = 1;

	// Set the polling delay
	prv_waitForCTS(fd);

	status = prv_setPollingDelay(fd, pollDelay);
	
	//Return value based on sub function response
	return status;
}
			
int * readTagPage(int fd, int pg) {

	int			* data;

	data = prv_readPage(fd, pg);
	
	return data;
}

int * readTagBlock(int fd, int blk) {
	
	int		* data;
	
	prv_waitForCTS(fd);

	data = prv_readBlock(fd, blk);

	return data;
}