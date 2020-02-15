#include "mbed.h"
 
Timer t;
 
int main() 
{
    t.start();
    printf("Hello World!\n");
    t.stop();
    printf("The time taken was %f seconds\n", t.read());
}
