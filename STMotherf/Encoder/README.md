\@note   
Encoder mode and External clock mode 2 are not compatible and must not be selected together  
        Ex: A call for @ref HAL_TIM_Encoder_Init will erase the settings of @ref HAL_TIM_ConfigClockSource using TIM_CLOCKSOURCE_ETRMODE2 and vice versa  
Unfinished ErrorHandle() function  
  
  
  

**Timer 3, 4:**
Length: 16 bits  
FCLK: 16MHz  
////////////////////////////////////////////////////////////////  
Users Manual:  
    First of all, declare encoder variables in Encoder type  
        Ex:  ```Encoder left, right;```  
    Then, use EncoderInit function to initialize the encoder  
        Ex: ```Encoder_Init(&left, &right);```  
    **Note** that the first parameter is assign to htim3 and second one for htim4  
    Use ```RPM(:grey_question:)``` or ```Direction(:grey_question:)``` to get the value you need  
///////////////////////////////////////////////////////////////  