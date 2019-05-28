#include <Servo.h>

  #define DRS 2

  #define CALIBRATION 3
  #define UpThird 6
  #define DownThird 7
  #define UpSecond 8
  #define DownSecond 9 
  
  #define THROTTLE 4
  int THRES_VALUE=120
  
  #define STEERING A5
  #define LIMIT1 0
  #define LIMIT2 1023
  #define CENTRE 511
  #define ZONE 0.25
  
  #define UPRIGHT A0
  #define UPLEFT A1
  #define DOWNRIGHT A2
  #define DOWNLEFT A3
   
  Servo UpRight;
  Servo UpLeft;
  Servo DownRight;
  Servo DownLeft;

// definición de valores iniciales preestablecidos (posición comprobada ideal)
  #define CLOSE_UpRight 2170
  #define OPEN_UpRight 1610
   
  #define CLOSE_UpLeft 940
  #define OPEN_UpLeft  1460
   
   
  #define CLOSE_DownRight 2000
  #define OPEN_DownRight 1610
   
  #define CLOSE_DownLeft 1050
  #define OPEN_DownLeft 1425

  int contA=0;
  int contB=0;
  int PressedTime=0;

  bool DRSButton;

  int DRS_STATE=0;  //DRS_STATE=0 ->POWER; DRS_STATE=1 ->OPEN; DRS_STATE=2 ->CLOSED
  
void setup() 
{
    pinMode(DRS, INPUT_PULLUP);
    pinMode(THROTTLE, INPUT_PULLUP);
    pinMode(CALIBRATION; INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    
    UpRight.attach(UPRIGHT);
    UpLeft.attach(UPLEFT);
    DownRight.attach(DOWNRIGHT);
    DownLeft.attach(DOWNLEFT);

//inicializar servos a posición cerrada
    UpRight.writeMicroseconds (CLOSE_UpRight);
    UpLeft.writeMicroseconds (CLOSE_UpLeft);
    DownRight.writeMicroseconds (CLOSE_DownRight);
    DownLeft.writeMicroseconds (CLOSE_DownLeft);

    Serial.begin(9600);

}

void loop() 
{
  {
  if (digitalRead(DRS)==0)         // si no se pulsa el botón de activación de DRS
  {
    contB=0;
    DRSButton=0;
  }
  else if (digitalRead(DRS)==1)    // si se pulsa el botón de activación de DRS
  {
    if (contB==0)
    {
      contA=millis();
      contB=contB+1; 
    }
    else if (contB!=0)
    {
      contB=contB+1;
    }
    PressedTime=contA-contB;
    if (PressTime>50)             // si el tiempo de mantenimiento de pulsación de botón de DRS superior a 50 ms se lleva a cabo la acción
    {
      DRSButton=1;
    }
    else if (PressedTime<50)      // si el tiempo de mantenimiento de pulsación de botón DRS inferior a 50 ms no se tiene en cuenta
    {
      DRSButton=0;
    }
  }
  if (DRSButtonBefore==0 && DRSButton==1)    //Flanco ascendente de Botón Pulsado (para evitar una activación o desactivación mientras se lleva a cabo una acción)
  {
    DRS_STATE=DRS_STATE+1;
    if (DRS_STATE==0)
    {
      DRS_STATE=DRS_STATE+1;
    }
    else if (DRS_STATE==1)
    {
      if (LIMIT1<LIMIT2)
      {
        if(analogRead(STEERING)<(CENTRE-(CENTRE-LIMIT1)*ZONE))|| (analogRead(STEERING)>((LIMIT2-CENTRE)*ZONE)+CENTRE)
        {
          DRS_STATE=0;
        }
        else if (analogRead(STEERING)>(CENTRE-(CENTRE-LIMIT1)*ZONE))||(analogRead(STEERING)<((LIMIT2-CENTRE)*ZONE)+CENTRE)
        {
          if (analogRead(THROTTLE)==THRES_VALUE)
          {
            UpRight.writeMicroseconds (DVUpRight);
            UpLeft.writeMicroseconds (DVUpLeft);
            DownRight.writeMicroseconds (DVDownRight);
            DownLeft.writeMicroseconds (DVDownLeft);
          }
        }
      }
      else if (LIMIT1>LIMIT2)
      {
        if (analogRead(STEERING)<((LIMIT1-CENTRE)*ZONE)+CENTRE)|| (analogRead(STEERING)>((CENTRE-(CENTRE-LIMIT2)*ZONE)
        {
          DRS_STATE=0;
        }
        else if (analogRead(STEERING)>((LIMIT1-CENTRE)*ZONE)+CENTRE)|| (analogRead(STEERING)<((CENTRE-(CENTRE-LIMIT2)*ZONE)
        {
          UpRight.writeMicroseconds (DVUpRight);
          UpLeft.writeMicroseconds (DVUpLeft);
          DownRight.writeMicroseconds (DVDownRight);
          DownLeft.writeMicroseconds (DVDownLeft);
        }
      }
    }
    else if (DRS_STATE==2)
    {
      UpRight.writeMicroseconds (CLOSE_UpRight);
      UpLeft.writeMicroseconds (CLOSE_UpLeft);
      DownRight.writeMicroseconds (CLOSE_DownRight);
      DownLeft.writeMicroseconds (CLOSE_DownLeft);
      DRS_STATE==0;
    }
  }
  DRSButtonBefore=DRSButton;
  break;
  }



  {
    if (digitalRead(THROTTLE)==0)
    {
      DVUpLeft= PosServoUpLeft;
      DVUpRight= PosServoUpRight;
      DVDownLeft= PosServoDownLeft;
      DVDownRight= PosServoDownRight;
    }
    while (digitalRead(THROTTLE)==1)
    {
      if (digitalRead(UpThird)==1)
      {
        PosServoUpLeft= OPEN_UpLeft+10;
        UpLeft.writeMicroseconds (PosServoUpLeft);
        PosServoUpRight= OPEN_UpRight+10;
        UpRight.writeMicroseconds (PosServoUpRight);
      }
      if (digitalRead(DownThird)==1)
      {
        PosServoUpLeft= OPEN_UpLeft-10;
        UpLeft.writeMicroseconds (PosServoUpLeft);
        PosServoUpRight= OPEN_UpRight-10;
        UpRight.writeMicroseconds (PosServoUpRight);
      }
      if (digitalRead(UpSecond)==1)
      {
        PosServoDownLeft= OPEN_DownLeft+10;
        DownLeft.writeMicroseconds (PosServoDownLeft);
        PosServDownRight= OPEN_DownRight+10;
        DownRight.writeMicroseconds (PosServoDownRight);
      }
      if (digitalRead(DownSecond)==1)
      {
        PosServoDownLeft= OPEN_DownLeft-10;
        DownLeft.writeMicroseconds (PosServoDownLeft);
        PosServDownRight= OPEN_DownRight-10;
        DownRight.writeMicroseconds (PosServoDownRight);
      }
    }
  }
  
}
