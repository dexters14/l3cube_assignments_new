//Making Sense of Http Log File
//Group Id: 21
//Group Name: The Dexters


#include<string.h>
#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#define MAX 100

typedef struct log_data
{
	char remotehost[20], rfc931[2], authuser[2], date[30];
	char request[500], status[10], bytes[10];
	char referrer[500], platform[500];
}log_data;

typedef struct R_count
{
	char remotehost[20];
	int count;
}R_count;

void getdata();
void count();
void line();

FILE *p;
log_data LD[400];
int cnt=0;

void main()
{
	char c, s[MAX];
	//clrscr();
	p=fopen("WEBLOG.TXT", "r");

	if(p==NULL)
	{
		printf("\n\tError in opening source file..");
		//getch();
		exit(0);
	}

	getdata();
	//getch();
	printf("\n\tTotal Records:: %d", cnt);

	count();
	//getch();
}

void getdata()
{
	int i, j, k=0;
	char A[500];

	for(i=0; i<399; i++)
	{
		fgets(A, 500, p);
		j=0;

		/*Store RemoteHost...IP Address or host/subdomain name of the
		HTTP Client making the HTTP request*/
		while(isdigit(A[j]) || A[j]=='.')
			LD[i].remotehost[k++]=A[j++];
		k=0;

		while(isspace(A[j]))
			j++;

		/* rfc931...Identifier used to identify client
		   making HTTP request...if no value, "-" is used */
		while(!isspace(A[j]))
			LD[i].rfc931[k++]=A[j++];
		k=0;

		while(isspace(A[j]))
			j++;

		//username...
		while(!isspace(A[j]))
			LD[i].authuser[k++]=A[j++];
		k=0;

		//date & time...
		while(A[j]!='[')
			j++;
		while(A[j]!=']')
			LD[i].date[k++]=A[j++];
		LD[i].date[k]=A[j];
		k=0;

		//request...
		while(A[j]!='"')
			j++;
		LD[i].request[k++]=A[j++];
		while(A[j]!='"')
			LD[i].request[k++]=A[j++];
		LD[i].request[k]=A[j++];
		k=0;

		/*StatusCode...numeric code indicating sucess/failure of HTTP request*/
		while(isspace(A[j]))
			j++;
		while(isdigit(A[j]))
			LD[i].status[k++]=A[j++];
		k=0;

		/*Transffered Bytes...no of bytes transfered as a part of HTTP request,
		  not including HTTP header   */
		while(isspace(A[j]))
			j++;
		if(A[j]=='-')
			LD[i].bytes[0]='-';
		else
		{
			while(isdigit(A[j]))
				LD[i].bytes[k++]=A[j++];
		}
		k=0;

		//referrer... The URL which linked the user to site
		while(A[j]!='"')
			j++;
		LD[i].referrer[k++]=A[j++];
		while(A[j]!='"')
			LD[i].referrer[k++]=A[j++];
		LD[i].referrer[k]=A[j++];
		k=0;

		//Platform(Browser & OS)...used by visitor...
		while(A[j]!='"')
			j++;
		LD[i].platform[k++]=A[j++];
		while(A[j]!='"')
			LD[i].platform[k++]=A[j++];
		LD[i].platform[k]=A[j++];
		k=0;

		//getch();
		printf("\n\n%d\nRemotehost:\t %s\nRFC931:\t\t %s\nUsername:\t %s\nDate:\t\t %s\nRequest:\t %s",i+1,  LD[i].remotehost, LD[i].rfc931, LD[i].authuser, LD[i].date, LD[i].request);
		printf("\nStatus:\t\t %s\nBytes:\t\t %s\nReferrer:\t %s", LD[i].status, LD[i].bytes, LD[i].referrer);
		printf("\nPlatform:\t %s", LD[i].platform);
		
		cnt++;
		//sleep(1);
	}
}

void count()
{
	int i,j, tot_host=0;
	R_count S[400];

	for(i=0; i<399; i++)
		S[i].count=0;

	j=0;
	
	tot_host=0;
	for(i=0; i<399; i++)
	{
		for(j=0; j<tot_host; j++)
		{
			if(strcmp(S[j].remotehost, LD[i].remotehost)==0)
			{
				S[j].count++;
				break;
			}	
		}
		if(j==tot_host)
		{
			strcpy(S[j].remotehost, LD[i].remotehost);
			tot_host++;	
			S[j].count++;	
		}
	}

	printf("\n\n");
	line();
	printf("\nRemoteHost\t\tCount\n");
	line();
	for(j=0; j<tot_host; j++)
	{
		printf("\n%s\t\t%d",S[j].remotehost, S[j].count);
	}
	printf("\n");
	line();
	//getch();
}

void line()
{
	int i;
	for(i=0; i<80; i++)
		printf("_");
	printf("\n");
}
