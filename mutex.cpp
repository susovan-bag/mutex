#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
void *car_thread (void *p) 
{
struct cars_on_bridge ;
pthread_mutex_lock(&m);
while(cars_on_bridge > 5 || (dir_on_bridge!=-1 && dir_on_bridge != car->dir))
pthread_cond_wait(cq[car->dir], &m)
cars_on_bridge++;
dir_on_bridge = car->dir;
pthread_mutex_unlock(&m);
usleep(5000000);
pthread_mutex_lock(&m);
cars_on_bridge--;
if (cars_on_bridge > 0) 
{
pthread_cond_signal(cq[car->dir]);
}
else 
{
dir_on_bridge = -1;
pthread_cond_broadcast(cq[1-car->dir]);
}
pthread_mutex_unlock(&m);
free(car);
}
int main () 
{
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
while (1) 
{
car = malloc(sizeof(struct CarInfo));
car->id = ++car_id;
car->dir = rand() & 1;
pthread_create(&thr_id, &attr,
car_thread, (void *) car)
unsleep(200000);
}
return 0;
}
struct bridge 
{   
  	int north_waiting;
    int north_crossing;     
	int north_consecutive;
	int south_waiting;     
	int south_crossing;     
	int south_consecutive;     
	struct lock *lock;     
	struct condition *northbound_done;
	struct condition *southbound_done; 
}; 
struct lock *lock; 
void bridge_init(struct bridge *b) 
{   
  	b->north_waiting = 0;
    b->north_crossing = 0;
	b->north_consecutive = 0;    
	b->south_waiting = 0;   
	b->south_crossing = 0;   
    b->south_consecutive = 0;     
    lock_init(&b->lock);    
    cond_init(&b->northbound_done);     
	cond_init(&b->southbound_done); 
} 
 
int bridge_arrive_north(struct bridge *b) 
{    
    lock_acquire(&b->lock);
    b->north_waiting++;     
	while ((b->south_crossing > 0) ||(b->south_waiting > 0) && (b->north_consecutive >= 5))
	{         
		cond_wait(&b->southbound_done);     
	}     
	b->north_waiting--;    
	b->north_crossing++;     
	b->north_consecutive++;   
	b->south_consecutive = 0;    
	lock_release(&b->lock); 
} 
 
int bridge_leave_north(struct bridge *b) 
{   
    lock_acquire(&b->lock);  
 	b->north_crossing--;    
	if (b->north_crossing == 0) 
	{        
		 cond_broadcast(b->northbound_done); 	
	}   
	lock_release(&b->lock); 
	}  
 
int bridge_arrive_south(struct bridge *b) 
{     
	lock_acquire(&b->lock); 
	b->south_waiting++;   
	while((b->north_crossing > 0) || ((b->north_waiting > 0) && (b->south_consecutive >= 5))) 
	{         
	  	cond_wait(&b->northbound_done);   
	}
	b->south_waiting--;  
	b->south_crossing++;   
	b->south_consecutive++;    
	b->north_consecutive = 0;   
	lock_release(&b->lock); 
} 
 
int bridge_leave_south(struct bridge *b) 
{   
	lock_acquire(&b->lock); 
    b->south_crossing--;   
	if (b->south_crossing == 0) 
	{         
		cond_broadcast(b->southbound_done);
	}     
	lock_release(&b->lock); 	
}

