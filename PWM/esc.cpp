#include "esc.h"



esc::esc(){
  
}



void esc::init(){
int i=0;

  for(i=0;i<5;i++){
  
        TIM_HandleTypeDef  *pTIM;
        TIM_OC_InitTypeDef *pOC;
        uint32_t tim_ch;
        uint32_t uwPeriodValue;

        if( pwm_pins[i] >= PINS_COUNT )     return;
        if( pwm_init[pwm_pins[i]] == true ) return;


        pTIM   = g_Pin2PortMapArray[pwm_pins[i]].TIMx;
        tim_ch = g_Pin2PortMapArray[pwm_pins[i]].timerChannel;
        uwPeriodValue = (uint32_t) (((SystemCoreClock/2)  / 400) - 1);

        if( pTIM == &hTIM3 )
        {
        pOC = &OC3;
        pTIM->Instance = TIM3;
        }
        else if( pTIM == &hTIM1 )
        {
        uwPeriodValue = (uint32_t) (((SystemCoreClock)  / 400) - 1);
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
        uwPeriodValue = (uint32_t) (((SystemCoreClock)  /400) - 1);
        pOC = &OC9;
        pTIM->Instance = TIM9;
        }
        else if( pTIM == &hTIM11 )
        {
        uwPeriodValue = (uint32_t) (((SystemCoreClock)  / 400) - 1);
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

        pTIM->Init.Prescaler         = 215;  //216  -1
        pTIM->Init.Period            = 2499; //2500 -1
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

        pOC->Pulse = 0;
        HAL_TIM_PWM_ConfigChannel(pTIM, pOC, tim_ch);
        HAL_TIM_PWM_Start(pTIM, tim_ch);
        pwm_init[pwm_pins[i]] = true;
  }
}


/*

bool     pwm_init[PINS_COUNT];
int pwm_pins[5] = { 3, 5, 9, 10, 11 };
TIM_OC_InitTypeDef        hOC1;
TIM_OC_InitTypeDef        hOC2;
TIM_OC_InitTypeDef        hOC3;
TIM_OC_InitTypeDef        hOC9;
TIM_OC_InitTypeDef        hOC11;
TIM_OC_InitTypeDef        hOC12;
void esc::init(){
	int i=0;
	for(i=0;i<5;i++){
	
				TIM_HandleTypeDef  *pTIM;
				TIM_OC_InitTypeDef *pOC;
				uint32_t tim_ch;
				uint32_t uwPeriodValue;

				if( ulPin >= PINS_COUNT )     return;
				if( pwm_init[ulPin] == true ) return;


				pTIM   = g_Pin2PortMapArray[ulPin].TIMx;
				tim_ch = g_Pin2PortMapArray[ulPin].timerChannel;
				uwPeriodValue = (uint32_t) (((SystemCoreClock/2)  / 400) - 1);

				if( pTIM == &hTIM3 )
				{
				pOC = &hOC3;
				pTIM->Instance = TIM3;
				}
				else if( pTIM == &hTIM1 )
				{
				uwPeriodValue = (uint32_t) (((SystemCoreClock)  / 400) - 1);
				pOC = &hOC1;
				pTIM->Instance = TIM1;
				}
				else if( pTIM == &hTIM2 )
				{
				pOC = &hOC2;
				pTIM->Instance = TIM2;
				}
				else if( pTIM == &hTIM9 )
				{
				uwPeriodValue = (uint32_t) (((SystemCoreClock)  /400) - 1);
				pOC = &hOC9;
				pTIM->Instance = TIM9;
				}
				else if( pTIM == &hTIM11 )
				{
				uwPeriodValue = (uint32_t) (((SystemCoreClock)  / 400) - 1);
				pOC = &hOC11;
				pTIM->Instance = TIM11;
				}
				else if( pTIM == &hTIM12 )
				{
				pOC = &hOC12;
				pTIM->Instance = TIM12;
				}
				else
				{
				return;
				}

				pTIM->Init.Prescaler         = 215;  //216  -1
				pTIM->Init.Period            = 2499; //2500 -1
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

				pOC->Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(pTIM, pOC, tim_ch);
				HAL_TIM_PWM_Start(pTIM, tim_ch);
				pwm_init[ulPin] = true;
		

	}

}


void esc::setvalue(uint32_t ulPin, uint32_t ulDuty){
  TIM_HandleTypeDef  *pTIM;
  TIM_OC_InitTypeDef *pOC;
  uint32_t tim_ch;

  if( ulPin >= PINS_COUNT )     return;
  if( pwm_init[ulPin] == false ) return;


  pTIM   = g_Pin2PortMapArray[ulPin].TIMx;
  tim_ch = g_Pin2PortMapArray[ulPin].timerChannel;

  if     ( pTIM->Instance == TIM3 ) pOC = &hOC3;
  else if( pTIM->Instance == TIM1 ) pOC = &hOC1;
  else if( pTIM->Instance == TIM2 ) pOC = &hOC2;
  else if( pTIM->Instance == TIM9 ) pOC = &hOC9;
  else if( pTIM->Instance == TIM11 ) pOC = &hOC11;
  else if( pTIM->Instance == TIM12 ) pOC = &hOC12;
  else
  {
    return;
  }
  pOC->Pulse = ulDuty;
  HAL_TIM_PWM_ConfigChannel(pTIM, pOC, tim_ch);
  HAL_TIM_PWM_Start(pTIM, tim_ch);
}
}

*/



void esc::setup(uint32_t ulPin )
{
  TIM_HandleTypeDef  *pTIM;
  TIM_OC_InitTypeDef *pOC;
  uint32_t tim_ch;
  uint32_t uwPeriodValue;

  drv_pwm_set_freq(ulPin, 400);

  
  if( ulPin >= PINS_COUNT )     return;
  if( pwm_init[ulPin] == true ) return;


  pTIM   = g_Pin2PortMapArray[ulPin].TIMx;
  tim_ch = g_Pin2PortMapArray[ulPin].timerChannel;
  uwPeriodValue = (uint32_t) (((SystemCoreClock/2)  / 400) - 1);

  if( pTIM == &hTIM3 )
  {
    pOC = &OC3;
    pTIM->Instance = TIM3;
  }
  else if( pTIM == &hTIM1 )
  {
    uwPeriodValue = (uint32_t) (((SystemCoreClock)  / 400) - 1);
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
    uwPeriodValue = (uint32_t) (((SystemCoreClock)  /400) - 1);
    pOC = &OC9;
    pTIM->Instance = TIM9;
  }
  else if( pTIM == &hTIM11 )
  {
    uwPeriodValue = (uint32_t) (((SystemCoreClock)  / 400) - 1);
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

  pTIM->Init.Prescaler         = 215;  //216  -1
  pTIM->Init.Period            = 2499; //2500 -1
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

  pOC->Pulse = 500;
  HAL_TIM_PWM_ConfigChannel(pTIM, pOC, tim_ch);
  HAL_TIM_PWM_Start(pTIM, tim_ch);
  pwm_init[ulPin] = true;
}

