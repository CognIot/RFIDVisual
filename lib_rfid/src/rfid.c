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
 * 
 */
int readVersion(int conn, char reply[]) {
	
	int			number = 0;
	
	number = rand();
	//sprintf(reply, "version is : %d", number);		//this line causes a segmentation fault
	
	return 0;
}

