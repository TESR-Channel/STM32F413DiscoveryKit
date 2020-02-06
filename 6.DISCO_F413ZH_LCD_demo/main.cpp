#include "mbed.h"
#include "Lib_DISCO_F413ZH\\Drivers\\BSP\\STM32F413H-Discovery\\stm32f413h_discovery_lcd.h"

int main()
{
    BSP_LCD_Init();

    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    BSP_LCD_DisplayStringAt(0, LINE(1), (uint8_t *)"MBED EXAMPLE", CENTER_MODE);
    thread_sleep_for(2);
    BSP_LCD_Clear(LCD_COLOR_GREEN);
    BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"DISCOVERY STM32F413ZH", CENTER_MODE);

    while(1) {
    }
}
