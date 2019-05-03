/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfid.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 13 April 2019, 16:12
 */

#ifndef RFID_H
#define RFID_H

#define		MIN_FIRMWARE_LENGTH		5			//The minimum acceptable length of the firmware response
#define		START_OF_VERSION_INFO	2			//The character where the version info starts, starts from zero!
#define		MAX_FIRMWARE_LENGTH		101			//The maximum size of the firmware response PLUS 1 for \0
#define		VALID_MODES				"abcABC"	//the valid modes for the sensor

/*
  * given the connection, return the version info in the pointer *reply.
  *   returns 0 or 1 for pass or fail
  * returns something like the below in the *reply
  * “a IDE MTRW H2 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd”  0x00
  * "b IDE MTRW H1 (firmware filename  V1.xx)  DD/MM/YY) Copyright message" 0x00
  * "c IDE MTRW EM400X/MC200 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd”  0x00
 *
 * using the comms, return the information from the get firmware command
 */
char *_getFirmwareInfo(int conn);

/* 
 * Takes the _getFirmware response and extracts the Version information
 * return the version information, excluding the mode.
 */
char *readVersion(int conn);

/* 
 * Takes the _getFirmware response and extracts the Version information
 * return the version information, excluding the mode.
 */
char *readMode(int conn);

#endif /* RFID_H */

