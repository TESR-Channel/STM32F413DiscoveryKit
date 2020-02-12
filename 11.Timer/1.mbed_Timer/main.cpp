#include "mbed.h"

Timer timer_fast;
Timer timer_slow;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
 
void task_fast(void);
void task_slow(void);
 
int main() 
{
  timer_fast.start();
  timer_slow.start(); 
  while(true)
  {
    if (timer_fast.read() > 0.2) 
    {
      task_fast();
      timer_fast.reset();
    }
    if (timer_slow.read() > 1) 
    {
      task_slow();
      timer_slow.reset();
    }
  }
}
 
void task_fast(void) 
{
  led1 = !led1;
}
void task_slow(void) 
{
  led2 = !led2;
}