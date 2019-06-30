/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidReader.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 26 May 2019, 10:57
 */

#ifndef RFIDREADER_H
#define RFIDREADER_H

/*****************************************************************************************
 * Description: Display the commands available
 *				
 * Arguments  : none
 *
 * Returns	  : nothing
 *  
 ****************************************************************************************/
void helpText(void);

/*****************************************************************************************
 * Description: Menu and control to set the reader operating mode
 *				
 * Arguments  : requires the serial connection
 *
 * Returns	  : nothing
 *  
 ****************************************************************************************/
void setOperatingMode(int conn);




#endif /* RFIDREADER_H */

