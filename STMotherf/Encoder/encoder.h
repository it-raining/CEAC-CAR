#ifndef encoder_h
#define encoder_h

class Encoder 
{
private:
    uint32_t value_1, value_2;
    TIM_HandleTypeDef *htim;
public: 
    Encoder(TIM_HandleTypeDef *htim):htim(htim) {};
    void Encoder_Init();
    int RPM(); //return speed of encoder
    byte Direction(); //get direction
}encoder_1, encoder_2;


#endif