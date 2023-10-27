# CEAC-CAR
\@note   Encoder mode and External clock mode 2 are not compatible and must not be selected together  
/  *         Ex: A call for @ref HAL_TIM_Encoder_Init will erase the settings of @ref HAL_TIM_ConfigClockSource using TIM_CLOCKSOURCE_ETRMODE2 and vice versa  

`Timer 3, 4:`  
Length: 16 bits  
FCLK: 16MHz  
