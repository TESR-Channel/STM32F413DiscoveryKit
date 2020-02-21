#include "mbed.h"

Thread thread;
DigitalOut led(LED1);

void led_thread()
 {
    while (true)
     {
        // Signal flags that are reported as event are automatically cleared.
        Thread::signal_wait(0x1);
        led = !led;
    }
}

int main (void) 
{
    thread.start(callback(led_thread));

    while (true) 
    {
        wait(0.25);
        thread.signal_set(0x1);
    }
}