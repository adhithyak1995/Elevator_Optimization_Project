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
	int k=0;	
	
	//maximum number of passengers in the lift is 10
	
	FILE *f;
	char c[10];
	
	//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
	struct passengers
	{
		int pid,time_of_arrival,st_floor,en_floor;
	}p[1000];
	
	f=fopen("C:\\Users\\leoad\\Downloads\\passbig.txt","r");
	int count=0,i=0;int n_p=0;int l=0;
	
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
	//for(i=0;i<=87;i++)
	//{
	//	printf("\n%d %d %d %d",p[i].pid,p[i].time_of_arrival,p[i].st_floor,p[i].en_floor);
	//}
	
	//To find the max number of floors
	int m_f=0;
	for(i=0;i<n_p;i++)
	{
		if(m_f<p[i].en_floor)
		{
			m_f=p[i].en_floor;
		}
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
	}em[no_of_lift];
	
	//Initializing the elevator's status
	for(i=0;i<no_of_lift;i++)
	{
		em[i].floor=1;
		em[i].move_up=false;
		em[i].move_down=false;
		em[i].first_floor=1;
	}
	
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
		int a[50];
		int number_of_members_in_queue;
	}q[100];
	int d[no_of_lift];
	for(l=0;l<no_of_lift;l++){d[l]=0;
	}
	for(i=1;i<=10;i++)
	{
		//After they enter the queue
		for(k=0;k<=m_f;k++)//k refers to the floor
		{
				
			if(q[k].number_of_members_in_queue!=0)
			{
				printf("\nAt this time %d we have to start the movement of the elevator and the %d passengers is at the floor %d",i,q[k].number_of_members_in_queue,k);
				l=0;
				while(l<no_of_lift)
				{
					d[l]=em[l].floor-k;
					printf("\nThe distance between the floor and the floor at which the elevator %d is there is %d",k,abs(d[l]));
					l++;
				}
				//To find the minimum distance between elevator and the floor
				int m=d[0],x=0;
				l=1;
				printf("\nIndia %d %d\n",l,no_of_lift);
				l=1;
				while(l<no_of_lift)
				{
					if(m>d[l])
					{
						m=d[l];
						x=l;
					}
					l++;
				}
				printf("\nUSA\n");
				printf("\nThe distance between the floor and elevator position is minimum for elevator %d",x);
				if(x==0)
				{
					//Take in the passenger into the lift
					
					
				}
				else if(x<0)
				{
					//Move the lift down
					
					
				}
				else if(x>0)
				{
					//Move the lift up
					
					
				}
				
			}
		
			//movement of elevator is implemented here.. 
			for(l=0;l<no_of_lift;l++)
			{
				printf("\nThe elevator %d is at floor %d",l+1,em[l].floor);
			}			
		
		
		}				
		//Before they enter the queue
		for(j=0;j<n_p;j++)
		{
			if(p[j].time_of_arrival==i)
			{
				q[p[j].st_floor].a[q[p[j].st_floor].number_of_members_in_queue]=p[j].pid;
				q[p[j].st_floor].number_of_members_in_queue++;
			}
		}	
	}	
	//To find which passengers are there in each and every queue 
	for(i=0;i<m_f;i++)
	{
		printf("\nAt queue no %d",i);
		for(j=0;j<q[i].number_of_members_in_queue;j++)
		{
			printf("\n%d",q[i].a[j]);
		}
	}

}
