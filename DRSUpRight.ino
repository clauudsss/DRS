
#include <Servo.h>
#include <EEPROM.h>
#define ABSMAX 2500
#define ABSMIN 500

Servo UpRight;
int CLOSE = 900;
int addr_CLOSE = 0;
int OPEN = 2100;
int addr_OPEN = addr_CLOSE + sizeof(CLOSE);

//steering
#define LIMIT1 0
#define LIMIT2 1023
#define CENTRE 511
#define ZONE 0.25

//brake
#define HIGHTHRES 1
#define LOWTHRES 2

int angle = 0;
int DRS_STATE = 0;
int THRES_TYPE = LOWTHRES;
int THRES_VALUE = 120;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  UpRight.attach(9);
  UpRight.writeMicroseconds (CLOSE);
  Serial.begin (57600);
  Serial.println ("HEY YO");
}

void loop() {
  if (DRS_STATE == 0)
  {
    UpRight.writeMicroseconds (CLOSE);
    if (digitalRead (2) == 1)
    {
      DRS_STATE++;
    }
  }
  else if (DRS_STATE == 1)
  {
    UpRight.writeMicroseconds (OPEN);
    if (digitalRead (2) == 0)
    {
      DRS_STATE++;
    }
  }
  else if (DRS_STATE == 2)
  {
    UpRight.writeMicroseconds (OPEN);
    if (digitalRead (2) == 1)
    {
      DRS_STATE ++;
    }
  }
  else if (DRS_STATE == 3)
  {
    UpRight.writeMicroseconds (CLOSE);
    if (digitalRead (2) == 0)
    {
      DRS_STATE = 0;
    }
  }
  else
  {
    UpRight.writeMicroseconds (CLOSE);
    DRS_STATE = 0;
  }

  int steeringpos = analogRead(A0);
  if (LIMIT1 < LIMIT2)
  {
    if (((LIMIT2 - CENTRE)*ZONE) + CENTRE < steeringpos || steeringpos < CENTRE - (CENTRE - LIMIT1)*ZONE)
    {
      DRS_STATE = 0;
    }
  }
  else if (LIMIT1 > LIMIT2)
  {
    if (((LIMIT1 - CENTRE)*ZONE) + CENTRE < steeringpos || steeringpos < CENTRE - (CENTRE - LIMIT2)*ZONE)
    {
      DRS_STATE = 0;
    }
  }
  else
  {
    DRS_STATE = 0;
  }

  int brakepos = analogRead(A1);
  if (THRES_TYPE == HIGHTHRES)
  {
    if (THRES_VALUE > brakepos)
    {
      DRS_STATE = 0;
    }
  }
  else if (THRES_TYPE == LOWTHRES)
  {
    if (THRES_VALUE < brakepos)
    {
      DRS_STATE = 0;
    }
  }
  else
  {
    DRS_STATE = 0;
  }

  int in = Serial.read();
  if (in == 'a')
  {
    Serial.println("what");
  }
  else if (in == 's')
  {
    int in2 = 0;
    while (in != 'q')
    {
      in = Serial.read();
      if (in == 'o')
      {
        in2 = 0;
        UpRight.writeMicroseconds (OPEN);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (OPEN < ABSMAX)
            {
              OPEN++;
              UpRight.writeMicroseconds (OPEN);
              Serial.print("OPEN is ");
              Serial.println(OPEN);
            }
          }
          else if (in2 == '-')
          {
            if (OPEN > ABSMIN)
            {
              OPEN--;
              UpRight.writeMicroseconds (OPEN);
              Serial.print("OPEN is ");
              Serial.println(OPEN);
            }
          }
        }
      }
      else if (in == 'c')
      {
        in2 = 0;
        UpRight.writeMicroseconds (CLOSE);
        while (in2 != 'q')
        {
          in2 = Serial.read();
          if (in2 == '+')
          {
            if (CLOSE < ABSMAX)
            {
              CLOSE++;
              UpRight.writeMicroseconds (CLOSE);
              Serial.print("CLOSE is ");
              Serial.println(CLOSE);
            }
          }
          else if (in2 == '-')
          {
            if (CLOSE > ABSMIN)
            {
              CLOSE--;
              UpRight.writeMicroseconds (CLOSE);
              Serial.print("CLOSE is ");
              Serial.println(CLOSE);
            }
          }
        }
      }
    }
  }
}
