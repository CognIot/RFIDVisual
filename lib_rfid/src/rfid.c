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
 * using the comms, return the information from the get firmware command
 */
char _getFirmwareInfo(int conn) {
    
    int             number;
    char            firmware_response[100] = '\0';
    
    printf("Getting firware information.");

    number = rand();
    sprintf(answer, "c IDE MTRW EM400X/MC200 (MTRW_LP  V%d) DD/MM/YY) Copyright IB Technology Ltd", number);
    printf("firmware Info is: >>%s<<\n", answer);
    
    return firmware_response;
}
    
/*
 * return the version information, excluding the mode.
 */
char readVersion(int conn) {
    
    int            number;
    static char    answer[100];
    answer[0] = '\0';
    
    printf("reading version\n");
    
    number = rand();
    sprintf(answer, "c IDE MTRW EM400X/MC200 (MTRW_LP  V%d) DD/MM/YY) Copyright IB Technology Ltd", number);
    printf("answer is: >>%s<<\n", answer);
    
    return answer;
}

