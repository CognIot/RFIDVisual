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

/*
 * The functions below are private functions only
 * 
 * todo: consider moving these into a rfid_private.c file
 */

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
