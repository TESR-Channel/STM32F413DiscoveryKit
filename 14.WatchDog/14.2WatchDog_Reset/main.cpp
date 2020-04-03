#include "mbed.h"

#define PressButton 1
DigitalIn  User_Button(PA_0,PullNone);

int main()
{
    int count = 0;

    printf("Watchdog int.\n");
    Watchdog &watchdog = Watchdog::get_instance(); // Watchdog setup
    printf("Loop Start.\n\n\n");
    while(true)
    {
        count++;
        printf("Run = %d\n",count);
        thread_sleep_for(1000);
        if(User_Button.read() == PressButton) // pressed button
        {
            printf("Press Switch to Restart now.");
            thread_sleep_for(50);
            watchdog.start(1); // Watchdog restart now
        }
       
    }
}