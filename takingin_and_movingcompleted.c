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

int max_floor=5;
int min_floor=1;

//Creation of various structures

//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
struct passengers
{
	int pid,time_of_arrival,st_floor,en_floor;
	int taken;//0 for passenger which is not in elevator and 1 for passenger which is already in elevator
};

//Creation of lift movement data structure
struct elevator_movement
{
	
	int floor;
	int es;
	int start;//1 for started moving and 0 for stop
	bool move_up,move_down,take_in,take_out;
	bool mid;
	bool first_floor;
	int time;
	int current_time;
	int check;//check is 0 then if es=0 first_floor boolean turns down
	
};


//Creation of datastructure of each elevator
struct elevators
{
	int npe;
	int len;
	struct people_in_elevators
	{
		
		int pid,arr_time,st_floor,en_floor,t;
		
	}pe[10];
	
	
};
	
//Creation of Data Structure for the passengers in each and every floor here we have threshold for floor be 100
struct queue_floors
{
	
	int up[50];
	int dn[50];
	int nu,nd;
	
};

void delete_passenger_elevators(struct elevators *e, int id)
{
	
}

void delete_passenger(struct queue_floors *q,bool up_down)
{
	if(up_down==1)
	{
		printf("\n\n\nCame into the delete function\n");
		int i=0;
		printf("\nBefore deletion the length of the queue is %d\n",q->nu);
		for(i=0;i<(q->nu-1);i++)
		{
			q->up[i]=q->up[i+1];
		}
		q->nu--;
		printf("\n\nAfter deletion the length of the queue is %d\n\n",q->nu);
	}	
	else
	{
		printf("\n\n\nCame into the delete function\n");
		int i=0;
		printf("\nBefore deletion the length of the queue is %d\n",q->nd);
		for(i=0;i<(q->nd-1);i++)
		{
			q->dn[i]=q->dn[i+1];
		}
		q->nd--;
		printf("\n\nAfter deletion the length of the queue is %d\n\n",q->nd);
	}
	
}

//Function for moving elevator up
void move_elevator_up(struct elevator_movement *em, struct elevators *e, bool *first_floor)
{
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
	else if(*first_floor == 1 && (em->es==2 ) && em->check == 1)
	{
		em->es--;
		em->current_time++;
		em->check=0;
	}
	else if(*first_floor == 1 && em->es==1 && em->check ==0 )
	{
		em->floor++;
		printf("\nThe floor is changed now increased");
		printf("\nThe floor is %d",em->floor);
		em->first_floor=0;
		em->check = 0;
		em->es=2;
		em->current_time++;
	}
	else if (*first_floor == 0 && em->es == 2 && em->check == 0)
	{
		em->es--;
		//em->floor++;
		em->current_time++;
	}
	else if (*first_floor == 0 && em->es == 1 && em->check == 0)
	{
		em->es--;
		em->current_time++;
	}
	else if (*first_floor == 0 && em->es ==0 && em->check ==0)
	{
		em->es=2;
		printf("\nThe floor is changed now increased");
		printf("\nThe floor is %d",em->floor);
		em->floor++;
		em->current_time++;
	}
	else
	{
		em->es--;
		em->current_time++;
	}
	
	if(em->floor>=max_floor)
	{
		printf("\nYou have reached the top most floor You can't go up\n");
		em->move_up=false;
		em->move_down=true;
		em->es=0;
		em->start=0;
		em->es=2;//First floor at the top end
	}
	printf("\nThe value of em es is %d\n",em->es);
	
}

//Function for moving elevator down
void move_elevator_down(struct elevator_movement *em,struct elevators *e,bool *first_floor)
{
	
/*	
	printf("\nIn the Moving down Function");
	printf("\nFirst floor flag is %d",*first_floor);
	printf("\n The move down flag is %d",em->move_down);
	printf("\nThe value of em es is %d",em->es);
	printf("\nThe check is %d",em->check);
	printf("\nThe first floor is %d",*first_floor);
	printf("\nThe floor no is %d\n",em->floor);
*/	
	
	if(*first_floor == 1 && em->es==0 && em->check==1)
	{
		em->es=2;
		em->move_up=false;
		em->move_down=true;
		em->current_time++;
	}
	else if(*first_floor == 1 && em->es==2 && em->check == 1 )
	{
		em->es--;
		em->current_time++;
	}
	else if(*first_floor == 1 && ( em->es==1) && em->check == 1)
	{
		em->es--;
		em->current_time++;
		em->check=0;
	}
	else if(*first_floor == 1 && em->es==0)
	{
	//	em->es--;
		em->floor--;
		printf("\nThe floor is changed now");
		em->first_floor=0;
		em->check = 0;
		em->es=1;
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
		printf("\nThe floor is changed now reduced");
		em->floor--;
		em->current_time++;
	}
	else
	{
		em->es--;
		em->current_time++;
	}
	
	if(em->floor<=min_floor)
	{
		//printf("\nYou have reached the lower most level.. You can't go below this level");
		em->move_down=false;
		em->move_up=true;	
		//printf("\nThe value es is given by %d\n",em->es);
		em->es=0;	
		em->start=0;
	}
	
	printf("\n\nThe value of em es is %d\n",em->es);
		
}

//Function for taking the passenger in to the elevator
void take_in(struct elevator_movement *em,struct elevators *e,struct queue_floors * q, struct passengers * p)
{

	if(em->move_up==true && em->move_down==false)
	{
		printf("\nIn the take in function");
		printf("\n%d",q->up[0]);
		printf("\n%d",q->nu);
	
		
		int n=10-q->nu;
		if(n>=0)
		{
			printf("\nAll the people in the queue can be accomodated");
		}
		else
		{
			printf("\n%d Elements wont be accomodated",abs(n));
		}
		int time=(q->nu)*2;
		printf("\n\nThe number of members the lift can take in is %d \n\nTime the lift has to wait is %d\n\n",n,time);
		
		if(em->mid==1)
		{
			time--;			
		}	
		int i=0;
		printf("\nTime the elevator will stay here is %d",time);
		if(time>1)
		{
			em->take_in=true;
		}
		else
		{
			printf("\nTake in false now\n");
			em->take_in=false;
			em->first_floor=1;
			em->move_up=true;
			em->move_down=false;
		}
		//e->len=0;
		printf("\n\nTime the lift has to stop here is %d\n\n",time);	
		//Block of code when the passenger is led into the elevator
		if (em->mid==0)
		{
			//Letting the first element of the queue into the elevators
			printf("\nThe number of members in the queue is %d\n",e->len);
			e->pe[e->len].pid=q->up[0];
			em->take_in=true;
			printf("\nFirst element to get in to the elevator is %d\n",e->pe[e->len].pid);
			for(i=0;i<88;i++)
			{
				if(p->pid==e->pe[e->len].pid)
				{
					e->pe[e->len].en_floor=p->en_floor;
					e->pe[e->len].st_floor=p->st_floor;
					em->mid=1;
				//	
					break;
				}	
				p++;
			}		
		}
		else
		{
			printf("\nWe are at the mid of adding a passenger into the elevator \n ");
			em->mid=0;
			//
			//Here we need to delete the passenger from the queue
			delete_passenger(q,em->move_up);
			e->len++;
			e->npe++;
			printf("\nAfter the %d addition the number of passengers in the elevator is %d\n",e->len,e->npe);
					
		}
	}
	else if(em->move_up==false && em->move_down==true)
	{
		printf("\nIn the take in function");
		printf("\n%d",q->dn[0]);
		printf("\n%d",q->nd);
		
		
		int n=10-q->nd;
		if(n>=0)
		{
			printf("\nAll the people in the queue can be accomodated");
		}
		else
		{
			printf("\n%d Elements wont be accomodated",abs(n));
		}
		int time=(q->nd)*2;
		printf("\n\nThe number of members the lift can take in is %d \n\nTime the lift has to wait is %d\n\n",n,time);
		
		if(em->mid==1)
		{
			time--;			
		}	
		int i=0;
		if(time>=0)
		{
			em->take_in=true;
		}
		else
		{
			em->take_in=false;
		}
		//e->len=0;
		printf("\n\nTime the lift has to stop here is %d\n\n",time);	
		//Block of code when the passenger is led into the elevator
		if (em->mid==0)
		{
			//Letting the first element of the queue into the elevators
			printf("\nThe number of members in the queue is %d\n",e->len);
			e->pe[e->len].pid=q->dn[0];
			em->take_in=true;
			printf("\nFirst element to get in to the elevator is %d\n",e->pe[e->len].pid);
			for(i=0;i<88;i++)
			{
				if(p->pid==e->pe[e->len].pid)
				{
					e->pe[e->len].en_floor=p->en_floor;
					e->pe[e->len].st_floor=p->st_floor;
					em->mid=1;
					em->current_time++;
					break;
				}	
				p++;
			}		
		}
		else
		{
			printf("\nWe are at the mid of adding a passenger into the elevator \n ");
			em->mid=0;
			em->current_time++;
			//Here we need to delete the passenger from the queue
			delete_passenger(q,em->move_up);
			e->len++;
			e->npe++;
			printf("\nAfter the %d addition the number of passengers in the elevator is %d\n",e->len,e->npe);		
		}
	}
	
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
	
	f=fopen("C:\\Users\\leoad\\Downloads\\passenger.txt","r");
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
			p[i].taken=0;
			//printf("\n%d\n",count);
			count=0;
			i++;
			n_p++;
		}	
	}
	fclose(f);
	printf("Number of lines is %d\n",i);
	
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
	//Creation of lift movement data structure
	struct elevator_movement em[no_of_lift];

	//Creation of datastructure of each elevator
	struct elevators e[no_of_lift];
	
	//Initializing the elevator's status
	for(i=0;i<no_of_lift;i++)
	{
		em[i].floor=1;
		em[i].move_up=true;
		em[i].move_down=false;
		em[i].take_in=false;
		em[i].mid=false;
		em[i].take_out=false;
		em[i].first_floor=true;
		em[i].es=0;
		em[i].current_time=0;
		em[i].check=1;
		em[i].start=0;
		e[i].npe=0;
		e[i].len=0;
	}
	

	
	
	//Creation of Data Structure for the passengers in each and every floor here we have threshold for floor be 100
	struct queue_floors q[100];
	for(i=1;i<=100;i++)
	{
		q[i].nu=0;
		q[i].nd=0;
	}
	
	
	int d[no_of_lift];
	for(l=0;l<no_of_lift;l++)
	{
		d[l]=0;
	}
	
	
	//The main loop is as follows
	for(i=1;i<=150;i++)
	{
		printf("\nTime is %d\n",i);
		//For elevators which are in moving stage and after handling the stuff
		
		//After they enter the queue
		for(k=1;k<=m_f;k++)//k refers to the floor
		{
			printf("\nFloor where the problem is %d",k);				
			if(q[k].nu!=0)
			{
				//printf("\nAt this time %d we have to start the movement of the elevator and the %d passengers is at the floor %d",i,q[k].number_of_members_in_queue,k);
				l=0;
				while(l<no_of_lift)
				{
					
					d[l]=k-em[l].floor;
					printf("\n%d",d[l]);
					l++;
				}
				int c[no_of_lift];
				
				printf("\nDeepCopy is made");
		//Deep copy is made now
				for(l=0;l<no_of_lift;l++)
				{
					
					c[l]=d[l];
					printf("\ne is %d",c[l]);
					
				}
				//To find the minimum distance between elevator and the 9
				//Need to implement a loop
				int s,t,m,x;
				for (s = 0; s < no_of_lift-1; s++)      
         		{
					for (t = 0; t< no_of_lift-s-1; t++)  
				    {
						if (c[t] > c[t+1])  
				        {
						
				           	int temp=c[t];
				           	c[t]=c[t+1];
				           	c[t+1]=temp;
						
						}
					
					}
				}	
			
				for(l=0;l<no_of_lift;l++)
				{
					printf("\nThe value of take in is %d for Elevator %d",em[l].take_in,l);
					printf("\nDistance is %d and the loop variable is %d\n",d[l],l);
					if(em[l].take_in==false || d[l]==0 || c[0]==d[l])
					{
						
						x=l;
						m=d[l];
						l=no_of_lift;
					}
					
				}		
						
				printf("\nFloor is %d",em[x].floor);
				printf("\nThe distance between the floor and elevator position is minimum for elevator %d and the distance is %d",x,m);
				printf("\nK is %d and elevator floor is %d\n",k,em[x].floor);
				if(k==em[x].floor)
				{
					if(em[x].es>0)
					{
						em[x].es=0;
					}
				}
				if(((k==em[x].floor && em[x].es==0) && (em[x].mid==1 || em[x].mid==0)))
				{
					if(em[x].current_time==i)
					{
						
					}
					else
					{
					em[x].take_in=1;
					//Take in the passenger into the lift
					printf("\nThe elevator number is %d and the floor number is %d\n",x,k);
					em[x].current_time=i;
					printf("\nCurrent time is %d and elevator number is %d",em[x].current_time,x);
					take_in(&em[x],&e[x],&q[k],p);
					printf("\nIraiva enna nadakudhu inga");
					continue;
					}	
					printf("\nwhat is this");			
										
				}
				else if(m<0 && em[x].es==0)
				{
					//Move the lift down
					printf("\nMove down to find the passenger and pick him up");
					if(em[x].start==0)
					{
						em[x].start=1;
						em[x].first_floor=true;
						em[x].current_time=i;
						//printf("\nMove down to find the passenger and pick him up");
						if(em[x].first_floor==true)
						{
							//printf("\nThe elevator number is %d",x);
							move_elevator_down(&em[x],&e[x],&em[x].first_floor);
							continue;
						}					
					}
					else
					{
						em[x].start=1;
						em[x].first_floor=true;
						em[x].current_time=i;
						//printf("\nMove down to find the passenger and pick him up");
						if(em[x].first_floor==true)
						{
							//printf("\nThe elevator number is %d",x);
							move_elevator_down(&em[x],&e[x],&em[x].first_floor);
							continue;
						}
					}
					
				}	
				else if(m>0 && em[x].es==0)
				{
					//printf("\nWhat the fuck start is %d\n",em->start);
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
					else
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
		
		//Going down 
		if(q[k].nd!=0)
			{
				//printf("\nAt this time %d we have to start the movement of the elevator and the %d passengers is at the floor %d",i,q[k].number_of_members_in_queue,k);
				l=0;
				while(l<no_of_lift)
				{
					
					d[l]=(k-em[l].floor);									
					l++;
				}
				//To find the minimum distance between elevator and the 9
				//Need to implement a loop
				l=0;int m=0;
				int s,t;
				for (s = 0; s < no_of_lift-1; s++)      
         		{
					 	for (t = 0; t< no_of_lift-s-1; t++)  
				        {
						if (d[t] > d[t+1])  
				           {
				           	int temp=d[t];
				           	d[t]=d[t+1];
				           	d[t+1]=temp;
										   }	}}	
				int x;
				for(l=0;l<no_of_lift;l++)
				{
					printf("\nThe value of take in is %d for Elevator %d",em[l].take_in,l);
					if(em[l].take_in==false)
					{
						x=l;
						m=d[l];
						l=no_of_lift;
					}
					
						}		
			
				printf("\nThe distance between the floor and elevator position is minimum for elevator %d and the distance is %d",x,m);
				
						
					
					if(m==0 && em[x].es==0)
					{
						//Take in the passenger into the lift
						em[x].take_in=true;
						printf("\nThe elevator number is %d and the floor number is %d\n",x,k);
						take_in(&em[x],&e[x],&q[k],p);										
					}
					else if(m<0 && em[x].es==0)
					{
						//Move the lift down
						//printf("\nMove down to find the passenger and pick him up");
						if(em[x].start==0)
						{
						em[x].start=1;
						em[x].first_floor=true;
						em[x].current_time=i;
						//printf("\nMove down to find the passenger and pick him up");
						if(em[x].first_floor==true)
						{
							//printf("\nThe elevator number is %d",x);
							move_elevator_down(&em[x],&e[x],&em[x].first_floor);
							continue;
						}					
						}
						
					}
					else if(m>0 && em[x].es==0)
					{
						//printf("\nWhat the fuck start is %d\n",em->start);
						//Move the lift up
						if(em[x].start==0)
						{
						em[x].start=1;
						em[x].first_floor=true;
						em[x].current_time=i;
		//				printf("\nMove up to find the passenger and pick him up");
						if(em[x].first_floor==true)
						{
							//printf("\nThe elevator number is %d",x);
							move_elevator_up(&em[x],&e[x],&em[x].first_floor);
							continue;
						}					
						}				
					}
	}
		
		//For elevators which are in moving stage and after handling the stuff
		for(a=0;a<no_of_lift;a++)
		{
			printf("\nNow the game starts\n");
			printf("\nE no is %d\n",a);
			if(em[a].start==1 && em[a].current_time==i)
			{
				printf("\nInto the loop");
			
				if(em[a].es!=0)
				{
					if(em[a].move_up==true && em[a].move_down==false && em[a].take_in==false && em[a].take_out==false)
					{	
	//					printf("\nMoving up");
						//printf("\nThe elevator number is %d",a);
					   	move_elevator_up(&em[a],&e[a],&em[a].first_floor);	
					   	continue;
					}
					else if(em[a].move_up==false && em[a].move_down==true && em[a].take_in==false && em[a].take_out==false)
					{
					   	move_elevator_down(&em[a],&e[a],&em[a].first_floor);	
					   	continue;
					}
				}
				else
				{
					printf("\nThe else part is most important");
					printf("\nMove up is %d and Move down is %d",em[a].move_up,em[a].move_down);
					printf("\nFloor is %d",em[a].floor);
					if(em[a].floor>=m_f)
					{
						printf("\nComing in");
						em[a].move_up=false;
						em[a].move_down=true;
						
					}
					else 
					{
						
					}
					if(em[a].move_up==true && em[a].move_down==false && em[a].take_in==false && em[a].take_out==false)
					{
						//em[a].es=2;
						printf("\nIs it getting executed");
						move_elevator_up(&em[a],&e[a],&em[a].first_floor);
					}
					else if(em[a].move_up==false && em[a].move_down==true && em[a].take_in==false && em[a].take_out==false) 
					{
	//					printf("\nNow es is 0, starting the next loop");
	//					em[a].es=2;
						printf("\nWeird");
						move_elevator_down(&em[a],&e[a],&em[a].first_floor);
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
				if((p[j].en_floor-p[j].st_floor)>0)
				{
					q[p[j].st_floor].up[q[p[j].st_floor].nu]=p[j].pid;
					
					q[p[j].st_floor].nu++;
				}
				else
				{
					q[p[j].st_floor].dn[q[p[j].st_floor].nd]=p[j].pid;
	
					q[p[j].st_floor].nd++;				
				}
				//If the difference is positive then has to go up and if the difference is negative they can go dnwn
				
			}
		}
		for(j=0;j<no_of_lift;j++)
		{
			printf("\nElevator %d and floor is %d and move_up flag is %d",j,em[j].floor,em[j].move_up);
			}	

	}	



	//To find which passengers are there in each and every queue 
	for(i=1;i<=m_f;i++)
	{
		printf("\nAt queue no %d",i);
		printf("\nGoing up");
		for(j=0;j<q[i].nu;j++)
		{
			printf("\n%d",q[i].up[j]);
		}
		printf("\nGoing down");
		for(j=0;j<q[i].nd;j++)
		{
			printf("\n%d",q[i].dn[j]);
		}
	}
	
	for(i=0;i<no_of_lift;i++)
	{
		printf("\nParameters of elevator %d",i);
		printf("\nFloor is %d\nFirst floor flag is %d\nMove_up flag is %d\nMove down Flag is %d\n",em[i].floor,em[i].first_floor,em[i].move_up,em[i].move_down);
	}
	
	for(i=0;i<no_of_lift;i++)
	{
		printf("\nAt Elevator no. %d\n",i);
		for(j=0;j<e[i].npe;j++)
		{
			printf("\n%d",e[i].pe[j].pid);
		}
	}


}
