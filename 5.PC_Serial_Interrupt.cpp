#include "mbed.h"

DigitalOut led1(LED1);

/* No need Serial to UART just usb debugger. */
Serial UART(SERIAL_TX, SERIAL_RX);
char UART_char;
void SerialEvent()
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

int main()
{
    UART.baud(115200);
    UART.attach(&SerialEvent,Serial::RxIrq);
    printf("Start\r\nTurn ON press '1' Turn OFF press '0'\r\n");
    while(true) 
    {
        printf("Wait Interrupt\r\n");
        wait(1000);
    }
}
