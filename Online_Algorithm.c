#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//Use fprintf to handle sending it to the file
/*
Actions of elevator:

1. Goes up
2. Goes down
3. Picks up a passenger
4. Drops off a passenger
5. Stops

*/


int max_floor;
int min_floor=1;
int n_p=0;

int total_floors_travelled=0;
int total_passengers_picked_up=0;

//Creation of various structures

//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
struct passengers
{
	int pid,time_of_arrival,st_floor,en_floor;
	int wait_time;
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
	bool mid_del;
	bool first_floor;
	int time;
	int current_time;
	int check;//check is 0 then if es=0 first_floor boolean turns down
	int take_out_timer;
	int floors_t;
	int p_s;
	
};


//Creation of datastructure of each elevator
struct elevators
{
	int npe;
	int len;
	int floor_handled;
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


void delete_passenger(struct queue_floors *q,bool up_down)
{
	if(up_down==1)
	{
		
		int i=0;
		
		for(i=0;i<(q->nu-1);i++)
		{
			q->up[i]=q->up[i+1];
		}
		q->nu--;
		
	}	
	else
	{
		
		int i=0;
		
		for(i=0;i<(q->nd-1);i++)
		{
			q->dn[i]=q->dn[i+1];
		}
		q->nd--;
		
	}
	
}

//Function for moving elevator up
void move_elevator_up(struct elevator_movement *em, struct elevators *e, bool *first_floor)
{

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
		em->floors_t++;

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

	else if (*first_floor == 0 && em->es ==1 && em->check ==0)
	{
		em->es=2;
		printf("\nThe floor is changed now increased");
		printf("\nThe floor is %d",em->floor);
		em->floor++;
		em->floors_t++;
		em->current_time++;
	}
	else
	{
		em->es--;
		em->current_time++;
	}
	
	if(em->floor>=max_floor)
	{
		//printf("\nYou have reached the top most floor You can't go up\n");
		em->move_up=false;
		em->move_down=true;
		em->es=0;
		em->start=0;
		em->first_floor=1;
	}
	//printf("\nThe value of em es is %d\n",em->es);
	
}

//Function for moving elevator down
void move_elevator_down(struct elevator_movement *em,struct elevators *e,bool *first_floor)
{
	
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
		em->floors_t++;
	//	printf("\nThe floor is changed now");
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
		em->floor--;
		em->floors_t++;
		em->current_time++;
	}
	else
	{
		em->es--;
		em->current_time++;
	}
	
	if(em->floor<=min_floor)
	{
//		printf("\nYou have reached the lower most level.. You can't go below this level");
		em->move_down=false;
		em->move_up=true;	
		//printf("\nThe value es is given by %d\n",em->es);
		em->es=0;	
		em->start=0;
		em->es==3;//First floor at the bottom end
	}
	
	//printf("\n\nThe value of em es is %d\n",em->es);
		
}

//Function for taking the passenger in to the elevator
int take_in(struct elevator_movement *em,struct elevators *e,struct queue_floors * q, struct passengers * p)
{

	if(em->move_up==true && em->move_down==false)
	{
		printf("\nIn the take in function");
		printf("\n%d",q->up[0]);
		printf("\n%d",q->nu);
	
		
		int n=10-q->nu;
		if(n>=0)
		{
	//		printf("\nAll the people in the queue can be accomodated");
		}
		else
		{
	//		printf("\n%d Elements wont be accomodated",abs(n));
		}
		int time=(q->nu)*2;
	//	printf("\n\nThe number of members the lift can take in is %d \n\nTime the lift has to wait is %d\n\n",n,time);
		
		if(em->mid==1)
		{
			time--;			
		}	
		int i=0;
	//	printf("\nTime the elevator will stay here is %d",time);
		if(time>1)
		{
			em->take_in=true;
		}
		else
		{
			time--;
	//		printf("\nTake in false now\n");
			em->take_in=false;
			em->first_floor=1;
			em->move_up=true;
			em->move_down=false;
			em->es=3;
		}
		//e->len=0;
	//	printf("\n\nTime the lift has to stop here is %d\n\n",time);	
		//Block of code when the passenger is led into the elevator
		if (em->mid==0)
		{
			//Letting the first element of the queue into the elevators
	//		printf("\nThe number of members in the queue is %d\n",e->len);
			e->pe[e->len].pid=q->up[0];
			em->take_in=true;
	//		printf("\nFirst element to get in to the elevator is %d\n",e->pe[e->len].pid);
			for(i=0;i<88;i++)
			{
				if(p->pid==e->pe[e->len].pid)
				{
					e->pe[e->len].pid=p->pid;
					e->pe[e->len].en_floor=p->en_floor;
					e->pe[e->len].st_floor=p->st_floor;
					p->wait_time=em->current_time - p->time_of_arrival;
					em->mid=1;
				//	
					break;
				}	
				p++;
			}		
		}
		else
		{
	//		printf("\nWe are at the mid of adding a passenger into the elevator \n ");
			em->mid=0;
			//
			//Here we need to delete the passenger from the queue
			delete_passenger(q,em->move_up);
			e->len++;
			e->npe++;
	//		printf("\nAfter the %d addition the number of passengers in the elevator is %d\n",e->len,e->npe);
			em->p_s++;
					
		}
		for(i=0;i<e->npe;i++)
		{
	//		printf("\n%d",e->pe[i].pid);
		}
		return time;
	}
	else if(em->move_up==false && em->move_down==true)
	{
	//	printf("\nIn the take in function");
	//	printf("\n%d",q->dn[0]);
	//	printf("\n%d",q->nd);
		
		
		int n=10-q->nd;
		if(n>=0)
		{
	//		printf("\nAll the people in the queue can be accomodated");
		}
		else
		{
	//		printf("\n%d Elements wont be accomodated",abs(n));
		}
		int time=(q->nd)*2;
	//	printf("\n\nThe number of members the lift can take in is %d \n\nTime the lift has to wait is %d\n\n",n,time);
		
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
	//		printf("\nTake in false now\n");
			em->take_in=false;
			em->first_floor=1;
			em->move_up=false;
			em->move_down=true;
			em->es=2;
		}
		//e->len=0;
	//	printf("\n\nTime the lift has to stop here is %d\n\n",time);	
		//Block of code when the passenger is led into the elevator
		if (em->mid==0)
		{
			//Letting the first element of the queue into the elevators
	//		printf("\nThe number of members in the queue is %d\n",e->len);
			e->pe[e->len].pid=q->dn[0];
			em->take_in=true;
	//		printf("\nFirst element to get in to the elevator is %d\n",e->pe[e->len].pid);
			for(i=0;i<n_p;i++)
			{
				if(p->pid==e->pe[e->len].pid)
				{
					e->pe[e->len].pid=p->pid;
	//				printf("\nPID is %d",e->pe[e->len].pid);
					e->pe[e->len].en_floor=p->en_floor;
					e->pe[e->len].st_floor=p->st_floor;
					p->wait_time=em->current_time - p->time_of_arrival;
					em->mid=1;
					em->current_time++;
					break;
				}	
				p++;
			}		
		}
		else
		{
	//		printf("\nWe are at the mid of adding a passenger into the elevator \n ");
			em->mid=0;
			em->current_time++;
			//Here we need to delete the passenger from the queue
			delete_passenger(q,em->move_up);
			
			e->len++;
			e->npe++;
			em->p_s++;
	//		printf("\nAfter the %d addition the number of passengers in the elevator is %d\n",e->len,e->npe);		
		}
		for(i=0;i<e->npe;i++)
		{
	//		printf("\n%d",e->pe[0].pid);
		}
		return time;
	}
	
}
 	


//Function for leaving the passenger out 
void take_out(struct elevator_movement *em,struct elevators *e, int a)
{
	int x;
	//Block of code where the passengers are taken off the elevators
	
	if ( em->mid_del == 0 )
	{
		//printf("\nStarting to delete the passenger from the str array");
		em->mid_del=1;
		em->current_time++;
	}
	else if ( em->mid == 1 )
	{
		//printf("\nWe are at the last step of deleting a passenger");
		em->mid_del=0;
		em->current_time++;
		if(e->npe==1)
		{
			e->npe=0;
		}
		else if (a==e->npe)
		{
			e->npe--;
		//	printf("\nEnna koduma saravana");
		}
		else
		{
			for ( x=a;x<e->npe-1;x++ )
			{
				e->pe[a].pid=e->pe[a+1].pid;
				e->pe[a].st_floor=e->pe[a+1].st_floor;
				e->pe[a].en_floor=e->pe[a+1].en_floor;
			}
		}
		
	}
}


void main()
{
	//Parameters to be calculated
	int no_of_floors_travelled=0;
	int no_of_passengers_picked_up=0;
	int k=0;
	int a=0;	
	int y=0;//y is gonna help me handle every possible thing of not assigning an elevator after a particular time
	//maximum number of passengers in the lift is 10
	
	FILE *f,*sch,*s_e,*s_p;
	char c[10];
	
	//Data structure for the passengers structure which has following variables pid, time_of_arrival, st_floor, en_floor
	struct passengers p[1000];
	
	f=fopen("C:\\Users\\leoad\\Downloads\\passenger.txt","r");
	sch=fopen("C:\\Users\\leoad\\Downloads\\schedule.txt","w");
	s_e=fopen("C:\\Users\\leoad\\Downloads\\s_e.txt","w");
	s_p=fopen("C:\\Users\\leoad\\Downloads\\s_p.txt","w");	
	
	int count=0,i=0;int l=0;
	
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
			p[i].wait_time=0;
			p[i].taken=0;
			//printf("\n%d\n",count);
			count=0;
			i++;
			n_p++;
		}	
	}
	fclose(f);
	//printf("Number of lines is %d\n",i);
	
	int j=0;
	//for(i=0;i<=87;i++)
	//{
	//	printf("\n%d %d %d %d",p[i].pid,p[i].time_of_arrival,p[i].st_floor,p[i].en_floor);
	//}
	
	//To find the max number of floors
	int m_s=0,m_e=0;
	for(i=0;i<n_p;i++)
	{
		if(m_e<p[i].en_floor)
		{
			m_e=p[i].en_floor;
		}
		if(m_s<p[i].st_floor)
		{
			m_s=p[i].st_floor;
		}
	}
	if(m_e>=m_s)
	{
		max_floor = m_e;
	}
	else
	{
		max_floor = m_s;
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
		em[i].mid_del=false;
		em[i].take_out=false;
		em[i].first_floor=true;
		em[i].es=0;
		em[i].current_time=0;
		em[i].check=1;
		em[i].start=0;
		e[i].npe=0;
		e[i].len=0;
		em[i].take_out_timer=0;
		em[i].floors_t=0;
		em[i].p_s=0;
		e[i].floor_handled=0;
		
	}
	//printf("\nMax floor is %d and Min Floor is %d\n",max_floor,min_floor);
	
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
	int del[10];
	
	
	//The main loop is as follows
	for(i=1;i<=10;i++)
	{
		//printf("\nTime is %d\n",i);
		fprintf(s_e,"Time = %d\n",i);
		//For elevators which are in moving stage and after handling the stuff
		
		int z=0;
		int m=0;
		//Once they enter the queue, Let me check the entire thing with respect to elevator
		for (j=0;j<no_of_lift;j++)
		{	
			
			fprintf(s_e,"Elevator %d\n",j+1);	
			//Elevator which are moving up
			if(em[j].move_up==true && em[j].move_down==false)
			{				
				//Scanning through the floors
				for(k=em[j].floor;k<=max_floor;k++)//Starting part
				{
					int b=0;
					//To find how many values u need to delete
					for(m=0;m<e[j].npe && em[j].current_time <= i ;m++)
					{
						//printf("\nK is %d and position is %d",k,e[j].pe[m].en_floor);
						if(e[j].pe[m].en_floor == em[j].floor)
						{
							//Editing
						//	printf("\nEntered the b loop");
							del[b]=m;
							b++;	
						}
					}
					//printf("\nElevator number is %d",j);
					//printf("\nYou need to delete %d many variables",b);
					int r,s;
					for(r=0;r<b;r++)
					{   
					fprintf(sch,"%d %d %d drop out %d\n",i,j+1,em[j].floor,e[j].pe[r].pid);
							fprintf(s_e,"%d %d drop out %d\n",i,em[j].floor,e[j].pe[r].pid);
							fprintf(s_p,"%d %d %d %d\n",e[j].pe[r].pid,j+1,e[j].pe[r].arr_time,em[j].current_time+r*2);
						
						for(s=del[r];r<e[j].npe;r++)
						{
							
							//fprintf(sch," %d",e[j].pe[del[0]].pid);
					//		printf("\nHopefully performing deletion");
							e[j].pe[s].pid=e[j].pe[s+1].pid;
							e[j].pe[s].st_floor=e[j].pe[s+1].st_floor;
							e[j].pe[s].en_floor=e[j].pe[s+1].en_floor;
							
						}
						em[j].current_time=em[j].current_time+2*b;
					//	printf("\nHopefully time is changed");
						e[j].npe=e[j].npe-b*1;
						e[j].len=e[j].len-b*1;
					//	printf("\nLength is decremented");
					//	printf("\nElevator %d No of passengers remaining is %d",j,e[j].npe);
						
					}	
					//printf("\nElements in the elevator after deletion are ");
					
					for(r=0;r<e[j].npe;r++)
					{
					//	printf("\n%d",e[j].pe[r].pid);
					}
					
					//printf("\nChecking whether it is allowed to move in");
					//printf("\nElevator's current floor is %d\nK is %d\nCurrent Time is %d",em[j].floor,k,em[j].current_time);			
					//printf("\nFloor handled by elevator %d is %d",j,e[j].floor_handled);
					
					
					if(em[j].floor == k && q[k].nu != 0 && (e[j].floor_handled == 0 || e[j].floor_handled == k) && em[j].current_time<=i)
					{
					//	printf("\nCame in");	
						//Floor handling data structure
						//For this floor to be handled by an elevator, the elevator should not handle a floor and the floor should not be handled by an elevator
						int count=0;
						for(m=0;m<no_of_lift;m++)
						{
							if(e[m].floor_handled == k)
							{
								count++;
							}
						}
						if(count == 0)
						{
							e[j].floor_handled = k;
					//		printf("\nAlready set value");
							
						}
						else
						{
					//		printf("\nNew Value is set");
						}
					//	printf("\nFloor %d is handled by Elevator %d",k,j);
					//	printf("Elevator %d handles %d",j,e[j].floor_handled);
							//Take the passengers in only [Floor of lift] = [Floor of passenger]
						
						if(e[j].floor_handled == k)
						{
						
							em[j].take_in=true;
							fprintf(sch,"%d %d %d pick-up %d\n",i,j+1,em[j].floor,q[k].up[0]);
							fprintf(s_e,"%d %d pick-up %d\n",i,em[j].floor,q[k].up[0]);
							if( em[j].mid == 0 )
							{
								e[j].pe[e[j].len].arr_time = em[j].current_time;
					//			printf("\nFirst part of insertion");
								y=take_in(&em[j],&e[j],&q[k],p);
					//			printf("\nTake In flag is %d",em[j].take_in);
							}
							else if ( em[j].mid == 1 )						
							{
					//			printf("\nSecond part of insertion");
								
								y=take_in(&em[j],&e[j],&q[k],p);
								
					//			printf("\nTake In flag is %d",em[j].take_in);
								e[j].floor_handled = 0;
								
								
							}
							else
							{
												}}					
							if(y==0)
							{
					//			printf("\nReleasing elevator %d",j);
								e[j].floor_handled = 0;
							}
						
					}
					else 
					{
					if(em[j].take_out == false && em[j].current_time <= i )
					{
						fprintf(sch,"%d %d %d moving up\n",i,j+1,em[j].floor);
						fprintf(s_e,"%d %d moving up\n",i,em[j].floor);
					//	printf("\nj is %d",j);
						//Move up only
					//	printf("\nMove up and the new function");						
												
						em[j].current_time=i;
						if(em[j].es<0)//For the first floor
						{
							em[j].first_floor = 1;
							em[j].es=3;
						}
						move_elevator_up(&em[j],&e[j],&em[j].first_floor);						
						
					}}
					
					
				}				
				
			}
			else if(em[j].move_up==false && em[j].move_down==true)
			{
				
				//printf("\nPart of the algo dealing with people stepping down");
				//Scanning through the floors
				for(k=em[j].floor;k>=1;k--)//Starting from the floor 
				{

					
					int b=0;
					//To find how many values u need to delete
					for(m=0;m<e[j].npe && em[j].current_time <= i ;m++)
					{
						if(e[j].pe[m].en_floor == em[j].floor)
						{
				//			printf("\nEntered the b loop");
							del[b]=m;
							b++;	
						}
					}
				//	printf("\nElevator number is %d",j);
				//	printf("\nYou need to delete %d many variables",b);
					int r,s;
					
					for(r=0;r<b;r++)
					{   
						fprintf(sch,"%d %d %d drop out %d\n",i,j+1,em[j].floor,e[j].pe[r].pid);
						fprintf(s_e,"%d %d drop out %d\n",i,em[j].floor,e[j].pe[r].pid);
						fprintf(s_p,"%d %d %d %d\n",e[j].pe[r].pid,j+1,e[j].pe[r].arr_time,em[j].current_time+r*2);
						//fprintf(sch," %d",e[j].pe[del[0]].pid);
						for(s=del[r];r<e[j].npe;r++)
						{
				//			printf("\nHopefully performing deletion");
							e[j].pe[s].pid=e[j].pe[s+1].pid;
							e[j].pe[s].st_floor=e[j].pe[s+1].st_floor;
							e[j].pe[s].en_floor=e[j].pe[s+1].en_floor;
							
						}
						em[j].current_time=em[j].current_time+2*b;
				//		printf("\nHopefully time is changed");
						e[j].npe=e[j].npe-b*1;
						e[j].len=e[j].len-b*1;
				//		printf("\nLength is decremented");
						
									}	
				//	printf("\nElements in the elevator after deletion are ");
					
					for(r=0;r<e[j].npe;r++)
					{
				//		printf("\n%d",e[j].pe[r].pid);
					}

					
					if(em[j].floor == k && q[k].nd != 0  && (e[j].floor_handled == 0 || e[j].floor_handled == k) && em[j].current_time<=i)
					{
						
						
						//Floor handling data structure
						//For this floor to be handled by an elevator, the elevator should not handle a floor and the floor should not be handled by an elevator
						int count=0;
						for(m=0;m<no_of_lift;m++)
						{
							if(e[m].floor_handled == k)
							{
								count++;
							}
						}
						if(count == 0)
						{
							e[j].floor_handled = k;
						}
						else
						{
							
						}
						fprintf(sch,"%d %d %d pick up %d\n",i,j+1,em[j].floor,q[k].dn[0]);
						fprintf(s_e,"%d %d pick up %d\n",i,em[j].floor,q[k].dn[0]);
				//		printf("\nFloor %d is handled by Elevator %d",k,j);
				//		printf("Elevator %d handles %d",j,e[j].floor_handled);
						if(e[j].floor_handled == k)
						{
								
							//Take the passengers in only [Floor of lift] = [Floor of passenger]
							em[j].take_in=true;
							
							if( em[j].mid == 0 )
							{
								e[j].pe[e[j].len].arr_time = em[j].current_time;
				//				printf("\nFirst part of insertion");
								y=take_in(&em[j],&e[j],&q[k],p);
				//				printf("\nTake In flag is %d",em[j].take_in);
							}
							else if ( em[j].mid == 1 )						
							{
				//				printf("\nSecond part of insertion");
								y=take_in(&em[j],&e[j],&q[k],p);
				//				printf("\nTake In flag is %d",em[j].take_in);
								e[j].floor_handled = 0;
								
							}
							else
							{
								
							}	
							if(y==0)
							{
				//				printf("\nReleasing elevator %d",j);
								e[j].floor_handled = 0;
								}
											
						}	
					}
					else 
					{
						
					if(em[j].take_out == false && em[j].current_time <= i )
					{
						fprintf(sch,"%d %d %d moving down\n",i,j+1,em[j].floor);
						
						fprintf(s_e,"%d %d moving down\n",i,em[j].floor);
						//Move up only
				//		printf("\nMove up and the new function");						
												
						em[j].current_time=i;
						move_elevator_down(&em[j],&e[j],&em[j].first_floor);						
						
					}}				
					
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
		//	printf("\nElevator %d and floor is %d and move_up flag is %d and move down flag is %d Take in is %d Take out is %d",j,em[j].floor,em[j].move_up,em[j].move_down,em[j].take_in,em[j].take_out);
			}	
			
		for(j=0;j<no_of_lift;j++)
		{
		printf("\nAt Elevator no. %d\n",j);
		printf("\nNumber of passengers is %d",e[j].npe);
		for(k=0;k<e[j].npe;k++)
		{
			printf("\n%d",e[j].pe[k].pid);
		}
		}
	}	



	//To find which passengers are there in each and every queue 
	for(i=1;i<=max_floor;i++)
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
	fprintf(s_e,"\nStats for Elevators\n");
	for(i=0;i<no_of_lift;i++)
	{
		printf("\nAt Elevator no. %d and no of elements in the list is %d\n",i,e[i].npe);
		for(j=0;j<e[i].npe;j++)
		{
			printf("\n%d",e[i].pe[j].pid);
		}
		fprintf(s_e,"\nElevator %d\nNo. of floors travelled %d\nNo. of Passengers served is %d\n",i+1,em[i].floors_t,em[i].p_s);
	}
	
	int avg_w,max_x=0;int s_w=0;int s_a=0;
	for(i=0;i<n_p;i++)
	{
		if(max_x<p[i].wait_time)
		{
			max_x=p[i].wait_time;
		}
		s_w+=p[i].wait_time;
	}
	avg_w=s_w/n_p;
	fprintf(s_p,"\nAverage Wait time is %d\nMax Wait time is %d",avg_w,max_x);
	
}
