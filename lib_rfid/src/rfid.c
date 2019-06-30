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
	
    printf("reading version\n");
	
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
	
    printf("reading mode\n");
	
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
	// check response
	
	// repeat if failed
	return status;
}

int resetReader(int conn) {
	
	int			status;
	
	status = waitForCTS(conn);
	
	if (status == 0) {
		status = prv_sendResetCommand(conn);
	}
	else {
		status = 1;
	}
		
	return status;
}

int setupComms(){
	
	int			conn = 1;
	//ToDO: Write function
	
	prv_setupWiringPi();
	
	//ToDo: The bit below needs to have better failure handling...
	
	conn = prv_openCommsPort();
	if (conn > 1) {

		// We have opened communications with the onboard Serial device
		int antennaOK = 0;

		printf("Opened communications with PirFix.\n");  // Communications opened successfully

		antennaOK = GetAntennaStatus(conn);  // Check status of the antenna.

		if (antennaOK != 0) {
			conn = 1;
		}		
	}

	//ToDo: What do I return at this stage>> should be 0 - success, 1 - failure
	// actually returning the connection number or 1 if failure.
	return conn;
}

int readTagStatus(int fd) {
	int		noTag = 1;

	printf("\nWaiting for a tag ....\n");

	while (noTag == 1)
	{
		waitForCTS(fd);

		noTag = prv_checkTagPresent(fd);
	}
	//ToDo: No idea what to do here at present!
	return noTag;
}

int setPollingDelay(int fd, int pollDelay) {
	
	int		status = 1;
	// validate the parameters given
	//ToDo: Need to validate the delay given

	// Set the polling delay
	waitForCTS(fd);

	//ToDo: How do I all the user to set the value?
	//		especially as it isn't used on the visual stuff
	status = prv_setPollingDelay(fd, pollDelay);
	
	//ToDo: Set the return value based on 
	return status;
}
			
int * readTagPage(int fd, int pg) {

	int			* data;

	data = prv_readPage(fd, pg);
	
	return data;
}

int * readTagBlock(int fd, int blk) {
	
	int		noTag = 1;
	int		* data;
	
	while (noTag == 1)
	{
		waitForCTS(fd);

		data = prv_readBlock(fd, blk);
	}
	return data;
}