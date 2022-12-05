extern "C"
{
#include <stm32l4xx_hal.h>
}

#include <gpio.h>
#include <interrupt.h>
#include <cstring>

void initClock();

extern "C"
{
extern unsigned long _estack;

void handler_reset()
{
    while(1)
    {}
}

void handler_default()
{
    while(1)
    {}
}

void exti95_handler()
{

}

}

int main(void)
{
// LD2 on Nucleo-64
using green_led = gpio::DigitalOut<gpio::GpioPort::PORTA, 5>;
// USER BUTTON on Nucleo-64
using input = gpio::DigitalIn<gpio::GpioPort::PORTC, 13U, gpio::GpioPull::NO_PULL>;

    nvic<107> interrupts;
    interrupts.register_callback(15, (uint32_t)&HAL_IncTick);

    HAL_Init();
    initClock();

    green_led::init();
    input::init();

    uint32_t blink_period = 100;
    for(;;)
    {
        green_led::toggle();
        HAL_Delay(blink_period);
        if( input::read() )
        {
            blink_period = 1000;
        }
        else
        {
            blink_period = 100;
        }
    }

    return 0;
}

void initClock()
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    /* MSI is enabled after System reset, activate PLL with MSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLP = 7;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }
    
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
        clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        /* Initialization Error */
        while(1);
    }
}