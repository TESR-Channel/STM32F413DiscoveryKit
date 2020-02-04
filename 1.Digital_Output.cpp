#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

int main()
{
    while (true)
    {
        led1.write(1);
        thread_sleep_for(100);
        led1.write(0);
        thread_sleep_for(100);

        led2.write(1);
        thread_sleep_for(100);
        led2.write(0);
        thread_sleep_for(100);

        led3.write(1);
        thread_sleep_for(100);
        led3.write(0);
        thread_sleep_for(100);
        
    }
}
