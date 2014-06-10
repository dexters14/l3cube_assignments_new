//GROUP Id: 21
//GROUP NAME: The Dexters
//Program to find duplicate files in the given folder

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <inttypes.h>
#include <string.h>

//Structure node for creating a linked list for all files
struct file_node
{
	char name[1024];
	int size;
	int inode_no;
	struct file_node *next;
};

//Structure node for creating a tree with duplicate files
struct same_size
{
	struct file_node f_node;
	struct same_size *down;
	struct same_size *right;
};


struct file_node* create_list(struct file_node*,struct file_node*);
void display_list(struct file_node*);
void display_same(struct same_size *);
int compare(char*,char*);
void deallocate_node(struct file_node**);
struct same_size* filter2(struct file_node*);
void scan_sys2(char *,struct file_node**);
void disp_format(char *);


int main(int argc,char **argv)
{
	struct file_node *head=NULL;
	struct same_size *h2=NULL,*h3=NULL;

	scan_sys2(*(argv+1),&head);

	h2=filter2(head);
	printf("\n\nDuplicate files:");
	display_same(h2);
	return 0;

}


void scan_sys2(char *name,struct file_node **head)
{
        DIR *d;
        struct dirent *dir;
        struct stat statbuf;
        struct file_node *p=NULL;
        char fullname[1024];


        d=opendir(name);
        if(d)
        {
                while((dir=readdir(d))!=NULL)
                {
                        strcpy(fullname,name);

                        if(strcmp(name,"/"))
                                strcat(fullname,"/");

                        strcat(fullname,dir->d_name);
                        if(stat(fullname,&statbuf)==-1)
                                printf("\nCannot access file %s",fullname);
                        else
                        if(S_ISDIR(statbuf.st_mode))
                        {
                                if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,".."))
                                        continue;
                                scan_sys2(fullname,head);
                        }
                        else
                        {
                                p=(struct file_node*)calloc(1,sizeof(struct file_node));
                                strcpy(p->name,fullname);
                                p->size=statbuf.st_size;
                                p->inode_no=statbuf.st_ino;

                                *head=create_list(*head,p);

                        }


                }
        }
        closedir(d);

}








struct file_node* create_list(struct file_node *head,struct file_node *p)
{
	struct file_node *temp=head;

	if(head==NULL)
	{
		head=p;	
		return head;
	}

	if(head->size > p->size)
	{
		p->next=head;
		head=p;
		return head;
	}

	while(temp->next!=NULL)
	{
		if(temp->next->size > p->size)
		{
			p->next=temp->next;
			temp->next=p;
			return head;
		}
		temp=temp->next;
	}
	temp->next=p;
	p->next=NULL;
	return head;
}


void display_list(struct file_node *head)
{
	while(head!=NULL)
	{
		printf("\n%s %d",head->name,head->size);
		head=head->next;
	}
}  




////Filter2////
//Function to create a tree which has a node with the duplicate file names to the right pointer and non duplicate filenames to the down pointer
struct same_size* filter2(struct file_node *head)
{
        struct same_size *h2=NULL,*td=NULL,*tr=NULL,*nod=NULL;
	struct file_node *temp,*prev;
	int flag=0;

        while(head!=NULL)
        {
		temp=head;
		prev=head;
		flag=1;
                while(temp->next!=NULL && head->size==temp->next->size)
                {
			if(head->inode_no != temp->next->inode_no && compare(head->name,temp->next->name))
			{
			
                        	if(flag==1)
				{
        	                        nod=(struct same_size*)calloc(1,sizeof(struct same_size));
	                                nod->f_node=*head;

					if(h2==NULL)
					{
						h2=nod;
						td=h2;
						tr=h2;
					}
					else
					{
                                		td->down=nod;
						td=td->down;
						tr=td;
					}
					flag=0;
				}
                                nod=(struct same_size*)calloc(1,sizeof(struct same_size));
                                nod->f_node=*(temp->next);
                                tr->right=nod;
                                tr=tr->right;
				deallocate_node(&temp);
			}
			else
				temp=temp->next;	

                }
                head=head->next;
		free(prev);
        }
        return h2;
}


//Function to display duplicate files
void display_same(struct same_size *head)
{
	struct same_size *r;

	while(head!=NULL)
	{
		r=head;
		printf("\n");
		while(r!=NULL)
		{
		//	printf("\n\tName:%s\n",r->f_node.name,r->f_node.size);
			disp_format(r->f_node.name);
			r=r->right;
		}
		head=head->down;
		printf("\n----------------------------------------------------------------------------------------\n");
	}
}



//Function to compare 2 files
int compare(char *n1,char *n2)
{
        FILE *fp1,*fp2;
        char buf1[20],buf2[20];
        int i;

	if(!strcmp(n1,".") || !strcmp(n1,".."))
		return 0;

        fp1=fopen(n1,"r");
        if(fp1==NULL)
        {
                printf("\nFile %s could not be opened",n1);
                exit(0);
        }

        fp2=fopen(n2,"r");
        if(fp2==NULL)
        {
                printf("\nFile %s could not be opened",n2);
                exit(0);
        }

        while(!feof(fp1) && !feof(fp2))
        {
		memset(buf1,'\0',sizeof(buf1));
		memset(buf2,'\0',sizeof(buf2));

                fread(buf1,sizeof(char),sizeof(buf1),fp1);
                fread(buf2,sizeof(char),sizeof(buf2),fp2);

                for(i=0;i<20 && (buf1[i]!='\0' || buf2[i]!='\0');i++)
                {
                        if(buf1[i]!=buf2[i])
                                return 0;
                }
        }

        return 1;
}


void deallocate_node(struct file_node **node)
{
        struct file_node *temp;

        temp=(*node)->next;
        (*node)->next=temp->next;
        free(temp);
}


void disp_format(char *fullpath)
{
	char *ptr;

	ptr=strrchr(fullpath,'/');
	ptr++;
	printf("\nPath: ");
	while(fullpath!=ptr)
		printf("%c",*(fullpath++));
	printf("\tName: %s\n",ptr);
}

