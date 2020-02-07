#include "mbed.h"

DigitalOut led1(LED1);

/* No need Serial to UART just usb debugger. */
Serial UART(SERIAL_TX, SERIAL_RX);

/* External interrupt handler */
void UARTIrq();

int main()
{
    UART.baud(115200);
    UART.attach(UARTIrq,Serial::RxIrq);
    printf("Start\r\nTurn ON press '1' Turn OFF press '0'\r\n");
    while(1) 
    {
        thread_sleep_for(10);
    }
}

void UARTIrq()
{
    char input_char = UART.getc();
    printf("%c \n\r",input_char);
    if(input_char == '1')
    {
        printf("Press '1' turn on \r\n");
        led1.write(1);
    }
    else if(input_char == '0')
    {
        printf("Press '0' turn off \r\n");
        led1.write(0);
    }
}
