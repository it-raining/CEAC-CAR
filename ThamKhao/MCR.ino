#include <Servo.h>
Servo myservo;
#define RDIR 10// chiều quay động cơ phải
#define LDIR 9// chiều quay động cơ trái
#define LPWM 5// tốc độ động cơ trái
#define RPWM 6// tốc độ động cơ phải
#define BUTTON1 0// nút nhấn 1
#define BUTTON2 1// nút nhấn 2
#define BUTTON3 7// nút nhấn 3
#define BUTTON4 8// nút nhấn 4
#define BUZZER 4// chân điều khiển loa
#define SERVO 11// Chân điều khiển RC servo
#define LED3 12// Chân led3 trên mạch
#define LED4 13// Chân led4 trên mạch

//---------------------------------------------------

unsigned char sensor;
unsigned char in, start;
int RC_ANGLE;
int handle_center = 81;
int speed_run_forward;
signed int line;
signed char vitri;
unsigned long lastTime, cnt4;
unsigned char pattern;
char code;
int RF_speed = 0;
const char hesoR1[51] ={ 
  100, 99, 	98, 	97, 	97, 	96, 	95, 	94, 	93, 	92, 	91, 	90, 	89, 	88, 	88, 	87, 	86, 	85, 	84, 	83, 	82, 	81, 	80, 	79, 	78, 	77, 	76, 	75, 	73, 	72, 	71, 	70, 	69, 	68, 	66, 	65, 	64, 	62, 	61, 	60, 	58, 	57, 	55, 	53, 	52, 	50, 	48, 	46, 	44, 	42, 	40
};// vi sai
const char hesoR3[51] ={
  100, 101, 	102, 	103, 	103, 	104, 	105, 	106, 	107, 	108, 	109, 	110, 	111, 	112, 	112, 	113, 	114, 	115, 	116, 	117, 	118, 	119, 	120, 	121, 	122, 	123, 	124, 	125, 	127, 	128, 	129, 	130, 	131, 	132, 	134, 	135, 	136, 	138, 	139, 	140, 	142, 	143, 	145, 	147, 	148, 	150, 	152, 	154, 	156, 	158, 	160
};// vi sai

void setup() {


  //---------------PWM------------------------//
  myservo.attach(SERVO); // chân 9 là chân servo
  pinMode(LDIR, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(RDIR, LOW);
  digitalWrite(LDIR, LOW);

  //---------------Port Sensor------------------------//
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);  
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  //-------------------------------------------------//
  speed_run_forward =230; //bạn thay đổi tốc độ ở đây, tốc độ chạy max 255, min 10
  //CÀI ĐẶT CÁC THÔNG SỐ BAN ĐẦU
  handle( 0 );// bẻ góc 0 độ
  ( 0, 0 );// dừng 2 bánh
  pattern = 11;// set trạng thái chạy
  vitri = 0;
  start = 0;
  //-------------------------------------------------//
  for(int i = 2000; i< 3500; i += 500){
    tone(BUZZER, i ,100);
    delay(100);
  }
  //  noTone(BUZZER);
  //-------------------------------------------------//
  Serial.begin(9600);
}

void loop()// vòng lặp, không dùng delay() trong này
{

  while(start == 0)// nhấn nút để chạy
  {
    if((millis()/100%2) == 0) 
      digitalWrite(LED3, HIGH);
    else digitalWrite(LED3, LOW);
    if (digitalRead(BUTTON3) == 0) {
      start = 1;
      cnt4 = millis();
    }
    sensor = sensor_inp(0xff);
     Serial.println(sensor);
  }
 
  switch( pattern ) {// đoạn mã trạng thái máy

 case 11:
       /* time run = cnt4    60000 = 1phut */
        if((millis() - cnt4) > 60000){
          pattern = 100;
          break;
        }
        
        if(check_crossline()) {       // Kiem tra line ngang cua vuong
          pattern = 21;
          break;
        }

        else {          // kiem tra nua line ngang qua chuyen lan
          switch (check_crosshalfline())
          {
            case 1:
              pattern = 12;
              break;
            case 2:
              pattern = 13;
              break;
            default : 
              break;
          }
        }
        runforwardline(speed_run_forward);
        break;
      case 12:
        /* Check of large turning to the right completion */
        if( check_crossline()) {   /* Crossline check even during turning */
          pattern = 21;
          break;
        }
        pattern = left_lance(80);
        break;
      case 13:
        /* Check of large turning completion to the left */
        if( check_crossline() ) {   /* Crossline check even during large turn */
          pattern = 21;
          break;
        }
        pattern = right_lance(80);
        break;

      case 21:
        /* Process when first crossline is detected */
        pattern = gocturn90(80);
        break;
      
      case 100: 
        runforwardline(0);
        break;
      default:
        pattern = 11;        
        break;

    break;
  }

}
//--------------------------------------------------------------------------//
void runforwardline (int tocdo)// hàm chạy bám line
{
  unsigned char temp;
  temp = sensor_inp(0xff);
  switch(temp) {
  case 0x18:// 00011000
  case 0x3c:// 00111100
  case 0x38:// 00111000
  case 0x1C:// 00011100


    handleAndSpeed (0,tocdo);
    vitri = 0;
    break;
  case 0x08:// 00001000
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }
    else
      handleAndSpeed (1,tocdo);		
    vitri = 1;
    break;
  case 0x0c:// 00001100
  case 0x1e:
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }
    else

        handleAndSpeed (2,tocdo);

    vitri = 2;
    break;
  case 0x04:// 00000100
  case 0x0e:// clear 00001110
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }

    else

        handleAndSpeed (5,tocdo);		
    vitri = 3;
    break;
  case 0x06:// 00000110
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }
    else

        handleAndSpeed (15,tocdo*85/100);

    vitri = 4;
    break;
  case 0x02:// 00000010
  case 0x07:// 00000111
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }

    else

        handleAndSpeed (15,tocdo*85/100);

    vitri = 5;
    break;
  case 0x03:// 00000011
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }
    else

        handleAndSpeed (17,tocdo*85/100);
    vitri = 6;
    break;
  case 0x01:// 00000001
    if ( vitri < -3)
    {
      handleAndSpeed (-30,0);
      break;
    }

    handleAndSpeed (17,tocdo*85/100);
    vitri = 6;

    break;
  case 0x81:// 10000001
  case 0xc1:// 11000001
  case 0x00:// 00000000
  case 0x83:// 10000011
    if ( vitri < -4)
    {
      handleAndSpeed (-27,0);
      speed_run(30,0);
      break;
    }
    else if ( vitri > 4)
    {
      handleAndSpeed (27,0);
      speed_run(0,30);
      break;
    }
    break;
  case 0x10:// 00010000
    if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }
    else

        handleAndSpeed (-1,tocdo);
    vitri = -1;
    break;
  case 0x30:// 00110000
  case 0x78:
    if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }
    else

        handleAndSpeed (-2,tocdo);
    vitri = -2;
    break;

  case 0x20:// 00100000
  case 0x70:// clear 01110000
    if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }

    else

        handleAndSpeed (-5,tocdo);


    vitri = -3;
    break;
  case 0x60:// 01100000

      if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }
    else

        handleAndSpeed (-15,tocdo*85/100);	
    vitri = -4;
    break;
  case 0x40:// 01000000
  case 0xe0:// 11100000

      if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }
    else
      handleAndSpeed (-15,tocdo*85/100);		
    vitri = -5;
    break;
  case 0xc0:// 11000000
    if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }
    else
      handleAndSpeed (-17,tocdo*85/100);		
    vitri = -6;
    break;
  case 0x80:// 10000000
    if ( vitri > 3)
    {
      handleAndSpeed (30,0);
      break;
    }
    else


        handleAndSpeed (-17,tocdo*85/100);

    vitri = -6;
    break;
  case 0x0f: 
    break;
  case 0xf0: 
    break;
  default:
    speed_run(0,0);
    break;
  }
}
//---------------------------------------------------------------------------//
void handleAndSpeed (int angle,int speed1)// hàm bẻ góc đồng thời tính vi sai cho 2 bánh
{
  int speed2;
  int speed3;
  handle (angle);
  if (angle<0){
    angle = -angle;
    speed2 = speed1*hesoR1[angle]/100;
    speed3 = speed1*hesoR3[angle]/100;
    speed_run(speed2,speed3);
  }
  else if (angle == 0 )
  {
    speed_run(speed1,speed1);
  }
  else {
    speed2 = speed1*hesoR1[angle]/100;
    speed3 = speed1*hesoR3[angle]/100;
    speed_run(speed3,speed2);
  }
}
//--------------------------------------------------------------------------//
char check_crossline()// hàm kiểm tra line ngang
{
  unsigned char b;

  b = sensor_inp(0xe7);

  if(b == 0xe7)
    return 1;
  else 
    return 0;

}
//--------------------------------------------------------------------------//
char check_crosshalfline()// hàm kiểm tra nữa line ngang
{
  if ((check_crossline() == 0)){
    if ((sensor_inp(0xf0)==0xf0)||(sensor_inp(0xf0)==0xd0)||(sensor_inp(0xf0)==0xb0))
      return 1;
    else if ((sensor_inp(0x0f)==0x0f)||(sensor_inp(0x0f)==0x0b)||(sensor_inp(0x0f)==0x0d))
      return 2;		
    else 
      return 0;	
  }
  else return 0;
}
//-----------------------------------------------------------------------//
unsigned char sensor_inp (unsigned char MASK)// hàm mặt nạ để che cảm biến
{
  sensor = read_sensor();
  return ( sensor & MASK);
}
//-------------------------------------------------------------------//
unsigned char read_sensor()// hàm đọc cảm biến
{
  char i;
  unsigned char tam = 0, ret = 0;
  unsigned char pin[8];
  pin[0] = digitalRead(3);
  pin[1] = digitalRead(A5);
  pin[2] = digitalRead(A4);
  pin[3] = digitalRead(A3);
  pin[4] = digitalRead(A2);
  pin[5] = digitalRead(A1);
  pin[6] = digitalRead(A0);
  pin[7] = digitalRead(2);
  for (i = 0; i < 8; i++)
  {
    tam = (tam | pin[i]);
    if (i == 7)
    {
      ret = tam;
      break;
    }
    else tam = (tam << 1);

  }
  ret = ~ret;
  return ret;
}



//-----------------------------------------------------------//
void speed_run( int speedDC_left, int speedDC_right)// hàm truyền vào tốc độ động cơ trái + phải
{

  if (speedDC_left < 0)
  {
    analogWrite(LPWM, -speedDC_left);
    digitalWrite(LDIR, HIGH);
  }
  else if (speedDC_left >= 0)
  { 
    speedDC_left = speedDC_left;
    analogWrite(LPWM, speedDC_left); 
    digitalWrite(LDIR, LOW);

  }
  if (speedDC_right < 0)
  {
    analogWrite(RPWM, -speedDC_right);
    digitalWrite(RDIR, HIGH);
  }
  else if (speedDC_right >= 0)
  { 
    speedDC_right = speedDC_right;
    analogWrite(RPWM, speedDC_right);
    digitalWrite(RDIR, LOW);
  }

}
//-------------------------------------------------------------//
void handle(int _angle){// hàm bẻ góc
  RC_ANGLE = handle_center + _angle;
  myservo.write(RC_ANGLE);


}
//-------------------------------------------------------------//
unsigned long getTimer(){
  return (millis()-lastTime);  
}
//-------------------------------------------------------------//
void resetTimer(){
  lastTime = millis();
}
//-------------------------------------------------------------//

// GOC VUONG
/////////////////////////////////////////////////////////////////////////////////////////
int gocturn90(int tocdo)
{
  int pattern2 = 19;
  resetTimer();
  while (1){
    switch (pattern2)
    {
      case 19:
      if (getTimer() < 100)
      {
        runforwardline(0);
        break;
      }
      else
      {
        runforwardline(150);
        pattern2 = 23;
        break;
      }
      break;

      case 23:
      if(getTimer() > 2000){
        return 11;
        break;
      }
        switch (check_crosshalfline())
        {
          case 2://left
          line = -1
          ;
          break;
          case 1://right
          line = 1;
          break;
          default : break;
        }
      if (sensor_inp(0x7f)== 0x00)
      {
        pattern2 = 24;
        resetTimer();
        
        break;
      }
      runforwardline(120);
      break;
      case 24:
      switch( line ) {
        case -1:
        handle (-45);
        speed_run(0,tocdo);
        pattern2 = 41;
        resetTimer();
        
        break;
        case 1:
        handle(45);
        speed_run(tocdo,0);
        pattern2 = 31;
        resetTimer();
        
        break;
        default:
        runforwardline (tocdo);
        break;
      }
      case 31:
      handle (-45);
      speed_run(0,tocdo);
      if ((sensor_inp (0x70) == 0x60))
      {
        resetTimer();
        
        pattern2 = 35;
        break;
      }
      if ((sensor_inp (0x0f) == 0x03))
      {
        resetTimer();
        
        break;
      }
      break;
      case 32:
        handle (-45);
        speed_run(0,tocdo);
        if((sensor_inp(0x0f) == 0x06))
        {
          pattern2 = 33;
          break;
        }
        if((sensor_inp(0x0f) == 0x01))
        {
          pattern2 = 35;
          break;
        }
        break;
      case 33: 
        handle (-45);
        speed_run(0,tocdo);
        if ((sensor_inp(0x0f) == 0x01))
        {
          pattern2 = 35;
          break;
        }
        break;
      case 35:
      handle (-45);//35
      speed_run(0,tocdo);
      if ((sensor_inp (0x0f) == 0x0c) ||  (sensor_inp (0x0f) == 0x0e))
      {
        resetTimer();
        pattern2 = 36;
      }
      break;
      case 36:
      while(getTimer() < 200)
      {
        runforwardline(tocdo);
      }
      return 11;
      break;
      case 41:
      handle (45);
      speed_run(tocdo,0);
      if ((sensor_inp (0x07) == 0x03))
      {
        resetTimer();
        pattern2 = 45;
        break;
      }
      if ((sensor_inp (0x70) == 0x60))
      {
        resetTimer();
        break;
      }
      break;
      case 42:
      handle (45);
      speed_run(tocdo,0);
      if ((sensor_inp(0x70) == 0x03))
      {
        pattern2 = 43;
        break;
      }
      if ((sensor_inp(0x70) == 0x04))
      {
        pattern2 = 45;
        break;
      }
      break;
      case 43:
      handle (45);
      speed_run(tocdo,0);
      if ((sensor_inp(0x70) == 0x40))
      {
        pattern2 = 45;
        break;
      }
      break;
      case 45:
      handle (45);//40
      speed_run(tocdo,0);
      if ((sensor_inp(0x70) == 0x60) || (sensor_inp(0x78) == 0x38) || (sensor_inp(0xf0) == 0x40) || (sensor_inp(0xf0) == 0xe0))
      {
        resetTimer();
        pattern2 = 46;
      }
      break;
      case 46:
      while(getTimer() < 200)
      {
        runforwardline(tocdo);
      }
      return 11;
      break;
      default:
      return 11;
      break;
    }
  }
}

//Chuyen lan trai
//////////////////////////////////////////////////////////////////////////////////////////
int left_lance (int tocdo){
  int pattern3 = 51;
  while (1)
  {  
    if (check_crossline())
    {
      resetTimer();
      return 21;
    }
    
    switch (pattern3)
    {
      case 51:
      if (sensor_inp (0x7f) == 0x00){
        handleAndSpeed (-10,tocdo);
        pattern3 = 56;
        resetTimer();
        break;
      }
      else
      {
        runforwardline(tocdo);
      }
      if (getTimer()>1000)
      {
        resetTimer();
        return 11;
      }
      break;
      case 56:
      if (sensor_inp(0x40)!=0)
      {
        resetTimer();
        handleAndSpeed(0,tocdo);
        pattern3 = 57;
      }
      break;
      case 57:
      if (sensor_inp(0x0f)!=0)
      {
        resetTimer();
        pattern3 = 58;
        break;
      }
      break;
      case 58:
      while(getTimer() < 300)
      {
        runforwardline(tocdo);
      }
      resetTimer();
      pattern3 = 59;
      break;
      case 59:
      while(getTimer() < 200)
      {
        runforwardline(speed_run_forward);
      }
      resetTimer();
      return 11;
      break;
      default:
      return 11;

    }
  }
}



// CHUYEN LAN PHAI
///////////////////////////////////////////////////////////////////////////////////
int right_lance(int tocdo)
{
  int pattern4 = 61;
  while (1)
  {
    if (check_crossline())
    {
     resetTimer();
    
      return 21;
    }
    
    switch (pattern4)
    {
      case 61:
      if (sensor_inp (0x7f) == 0x00){
        handleAndSpeed (10,tocdo);
        pattern4 = 66;
        resetTimer();
        break;
      }
      else
      {
        runforwardline(tocdo);
      }
      if (getTimer()>1500)
      {
        resetTimer();
        
        return 11;
      }
      break;
      case 66:
      if (sensor_inp(0x01)!=0)
      {
        resetTimer();
        handleAndSpeed(0,tocdo);
        pattern4 = 67;
      }
      break;
      case 67:
      resetTimer();
      if (sensor_inp(0x78)!=0)
      {
        resetTimer();
        
        pattern4 = 68;
        break;
      }
      break;
      case 68:
      while(getTimer() < 200)
      {
        runforwardline(tocdo);
      }
      pattern4 = 69;
      resetTimer();
      break;
      case 69:
      while(getTimer() < 200)
      {
        runforwardline(speed_run_forward);
      }
      resetTimer();
      return 11;
      break;
      default:
      return 11;

    }
  }
}
