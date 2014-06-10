// Birthday Paradox
//Group Id : 21
//Group Name: The Dexters

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
//#define e 2.7182


typedef struct date        //structure for Birthday date
{
   int month;
   int day;
}date;

void main()
{
   date d[400];
   int n,i=0,j,no=0,k,f;
   float cnt=0;
   double tval=0,t2,e=2.7182;
   clrscr();

   printf("\n\n\t\t ##  Verification of Birthday Paradox  ##\n\n");

   printf("\n\t\tEnter number of people :");  //Number of people in the room
   scanf("%d",&n);

  /* t2=(-n*n/730.0000);
   tval=pow(e,t2);
   printf("tval= %lf\n",tval);  */

   while(no!=10000)    //verifying 10000 times for n people
   {
      for(j=1;j<=n;j++)
      {
	 d[j].month=(rand() % 12)+1;  //generating random month
	 if(d[j].month==1 || d[j].month==3 ||d[j].month==5 ||d[j].month==7||d[j].month==8 || d[j].month==10 || d[j].month==12)
	 {
	    d[j].day=(rand()%31)+1;   //generating random day for month having 28 days
	 }
	 else if(d[j].month==2)
	 {
	    d[j].day=(rand() % 28)+1;  //generating random day for month having 30 days
	 }

	 else
	 {
	    d[j].day=(rand() % 30)+1;
	 }

      }


      f=0;
      for(i=1;i<=n;i++)
      {
	 for(k=i+1;k<=n;k++)
	 {
	   if(d[i].month==d[k].month && d[i].day==d[k].day) //checking for possible pairs
	   {
	     cnt=cnt+1;
	     f=1;
	     break;
	   }
	 }
	 if(f==1)
	    break;
      }

      no++;


   }
   printf("\n\t\tNumber of counts out of 10,000 : %.2f",cnt);
   printf("\n\n\n\n\t\tPractical probability \t Theorotical probability\n\n ");
   t2=(-n*n/730.0000);
   tval=1-pow(e,t2);
   printf("\n\t\t %.2f \t\t\t  %lf \n",cnt/100,tval*100);
   printf("\n\n\n\n\t\t ## Birthday Paradox is valid ## ");

   getch();
}