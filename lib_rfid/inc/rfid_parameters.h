/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfid_parameters.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 July 2019, 09:20
 */

#ifndef RFID_PARAMETERS_H
#define RFID_PARAMETERS_H

// set for GPIO Pin to use based on the jumper connection
#define GPIO_PIN			1       // Jumper 1, also known as GPIO18
// #define GPIO_PIN			0       // Jumper 2, also known as GPIO17
// #define GPIO_PIN			2       // Jumper 3, also known as GPIO21 (Rv 1) or GPIO27 (Rv 2)
// #define GPIO_PIN			3       // Jumper 4, also known as GPIO22

// Set the serial Port
#define		SERIAL_PORT				"/dev/serial0"
#define		SERIAL_BAUD_RATE		9600

// The values below are for the polling delay
#define		POLLING_DELAY_0MS		0x00		// 0mS polling delay (none)
#define		POLLING_DELAY_8MS		0x10		// 8mS polling delay
#define		POLLING_DELAY_16MS		0x20		// 16mS polling delay
#define		POLLING_DELAY_32MS		0x30		// 32mS polling delay
#define		POLLING_DELAY_65MS		0x40		// 65mS polling delay
#define		POLLING_DELAY_132MS		0x50		// 132mS polling delay
#define		POLLING_DELAY_262MS		0x60		// 262mS polling delay
#define		POLLING_DELAY_524MS		0x70		// 524mS polling delay
#define		POLLING_DELAY_1S		0x80		// 1S polling delay
#define		POLLING_DELAY_2S		0x90		// 2S polling delay
#define		POLLING_DELAY_4S		0xA0		// 4S polling delay
#define		POLLING_DELAY_8S		0xB0		// 8S polling delay


#endif /* RFID_PARAMETERS_H */

