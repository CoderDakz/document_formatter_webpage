#include "listio.h"

struct returnStruct * buildHeader()
{
	struct returnStruct * returnVal = (struct returnStruct*)malloc(sizeof(struct returnStruct));
	if(returnVal == NULL)
	{
		return FAILURE;
	}
	
	struct dataHeader * headerHead = (struct dataHeader*)malloc(sizeof(struct dataHeader));
	if(headerHead == NULL)
	{
		return FAILURE;
	}

	/*initializing variables inside of struct*/
	headerHead->name = NULL;
	headerHead->length = 0;
	headerHead->next = NULL;
	
	returnVal->header = headerHead;
	if(headerHead == NULL)
	{
		returnVal->value = FAILURE;
	}
	else
	{
		returnVal->value = SUCCESS;
	}
	
	return returnVal;
}

int setName(struct dataHeader * header, char * name)
{
	if(header == NULL)
	{
		return FAILURE;
	}
	if(name == NULL)
	{
		return FAILURE;
	}
	
	/*assigning name value to header->name*/
	header->name = (char *)malloc(sizeof(char)* (strlen(name) + 1));
	strcpy(header->name, name);
	
	if(header->name == NULL)
	{
		return FAILURE;
	}
	else
	{
		return SUCCESS;
	}
	
}

char * getName(struct dataHeader * header)
{
	if(header == NULL)
	{
		return NULL;
	}
	if(header->name == NULL)
	{
		return NULL;
	}
	
	/*getting name value from header->name and returning it (could just return header->name instead of this extra code)*/
	char * name = (char*)malloc(sizeof(char)*strlen(header->name));
	if(name == NULL)
	{
		return FAILURE;
	}
	
	strcpy(name, header->name);
	
	if(strcmp(name, "") == 0)
	{
		return NULL;
	}
	
	else
	{
		return name;
	}
}

int getLength(struct dataHeader * header)
{
	if(header == NULL)
	{
		return FAILURE;
	}
	
	/*getting length value from header->length and returning it (could just return header->length instead of this extra code)*/
	int length = header->length;
	return length;
}

int addString(struct dataHeader * header, char * string)
{
	if(header == NULL)
	{
		return FAILURE;
	}
	if(string == NULL)
	{
		return FAILURE;
	}
	/*If there are no elements in the linked list (besides original header) program uses this if statement*/
	if(header->next == NULL)
	{
		/*creates & allocates memory for first element in linked list*/
		struct dataString * newString = (struct dataString*)malloc(sizeof(struct dataString));
		if(newString == NULL)
		{
			return FAILURE;
		}
		
		newString->string = (char*) malloc(sizeof(char) * (strlen(string) + 6));
		if(newString->string == NULL)
		{
			return FAILURE;
		}
		
		newString->next = NULL;
		
		/*copies the desired string into the linked list */
		strcpy(newString->string, string);
		
		/*Finds length of current string & updates sum length*/
		int strLength = strlen(newString->string);
		header->length = header->length+strLength;
		
		/*sets first element of the list to be the newly created newString structure value*/
		header->next = newString;
		
		return SUCCESS;
	}
	/*Runs this block of code if the first element in the linked list has already been created*/
	else 
	{
		/*initializes & allocates memory for new element in linked list (and sets it's string value to be equal to 
		  the string sent)*/
		struct dataString * newString = (struct dataString*)malloc(sizeof(struct dataString));
		if(newString == NULL)
		{
			return FAILURE;
		}
		
		newString->string = (char*)malloc(sizeof(char)* (strlen(string) + 6));
		if(newString->string == NULL)
		{
			return FAILURE;
		}
		
		newString->next = NULL;
		strcpy(newString->string,string);
		
		
		struct dataString * temp = header->next;
		/*moving to end of list*/
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		/*Finds length of current string & updates sum length*/
		int strLength = strlen(newString->string);
		header->length = header->length+strLength;
		
		/*adds newly created element to the end of the linked list*/
		temp->next = newString;
		
		return SUCCESS;
	}
}

int printString(struct dataHeader * header)
{
	if(header != NULL)
	{
		struct dataString * temp = header->next;
		/*starting at first element in the list, prints current element and moves through list printing every string*/
		while(temp != NULL)
		{
			printf("%s\n", temp->string);
			temp = temp->next;
		}
		return SUCCESS;
	}
	
	else 
	{
		return FAILURE;
	}
	
}

int processStrings(struct dataHeader * header, int dbBool)
{
	
	if(header != NULL)
	{
		
		struct dataString * temp = header->next;
		
		if(temp == NULL)
		{
			return FAILURE;
		}
		
		/*MY CURRENT PLAN:  parse through entire string, char by char, until reaching '\0',
		                    if char == ' ' (space or a tab), check next char in the string 
		                    to see if it is a space or a tab. If so, remove extra spaces/tabs
		                    and move all following characters in the string back based on how ever many
		                    spaces or tabs I removed. Then continue parsing through string and repeat if
		                    it finds more of the same. 
		                    Once reaching new line or carriage return, replace with <BR>. If there are
		                    multiple consecutive \n or \r then replace all of them with <P>.
		                    AFTER ALL OF THAT, before continuing to next node in linked list, take the
		                    updated length of the whole string and add it to headerLength value.*/
		
		
		/*A2: PROCESSING PLAN
		           - If there is a <BR> or a <P>, AND there is whitespace after (\t or " ")
		             then another <BR> or <P>, get rid of whitespace & remove one of the <BR> or 
		             <P> tags and shift string accordingly.
		           - Once done all processing in current string, need to check last 3 chars to see
		             if they are "<P>" or whitespace. If whitespace, check previous chars until seeing
		             one that isn't whitespace, and check to see if the last 3 chars (that aren't
		             whitespace) are "<P>".   If yes, check first chars of next string (same thing 
		             with whitespaces, if they are whitespace then move forward until reaching chars
		             that aren't whitespace and check if they are "<P>") to see if they are <P> and 
		             if both last chars in last string are  */
		
		/*First we set the total length back to 0 because we are going to be recalculating it here*/
		header->length = 0;
		
		
		int currentLoc = 0;
		int locCounter = 0;
		int spaceCounter = 0;
		int tabCounter = 0;
		int newLineCounter = 0;
		int i = 0;
		
		/*int whiteRemoveCount = 0;
		int ptagCounter = 0;*/
		
		while(temp!= NULL)
		{
			/*while loop checking to see if current location in character array is the null terminator
			  aka end of the string.*/
			
			if (temp->string == NULL)
			{
				return FAILURE;
			}

			while(temp->string[currentLoc] != '\0')
			{
				newLineCounter = 0;
				spaceCounter = 0;
				tabCounter = 0;
				/*while loop used for checking if current (and next consecutive) location(s) in character array
				  are a space or a tab*/
				while(temp->string[currentLoc+spaceCounter] == ' ' || temp->string[currentLoc+tabCounter] == '\t' ||
				      temp->string[currentLoc+newLineCounter] == '\n' || temp->string[currentLoc+newLineCounter] == '\r')
				{
					if(temp->string[currentLoc+spaceCounter] == ' ')
					{
						spaceCounter++;
					}
					if(temp->string[currentLoc+tabCounter] == '\t')
					{
						tabCounter++;
					}
					if(temp->string[currentLoc+newLineCounter] == '\n' || temp->string[currentLoc+newLineCounter] == '\r')
					{
						newLineCounter++;
					}
				}
				/*Next blocks of code are checking to see if there were more than one consecutive space/tab/newline/carriage 
				return. If so, process the string by moving every character in the rest of the array back however 
				many spaces necessary,OR by altering string to have <BR> or <P> then continue moving through the string.*/
				if(spaceCounter > 1)
				{				
					int length = strlen(temp->string);
					locCounter = currentLoc;
					for(i = locCounter+spaceCounter; i != length; i++)
					{
						temp->string[locCounter+1] = temp->string[i];
						locCounter++;
					}

					length = strlen(temp->string);
					/*When string is processed, it leaves the old values at the end of string. This next for loop
					  places null terminator in correct location at end of newly processed string*/
					for(i= length; i > (length-spaceCounter)+1; i--)
					{
					}
					
					temp->string[i] = '\0';
					
					temp->string = realloc(temp->string, sizeof(char)*(length + 10));

					if(temp->string == NULL)
					{
						return FAILURE;
					}
					currentLoc = -1;
				}
				
				if(tabCounter > 1)
				{				
					locCounter = currentLoc;

					int length = strlen(temp->string);

					for(i = locCounter+tabCounter; i != length; i++)
					{
						temp->string[locCounter+1] = temp->string[i];
						locCounter++;
					}

					length = strlen(temp->string);
					/*When string is processed, it leaves the old values at the end of string. This next for loop
					  places null terminator in correct location at end of newly processed string*/
					for(i= length; i > (length-tabCounter)+1; i--)
					{
					}
					temp->string[i] = '\0';
					
					temp->string = (char*)realloc(temp->string, sizeof(char)*(length + 6));

					if(temp->string == NULL)
					{
						return FAILURE;
					}
					currentLoc = -1;
				}
				
				/*If statement to change a single \n or \r to <BR>*/
				if(newLineCounter == 1)
				{
					int length = strlen(temp->string);
					temp->string = (char*)realloc(temp->string, sizeof(char)*(length+6));

					if(temp->string == NULL)
					{
						return FAILURE;
					}
					
					locCounter = currentLoc;

					length = strlen(temp->string);
					/*loop starting at last character in string and shifting right 3 to make space for <BR>*/

					for(i = length - 1; i != currentLoc; i--)
					{
						temp->string[i+3] = temp->string[i];
					}
					/*For loop to add '<BR>' into string*/
					for(i = currentLoc; i != currentLoc + 4; i++)
					{
						if(i == currentLoc)
						{
							temp->string[i] = '<';
						}
						if(i == currentLoc+1)
						{
							temp->string[i] = 'B';
						}
						if(i == currentLoc+2)
						{
							temp->string[i] = 'R';
						}
						if(i == currentLoc+3)
						{
							temp->string[i] = '>';
						}
					}
					temp->string[i] = '\0';

					length = strlen(temp->string);

					temp->string[length] = '\0';
					
					length = strlen(temp->string);

					temp->string = (char*)realloc(temp->string, sizeof(char)* (length + 6));

					if(temp->string == NULL)
					{
						return FAILURE;
					}
					currentLoc = -1;
				}
				
				/*If statement to change multiple consecutive \n or \r to <P>*/
				if(newLineCounter > 1)
				{
					int length = strlen(temp->string);
					temp->string = (char*)realloc(temp->string, sizeof(char)*(length+6-newLineCounter));

					//printf("%d\n",newLineCounter);
					if(temp->string == NULL)
					{
						return FAILURE;
					}
					
					locCounter = currentLoc;
					for(i = length - 1; i != currentLoc; i--)
					{
						temp->string[i+3-newLineCounter] = temp->string[i];
					}
					/*For loop to add '<P>' into string*/
					for(i = currentLoc; i != currentLoc + 3 ;i++)
					{
						if(i == currentLoc)
						{
							temp->string[i] = '<';
						}
						if(i == currentLoc+1)
						{
							temp->string[i] = 'P';
						}
						if(i == currentLoc+2)
						{
							temp->string[i] = '>';
						}
					}
					//int tempVar = strlen(temp->string);
					//printf("\n%d %s\n", tempVar, temp->string);

					length = strlen(temp->string);
					temp->string[length] = '\0'; 
					
					length = strlen(temp->string);
					temp->string = (char*)realloc(temp->string, sizeof(char)* (length + 6));
					if(temp->string == NULL)
					{
						return FAILURE;
					}
					currentLoc = -1;
				}
				
				/*resetting a few variables here for next index location in string*/
				locCounter = 0;
				spaceCounter = 0;
				tabCounter = 0;
				newLineCounter= 0;
				++currentLoc;
				
			}
			
			//printString(header);
			/*Once this string is done processing, REPROCESS IT to run through it again and this time
			  check to see if there are whitespaces in between the <P>'s inside of a string.
			  for ex. "string<P> <P>" should turn into string<P>*/
			currentLoc = 0;
			while(temp->string[currentLoc] != '\0')
			{
				/*if statement to check if reached a <P>*/
				if(temp->string[currentLoc] == '<' && temp->string[currentLoc+1] == 'P' &&
				temp->string[currentLoc+2] == '>')
				{
					/*Checking if next spot after is '\t' or ' '*/
					if(temp->string[currentLoc+3] == ' ' || temp->string[currentLoc+3] == '\t')
				   	{
					   	/*Checking to see if there's another '<P>' after the space. If yes, shift
						  string back to remove currentLoc+3 to currentLoc+6*/
						if(temp->string[currentLoc+4] == '<' && temp->string[currentLoc+5] == 'P' &&
			               temp->string[currentLoc+6] == '>')
						{
						   	locCounter = currentLoc;
							    
							int length = strlen(temp->string);

						    for(i = locCounter+7; i != length; i++)
						    {
								temp->string[locCounter+3] = temp->string[i];
								locCounter++;
							}
								
							length = strlen(temp->string);

						    for(i= length; i > (length-4); i--)
							{
							}
							temp->string[i] = '\0';

							temp->string = (char*)realloc(temp->string, sizeof(char)*(i + 6));
							if(temp->string == NULL)
							{
								return FAILURE;
							}
						    currentLoc = -1;
					    }
					    else if(temp->string[currentLoc+4] == '<' && temp->string[currentLoc+5] == 'B' && temp->string[currentLoc+6] == 'R' &&
			                    temp->string[currentLoc+7] == '>')
						{
							locCounter = currentLoc;
							
							int length = strlen(temp->string);

							for (i = locCounter+8; i != length; i++)
							{
								temp->string[locCounter+3] = temp->string[i];
								locCounter++;
							}
								

							for(i = length; i > (length-5); i--)
							{
							}

							temp->string[i] = '\0';

							temp->string = (char*)realloc(temp->string, sizeof(char)*(i + 6));
							if(temp->string == NULL)
							{
								return FAILURE;
							}
							currentLoc = -1;
						}
					    
					}
					
				}
				
				if(temp->string[currentLoc] == '<' && temp->string[currentLoc+1] == 'B' && temp->string[currentLoc+2] == 'R' &&
			       temp->string[currentLoc+3] == '>')
			       {
						if(temp->string[currentLoc+4] == ' ' || temp->string[currentLoc+4] == '\t')
						{
							if(temp->string[currentLoc+5] == '<' && temp->string[currentLoc+6] == 'P' &&
							temp->string[currentLoc+7] == '>')
							{
								locCounter = currentLoc;

								int length = strlen(temp->string);
							    
								for(i = locCounter+5; i != length; i++)
								{
									temp->string[locCounter] = temp->string[i];
									locCounter++;
								}
								
								for(i= length; i > (length-5); i--)
								{
								}
								temp->string[i] = '\0';
								temp->string = (char*)realloc(temp->string, sizeof(char)*(i + 6));
								if(temp->string == NULL)
								{
									return FAILURE;
								}
								currentLoc = -1;
							}
							
							else if(temp->string[currentLoc+5] == '<' && temp->string[currentLoc+6] == 'B' && temp->string[currentLoc+7] == 'R' &&
			                    temp->string[currentLoc+8] == '>')
							{
								
								for(i = currentLoc; i != currentLoc + 3; i++)
								{
									if(i == currentLoc)
									{
										temp->string[i] = '<';
									}
									if(i == currentLoc+1)
									{
										temp->string[i] = 'P';
									}
									if(i == currentLoc+2)
									{
										temp->string[i] = '>';
									}
								}
									
								locCounter = currentLoc;
								
								int length = strlen(temp->string);

								for (i = locCounter+9; i != length; i++)
								{
									temp->string[locCounter+3] = temp->string[i];
									locCounter++;
								}
								
								for(i = length; i > (length-6); i--)
								{
								}
								temp->string[i] = '\0';
								temp->string = (char*)realloc(temp->string, sizeof(char)*(i + 6));
								if(temp->string == NULL)
								{
									return FAILURE;
								}
								currentLoc = -1;
							}
						}
					   
				   }
				
				currentLoc++;
			}
			/*resetting currentLoc for next string & moving to next  */
			currentLoc = 0;
			temp = temp->next;
		}
		
		/*resetting temp to beginning of list again to reprocess list now*/
		temp = header->next;
		int shifter = 0;
		int lenVal= 0;
		
		while(temp != NULL)
		{
			currentLoc = 0;
			locCounter = 0;
			
			int length = strlen(temp->string);
			i = length - 1; 		
			/*Checking to see if last char in string is space or tab, if so then decrement
			  i by 1 and continue checking*/
			while(temp->string[i] == ' ' || temp->string[i] == '\t')
			{
				i--;
			}
			
				
			/*Checking to see if end of string is <P> and if so, check beginning of next string*/
			if(temp->string[i-2] == '<' && temp->string[i-1] == 'P' && temp->string[i] == '>')
			{
				i=0;
				shifter = 0;
				temp = temp->next;/*DEFENSIVE CODE!!!!!!!!!!!!!!!!! VS temp != NULL*/
				if(temp == NULL)
				{
					break;
				}
				
				while(temp->string[i] == ' ' || temp->string[i] == '\t')
				{
					i++;/*keep track of how many spots to shift left if needed*/
					shifter++;
				}
				
				if(temp->string[i] == '<' && temp->string[i+1] == 'P' && temp->string[i+2] == '>')
				{
					lenVal = strlen(temp->string);
					for(i = i; i != lenVal - 1; i++)
					{
						temp->string[shifter] = temp->string[i+3];
						shifter++;
					}

					int length = strlen(temp->string);
					for(i= length; i != (length-spaceCounter); i--)
					{
					}
					temp->string[i] = '\0';
					//temp = header->next; /*resetting to go through all strings again*/
				}
				else
				{
					temp = temp->next;
				}
			}
			else
			{
				temp=temp->next;
			}	
			currentLoc = 0;
		}
		
		/*Code to check for multiple consecutive <BR>'s over different strings*/
		temp = header->next;
		shifter = 0;
		lenVal = 0;
		int tempCounter = 0;
		int looper = 0;
		struct dataString * tmpHolder;
		
		while(temp != NULL)
		{
			temp = header->next; /*start from beginning every time*/
			currentLoc = 0;
			locCounter = 0;
			looper = 0;
			
			while(looper != tempCounter) /*loop to return to desired node in list*/
			{
				temp = temp->next;
				looper++;
			}
			
			int length = strlen(temp->string);
			i = length - 1; /*setting i to be equal to index of last char in string (before '\0')*/ 
			
			while(temp->string[i] == ' ' || temp->string[i] == '\t') /*decrement i until reaching something besides space*/
			{
				i--;
			}
			
			/*checking end of string for <BR>*/
			if(temp->string[i-3] == '<' && temp->string[i-2] == 'B' && temp->string[i-1] == 'R' && temp->string[i] == '>')
			{
				i = 0;
				temp = temp->next;
				if(temp == NULL)
				{
					break;
				}
				
				while(temp->string[i] == ' ' || temp->string[i] == '\t')
				{
					i++;/*keep track of how many spots to shift left if needed*/
					shifter++;
				}
				
				
				if(temp->string[i] == '<' && temp->string[i+1] == 'B' && temp->string[i+2] == 'R' && temp->string[i+3] == '>')
				{
					/*check to see if string is ONLY a BR (or P) and if so, delete it*/
					if(temp->string[i+4] == '\0')
					{
						looper = 0;
						temp = header->next;
						while(looper != tempCounter) /*loop to return to desired node in list*/
						{
							temp = temp->next;
							looper++;
						}
						tmpHolder = temp->next;
						temp->next = temp->next->next;
						free(tmpHolder->string);
						free(tmpHolder);
						
						int length = strlen(temp->string);
						i = length - 1;
						
						temp->string[i-2] = 'P';
						temp->string[i-1] = '>';
						temp->string[i] = '\0';
						
						length = strlen(temp->string);

						temp->string = realloc(temp->string, sizeof(char)* (length + 6));
						
						temp = header->next; /*resetting*/
						tempCounter = 0; /*resetting*/
					}
					else
					{
						temp = temp->next;
					}
				}
			}
			
			/*Checking end of string for <P>*/
			if(temp->string[i] == '<' && temp->string[i+1] == 'P' && temp->string[i+2] == '>')
			{
				i = 0;
				temp = temp->next;
				if(temp == NULL)
				{
					break;
				}
				
				while(temp->string[i] == ' ' || temp->string[i] == '\t')
				{
					i++;/*keep track of how many spots to shift left if needed*/
					shifter++;
				}
				if(temp->string[i] == '<' && temp->string[i+1] == 'B' && temp->string[i+2] == 'R' && temp->string[i+3] == '>')
				{
					/*check to see if string is ONLY a BR (or P) and if so, delete it*/
					if(temp->string[i+4] == '\0')
					{
						looper = 0;
						temp = header->next;
						while(looper != tempCounter) /*loop to return to desired node in list*/
						{
							temp = temp->next;
							looper++;
						}
						tmpHolder = temp->next;
						temp->next = temp->next->next;
						free(tmpHolder->string);
						free(tmpHolder);
						
						temp = header->next; /*resetting*/
						tempCounter = 0; /*resetting*/
					}
					else
					{
						temp = temp->next;
					}
				}
			}
			
			//temp = temp->next;
			tempCounter++;
			
		}
		
		
		
		
		/*calculating length here*/
		temp = header->next;
	
		while(temp != NULL)
		{	
			int length = strlen(temp->string);
			header->length = length + header->length;
			temp = temp->next;
		}
		
		/*appending strings to become 1*/
		
		char * newString;// = (char*)malloc(sizeof(char)*(header->length + 6));
		newString = appendStrings(header);
		
		/*WRITE TO MKFIFO HERE*/
		
		
		FILE * py = popen("python a4.py","r");
		if(py == NULL)
		{
			return FAILURE;
		}
		
		temp = header->next;
		
		FILE * mf;
		
		mf = fopen("./files/firstFile", "w");
		
		fprintf(mf,"%s\n", header->name);
		fprintf(mf, "%s", newString);
		fclose(mf);
		
		char printMe;
		
		mkfifo("./files/secondFile", 0777);
		mf = fopen("./files/secondFile", "r");
		
		//char returnedStr[10000];
		int addCharCount = 0;
		while((printMe = getc(mf)) != EOF)
		{
			putchar(printMe);
			//returnedStr[addCharCount] = printMe; /*DOESNT WORK FOR SUPER LARGE FILES*/
			addCharCount++;
		}
		
		fclose(mf);
		
		
		remove("./files/secondFile");
		
		pclose(py);
		
		
		
		
		
		/*Write functionality to open and read newly created html file into a string so it can be
		 * sent to SQL*/
		
		int length = strlen(header->name);
		int x;	
		int r = 0;
		char tempy[25];
		int fileSize = 0;
		strcpy(tempy, header->name);
		
		strcat(tempy,".html");
		
		char htmlContent[5000];
		htmlContent[0] = '\0';
		if(access(tempy, F_OK) != -1)
		{
			FILE * html = fopen(tempy, "r");
			
			fseek(html, 0L, SEEK_END);
			fileSize = ftell(html);
			fseek(html, 0L, SEEK_SET);
			
			int compareVal = 0;
			char tempGrab[5000];
			
			
			while(fgets(tempGrab, sizeof(tempGrab), html))
			{
				if(compareVal == 0)
				{
					strcpy(htmlContent, tempGrab);
					compareVal++;
				}
				
				if(compareVal != 0)
				{
					strcat(htmlContent, tempGrab);
				}
			}
			//printf("%s\n", htmlContent);
			
			fclose(html);
		}
		
		
		
		
		if(dbBool == 1)
		{
			MYSQL mysql;
			/*MYSQL_RES *res;
			MYSQL_ROW row;*/
			//MYSQL_FIELD *field;
			char query[MAX_QUERY];
			
			/* 
				Connect to database server.
				Username and password must be filled in here.
				If no username or password is stored in DB then use NULL.
			*/
			
			mysql_init(&mysql);
			mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
			if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,
				DATABASE, 0, NULL, 0)) {
			   error("Could not connect to host.",&mysql);
			}

			/*
				Build query
			*/
			
			clrstr(query);
			strcat(query, "create table if not exists htmlList (htmlContent text(60000) not null,");
			strcat(query, "fileSize int,");
			strcat(query, "fileName char(50) not null,");
			strcat(query, "date_and_time timestamp,");
			strcat(query, "primary key(fileName) )");
			
			/*
				Create htmlList table
			*/
			if(mysql_query(&mysql, query))
			{
			  error("Could not create table!",&mysql);
			}
			
			clrstr(query);
			
			/*
				Insert a records into the students table
			*/
			
			
			/*
			for(x = 0; x < 3; x++){
				if(mysql_query(&mysql, records[x])){
					printf("Failure to insert: %s\n",records[x]);
					error("Could not insert record",&mysql);
				}
			}*/
			
			
			char inserter[6000] = {"insert into htmlList values ('"};//11',5,'"};//Victor','B+')"};
			strcat(inserter, htmlContent);
			strcat(inserter, "', ");//5,'");
			char tempStr[15];
			sprintf(tempStr, "%d", fileSize);
			strcat(inserter, tempStr);
			strcat(inserter, ",'");
			
			
			tempy[0] = '\0';
			
			r = 0;
			
			length = strlen(header->name);
			
			for(x=8;x<length;x++)
			{
				tempy[r] = header->name[x];
				r++;
			}
			tempy[r] = '\0';
			
			x =0;
			
			while(tempy[x] != '\0')
			{
				if(tempy[x] == '.')
				{
					tempy[x] = '\0';
					break;
				}
				x++;
			}
			
			
			strcat(inserter, tempy);
			strcat(inserter, "', NOW())");
			
			//sprintf(inserter, "insert into htmlList values (10, 5, '%s', '1995-11-23')", header->name);
			
			
			if(mysql_query(&mysql, inserter))
			{
				error("Could not insert record",&mysql);
			}
			/*
				Store results from query into res structure.
			*/
			/*
			if (!(res = mysql_store_result(&mysql)))
			{
				error("failed store 1",&mysql);
			}
			*/
			/*
				print first row elements
			*//*
			while ((row = mysql_fetch_row(res))) {
				printf("%s ", row[0]);
			}
			
			printf("\n");
			*/
			/*
				second query
			*//*
			strcpy(query, "select * from students order by last_name");
			
			if(mysql_query(&mysql, query)){
				error("fail select 2",&mysql);
			}
			*/
			/*
				Store results from query into res structure.
			*//*
			if (!(res = mysql_store_result(&mysql))){
				error("fail store 2",&mysql);
			}*/

			/*
				print all results
			*/
			/*
			while ((row = mysql_fetch_row(res))) {
				for (i=0; s < mysql_num_fields(res); s++){
					printf("%s ", row[s]);
				}
				printf("\n");
			}
			*/
			/*
				Drop the students table
			*/
			/*
			strcpy(query, "drop table students");
			
			if(mysql_query(&mysql,query))
			  error("fail drop 1",&mysql);
			*/
			/*
				Finally close connection to server
			*/
			mysql_close(&mysql);

			//printf("All done\n");
		}
		
		
		free(newString);
		
		
		return SUCCESS;
	}
	
	else 
	{
		return FAILURE;
	}
}

int freeStructure(struct dataHeader * header)
{	
	if(header != NULL)
	{
		struct dataString * temp = header->next;	
		/*Loop until first element in list has been freed*/
		
		while(header->next != NULL)
		{
			if(temp->next == NULL)
			{
				free(header->next->string);
				header->next->string = NULL;
				free(header->next);
				header->next = NULL;
				break;
			}
			/*Check to see if we are at the second last node, if so, then free all malloced values and then the ptr*/
			if(temp->next->next == NULL)
			{
				free(temp->next->string);

				temp->next->string = NULL;
				free(temp->next);
				temp->next = NULL;
				temp = header->next;
			}
			/*not at second last node so continue moving through list*/
			else
			{
				temp = temp->next;
			}
			/*if at the last node in list, free it by using header free(struct->next)*/
		}
		
		/*Once entire list has been freed, free header*/
		if(header->next == NULL)
		{
			free(header->name);

			header->name = NULL;
			header->length = 0;
			free(header);
			header = NULL; 
			// printf("\nHeader has been freed!\n");
			return SUCCESS;
		}
		else
		{
			return FAILURE;
		}
	}
	
		else 
	{
		return FAILURE;
	}
}

int writeStrings(char * filename, struct dataHeader * header)
{
	if(filename == NULL)
	{
		return FAILURE;
	}
	if(header == NULL)
	{
		return FAILURE;
	}
	
	
	FILE * fp;
	int nameLength = 0;
	
	struct dataString * temp = header->next;
	int stringLength = 0;
	
	fp = fopen( filename , "wb");
	nameLength = strlen(header->name) + 1; /*Have +1 here to account for null terminator '\0'*/
	fwrite(&nameLength, sizeof(int), 1, fp); /*Writing length of the name string to file*/
	
	fwrite(header->name, sizeof(char), strlen(header->name)+1, fp); 
	
	fwrite(&header->length, sizeof(int), 1 , fp); /*Writes current header->length into file*/
	
	while(temp != NULL) /*LOOPING until the current node in the list we are on is NULL*/
	{
		stringLength = strlen(temp->string) + 1; /*Grabs the current strings length (adds one to account for null terminator)*/
		fwrite(&stringLength, sizeof(int), 1, fp); /*writes length to bin file*/ 
		
		fwrite(temp->string, sizeof(char), strlen(temp->string)+1, fp); /*WRites string to file after writing string length*/
		
		temp = temp->next; /*Moves to next node in the list*/
	}
	fclose(fp);
	
	return SUCCESS;
}


struct returnStruct * readStrings(char * filename)
{
	
	struct returnStruct * returnCheck = buildHeader();
	struct dataHeader * tmpHead;
	
	if(returnCheck->value == SUCCESS)
	{
		tmpHead = returnCheck->header;
	}
	else
	{
		tmpHead = NULL;
	}

	if(access(filename, F_OK) != -1) /*CHECKING TO SEE IF FILE EXISTS*/
	{	
		FILE * fp;
	
		int nameLength = 0;
		int stringLength = 0;
		int totalLength = 0;
	
		char * tempString = (char*)malloc(sizeof(char)); /*Just initializing tempString here with size of 1 char*/
	
		fp = fopen( filename , "rb");
		
		 /*THIS BLOCK OF CODE CHECKING IF FILE HAS LENGTH OF 0*/
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		fseek(fp, 0 , SEEK_SET);
		if(fileSize == 0)
		{
			returnCheck->value = FAILURE;
			return returnCheck;
		}
		
		
		fread(&nameLength, sizeof(int), 1, fp); /*Reading length of name of the header*/
	
		char nameString[nameLength-1]; /*Declaring char array to temporarily hold the name of header*/
		fread(nameString, sizeof(char), nameLength, fp); /*Reading the name string into a temp char array*/
		nameString[nameLength-1] = '\0'; 
	
		setName(tmpHead, nameString); /*Assigning the name string to new dataHeader structure */
	
		/*fread(&tmpHead->length, sizeof(int), 1, fp);*/ /*Reading (and writing) length value directly from file into header struct*/
		fread(&totalLength, sizeof(int), 1, fp); /*Reading total Length into a variable (not assigning to tmpHead->length)*/
	
		while(fread(&stringLength, sizeof(int),1,fp) == 1) /*Looping until error OR end of file (checking if num val is correct)*/
		{
			tempString = (char *)realloc(tempString, sizeof(char)* (stringLength + 6));
			if(fread(tempString, sizeof(char), stringLength, fp) == stringLength)
			{
				tempString[stringLength-1] = '\0';
				addString(tmpHead, tempString);
			}
		}
	
		fclose(fp);
	
		returnCheck->header = tmpHead;
		returnCheck->value = SUCCESS;
		return returnCheck;
	}
	
	else
	{
		returnCheck->value = FAILURE;
		return returnCheck;
	}
}

struct returnStruct * readTextFile(char * filename)
{
	struct returnStruct * returnCheck = buildHeader();
	struct dataHeader * tmpHead;
	
	if(returnCheck->value == SUCCESS)
	{
		tmpHead = returnCheck->header;
	}
	else
	{
		tmpHead = NULL;
	}
	if(access(filename, F_OK) != -1) /*CHECKING TO SEE IF FILE EXISTS*/
	{	

		FILE * fp;		
		
		fp = fopen( filename , "r");
		
		 /*THIS BLOCK OF CODE CHECKING IF FILE HAS LENGTH OF 0*/
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		fseek(fp, 0 , SEEK_SET);
		if(fileSize == 0)
		{
			returnCheck->value = FAILURE;
			return returnCheck;
		}
		
		char stringBuff[1024];
		
		while(fgets(stringBuff, sizeof(stringBuff), fp))
		{
			
			// printf("%s", stringBuff);
			addString(tmpHead,stringBuff);
		}
		
	
		fclose(fp);
	
		returnCheck->header = tmpHead;
		returnCheck->value = SUCCESS;
		return returnCheck;
	}
	
	else
	{
		
		returnCheck->value = FAILURE;
		return returnCheck;
	}
	
}

char * appendStrings(struct dataHeader * header)
{
	struct dataString * temp = header->next;
	char * newString = (char*)malloc(sizeof(char)*(header->length + 6));
	strcpy(newString,temp->string);
	temp = temp->next;
	while(temp != NULL)
	{
		strcat(newString, temp->string);
		
		temp = temp->next;
	}
	
	return newString;
}

/*
	standard error clause.
*/
void error(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(1);
}


/*
	clear the contents of an array of char's
*/
void clrstr(char *buf){
	buf[0] = '\0';
}

