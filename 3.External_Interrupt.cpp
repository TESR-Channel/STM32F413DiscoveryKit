#include "mbed.h"

#define PressButton 1
#define ON 1
#define OFF 0

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

InterruptIn  User_Button(PA_0);

int delay_time = 250;    //time to wait

void Interrupt_pushButton()
{
    if(delay_time == 250)   
        delay_time = 1000;  
    else             
        delay_time = 250;  
}

int main()
{

    User_Button.fall(&Interrupt_pushButton);  //Interrupt to change tempo
    while (true)
    {
        led1.write(ON);
        led2.write(ON);
        led3.write(ON);
        thread_sleep_for(delay_time);
        led1.write(OFF);
        led2.write(OFF);
        led3.write(OFF);
        thread_sleep_for(delay_time);
    }
}
