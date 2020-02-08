#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*
	Need to implement the stop in between the travel
*/

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
	bool status;//0 for stop and 1 for moving
	int time;
	int current_time;
	int check;//check is 0 then if es=0 first_floor boolean turns down
	int take_out_timer;
	int floors_t;
	int p_s;
	int stop;	
	int st;
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
	int up[50][2];
	int dn[50][2];
	int nu,nd;
	
};


void delete_passenger(struct queue_floors *q,bool up_down)
{
	if(up_down==1)
	{		
		int i=0;		
		for(i=0;i<(q->nu-1);i++)
		{
			q->up[i][0]=q->up[i+1][0];
			q->up[i][1]=q->up[i+1][1];
		}
		q->nu--;		
	}	
	else
	{		
		int i=0;		
		for(i=0;i<(q->nd-1);i++)
		{
			q->dn[i][0]=q->dn[i+1][0];
			q->dn[i][1]=q->dn[i+1][1];
		}
		q->nd--;		
	}	
}

//Function for moving elevator up
void move_elevator_up(struct elevator_movement *em, struct elevators *e, bool *first_floor)
{
	//printf("\nMove up called");
	if(em->take_in == false)
	{
		//printf("\nTry");
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
		//printf("\nFloor incremented to %d",em->floor);
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
	//	printf("\nThe floor is changed now increased");
		//printf("\nThe floor is %d",em->floor);
		em->floor++;
	//	printf("\nFloor incremented to %d",em->floor);
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
		em->es=2;
		em->start=0;
		em->check=1;
		em->first_floor=1;
	}
	//printf("\nThe value of em es is %d\n",em->es);
}
	
}

//Function for moving elevator down
void move_elevator_down(struct elevator_movement *em,struct elevators *e,bool *first_floor)
{
	if(em->take_in == false)
	{	
	//printf("\nProblem path");
	//printf("\nCheck is %d",em->check);
	if(*first_floor == 1 && em->es==0 && em->check==1)
	{
		//printf("\nWent to the top floor and getting down");
		em->es=2;
		em->move_up=false;
		em->move_down=true;
		em->current_time++;
	}
	else if(*first_floor == 1 && em->es==2 && em->check == 1 )
	{
		//printf("\nIs it in");
		em->es--;
		em->current_time++;
	}
	else if(*first_floor == 1 && ( em->es==1) && em->check == 1)
	{
		//printf("\nProblematic");
		em->es--;
		em->current_time++;
		em->check=0;
	}
	else if(*first_floor == 1 && em->es==0)
	{
	//	em->es--;
		em->floor--;
		//printf("\nFloor dec to %d",em->floor);
		em->floors_t++;
		//printf("\nThe floor is changed now");
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
	else if (*first_floor == 0 && em->es ==0 && em->check ==0)
	{
		//printf("\nWent to the top floor and getting down");
		em->es=1;
		em->floor--;
		//printf("\nFloor dec to %d",em->floor);

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
		//printf("\nYou have reached the lower most level.. You can't go below this level");
		em->move_down=false;
		em->move_up=true;	
		//printf("\nThe value es is given by %d\n",em->es);
		em->es=0;	
		em->start=0;
		em->check=1;
		em->es==3;//First floor at the bottom end
	}
}
		
}

//Function for taking the passenger in to the elevator
int take_in(struct elevator_movement *em,struct elevators *e,struct queue_floors * q, struct passengers * p)
{
	int real_len=0,i;
//	printf("\nTime is %d and Floor is %d",em->current_time,em->floor);
	if(em->move_up==true && em->move_down==false)
	{	
		for(i=0;i<q->nu;i++)
		{
			if(q->up[i][1]<=em->current_time)
			{
				real_len++;
			}
		}
		int n=10-real_len;
		if(n>=0)
		{
	//		printf("\nAll the people in the queue can be accomodated");
		}
		else
		{
	//		printf("\n%d Elements wont be accomodated",abs(n));
		}
		int time=(real_len)*2;		
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
			//printf("\nTake in false now\n");
			//printf("\nCurrent time of the elevator is %d",em->current_time);
			em->take_in=false;
			em->first_floor=1;
			em->move_up=true;
			em->move_down=false;
			em->es=2;
		}
		//e->len=0;

		//Block of code when the passenger is led into the elevator
		if (em->mid==0)
		{
			e->pe[e->len].pid=q->up[0][0];
			em->take_in=true;
			for(i=0;i<88;i++)
			{
				if(p->pid==e->pe[e->len].pid)
				{
					e->pe[e->len].pid=p->pid;
					e->pe[e->len].en_floor=p->en_floor;
					e->pe[e->len].st_floor=p->st_floor;
					p->wait_time=em->current_time - p->time_of_arrival;
					em->mid=1;
					break;
				}	
				p++;
			}		
		}
		else
		{
			em->mid=0;
			delete_passenger(q,em->move_up);
			e->len++;
			e->npe++;
			em->p_s++;
					
		}
		//printf("\nReturning time variable is %d",time);
		em->es=3;
		return time;
	}
	else if(em->move_up==false && em->move_down==true)
	{
		for(i=0;i<q->nd;i++)
		{
			if(q->dn[i][1]<=em->current_time)
			{
				real_len++;
			}
		}
		int n=10-real_len;
		if(n>=0)
		{
	//		printf("\nAll the people in the queue can be accomodated");
		}
		else
		{
	//		printf("\n%d Elements wont be accomodated",abs(n));
		}
		int time=(real_len)*2;
	//	printf("\n\nThe number of members the lift can take in is %d \n\nTime the lift has to wait is %d\n\n",n,time);
		
		if(em->mid==1)
		{
			time--;
						
		}	
		//printf("\nTime is %d at the down part",time);
		int i=0;
		if(time>1)
		{
			em->take_in=true;
		}
		else
		{
			//printf("\nTake in false now\n");
			time--;
			em->take_in=false;
			em->first_floor=1;
			em->move_up=false;
			em->move_down=true;
			em->es=0;
		}
		//e->len=0;
	//	printf("\n\nTime the lift has to stop here is %d\n\n",time);	
		//Block of code when the passenger is led into the elevator
		if (em->mid==0)
		{
			//Letting the first element of the queue into the elevators
	//		printf("\nThe number of members in the queue is %d\n",e->len);
			e->pe[e->len].pid=q->dn[0][0];
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
		em->es=2;
		return time;
	}	
}
//Function for leaving the passenger out 
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
	
	f=fopen("C:\\Users\\leoad\\Downloads\\bigfloor.txt","r");
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

	int j=0;

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
	for(i=0;i<no_of_lift;i++)
	{
		em[i].floor=1;
		em[i].status=1;
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
	int diff;
	int endcheck=0;
	//To add the passengers to the queue, each floor has content - PID and Arrival Time
	for(i=0;i<n_p;i++)
	{
		diff=p[i].en_floor - p[i].st_floor;
		if(diff > 0 && p[i].time_of_arrival<=86400)
		{
			q[p[i].st_floor].up[q[p[i].st_floor].nu][0] = p[i].pid;
			q[p[i].st_floor].up[q[p[i].st_floor].nu][1] = p[i].time_of_arrival;
			q[p[i].st_floor].nu++;
		}
		else if(diff < 0 && p[i].time_of_arrival<=86400)
		{
			q[p[i].st_floor].dn[q[p[i].st_floor].nd][0] = p[i].pid;
			q[p[i].st_floor].dn[q[p[i].st_floor].nd][1] = p[i].time_of_arrival;
			q[p[i].st_floor].nd++;
		}
	}	
	//The main loop is as follows
	for(i=1;i<=86400;i++)
	{
	//	printf("\nTime is %d\n",i);
		fprintf(s_e,"Time = %d\n",i);
	
		int z=0;
		int m=0;
		//Once they enter the queue, Let me check the entire thing with respect to elevator
		for (j=0;j<no_of_lift;j++)
		{			
			fprintf(s_e,"Elevator %d\n",j+1);	
			//Elevator which are moving up
			if(em[j].stop == 0)
			{
			if(em[j].move_up==true && em[j].move_down==false)
			{				
				//Scanning through the floors
				for(k=em[j].floor;k<=max_floor;k++)//Starting part
				{
					int b=0;
					//To find how many values u need to delete
//					if(em[j].take_in == false)
//					{
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
						//printf("\nTime is %d and B is %d",i,b);
						int r,s;
						int v=0;
						int g;
						for(r=0;r<b;r++)
						{
							if(r==0)
							{
									g=del[r];
								}
							else{
								g=del[r]-r*1;}
								fprintf(sch,"%d %d %d drop out %d\n",em[j].current_time,j+1,em[j].floor,e[j].pe[g].pid);
								fprintf(s_e,"%d %d drop out %d\n",em[j].current_time,em[j].floor,e[j].pe[g].pid);
								fprintf(s_p,"%d %d %d %d\n",e[j].pe[g].pid,j+1,e[j].pe[g].arr_time,em[j].current_time);
							v=1;
							for(s=g;s<e[j].npe;s++)
							{
								e[j].pe[s].pid=e[j].pe[s+1].pid;
								e[j].pe[s].st_floor=e[j].pe[s+1].st_floor;
								e[j].pe[s].en_floor=e[j].pe[s+1].en_floor;
								e[j].pe[s].arr_time=e[j].pe[s+1].arr_time;																						
							}
							em[j].current_time=em[j].current_time+2;
							//printf("\nNo of passengers in the elevator is %d",e[j].len);
								e[j].npe=e[j].npe-1;
								e[j].len=e[j].len-1;
							
												
						}//	}
					if(em[j].floor == k && em[j].es >= 2 && (q[k].nu != 0 && q[k].up[0][1]<=i) && (e[j].floor_handled == 0 || e[j].floor_handled == k) && em[j].current_time<=i)
					{
						//fprintf(sch,"Time is %d and passenger in elevator time is %d\n",i,q[k].up[0][1]);
						int count=0;
						for(m=0;m<no_of_lift;m++)
						{
							if(e[m].floor_handled == k)
							{
								count++;
								//printf("\nCount is incremented");
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
						if(e[j].floor_handled == k)
						{			
							//printf("\nLift no %d and Floor handled is %d",j,e[j].floor_handled);		
							em[j].take_in=true;							
							fprintf(sch,"%d %d %d pick-up %d\n",i,j+1,em[j].floor,q[k].up[0][0]);
							fprintf(s_e,"%d %d pick-up %d\n",i,em[j].floor,q[k].up[0][0]);
							if( em[j].mid == 0 )
							{
								em[j].current_time = i;
								//em[j].floor=em[j].floor;
								e[j].pe[e[j].len].arr_time = em[j].current_time;
								y=take_in(&em[j],&e[j],&q[k],p);
							}
							else if ( em[j].mid == 1 )						
							{					
								em[j].current_time = i;
								//em[j].floor=em[j].floor;
								y=take_in(&em[j],&e[j],&q[k],p);								
								//e[j].floor_handled = 0;			
							}
							else
							{
												}}					
							if(y==0)
							{
								e[j].floor_handled = 0;
								em[j].take_in = false;
							}
						
					}
					else 
					{
					if(em[j].take_out == false && em[j].current_time <= i && em[j].take_in == false)
					{
						fprintf(sch,"%d %d %d moving up\n",i,j+1,em[j].floor);
						fprintf(s_e,"%d %d moving up\n",i,em[j].floor);
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

				for(k=em[j].floor;k>=1;k--)//Starting from the floor 
				{					
					int b=0;
//					if(em[j].take_in==false){
					//To find how many values u need to delete
						for(m=0;m<e[j].npe && em[j].current_time <= i ;m++)
						{
							if(e[j].pe[m].en_floor == em[j].floor)
							{
					//			printf("\nEntered the b loop");
								del[b]=m;
								b++;
								//printf("\n b is incremented and value is %d",b);	
							}
						}
						int r,s;
						int v=0;
						int g;
						//printf("\nTime is %d and B is %d",i,b);
						for(r=0;r<b;r++)
						{   
							if(r==0)
							{
								g=del[r];
							}
							else
							{
								g=del[r]-r*1;
							}
							fprintf(sch,"%d %d %d drop out %d\n",em[j].current_time,j+1,em[j].floor,e[j].pe[g].pid);
							fprintf(s_e,"%d %d drop out %d\n",em[j].current_time,em[j].floor,e[j].pe[g].pid);
							fprintf(s_p,"%d %d %d %d\n",e[j].pe[g].pid,j+1,e[j].pe[g].arr_time,em[j].current_time+v*2);
							//fprintf(sch," %d",e[j].pe[del[0]].pid);
							v=1;
							for(s=g;s<e[j].npe;s++)
							{
								e[j].pe[s].pid=e[j].pe[s+1].pid;
								e[j].pe[s].st_floor=e[j].pe[s+1].st_floor;
								e[j].pe[s].en_floor=e[j].pe[s+1].en_floor;
								e[j].pe[s].arr_time=e[j].pe[s+1].arr_time;																				
							}
							em[j].current_time=em[j].current_time+2;	
							//printf("\nNo of passengers in the elevator is %d",e[j].len);
								e[j].npe=e[j].npe-1;
								e[j].len=e[j].len-1;
											
						}	//}
								
					if(em[j].floor == k && em[j].es >= 1 && (q[k].nd != 0 && q[k].dn[0][1]<=i)  && (e[j].floor_handled == 0 || e[j].floor_handled == k) && em[j].current_time<=i)
					{
						//fprintf(sch,"Time is %d and passenger in elevator time is %d\n",i,q[k].dn[0][1]);
						int count=0;
						for(m=0;m<no_of_lift;m++)
						{
							if(e[m].floor_handled == k)
							{
								count++;
							//	printf("\nCount is incremented");
							}
						}
						if(count == 0)
						{
							e[j].floor_handled = k;
						}
						else
						{
							
						}
						if(e[j].floor_handled == k)
						{
							fprintf(sch,"%d %d %d pick up %d\n",i,j+1,em[j].floor,q[k].dn[0][0]);
							fprintf(s_e,"%d %d pick up %d\n",i,em[j].floor,q[k].dn[0][0]);
							//printf("\nLift no %d and Floor handled is %d",j,e[j].floor_handled);	
							//Take the passengers in only [Floor of lift] = [Floor of passenger]
							em[j].take_in=true;							
							if( em[j].mid == 0 )
							{
								em[j].current_time = i;
								e[j].pe[e[j].len].arr_time = em[j].current_time;
								em[j].floor=em[j].floor;
								y=take_in(&em[j],&e[j],&q[k],p);
							}
							else if ( em[j].mid == 1 )						
							{
				//				printf("\nSecond part of insertion");
								em[j].current_time = i;
								em[j].floor=em[j].floor;
								y=take_in(&em[j],&e[j],&q[k],p);
								//e[j].floor_handled = 0;								
							}
							else{
							}
							if(y==0)
							{
				//				printf("\nReleasing elevator %d",j);
								e[j].floor_handled = 0;
								em[j].take_in = false;
							}											
						}	
					}
					else 
					{						
					if(em[j].take_out == false && em[j].current_time <= i && em[j].take_in == false )
					{
						fprintf(sch,"%d %d %d moving down\n",i,j+1,em[j].floor);						
						fprintf(s_e,"%d %d moving down\n",i,em[j].floor);
						//printf("\nMoving down");
						//printf("\nElevator es is %d",em[j].es);				
						em[j].current_time=i;
						move_elevator_down(&em[j],&e[j],&em[j].first_floor);						
					}}					
				}						
		}
		
		
			}
		else
		{
			fprintf(sch,"%d %d %d stopped completely\n",i,j+1,em[j].floor);
			fprintf(s_e,"%d %d stopped completely\n",i,em[j].floor);
		}
		}
		int stop_it=0;
		for(j=1;j<=max_floor;j++)
		{
			if(q[j].nu == 0 && q[j].nd == 0)
			{
				stop_it++;
			}
		}
		for(j=0;j<no_of_lift;j++)
		{
			if(e[j].npe == 0)
			{
				stop_it++;
			}
		}
		if(stop_it == max_floor + no_of_lift)
		{
			endcheck=1;
			for(j=0;j<no_of_lift;j++)
			{
				//printf("\nYou can stop the elevator now");
				em[j].stop = 1;
			}
		}
		
//		for(j=0;j<no_of_lift;j++)
//		{
//			printf("\nElevator %d Moveup is %d Movedown is %d Take in is %d and floor is %d",j+1,em[j].move_up,em[j].move_down,em[j].take_in,em[j].floor);
//		}
		
	}	
	//To find which passengers are there in each and every queue 
	for(i=1;i<=max_floor;i++)
	{
		printf("\n\nAt queue no %d",i);
		printf("\nGoing up");
		for(j=0;j<q[i].nu;j++)
		{
			printf("\n%d and time is %d",q[i].up[j][0],q[i].up[j][1]);
		}
		printf("\n\nGoing down");
		for(j=0;j<q[i].nd;j++)
		{
			printf("\n%d and time is %d",q[i].dn[j][0],q[i].dn[j][1]);
		}
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
