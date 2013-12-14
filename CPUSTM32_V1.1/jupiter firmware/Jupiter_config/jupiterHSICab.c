#include "jupiterHSICab.h"

ErrorStatus CalibStatus = ERROR;
int32_t Current_RC_Frequency = 0;

void jupiterHSICab_init(void)
{
#if USE_HSI_Fixed_Error   
    /* Calibrate internal RC with the maximum error allowed in Hz */
    /* Fix the maximum value of the error frequency at +/- 14000Hz -> 0.17% */
    CalibStatus = HSI_CalibrateFixedError(14000, &Current_RC_Frequency);

#else   
    /* Calibrate internal RC and return its frequency in Hz after calibration */
    Current_RC_Frequency = HSI_CalibrateMinError();

#endif  

    /* Get the HSITRIM value from the RCC_CR register (5 bits) after calibration */
    //DisplayHSITRIMbits();

#if USE_HSI_Fixed_Error /* If the user selected the demo 1: calibration with */
    if(CalibStatus == SUCCESS) /* fixed Error */
    {
        /* The LED Green glows when the Calibration was done */
        //GPIO_SetBits(GPIOC, LED_Green);
    }
    else
    {
        /* The LED Red glows when the Calibration was not done */
        //GPIO_SetBits(GPIOC, LED_Red);
    }
#else  /* The user selected the demo 2: calibration with the minimum Error value found */
    /* The LED Green glows */
    //GPIO_SetBits(GPIOC, LED_Green);
#endif     
}
