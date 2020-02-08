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

//Creation of various structures

//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
struct passengers
{
	int pid,time_of_arrival,st_floor,en_floor;
};

//Creation of lift movement data structure
struct elevator_movement
{
	
	int floor;
	int es;
	int start;//1 for started moving and 0 for stop
	bool move_up;
	bool move_down;
	bool first_floor;
	int time;
	int current_time;
	int check;//check is 0 then if es=0 first_floor boolean turns down
	
};


//Creation of datastructure of each elevator
struct elevators
{
	
	struct people_in_elevators
	{
		
		int pid,arr_time,st_floor,en_floor,t;
		
	}pe[10];
	
};
	
//Creation of Data Structure for the passengers in each and every floor here we have threshold for floor be 100
struct queue_floors
{
	
	int a[50];
	int number_of_members_in_queue;
	
};

//Function for moving elevator up
void move_elevator_up(struct elevator_movement *em, struct elevators *e, bool *first_floor)
{
	//printf("\nIn the Moving Up Function");
	//printf("\nFirst floor flag is %d",*first_floor);
	//printf("\n The move up flag is %d",em->move_up);
	//printf("\nThe value of em es is %d",em->es);
	//printf("\nThe check is %d",em->check);
	//printf("\nThe first floor is %d",*first_floor);
	printf("\nThe floor no is %d\n",em->floor);
	
	if(*first_floor == 1 && em->es==0 && em->check==1)
	{
		em->es=3;
		em->move_up=true;
		em->move_down=false;
		em->current_time++;
	}
	else if(*first_floor == 1 && em->es==3 && em->check == 1 )
	{
		em->es--;
		em->current_time++;
	}
	else if(*first_floor == 1 && (em->es==2 || em->es==1) && em->check == 1)
	{
		em->es--;
		em->current_time++;
		em->check=0;
	}
	else if(*first_floor == 1 && em->es==0)
	{
	//	em->es--;
		em->floor++;
		printf("\nThe floor is changed now");
		em->first_floor=0;
		em->check = 0;
		em->es=2;
		em->current_time++;
	}
	else if (em->es == 2 && em->check == 0)
	{
		em->es--;
		//em->floor++;
		em->current_time++;
	}
	else if (em->es == 1 && em->check == 0)
	{
		em->es--;
		em->current_time++;
	}
	else if (em->es ==0 && em->check ==0)
	{
		em->es=2;
		printf("\nThe floor is changed now");
		em->floor++;
		em->current_time++;
	}
	else
	{
		em->es--;
		em->current_time++;
	}
	


}

//Function for moving elevator down
void move_elevator_down(struct elevator_movement em,struct elevators e,bool first_floor)
{
		
}

//Function for taking the passenger in to the elevator
void take_in(struct elevator_movement em,struct elevators e,struct queue_floors q)
{
	printf("\nIn the take in function");
	printf("\n%d",q.a[0]);
	printf("\n%d",q.number_of_members_in_queue);
	
	
}

//Function for leaving the passenger out 
void take_out(struct elevator_movement em, struct elevators e)
{
	
}


void main()
{
	//Parameters to be calculated
	int no_of_floors_travelled=0;
	int no_of_passengers_picked_up=0;
	int k=0;
	int a=0;	
	
	//maximum number of passengers in the lift is 10
	
	FILE *f;
	char c[10];
	
	//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
	struct passengers p[1000];
	
	f=fopen("C:\\Users\\leoad\\Downloads\\passengers.txt.txt","r");
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
	//printf("\nThe number of passengers in the problem is %d\n",n_p);
	//Creation of lift movement data structure
	struct elevator_movement em[no_of_lift];

	
	//Initializing the elevator's status
	for(i=0;i<no_of_lift;i++)
	{
		em[i].floor=1;
		em[i].move_up=false;
		em[i].move_down=false;
		em[i].first_floor=true;
		em[i].es=0;
		em[i].current_time=0;
		em[i].check=1;
		em[i].start=0;
	}
	
	//Creation of datastructure of each elevator
	struct elevators e[no_of_lift];
	
	
	//Creation of Data Structure for the passengers in each and every floor here we have threshold for floor be 100
	struct queue_floors q[100];
	
	int d[no_of_lift];
	for(l=0;l<no_of_lift;l++)
	{
		d[l]=0;
	}
	
	
	//The main loop is as follows
	for(i=1;i<=10;i++)
	{
		printf("\nTime is %d\n",i);
		//For elevators which are in moving stage and after handling the stuff
		
		//After they enter the queue
		for(k=0;k<=m_f;k++)//k refers to the floor
		{
				
			if(q[k].number_of_members_in_queue!=0)
			{
				//printf("\nAt this time %d we have to start the movement of the elevator and the %d passengers is at the floor %d",i,q[k].number_of_members_in_queue,k);
				l=0;
				while(l<no_of_lift)
				{
					d[l]=abs(k-em[l].floor);
	//				printf("\nThe distance between the floor and the floor at which the elevator %d is there is %d",k,abs(d[l]));
					l++;
				}
				//To find the minimum distance between elevator and the floor
				int m=d[0],x=0;
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
			
				printf("\nThe distance between the floor and elevator position is minimum for elevator %d and the distance is %d",x,m);
				if(m==0 && em[x].es==0)
				{
					
					//Take in the passenger into the lift
					
					take_in(em[x],e[x],q[1]);
					
				}
				else if(m<0 && em[x].es==0)
				{
					//Move the lift down
	//				printf("\nMove down to find the passenger and pick him up");
					
				}
				else if(m>0 && em[x].es==0)
				{
					//Move the lift up
					if(em[x].start==0)
					{
					em[x].start=1;
					em[x].first_floor=true;
					em[x].current_time=i;
	//				printf("\nMove up to find the passenger and pick him up");
					if(em[x].first_floor==true)
					{
						printf("\nThe elevator number is %d",x);
						move_elevator_up(&em[x],&e[x],&em[x].first_floor);
						continue;
					}
					
					}
				
				}
		}
		
		//For elevators which are in moving stage and after handling the stuff
		for(a=0;a<no_of_lift;a++)
		{
			if(em[a].start==1 && em[a].current_time==i)
			{
			
				if(em[a].es!=0)
				{
					if(em[a].move_up==true)
					{	
	//					printf("\nMoving up");
						printf("\nThe elevator number is %d",a);
					   	move_elevator_up(&em[a],&e[a],&em[a].first_floor);	
					   	continue;
					}
					else
					{
						//move_elevator_down(&em[a],&e[a],&em[a].first_floor);
					}
				}
				else
				{
	//				printf("\nes is zero");
	//				printf("\nflag is %d",em[a].move_up);
					if(em[a].move_up==true)
					{
	//					printf("\nNow es is 0, starting the next loop");
	//					em[a].es=2;
	//					printf("\nWeird");
						printf("\nThis is different the floor has to change now\n");
						printf("\nThe elevator number is %d",a);
						move_elevator_up(&em[a],&e[a],&em[a].first_floor);
						continue;
					}
				}
			}
			else
			{
				
			}
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
	for(i=0;i<no_of_lift;i++)
	{
		printf("\nParameters of elevator %d",i);
		printf("\nFloor is %d\nFirst floor flag is %d\nMove_up flag is %d\n",em[i].floor,em[i].first_floor,em[i].move_up);
	}


}
