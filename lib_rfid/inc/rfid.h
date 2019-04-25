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
  given the connection, return the version info in the pointer *reply.
    returns 0 or 1 for pass or fail
 */
int readVersion(int conn, int *reply);
#endif /* RFID_H */

