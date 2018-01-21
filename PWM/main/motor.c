#include "motor.h"

int pwm_pins[5] = { 3, 5, 9, 10, 11 };

  TIM_OC_InitTypeDef        OC1;
  TIM_OC_InitTypeDef        OC2;
  TIM_OC_InitTypeDef        OC3;
  TIM_OC_InitTypeDef        OC9;
  TIM_OC_InitTypeDef        OC11;
  TIM_OC_InitTypeDef        OC12;
int frequency ;


void motor_init(int freq){
	
  frequency = freq;	
  TIM_HandleTypeDef  *pTIM;
  TIM_OC_InitTypeDef *pOC;
  uint32_t tim_ch;
  uint32_t uwPeriodValue;
  int i=0;
  for(i=0;i<5;i++){
  pTIM   = g_Pin2PortMapArray[pwm_pins[i]].TIMx;
  tim_ch = g_Pin2PortMapArray[pwm_pins[i]].timerChannel;
  uwPeriodValue = (uint32_t) (((SystemCoreClock/2)  / frequency) - 1);

  if( pTIM == &hTIM3 )
  {
    pOC = &OC3;
    pTIM->Instance = TIM3;
  }
  else if( pTIM == &hTIM1 )
  {
    uwPeriodValue = (uint32_t) (((SystemCoreClock)  /  frequency) - 1);
    pOC = &OC1;
    pTIM->Instance = TIM1;
  }
  else if( pTIM == &hTIM2 )
  {
    pOC = &OC2;
    pTIM->Instance = TIM2;
  }
  else if( pTIM == &hTIM9 )
  {
    uwPeriodValue = (uint32_t) (((SystemCoreClock)  /frequency) - 1);
    pOC = &OC9;
    pTIM->Instance = TIM9;
  }
  else if( pTIM == &hTIM11 )
  {
    uwPeriodValue = (uint32_t) (((SystemCoreClock)  /  frequency) - 1);
    pOC = &OC11;
    pTIM->Instance = TIM11;
  }
  else if( pTIM == &hTIM12 )
  {
    pOC = &OC12;
    pTIM->Instance = TIM12;
  }
  else
  {
    return;
  }

  
  pTIM->Init.Period            = 2500;
  pTIM->Init.Prescaler = (uwPeriodValue /pTIM->Init.Period) -1;
  pTIM->Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  pTIM->Init.CounterMode       = TIM_COUNTERMODE_UP;
  pTIM->Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(pTIM);

  memset(pOC, 0, sizeof(TIM_OC_InitTypeDef));

  pOC->OCMode       = TIM_OCMODE_PWM1;
  pOC->OCPolarity   = TIM_OCPOLARITY_HIGH;
  pOC->OCFastMode   = TIM_OCFAST_DISABLE;
  pOC->OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  pOC->OCNIdleState = TIM_OCNIDLESTATE_RESET;
  pOC->OCIdleState  = TIM_OCIDLESTATE_RESET;

  pOC->Pulse =1250;
  HAL_TIM_PWM_ConfigChannel(pTIM, pOC, tim_ch);
  HAL_TIM_PWM_Start(pTIM, tim_ch);
  }
}

motor_set(int num,float duty){
TIM_HandleTypeDef  *pTIM;
  TIM_OC_InitTypeDef *pOC;
  uint32_t tim_ch;
  pTIM   = g_Pin2PortMapArray[ pwm_pins[num]].TIMx;
  tim_ch = g_Pin2PortMapArray[pwm_pins[num]].timerChannel;
  if     ( pTIM->Instance == TIM3 ) pOC = &OC3;
  else if( pTIM->Instance == TIM1 ) pOC = &OC1;
  else if( pTIM->Instance == TIM2 ) pOC = &OC2;
  else if( pTIM->Instance == TIM9 ) pOC = &OC9;
  else if( pTIM->Instance == TIM11 ) pOC = &OC11;
  else if( pTIM->Instance == TIM12 ) pOC = &OC12;
  else
  {
    return;
  }
  pOC->Pulse = duty*2500;
  HAL_TIM_PWM_ConfigChannel(pTIM, pOC, tim_ch);
  HAL_TIM_PWM_Start(pTIM, tim_ch); 

}

