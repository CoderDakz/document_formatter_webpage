#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <mysql/mysql.h>

#define MAX_QUERY 2048
#define HOSTNAME "dursley.socs.uoguelph.ca"
#define USERNAME "asadakho"
#define PASSWORD "0838002"
#define DATABASE "asadakho"

void error(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(1);
}


int main(int argc, char * argv[])
{
	
	if(argc != 2 && argc != 3)
	{
		exit(1);
	}
	
	/*ADD DATABASE ACCESSING FUNCTIONALITY*/
	
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	//MYSQL_FIELD *field;
	char query[MAX_QUERY];
	int s;
	
	query[0] = '\0';		
	/* 
		Connect to database server.
		Username and password must be filled in here.
		If no username or password is stored in DB then use NULL
	*/
			
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,DATABASE, 0, NULL, 0)) 
	{
		error("Could not connect to host.",&mysql);
	}
	
	
	if(strcmp(argv[1], "-clear") == 0 && argc == 2)
	{
		strcpy(query, "truncate table htmlList;");
		
		if(mysql_query(&mysql, query))
		{
			error("Could not insert record",&mysql);
		}
	}
	
	if(strcmp(argv[1], "-reset") == 0 && argc == 2)
	{
		strcpy(query, "drop table htmlList;");
		
		if(mysql_query(&mysql, query))
		{
			error("Could not insert record",&mysql);
		}
		
	}
	
	if(strcmp(argv[1], "-show") == 0 && argc == 2)
	{
		strcpy(query, "select fileSize, fileName, date_and_time from htmlList;");
		
		
		if(mysql_query(&mysql, query))
		{
			error("No records to show.",&mysql);
		}
		
		if (!(res = mysql_store_result(&mysql))){
			error("failed store 1",&mysql);
		}
				
			
		while ((row = mysql_fetch_row(res))) 
		{
			for (s=0; s < mysql_num_fields(res); s++)
			{
				printf("%s ", row[s]);
			}
			printf("\n");
		}
		
	}
	
	if(strcmp(argv[1], "-fNames") == 0 && argc == 2)
	{
		strcpy(query, "select fileName from htmlList;");
		
		if(mysql_query(&mysql, query))
		{
			//error("No records to show.",&mysql);
		}
		
		if (!(res = mysql_store_result(&mysql))){
			//error("failed store 1",&mysql);
		}
				
			
		while ((row = mysql_fetch_row(res))) 
		{
			for (s=0; s < mysql_num_fields(res); s++)
			{
				printf("%s ", row[s]);
			}
			//printf("\n");
		}
	}
	
	if(strcmp(argv[1], "-returnHtml") == 0 && argc == 3)
	{
		strcpy(query, "select htmlContent from htmlList where fileName = '");//;");
		char tempo[50];
		strcpy(tempo, argv[2]);
		int x=0;
		while(tempo[x] != '\0')
		{
			if(tempo[x] == '.')
			{
				tempo[x] = '\0';
				break;
			}
			x++;
		}
		
		strcat(query, tempo);
		strcat(query, "';");
		
		
		if(mysql_query(&mysql, query))
		{
			error("No records to show.",&mysql);
		}
		
		if (!(res = mysql_store_result(&mysql))){
			//error("failed store 1",&mysql);
		}
				
			
		while ((row = mysql_fetch_row(res))) 
		{
			for (s=0; s < mysql_num_fields(res); s++)
			{
				printf("%s ", row[s]);
			}
			//printf("\n");
		}
	}
	
	
	
	
	
	if(strcmp(argv[1], "-help") == 0)
	{
		printf("Enter <./db -clear> on cmd line to delete all tuples from the table.\n");
		printf("Enter <./db -reset> on cmd line to drop the table.\n");
		printf("Enter <./db -show> on cmd line to show the name, size and date for all files in the table.\n");
	}

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

	return 0;
}


