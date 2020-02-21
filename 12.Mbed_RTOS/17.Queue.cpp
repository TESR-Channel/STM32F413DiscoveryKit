#include "mbed.h"

// Global Queue Handle
Queue<unsigned int, 2> queue;

void Q1_thread(void const *args);
void Q2_thread(void const *args);

int main (void) 
{
    Thread thread_Q1(Q1_thread,NULL,osPriorityNormal,1024,NULL);
    Thread thread_Q2(Q2_thread,NULL,osPriorityNormal,1024,NULL);
    
    while (true) 
    {
      
    }
}

/* Q1 Thread tx*/
void Q1_thread(void const *args)
{
    while (true) 
    {
      osStatus Staus = queue.put((unsigned int*) 1,10);
      if(Staus == osOK) // Put Passed
      {
        printf("Queue1 send sucsess\r\n");
      }
      else // Put fail
      {
        printf("Queue1 send Failed \r\n");
      }
      Thread::wait(500); // start new round
    }
}

/* Q2 Thread rx*/
void Q2_thread(void const *args)
{
    while (true) 
    {
      osEvent event = queue.get(50);
      if (event.status == osEventMessage) // check status receive complete
      {
          printf("Queue2 receive sucsess data -> %d\r\n",event.value.v);
      }
      else
      {
         printf("Queue2 receive Failed\r\n");
      }
      

    }
}
