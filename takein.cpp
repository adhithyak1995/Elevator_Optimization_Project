void take_in(struct elevator_movement *em,struct elevators *e,struct queue_floors * q, struct passengers * p)
{
	if(em->move_up==true && em->move_down==false)
	{
		printf("\nIn the take in function");
		printf("\n%d",q->up[0]);
		printf("\n%d",q->nu);
	
		
		int n=10-q->number_of_members_in_queue;
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
			e->pe[e->len].pid=q->a[0][0];
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
			delete_passenger(q);
			e->len++;
			e->npe++;
			printf("\nAfter the %d addition the number of passengers in the elevator is %d\n",e->len,e->npe);		
		}
	}
	
 	
}

