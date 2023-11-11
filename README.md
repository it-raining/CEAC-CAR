# CEAC-CAR
- 4INT encoder
- TIM3
	- CH1 : PB4
	- CH2 : PB5
 - TIM4
	- CH1 : PD12
	- CH2 : PD13
 
- OC after 16-bit pulses 4PWM DC motor
 - TIM8
	- CH1 : PC6
	- CH2 : PC7
	- CH3 : PC8	
	- CH4 : PC9
 
- 3INT echo
 - TIM9
	- CH2 : PE6
 - TIM10
	- CH1 : PB8 
 - TIM11
	- CH1 : PB9

- 1GPIO trig : PC3

- 8 analog do line
 - ADC1 - DMA2 Stream0
	- INT0 - PA0
	- INT1 - PA1
	- INT2 - PA2
	- INT3 - PA3
	- INT4 - PA4
	- INT5 - PA5
	- INT6 - PA6
	- INT7 - PA7

- 3x5 GPIO LED 7 
	- GROUP 1: 
		- PB2 
		- PE7
		- PE8
		- PE9
		- PE10
	- GROUP 2:
		- PE11
		- PE12
		- PE13
		- PE14
		- PE15
	- GROUP 3:
		- PD8
		- PB12
		- PB13
		- PB14
		- PB15

- 1 Analog for Power Supply 
	- ADC2
		- INT8 : PB0

- 5GPIO Led don
	- PA9
	- PA10
	- PA11
	- PA12
	- PA13

- 2INT end-stop
	- EXTI13 : PC13
	- EXIT14 : PC14

- 1PWM servo 
	- TIM2
		- CH4 : PB11

- 2UART BLE 
	- UART4
		- TX : PC10 
		- RX : PC11

- 2GPIO SW 
	- PD13
	- PD14

- 4INT button 
	- EXTI2 - PE2
	- EXTI3 - PE3
	- EXTI4 - PE4
	- EXTI5-- PE5

- 1 RESET Button -- NRST

Wake up by ADC1-INT0


