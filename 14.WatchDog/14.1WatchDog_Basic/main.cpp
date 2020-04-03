#include "mbed.h"

const uint32_t TIMEOUT_MS = 3000; // Watchdog Timer

#define PressButton 1
DigitalIn  User_Button(PA_0,PullNone);

int main()
{
    int count = 0;

    printf("Watchdog int.\n");
    Watchdog &watchdog = Watchdog::get_instance(); // Watchdog setup
    watchdog.start(TIMEOUT_MS); // Watchdog start
    printf("Loop Start.\n\n\n");
    while(true)
    {
        count++;
        printf("Run = %d\n",count);
        thread_sleep_for(1000);
        if(User_Button.read() == PressButton) // pressed button
        {
            printf("Press Switch and Stuck in While loop.\n");
            thread_sleep_for(50);
            printf("Wait to restart.\n");
            while(true);
        }
        Watchdog::get_instance().kick(); // Watchdog reload
    }
}