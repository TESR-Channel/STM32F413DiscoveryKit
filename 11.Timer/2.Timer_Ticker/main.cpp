#include "mbed.h"

void led_toggle(void);

Ticker time_up;
DigitalOut led1(LED1);
 
void led_toggle() 
{
    led1=!led1;       
}
 
int main()
{
    time_up.attach(&led_toggle, 0.2);
    while(true) 
    {
        thread_sleep_for(1000);
    }
}
