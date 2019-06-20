
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

  int max2R=2200;
  int max2L=2200;
  int max3R=2200;
  int max3L=2200;
  int min2R=900;
  int min2L=900;
  int min3R=900;
  int min3L=900;

// definición de valores iniciales preestablecidos de apertura 
  #define OPEN2L 1460
  #define OPEN2R 1610
  #define OPEN3L  1460
  #define OPEN3R 1610

  #define CLOSE2L 1050
  #define CLOSE2R 2000
  #define CLOSE3L 940
  #define CLOSE3R 2100
  
  int contA=0;
  int contB=0;
  bool FlagD=false;
  bool BotonPulsadoD=false;

  int Estado=0; //Estado=0-> CERRADO; Estado=1->ABIERTO;
  
void setup() 
{
    pinMode(BotonD, INPUT_PULLUP);
    pinMode(PosPedal, INPUT_PULLUP);
    pinMode(PosVolante; INPUT_PULLUP);
    pinMode(Pte Calibración; INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    2L.attach(Servo2L);
    2R.attach(Servo2R);
    3L.attach(Servo3L);
    3R.attach(Servo3R);

    //saludo
    3L.writeMicroseconds (max3L);
    3R.writeMicroseconds (min3R);

    //inicializar servos a posición cerrada
    2L.writeMicroseconds (CLOSE2L);
    2R.writeMicroseconds (CLOSE2R);
    3L.writeMicroseconds (CLOSE3L);
    3R.writeMicroseconds (CLOSE3R);

    Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
