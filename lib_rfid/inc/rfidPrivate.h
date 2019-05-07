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
char *prv_getFirmwareInfo(int conn);

/*
 * Set the mode for the reader
 * requires the serial connection and the mode
 * mode must be 0x01, 0x02 or 0x03
 * returns status, 0 or 1.
 */
int prv_modeSetting(int conn, int mode);


#endif /* RFIDPRIVATE_H */

