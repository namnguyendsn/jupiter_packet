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
	//deinit timer
	TIM_DeInit(TIM3);
	// deinit GPIOC
	GPIO_DeInit(GPIOC);
}
