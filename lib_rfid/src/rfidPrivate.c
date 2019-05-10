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

#include "../inc/rfidPrivate.h"

char *prv_getFirmwareInfo(int conn) {
    
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

int prv_modeSetting(int conn, int mode) {
	
	//todo: Set the mode
	return 0;
}


#include <stdio.h>
#include <stdlib.h>


