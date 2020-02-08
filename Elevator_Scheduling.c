#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*
Actions of elevator:

1. Goes up
2. Goes down
3. Picks up a passenger
4. Drops off a passenger
5. Stops
*/

void main()
{
	//Parameters to be calculated
	int no_of_floors_travelled=0;
	int no_of_passengers_picked_up=0;	
	
	//maximum number of passengers in the lift is 10
	
	FILE *f;
	char c[10];
	
	//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
	struct passengers
	{
		int pid,time_of_arrival,st_floor,en_floor;
	}p[1000];
	
	f=fopen("C:\\Users\\leoad\\Downloads\\passengers.txt.txt","r");
	int count=0,i=0;int n_p=0;
	
	while(fscanf(f,"%s",c)!=EOF)
	{
		//printf("\n%s\n",c);
		if(count==0)
		{
			//printf("\n%s",c);
			p[i].pid=atoi(c);
			count++;
		}
		else if(count==1)
		{
			p[i].time_of_arrival=atoi(c);
			count++;
		}
		else if(count==2)
		{
			p[i].st_floor=atoi(c);
			count++;
		}	
		else if(count==3)
		{
			//printf("\n%s\n",c);
			p[i].en_floor=atoi(c);
			//printf("\n%d\n",count);
			count=0;
			i++;
			n_p++;
		}	
	}
	fclose(f);
	printf("Number of lines is %d\n",i);
	printf("Hello World");
	int j=0;
	for(i=0;i<=87;i++)
	{
		printf("\n%d %d %d %d",p[i].pid,p[i].time_of_arrival,p[i].st_floor,p[i].en_floor);
	}
	
	int no_of_lift;
	printf("\nEnter the number of lifts is ");
	scanf("%d",&no_of_lift);
	
	printf("\nThe number of lifts is %d\n",no_of_lift);
	printf("\nThe number of passengers in the problem is %d\n",n_p);
	//Creation of lift movement data structure
	
	struct elevator_movement
	{
		int floor;
		bool move_up;
		bool move_down;
		bool first_floor;
		int time;
		}em[10];
	
	//Creation of datastructure of each elevator
	struct elevators
	{
		struct people_in_elevators
		{
			int pid,arr_time,st_floor,en_floor,t;
		}pe[10];
	}e[no_of_lift];
	
	
	//Creation of Data Structure for the passengers in each and every floor here we have threshold for floor be 100
	
	struct queue_floors
	{
		int a[10][2];
		int c;
	}q[30];
	for(i=0;i<30;i++)
	{
		q[i].c=0;
	}

	for(i=1;i<=86400;i++)
	{
		for(j=0;j<n_p;j++)
		{
			if(p[j].time_of_arrival==i)
			{
				//printf("\n%d\n",p[j].st_floor);
				q[p[j].st_floor].a[q[p[j].st_floor].c][0]=p[j].pid;
				q[p[j].st_floor].a[q[p[j].st_floor].c][1]=p[j].st_floor;
				q[p[j].st_floor].c+=1;
				//printf("%d %d",q[p[j].st_floor].a[k[l]][0],q[p[j].st_floor].a[k[l]][1]);
				
			}
		}		
	}
    for(i=0;i<10;i++)
    {
	printf("\n\nThe data in queue %d",i+1);
	for(j=0;j<30;j++)
    {
    	printf("\n%d %d",q[i].a[j][0],q[i].a[j][1]);
	}
}
}
