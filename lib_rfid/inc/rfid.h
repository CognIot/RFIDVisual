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
 * Takes the _getFirmware response and extracts the Version information
 * return the version information, excluding the mode.
 */
char *readVersion(int conn);

/* 
 * Takes the _getFirmware response and extracts the Version information
 * return the version information, excluding the mode.
 */
char *readMode(int conn);

/*
 * Sets the reader mode.
 * requires a serial connection and the mode requested
 * returns status, 0 or 1.
 */
int setReaderMode(int conn, char mode);

#endif /* RFID_H */

