#include <Shieldbot.h>

Shieldbot shieldbot = Shieldbot();

int rightSpeed = 20;
int leftSpeed = 20;                                   ;
int rightRead=0;
int leftRead=0;
int senseR;
int countR=0;
int senseL;
int countL=0;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rightRead,OUTPUT);
  pinMode(leftRead,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  leftRead = analogRead(A1);
  rightRead =analogRead(A0);
  rightWheel();
  leftWheel();
  straight();
  shieldbot.drive(leftSpeed,rightSpeed);
  straight();
  delay(10);

}
void rightWheel(){

  
  if (rightRead>200)
  {
    senseR=1; // black colour detected
    countR++;
  }
  if(rightRead<50)
  {
    senseR=0;// white colour detected
  }
  Serial.print("Right:");
  Serial.print(senseR);
  Serial.print(',');
  
}
void leftWheel(){

    
  if (leftRead>200)
  {
    senseL=1; // black colour detected
    countL++;
  }
  if(leftRead<50)
  {
    senseL=0;// white colour detected
  }
  Serial.print("Left:"); //label for the Left wheel sensor
  Serial.println(senseL);
}
void checkLeft()
{
  if (((countL >=3) && (countR >= 3))&& (countL < countR))
  {
    //if (countL < countR)
    //{
      if ((leftSpeed >= 124) && (rightSpeed>2))
      {
        rightSpeed--;
      }
      else (rightSpeed>2);
      {
        leftSpeed++;
        rightSpeed--;
      }
     }
     countL = 0;
     countR = 0;
  }
  
//}

void checkRight()
{
   if (((countL >=3) && (countR >= 3))&&(countL > countR))
  {
    //if (countL > countR)
    {
      if ((rightSpeed >= 124) && (leftSpeed >0))
      {
        rightSpeed++;
      }
      else
      {
        leftSpeed--;
        rightSpeed++;
      }
      
    }
    countL = 0;
    countR = 0;
  //}
}
}

void straight()
{
  
checkLeft();
checkRight();
}
/*{
  if ((countL >=3) && (countR >= 3))
  {
    if (countL < countR)
    {
      if ((leftSpeed >= 124) && (rightSpeed>2))
      {
        rightSpeed--;
      }
      else if (rightSpeed>2)
      {
        leftSpeed++;
        rightSpeed--;
      }
      
      countL = 0;
      countR = 0;
      
      //shieldbot.drive(0,rightSpeed);
    }
    else if (countL > countR)
    {
      if ((rightSpeed >= 124) && (leftSpeed >0))
      {
        leftSpeed--;
      }
      else
      {
        leftSpeed--;
        rightSpeed++;
      }
      countL = 0;
      countR = 0;
    // shieldbot.drive(leftSpeed,rightSpeed);
    }
    //else if (countR == countL)
    //{
      //shieldbot.drive(leftSpeed,rightSpeed);
      //countL = 0;
      //countR = 0;
    //}
  }
}*/
