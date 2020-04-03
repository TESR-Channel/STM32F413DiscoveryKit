#include "mbed.h"
#include "ResetReason.h"

#include <string>

const uint32_t TIMEOUT_MS = 3000; // Watchdog Timer

#define PressButton 1
DigitalIn  User_Button(PA_0,PullNone);

std::string reset_reason_to_string(const reset_reason_t reason)
{
    switch (reason) {
        case RESET_REASON_POWER_ON:
            return "Power On";
        case RESET_REASON_PIN_RESET:
            return "Hardware Pin";
        case RESET_REASON_SOFTWARE:
            return "Software Reset";
        case RESET_REASON_WATCHDOG:
            return "Watchdog";
        default:
            return "Other Reason";
    }
}

int main()
{
    int count = 0;
    const reset_reason_t reason = ResetReason::get();
    printf("Last system reset reason: %s\r\n", reset_reason_to_string(reason).c_str());
    
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