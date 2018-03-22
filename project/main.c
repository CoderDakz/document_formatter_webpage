#include "listio.h"

int main(int argc, char *argv[]) 
{
	
	int successCheck = 0;
	int dbCheck = 0;
	
	struct returnStruct * returner = buildHeader();
	struct dataHeader * head;
	if(returner->value == SUCCESS) /*WRITE A FUNCTION FOR THIS (to clean up main)*/
	{
		head = returner->header;
	}
	else
	{
		head = NULL;
	}
	
	if(argc != 2 && argc != 3)
	{
		exit(1);
	}
	
	if(argc == 2)
	{
		dbCheck = 0;
	}
	
	if(argc == 3)
	{
		if(strcmp(argv[2], "1") == 0)
		{
			dbCheck = 1;
		}
		if(strcmp(argv[2], "0") == 0)
		{
			dbCheck = 0;
		}
		/*if(strcmp(argv[2], "0") != 0 && strcmp(argv[2], "1") != 0)
		{
			exit(1);
		}*/
	}
	
	char htmlCheck[100];
	strcpy(htmlCheck, argv[1]);
	strcat(htmlCheck, ".html");
	
	int fileTypeCheck = strlen(htmlCheck) - 1;
	successCheck = freeStructure(head);
	//free(returner->header);
	free(returner);
	
	if(access(htmlCheck,F_OK) != -1)
	{
		   /*Code to print out html file is going to go here*/
		   /*Either use modified readStrings func OR write a new function to quickly read a text file*/
		   
		char printChar;
		FILE * htmlFile;
		htmlFile = fopen(htmlCheck, "r");
		while((printChar = getc(htmlFile)) != EOF)
		{
			putchar(printChar);
		}
		
		fclose(htmlFile);
		
	}
	else
	{
		/*I NEED TO CODE STILL TO ACCEPT EITHER <filename> or <filename>.txt*/
		
		returner = readTextFile(argv[1]); 
		
		if(returner->value == 1)
		{
			head = returner->header;
		}
		else
		{
			head = NULL;
		}
		
		successCheck = setName(head, argv[1]);
		
		successCheck = processStrings(head, dbCheck);
		
		successCheck = freeStructure(head);
		//free(returner->header);
		free(returner);
	}
	printf("\n");
	
	
	
	return 0;
}
