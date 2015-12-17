
// MD2 View

// Written by William Chin
// Developed in MSDEV C++ v6.0 using the DirectX 7.0a SDK
// Date : 16th May 2000
// File : debug.cpp

// Website: http://members.aol.com/billybop7
// Email:  billybop7@aol.com 

#define STRICT
#include <stdio.h>
#include "Debug.hpp"


int PrintMsgX = 10;
int PrintMsgY = 10;
char itoabuffer[256];

BOOL logfile_start_flag = TRUE;



char *ITOA(int x)
{
	itoa(x, itoabuffer, 10);
	return itoabuffer;
}

void PrintMessage(char *message1, char *message2)
{
	FILE *fp;
	char tmessage[100];


	if((message1 == NULL) && (message2 == NULL))
		return;

	if((message1 != NULL) && (message2 != NULL))
	{
		strcpy(tmessage, message1);
		strcat(tmessage, " ");
		strcat(tmessage, message2);
	}
	else
	{
		if(message1 != NULL) 
			strcpy(tmessage, message1);

		if(message2 != NULL) 
			strcpy(tmessage, message2);
	}


	if(logfile_start_flag == TRUE)
	{
		fp = fopen("AppLogfile.txt","w");
		fprintf( fp, "%s\n\n", "MD2 View Logfile");
	}
	else
		fp = fopen("AppLogfile.txt","a");

	logfile_start_flag = FALSE;
    
	if(fp == NULL)
    {     
		fclose(fp);
		return;
	}

	fprintf( fp, " %s\n", tmessage );
	
	fclose(fp);
	
}


