int prv_getFirmwareInfo(int conn, char **response, int *length) {
    
	int				i = 0;
	int				*firmware_response = malloc (sizeof(char));
    
    printf("Getting firmware information.\n");
	
	prv_waitForCTS(conn);
	serialPuts(conn,"z");
    delay(100);
	// get data and fill the buffer, less the last which needs to be \0
	while (serialDataAvail (conn) )
	{
		*response = (char*)realloc(firmware_response, (i+1) * sizeof(char));
		firmware_response[i] = serialGetchar (conn) ;
		//printf("Char Received:%i", text_result[i]);
		i++;
	}
	printf("out of get data loop\n");
	*response = (char*)realloc(firmware_response, (i+1) * sizeof(char));
	firmware_response[i] = '\0';
	printf("length:%d\n", i+1);
	*length = i+1;			// Set one higher as it is the length, not the last entry.
	
	serialFlush(conn);

    
    return 0;
}

int readVersion(int conn, char *answer, int max_length) {
    
	int				j = 0;
	char			*result = malloc (sizeof(char*));		//The firmware info is held here
	int				*arr_length = malloc (sizeof(int*));	//The length of the resulting array
	int				status = EXIT_FAILURE;

    printf("Reading version\n");
	
	prv_getFirmwareInfo(conn, &result, arr_length); //i think the parameters are right format.
	//printf("response:%s\n", result);
	//printf("length of response:%d", arr_length);
	j=0;
    while (result[j] != '\0')
    {
        printf("%d : %s", j, result[j]);
		j++;
    }
	printf("\n");
	
	if (*arr_length > MIN_FIRMWARE_LENGTH) {
		// sufficient size of length, now extract from the start onwards.
		printf("extracting the version info\n");
		
		strncpy(answer, result+START_OF_VERSION_INFO,max_length-1);
		printf("answer:%s\n", answer);
		status = EXIT_SUCCESS;
	}
    return status;
}

