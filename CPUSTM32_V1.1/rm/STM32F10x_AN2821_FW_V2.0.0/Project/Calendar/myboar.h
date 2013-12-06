#define LED_STATUS GPIO_Pin_4

#define SELECT_A 	GPIO_Pin_0
#define SELECT_B 	GPIO_Pin_1
#define SELECT_C 	GPIO_Pin_5

#define LED_OE 		GPIO_Pin_8
#define LED_CK 		GPIO_Pin_13
#define LED_DATA 	GPIO_Pin_15
#define LED_LAUCH 	GPIO_Pin_11

#define  OE_L()  GPIO_ResetBits(GPIOB, LED_OE)
#define  OE_H()  GPIO_SetBits(GPIOB, LED_OE )

#define  CK_L()  GPIO_ResetBits(GPIOB,LED_CK)
#define  CK_H()  GPIO_SetBits(GPIOB, LED_CK)

#define  DATA_L()  GPIO_ResetBits(GPIOB,LED_DATA)
#define  DATA_H()  GPIO_SetBits(GPIOB, LED_DATA)

#define  LAUCH_L()  GPIO_ResetBits(GPIOB,LED_LAUCH)
#define  LAUCH_H()  GPIO_SetBits(GPIOB, LED_LAUCH)


#define  SELECT_A_H()  GPIO_SetBits(GPIOB, SELECT_A)
#define  SELECT_A_L()  GPIO_ResetBits(GPIOB, SELECT_A)

#define  SELECT_B_H()  GPIO_SetBits(GPIOB, SELECT_B)
#define  SELECT_B_L()  GPIO_ResetBits(GPIOB, SELECT_B)

#define  SELECT_C_H()  GPIO_SetBits(GPIOB, SELECT_C)
#define  SELECT_C_L()  GPIO_ResetBits(GPIOB, SELECT_C)




