#include "mbed.h"

DigitalOut led1(LED1);

/* No need Serial to UART just usb debugger. */
Serial UART(SERIAL_TX, SERIAL_RX);


int main()
{
    int i = 1;
    UART.baud(115200);
    printf("Hello World !\r\n");

    printf("Hello World !\n");

    while(1) 
    {
        thread_sleep_for(100); // 1 second
        led1 = !led1; // Toggle LED
        printf("This program runs since %d seconds.\r\n", i++);
    }
}
