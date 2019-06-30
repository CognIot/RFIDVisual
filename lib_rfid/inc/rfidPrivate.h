/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidPrivate.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 04 May 2019, 14:01
 */

#ifndef RFIDPRIVATE_H
#define RFIDPRIVATE_H

//ToDo: Is this the right place for these to be defined???
// set for GPIO Pin to use based on the jumper connection
#define GPIO_PIN 1       // Jumper 1, also known as GPIO18
// #define GPIO_PIN 0          // Jumper 2, also known as GPIO17
// #define GPIO_PIN 2       // Jumper 3, also known as GPIO21 (Rv 1) or GPIO27 (Rv 2)
// #define GPIO_PIN 3       // Jumper 4, also known as GPIO22


/*****************************************************************************************
 * Description: Given the connection, returns the firmware response info as a pointer.
 * 
 * eg:
 * “a IDE MTRW H2 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd\0”
 * "b IDE MTRW H1 (firmware filename  V1.xx)  DD/MM/YY) Copyright message\0"
 * "c IDE MTRW EM400X/MC200 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd\0”
 *				
 * Arguments  : requires the serial port connection
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
char *prv_getFirmwareInfo(int conn);

/*****************************************************************************************
 * Description: Sets the operating mode of the module.
 *				Note: If the given mode is invalid, 1 - failure is returned
 *				
 * Arguments  : Requires the serial port connection and the required mode.
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int prv_modeSetting(int conn, int mode);

/*****************************************************************************************
 * Description: Sends the Reset command and waits before returning
 *				
 * Arguments  : Requires the serial port connection
 *
 * Returns	  : 1 - success
 *  
 ****************************************************************************************/
int prv_sendResetCommand(int conn);


/*****************************************************************************************
 * Description: Waits until the CTS line has gone high - when a tag is present in the field
 *				
 * Arguments  : Requires the serial port connection
 *
 * Returns	  : 0 - success, when the tag is read
 *  
 ****************************************************************************************/
//ToDo: This needs to be converted to prv_....
//ToDo:  All calls to this need to be changed to pass in the serial port
int waitForCTS(int fd);

/*****************************************************************************************
 * Description: this function reads teh data back from the given serial port
 *				
 * Arguments  : Requires the serial port connection
 *
 * Returns	  : the contents of the serial port buffer
 *  
 ****************************************************************************************/
//ToDo: This needs to be converted to prv_....
//ToDo:  All calls to this need to be changed to pass in the serial port
void GetTextResult(int fd);

	// Perform a firmware read to check the status of the antenna
	// requires the serial port to be given
//ToDo: This needs to be converted to prv_....
//ToDo:  All calls to this need to be changed to pass in the serial port
/*****************************************************************************************
 * Description: Performs a version read to check the antenna status
 *				
 * Arguments  : Requires the serial port connection
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int GetAntennaStatus(int fd);

/*****************************************************************************************
 * Description: Initialise WiringPi so we can use the GPIO on the Raspberry Pi
 *				
 * Arguments  : none
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int prv_setupWiringPi(void);


// Opens the serial port
// returns 1 or 0
/*****************************************************************************************
 * Description: Opens the serial port using wiring pi
 *				
 * Arguments  : none
 *
 * Returns	  : the serial port connection or 1 if failure
 *  
 ****************************************************************************************/
int prv_openCommsPort(void);

/*****************************************************************************************
 * Description: Reads the given page from the tag (waiting for it to be detected first)
 *				and returns a pointer to it
 *				Note: If the page is invalid, the function will return an empty response
 *				
 * Arguments  : Requires the serial port connection and the page number
 *
 * Returns	  : The page of data
 *  
 ****************************************************************************************/
//ToDo: I think this needs to be converted to return a string or maybe an array?
int *prv_readPage(int fd, int page);

/*****************************************************************************************
 * Description: Reads the given block from the tag (waiting for it to be detected first)
 *				and returns a pointer to it
 *				Note: If the block is invalid, the function will return an empty response
 *				
 * Arguments  : Requires the serial port connection and the block number
 *
 * Returns	  : The block of data
 *  
 ****************************************************************************************/
//ToDo: This needs to be converted to return a string
//ToDo: also need to consider what goes in this function and what goes in rfid.c
int *prv_readBlock(int fd, int block);

/*****************************************************************************************
 * Description: Checks to see if the tag is present
 *				
 * Arguments  : Requires the serial port connection
 *
 * Returns	  : returns 0 - tag present, 1 - tag NOT found
 *  
 ****************************************************************************************/
int prv_checkTagPresent(int fd);

/*****************************************************************************************
 * Description: Set the polling delay to the given value.
 *				Note: No validation is done on the given value
 *				
 * Arguments  : Requires the serial port connection and delay value
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int prv_setPollingDelay(int fd, int delay);
#endif /* RFIDPRIVATE_H */

