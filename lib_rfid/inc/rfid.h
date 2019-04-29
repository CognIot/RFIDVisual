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

/*
  * given the connection, return the version info in the pointer *reply.
  *   returns 0 or 1 for pass or fail
  * returns something like the below in the *reply
  * “a IDE MTRW H2 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd”  0x00
  * "b IDE MTRW H1 (firmware filename  V1.xx)  DD/MM/YY) Copyright message" 0x00
  * "c IDE MTRW EM400X/MC200 (MTRW_LP  V1.xx) DD/MM/YY) Copyright IB Technology Ltd”  0x00
 */
char _getFirmwareInfo(int conn);

/* 
 * Takes the _getFirmware response and extracts the Version information
 */
char readVersion(int conn);


#endif /* RFID_H */

