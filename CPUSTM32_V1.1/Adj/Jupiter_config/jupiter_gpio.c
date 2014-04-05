#include "jupiter_gpio.h"

static void LEDToggle(void);

void key_init(void)
{
	GPIO_InitTypeDef Key_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_APB2PeriphClockCmd(KEY_CLK, ENABLE);
	/* Configure the GPIO pin */
    Key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    Key_InitStructure.GPIO_Pin = KEY_UP;
    GPIO_Init(KEY_PORT, &Key_InitStructure);

    Key_InitStructure.GPIO_Pin = KEY_SEL;
    GPIO_Init(KEY_PORT, &Key_InitStructure);

    Key_InitStructure.GPIO_Pin = KEY_DOW;
    GPIO_Init(KEY_PORT, &Key_InitStructure);

    Key_InitStructure.GPIO_Pin = KEY_OK;
    GPIO_Init(KEY_PORT, &Key_InitStructure);

    Key_InitStructure.GPIO_Pin = KEY_CAN;
    GPIO_Init(KEY_PORT, &Key_InitStructure);
}

void sfoftPWM_init(void)
{
	GPIO_InitTypeDef pwm_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_APB2PeriphClockCmd(PWM_PORT_CLK, ENABLE);
	/* Configure the GPIO pin */
    pwm_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    pwm_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    pwm_InitStructure.GPIO_Pin = PWM_SDI;
    GPIO_Init(PWM_PORT, &pwm_InitStructure);
    
    pwm_InitStructure.GPIO_Pin = PWM_CLK;
    GPIO_Init(PWM_PORT, &pwm_InitStructure);

    pwm_InitStructure.GPIO_Pin = PWM_STR;
    GPIO_Init(PWM_PORT, &pwm_InitStructure);
}

void ledstt_init(void)
{
	GPIO_InitTypeDef ledstt_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_APB2PeriphClockCmd(LEDSTT_PORT_CLK, ENABLE);
	/* Configure the GPIO pin */
    ledstt_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    ledstt_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    ledstt_InitStructure.GPIO_Pin = LED_STT;
    GPIO_Init(LEDSTT_PORT, &ledstt_InitStructure);
}

/**
* @brief Toggles the selected LED.
*/
static void LEDToggle(void)
{
    LEDSTT_PORT->ODR ^= LED_STT;
}

void LEDstatus(void)
{
    LEDToggle();
}

// config MCO A8
void MCO_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    AFIO->MAPR &= 0; // clear remap
    /* Enable GPIOA clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Configure MCO output pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //enable clock for alternate function
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // select clock source
    RCC_MCOConfig(RCC_MCO_SYSCLK);// SYSTEMCLK selected
    // RCC_MCOConfig(RCC_MCO_HSI);// HSI selected
    // RCC_MCOConfig(RCC_MCO_HSE);// HSE selected
    // RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);// SYSTEMCLK selected
}
