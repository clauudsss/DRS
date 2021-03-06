
#include <Servo.h>

  #define BotonD 2
  
  #define BotonC 3
  #define BotonS3 4
  #define BotonB3 7
  #define BotonS2 8
  #define BotonB2 11 
  #define PteCalibración 12
  
  #define PosPedal A4
  #define delta 800
  #define minPedal 0
  #define maxPedal 1023
  
  #define PosVolante A5
  #define minVolante 0
  #define maxVolante 1023
  #define alpha 383
  #define beta 639

  #define Servo2L 5
  #define Servo2R 6
  #define Servo3L 9
  #define Servo3R 10
  
  Servo 2L;
  Servo 2R;
  Servo 3L;
  Servo 3R;

  #define max2R 2200
  #define max2L 2200
  #define max3R 2200
  #define max3L 2200
  #define min2R 900
  #define min2L 900
  #define min3R 900
  #define min3L 900

// definición de valores iniciales preestablecidos de apertura 
  #define OPEN2L 1460
  #define OPEN2R 1610
  #define OPEN3L  1460
  #define OPEN3R 1610

  #define CLOSE2L 1050
  #define CLOSE2R 2000
  #define CLOSE3L 940
  #define CLOSE3R 2100
  
  int A=0;
  int B=0;
  bool FlagD=false;
  bool BotonDPulsado=false;
  bool BotonDPulsadoAnt=false;
  int BotonS2Ant=0;
  int BotonB2Ant=0;
  int BotonS3Ant=0;
  int BotonB3Ant=0;

  int Estado=0; //Estado=0-> CERRADO; Estado=1->ABIERTO;
  
void setup() 
{
    pinMode(BotonD, INPUT_PULLUP);
    pinMode(PosPedal, INPUT_PULLUP);
    pinMode(PosVolante; INPUT_PULLUP);
    pinMode(PteCalibración; INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    2L.attach(Servo2L);
    2R.attach(Servo2R);
    3L.attach(Servo3L);
    3R.attach(Servo3R);

    //saludo
    2L.writeMicroseconds (min2L);
    2R.writeMicroseconds (max2R);
    3L.writeMicroseconds (min3L);
    3R.writeMicroseconds (max3R);
    delay(1000);
    3L.writeMicroseconds (max3L);
    3R.writeMicroseconds (min3R);
    2L.writeMicroseconds (max2L);
    2R.writeMicroseconds (min2R);
    delay(1000);
    2L.writeMicroseconds (min2L);
    2R.writeMicroseconds (max2R);
    delay(1000);
    3L.writeMicroseconds (min3L);
    3R.writeMicroseconds (max3R);
    2L.writeMicroseconds (max2L);
    2R.writeMicroseconds (min2R);
    delay(1000);
    2L.writeMicroseconds (min2L);
    2R.writeMicroseconds (max2R);
    delay (1000);

    //inicializar servos a posición cerrada
    2L.writeMicroseconds (CLOSE2L);
    2R.writeMicroseconds (CLOSE2R);
    3L.writeMicroseconds (CLOSE3L);
    3R.writeMicroseconds (CLOSE3R);
    delay(1000);

    Serial.begin(9600);

}

void loop() 
{
  if (digitalRead(PteCalibracion)==1)
  {
    if (digitalRead(BotonC)==1)
    {
      if ((digitalRead(BotonS2)==1) && BotonS2Ant==0)
      {
        posservo2L=digitalRead(Servo2L);
        posservo2R=digitalRead(Servo2R);
        if (posservo2L+10<=max2L) && (posservo2R-10<=CLOSE2R)
        posservo2L=posservo2L+10;
        posservo2R=posservo2R-10;
      }
      if ((digitalRead(BotonB2)==1) && BotonB2Ant==0)
      {
        posservo2L=digitalRead(Servo2L);
        posservo2R=digitalRead(Servo2R);
        if (posservo2L-10<=CLOSE2L) && (posservo2R+10<=max2R)
        posservo2L=posservo2L-10;
        posservo2R=posservo2R+10;
      }
      if ((digitalRead(BotonS3)==1)&& BotonS3Ant==0)
      {
        posservo3L=digitalRead(Servo3L);
        posservo3R=digitalRead(Servo3R);
        if (posservo3L+10<=max3L) && (posservo3R-10<=CLOSE3R)
        posservo3L=posservo3L+10;
        posservo3R=posservo3R-10;
      }
      if ((digitalRead(BotonB3)==1) && BotonB3Ant==0)
      {
        posservo3L=digitalRead(Servo3L);
        posservo3R=digitalRead(Servo3R);
        if (posservo3L-10<=CLOSE3L) && (posservo3R+10<=max3R)
        posservo3L=posservo3L-10;
        posservo3R=posservo3R+10;
      }
    }
    else if (digitalRead(BotonC)==0)
    {
      OPEN2L=posservo2L;
      OPEN2R=posservo2R;
      OPEN3L=posservo3L;
      OPEN3R=posservo3R;
    }
    BotonS2Ant=digitalRead(BotonS2);
    BotonB2Ant=digitalRead(BotonB2);
    BotonS3Ant=digitalRead(BotonS3);
    BotonB3Ant=digitalRead(BotonB3);
  }
  else if (digitalRead(PteCalibracion)==0)
  {
    if (digitalRead(BotonD)==1)
    {
      if (FlagD==false)
      {
        A=millis();
        FlagD=true;
      }
      B=millis();
      if (contB>=(contA+50))
      {
        BotonDPulsado=true;
      }
      else if (contB<(contA+50))
      {
        BotonDPulsado=false;
      }
    }
    else if (digitalRead(BotonD)==0)
    {
      FlagD=false;
      BotonDPulsado=false;
    }
    if ((Estado==0)&&((BotonDPulsado=true) && (BotonDPulsadoAnt=false))&&(alpha<=analogRead(PosVolante)<=beta)&&(analogRead(PosPedal)>=delta))
    {
      Estado=1;
      2L.writeMicroseconds (OPEN2L);
      2R.writeMicroseconds (OPEN2R);
      3L.writeMicroseconds (OPEN3L);
      3R.writeMicroseconds (OPEN3R);
      delay(1000);
      BotonDPulsadoAnt=true;
    }
    if ((Estado==1)&&((BotonDPulsado=true) && (BotonDPulsadoAnt=false))&&((analogRead(PosVolante)<alpha)||(analogRead(PosVolante>beta)&&(analogRead(PosPedal)<delta))
    {
      Estado=0;
      2L.writeMicroseconds (CLOSE2L);
      2R.writeMicroseconds (CLOSE2R);
      3L.writeMicroseconds (CLOSE3L);
      3R.writeMicroseconds (CLOSE3R);
      delay(1000);
    }
    BotonDPulsadoAnt=BotonDPulsado;
  }
}
