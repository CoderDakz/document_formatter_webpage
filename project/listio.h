#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mysql/mysql.h>


#define FAILURE 0
#define SUCCESS 1
#define MAX_QUERY 65000
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "asadakho"
#define PASSWORD "0838002"
#define DATABASE "asadakho"

struct dataString
{
	char * string;
	struct dataString * next;
};

struct dataHeader
{
	char * name;
	int length;
	struct dataString * next;
};

struct returnStruct
{
	int value;
	struct dataHeader * header;
};

struct returnStruct * buildHeader(); /*Mallocs the header struct*/
int setName(struct dataHeader * header, char * name); /*Assigns name to header*/
char * getName(struct dataHeader * header); /*Returns header's name value*/
int getLength(struct dataHeader * header); /*Returns the length value from header*/
int addString(struct dataHeader * header, char * string); /*adds a new string to the dataString linked list*/
int printString(struct dataHeader * header); /*Prints off all the strings attached to header*/
int processStrings(struct dataHeader * header, int dbBool); /*Replaces multiple consecutive spaces and/or tabs with only one,
Replaces \n or \r (carriage return) with <BR>, Replaces multiple consecutive new Line/Carriage returns with <P>*/
/*MAKE SURE YOU ALTER THE LENGTH AFTER STRINGS HAVE BEEN PROCESSED, AND PAY ATTENTION TO HOW THE LENGTH AND ACTUAL
STRINGS CHANGE (ex. \n COUNTS AS 1 CHAR BUT <BR> COUNTS AS 4, \n\n COUNTS AS 2 AND <P> COUNTS AS 3*/
int freeStructure(struct dataHeader * header); /*Frees EVERYTHING malloced, starting from end of dataString and working
back until reaching header*/ 
int writeStrings(char * filename, struct dataHeader * header); /*Writes header and entire dataString list to a binary file*/
struct returnStruct * readStrings(char * filename); /*Reads the linked list structure from a file created using writeStrings()
& rebuilds the linked list that is stored in the file*/
struct returnStruct * readTextFile(char * filename); /*FOR A2: Used to read in entire text file and input them into 
text file*/
char * appendStrings(struct dataHeader * header);
void error(char *msg, MYSQL *mysql);
void clrstr(char *buf);


