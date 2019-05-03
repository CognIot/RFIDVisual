/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   charPointers.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 28 April 2019, 10:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: need to move this to my learning git repository, rather than here

char *readVersion(int conn) {
    
    int            number;
    static char           answer[100];
    answer[0] = '\0';
    printf("reading version\n");
    
    printf("about to get a number\n");
    number = rand();
    printf("Got a number:%d\n", number);
    sprintf(answer, "c IDE MTRW EM400X/MC200 (MTRW_LP  V%d) DD/MM/YY) Copyright IB Technology Ltd", number);
    printf("answer is: >>%s<<\n", answer);

    //strcpy(answer,"\0"); Use this to check for zero length
    
    return answer;
}

void get_version_info(void) {

    char            version[100] = "\0";
    //char            *version = "\0";
    int             status = 1;
    int             count = 0;
    int             connection;
    
    connection = 13;
    do {
        strcpy(version,readVersion(connection));

        // check length of version
        //
        printf("size of Version: %d\n", sizeof(version)/sizeof(version[0]));        // returns 100
        printf("Version Information: >>%s<<\n", version);
        
// Version is empty - not returned!!        
        
        count ++;
    } while  ((count < 5) & (status != 0));
    
    if (status == 0) {
        printf("status is zero\n");

    }
    
    return;
}

/*
 * 
 */
int main(int argc, char** argv) {

	printf("starting the test program\n");
	get_version_info();
	
	return (EXIT_SUCCESS);
}

