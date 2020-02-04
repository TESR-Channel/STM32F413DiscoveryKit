#include "mbed.h"

#define PressButton 1

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

DigitalIn  User_Button(PA_0,PullNone);

int main()
{
    while (true)
    {
        if(User_Button.read() == PressButton) // pressed button
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
        else
        {
            led1.write(0);
            led2.write(0);
            led3.write(0);
        }
        
    }
}
