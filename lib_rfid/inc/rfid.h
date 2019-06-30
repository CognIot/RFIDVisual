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


/*****************************************************************************************
 * Description: Takes the response from the module and extracts the version info
 *				
 * Arguments  : Serial port connection
 *
 * Returns	  : Returns a delimited string, max size set by MAX_FIRMWARE_LENGTH inc delimiter
 *  
 ****************************************************************************************/
char *readVersion(int conn);

/*****************************************************************************************
 * Description : Takes the response from the module and extracts the mode of operation
 * 
 * Arguments   : Serial port connection
 *
 * Returns	   : Returns a single char with the mode letter
 *				 Or \0 if unable to obtain it
 *  
 ****************************************************************************************/
char *readMode(int conn);

/*****************************************************************************************
 * Description: Sets the reader mode based on VALID_MODES
 *				
 * Arguments  : Requires the serial port connection and the mode
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int setReaderMode(int conn, char mode);

/*
 * Resets the reader.
 * requires a serial connection
 * returns status, 0 or 1.
 */
/*****************************************************************************************
 * Description: Sends a reset command to the module
 *				Note: Currently there is no validation if the command was successful as the 
 *				module does not reply to the reset command
 *				
 * Arguments  : Requires serial port connection
 *
 * Returns	  : 0 - success
 *  
 ****************************************************************************************/
int resetReader(int conn);

/*****************************************************************************************
 * Description: Performs all the functions to setup and check the comms are ready to use
 *				
 * Arguments  : none
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int setupComms(void);

//ToDo: Need to check valid ranges and set them as #defines.
/*****************************************************************************************
 * Description: Sends the relevant comms to set the polling day to values defined in the 
 *				specification
 *				
 * Arguments  : Requires the serial port connection and the required delay from
 *				0x00 is no delay
 *				0x20 is approx 20ms
 *				0x40 is approx 65ms
 *				0x60 is approx 262ms		
 *				0x60 is approx 1 Seconds
 *				0x60 is approx 4 Seconds
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int setPollingDelay(int fd, int delay);

/*****************************************************************************************
 * Description: Reads and returns a pointer to a page of data from the tag as an array
 *				
 * Arguments  : Requires the serial connection and the required page
 *
 * Returns	  : The page of data
 *  
 ****************************************************************************************/
//ToDo: What happens on failure???
int * readTagPage(int fd, int pg);

/*****************************************************************************************
 * Description: Reads and returns a pointer to a block of data from the tag
 *				
 * Arguments  : Requires the serial connection and the required block
 *
 * Returns	  : The block of data
 *  
 ****************************************************************************************/
//ToDo: This needs to be converted to return a string
int * readTagBlock(int fd, int blk);

/*****************************************************************************************
 * Description: Waits in a loop until a tag is detected, no timeout.
 *				
 * Arguments  : Requires the serial connection
 *
 * Returns	  : 0 - success, tag found or 1 - failure
 *  
 ****************************************************************************************/
int readTagStatus(int fd);


#endif /* RFID_H */

