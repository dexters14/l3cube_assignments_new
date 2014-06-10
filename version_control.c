//Version Control 
//Group Id: 21
//Group Name: The Dexters

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <time.h>

char * get_file_name(char original_name[],int version);
char * remove_txt(char * original_name);
char * make_new_file_name(char*);
void display_data(char *,int );


FILE *fp1,*fp2,*fp3;

int find_switch_value(char[]);

int main()
{
	char buffer[50];
	
	char original_name[20],*file_name,line[50],*fname,flag=0,str[20];
	int version,op1,op2, e;
	
	do
	{		
		printf("\n $>> command to open a file : \"open\"\n\n $>> ");
		scanf("%s",str);
		if(strcmp(str,"open")!=0 && strcmp(str,"OPEN")!=0)
		{
		 sleep(1);
                printf("\n\n $>> Invalid Command\n");
		
		}
	}while(strcmp(str,"open")!=0 && strcmp(str,"OPEN")!=0);

	
	sleep(1);
	printf("\n $>> File to be openend : ");
	scanf("%s",original_name);
	printf("\n $>> Version No : ");
	scanf("%d",&version);
	
	if(version!=0)
	{
			file_name=get_file_name(original_name,version);
			fp1=fopen(file_name,"r");
			if(fp1==NULL)
			{
				printf("\n $>> File Does Not Exist.\n");
				exit(0);
			}
			
	}
	else
	{
		file_name=original_name;
		fp1=fopen(file_name,"r");
		if(fp1==NULL)
		{
			fp1=fopen(file_name,"w");
			printf("\n $>> New File %s Created.",original_name);
			fp2=fopen("metadata.txt","a+");
			if(fp2==NULL)
			{
				fp2=fopen("metadata.txt","w+");
			}
			fprintf(fp2,"\n");
			fprintf(fp2,"%s %s %d",file_name,file_name,0);
			fclose(fp2);
			flag=1;
		}
	}

	fp2=fopen("temp.txt","w");
	if(fp2==NULL)				// If temp.txt can not be created
	exit(0);		
	
	while(fgets(buffer,50,fp1))
	{
		fputs(buffer,fp2);			// Dumped data into temp.txt
	}
	
	while(fgets(buffer,50,fp2))			// printing temp.txt
	printf("%s",buffer);
	
	
	fclose(fp2);			// closed temp.txt
	fclose(fp1);
	
	
	
	
	
	do{
	sleep(1);
printf("\n $>> Valid commands:\n\tAppend to file\t\t\t:\"append\"\n\tDelete A Line from file\t\t:\"del\"\n\tDisplay all files\t\t:\"show\"\n\tExit\t\t\t\t:\"exit\"\n");
			printf("\n $>> ");
			scanf("%s",str);
			
			op1=find_switch_value(str);
			
			
			switch(op1)
			{
				case 1:
					sleep(1);
					printf("\n $>> Current Open File : %s ",file_name);
					sleep(1);
					printf("\n\n $>> Enter line to append : ");
					scanf(" %s",buffer);
					fp2=fopen("temp.txt","a+");
					
					fputs("\n",fp2);
					fputs(buffer,fp2);			// appended
					
					rewind(fp2);				// goto begining
					
					sleep(1);
					
					printf("\n $>> File with changes : %s\n\n",file_name);
					
					while(fgets(buffer,50,fp2))		// while not finished
					{
					  printf("%s",buffer);			// print each line
					  sleep(1);
					}
					fclose(fp2);				// close temp.txt


					sleep(1);										
					printf("\n\n\n $>> Successfully Appended To File.\n");
					
				break;
				
				case 2:				// delete
						sleep(1);
						printf("\n $>> File opened : %s\n",file_name);
														
						fp2=fopen("temp.txt","r");
						
						printf("\n $>> Current Contents of File %s : \n\n",file_name);


						while(fgets(buffer,50,fp2))		// while temp.txt not finished
						{
							sleep(1);
							printf("%s",buffer);			// print each line
						}
						rewind(fp2);					// Pointing at start
						sleep(1);
						printf("\n\n $>> Enter The line to Delete : ");
						scanf(" %s",line);
						

						fp3=fopen("temp1.txt","w+");
						while(fscanf(fp2,"%s",buffer)!=EOF)
						{
							if(strcmp(buffer,line)!=0)
							{
								fprintf(fp3,"%s",buffer);
								fprintf(fp3,"\n");
							}
						}
						sleep(1);
						printf("\n\n $>> Line Successfully deleted From File.\n\n");
						
						rewind(fp3);
						
						printf(" $>> Changes made to File %s :\n\n",file_name);
						
						sleep(1);
						
						while(fgets(buffer,50,fp3))		// while file not finished
						printf("%s",buffer);			// print each line
						
						remove("temp.txt");
						rename("temp1.txt","temp.txt");
						
						fclose(fp3);
						fclose(fp2);
				
				break;
				
				case 3:
						// Display all files details
						display_data(original_name,version);
					
					
				break;
				
				case 7:
						printf("\n\n\t\tDo u really want to Quit? <1- Yes>");	
						scanf("%d", &e);
						if(e==1)
							exit(0);
				break;
	
				default:
				
				printf("\n $>> Please Enter Again.\n");
				sleep(1);
			}
sleep(1);
L:printf("\n $>> Valid commands:\n\tGo back to make changes : \"back\"\n\tSave Changes : \"commit\"\n\tDiscard Chabges  :\"revert\"\n");
	printf("\n\n $>> ");
			scanf("%s",str);
	  }while((strcmp(str,"back")==0) || (strcmp(str,"BACK")==0));

	  sleep(1);

	  if(strcmp(str,"commit")==0 || strcmp(str,"COMMIT")==0)
	  {
		if(flag==0)
		{
			fname=make_new_file_name(file_name);
			strcpy(buffer,fname);
			rename("temp.txt",buffer);
		}
		else
		{
			fname=file_name;
			rename("temp.txt",fname);
		}
	 	sleep(1);
	 	printf("\n\n $>> New file name : %s",fname);
	  }
	  else if(strcmp(str,"REVERT")==0 || strcmp(str,"revert")==0)
	 {
	 	sleep(1);
	 	printf("\n\n $>> Changes Not Saved.\n\n");
	 	exit(0);
	 }
	 else 
	 {
		sleep(1);
	 	printf("\n\n$>> Invalid command Error\n\n");
	 	goto L;
	 }
	 sleep(1);
	 printf("\n $>> Done :-)\n\n"); 
	  
	return 0;
}


char * get_file_name(char *original_name,int version)
{
	char *name,*temp;

	temp=(char*)calloc(5,sizeof(char));	
	name=remove_txt(original_name);
	
	strcat(name,"_");			// make name_
	sprintf(temp,"%d",version);
	strcat(name,temp);
	strcat(name,".txt");
	return name;
}

char *remove_txt(char *original_name)
{
	int i;
	char *temp;
	
	temp=(char*)calloc(30,sizeof(char));

	for(i=0;original_name[i]!='.';i++)
	{
		temp[i]=original_name[i];
	}
	temp[i]='\0';
	return temp;
}

char *make_new_file_name(char *fname)
{
	char original_name[20],name[20],o_name[20],*new_name;
	int no,count=0;
	
	fp1=fopen("metadata.txt","r+");
	if(fp1==NULL)
	{
		fp1=fopen("metadata.txt","w+");
		if(fp1==NULL)		
		printf("\t\t\nMETADATA.TXT could not be created.\n");
	}

	while(fscanf(fp1,"%s%s%d",name,original_name,&no)!=EOF)
	{
			if(strcmp(fname,name)==0)
			{
				strcpy(o_name,original_name);
				break;
			}
	}

	rewind(fp1);
	while(fscanf(fp1,"%s%s%d",name,original_name,&no)!=EOF)
	{
		if(strcmp(o_name,original_name)==0)
		{
				count=no;
		}
	}
	
	
new_name=get_file_name(o_name,count+1);

fprintf(fp1,"\n%s %s %d",new_name,o_name,count+1);

fclose(fp1);

return new_name;
}


int find_switch_value(char str[])
{
	if(!strcmp(str,"append") || !strcmp(str,"APPEND"))
          return 1;
	else if
	  (!strcmp(str,"del") || !strcmp(str,"DEL"))
	  return 2;
	else if
	  (!strcmp(str,"show") || !strcmp(str,"SHOW"))
	  return 3;
	else if
	  (!strcmp(str,"y") || !strcmp(str,"Y"))
	  return 4;
	else if
	  (!strcmp(str,"n") || !strcmp(str,"N"))
	  return 5;
	else if(!strcmp(str, "exit"))
	  return 7;
	else 
	  return 6;
}


void display_data(char *f_name,int version)
{
        FILE *fp;
        struct stat fi;
        struct file_node *head=NULL,*p=NULL;
        struct same_size *h2=NULL,*h3=NULL;
        char line[30],part[20],*t1,*t3;
        int i=0,j;

        fp=fopen("metadata.txt","r");

        while(!feof(fp))
        {
                fgets(line,sizeof(line),fp);
                i=0;
                while(line[i++]!=' ');
                j=0;
                while(!isspace(line[i]))
                {
                        part[j++]=line[i++];
                }
                part[j]='\0';
                if(!strcmp(part,f_name))
                {
                        printf("%s\n",line);

                }
        }


        printf("\nEnter file name: ");
        scanf("%s",f_name);

        stat(f_name,&fi);

        printf("\n\nName\t\t\t:%s\nSize\t\t\t:%lld\nLast Access Time\t:%sLast Modification Time\t:%s",f_name,(long long)fi.st_size,ctime(&fi.st_atime),ctime(&fi.st_mtime));

}
