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


// ToDo: Update description
// conn is the serial connection, **response is the array that the reply is in, *length is the size of the array

/*****************************************************************************************
 * Description: Given the connection, returns the firmware response in the supplied pointer
 *				to a maximum size.
 * 
 * eg:
 * “a IDE MTRW H2 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd\0”
 * "b IDE MTRW H1 (firmware filename  V1.xx)  DD/MM/YY) Copyright message\0"
 * "c IDE MTRW EM400X/MC200 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd\0”
 *				
 * Arguments  : requires the serial port connection, a pointer to the char array for the 
 *				response and the maximum size allowed.
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int prv_getFirmwareInfo(int conn, char **response, int *length);

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
int prv_waitForCTS(int fd);

/*****************************************************************************************
 * Description: Performs a version read to check the antenna status
 *				
 * Arguments  : Requires the serial port connection
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int prv_getAntennaStatus(int *fd);

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
 * Arguments  : A pointer to the resulting connection
 *
 * Returns	  : 0 if successful, 1 if failure
 *				the serial port connection
 *  
 ****************************************************************************************/
int prv_openCommsPort(int *fd);

/*****************************************************************************************
 * Description: Reads the given page from the tag (waiting for it to be detected first)
 *				and returns a pointer to it's contents
 *				Note: If the page is invalid, the function will return an empty response
 *				
 * Arguments  : Requires the serial port connection, the page number, a pointer to the 
 *				array to store the response it and the size of that array
 *
 * Returns	  : EXIT_SUCCESS or EXIT_FAILURE
 *  
 ****************************************************************************************/
int prv_readPage(int fd, int page, int *page_contents, int page_size);

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

/*****************************************************************************************
 * Description: Given the connection, returns the firmware response in the supplied pointer
 *				to a maximum size.
 * 
 * eg:
 * “a IDE MTRW H2 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd\0”
 * "b IDE MTRW H1 (firmware filename  V1.xx)  DD/MM/YY) Copyright message\0"
 * "c IDE MTRW EM400X/MC200 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd\0”
 *				
 * Arguments  : requires the serial port connection, a pointer to the char array for the 
 *				response and the maximum size allowed.
 *
 * Returns	  : 0 - success, 1 - failure
 *  
 ****************************************************************************************/
int prv_getFirmwareInfo_old(int conn, char *response, int response_size);
#endif /* RFIDPRIVATE_H */

