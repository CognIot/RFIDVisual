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

/*
 * The functions below are private functions only
 * 
 * todo: consider moving these into a rfid_private.c file
 */

char *_getFirmwareInfo(int conn) {
    
	//todo: This function does not yet call into the RFID module.
    int             number;
    static char     firmware_response[100];		// todo: need to set this size parameter to a #define rather than fixed.
	firmware_response[0]= '\0';
    
    printf("Getting firmware information.\n");

    number = rand();
    sprintf(firmware_response, "c IDE MTRW EM400X/MC200 (MTRW_LP  V%d) DD/MM/YY) Copyright IB Technology Ltd", number);
    printf("firmware Info is: >>%s<<\n", firmware_response);
    
    return firmware_response;
}
    
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
	
	strcpy(reply,_getFirmwareInfo(conn));
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
	
	strcpy(reply,_getFirmwareInfo(conn));
	
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