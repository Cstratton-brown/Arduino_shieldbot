#include <Shieldbot.h>

Shieldbot shieldbot = Shieldbot();

int rightSpeed = 20;  //sets the base speed for the right motor
int leftSpeed = 20;   //sets the base speed for the left motor                                  
int rightRead=0;  //sets default value of right read to 0
int leftRead=0;   //sets default value of left read to 0
int senseR; //initialize the right sensor
int senseL; //initialize the left sensor
int countR=0; //sets default value of count right to 0
int countL=0; //sets default value of count left to 0
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rightRead,OUTPUT);
  pinMode(leftRead,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  leftRead = analogRead(A1); //sets the variable leftRead to be the value from pin A1
  rightRead =analogRead(A0); //sets the variable rightRead to be the value from pin A0
  rightWheel(); //calls void rightWheel
  leftWheel();  //calls void leftWheel
  straight();   //calls void straight
  shieldbot.drive(leftSpeed,rightSpeed);  //sets the shieldbot to drive with the left and right motors rotation speed set to the values of variable leftSpeed and rightSpeed respectively
  delay(10); //delay of 10 miliseconds

}
void rightWheel(){
// used to determine when the sensor is over a white or black segment of the right wheel
  
  if (rightRead>200) 
  {
    senseR=1; // black colour detected
    countR++; // increase value of countR by 1
  }
  if(rightRead<50)
  {
    senseR=0;// white colour detected
  }
  Serial.print("Right:"); //sets label for 1st variable for serial plotter
  Serial.print(senseR); // print value of senseR to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
  
}
void leftWheel(){
// used to determine when the sensor is over a white or black segment of the left wheel
   
  if (leftRead>200)
  {
    senseL=1; // black colour detected
    countL++; // increase value of countL by 1
  }
  if(leftRead<50)
  {
    senseL=0;// white colour detected
  }
  Serial.print("Left:"); //label for the Left wheel sensor
  Serial.println(senseL); // print value of senseL to serial plotter
}
void checkLeft()
  //checks if the left wheel is rotating slower than the right
{
  constrain(leftSpeed,10, 150);
  if (((countL >=3) && (countR >= 3))&& (countL < countR))
  {
    leftSpeed++;
      /*if ((leftSpeed >= 124) && (rightSpeed>2))
      {
        rightSpeed--;
      }
      else (rightSpeed>2);
      {
        leftSpeed++;
        rightSpeed--;
      }
     */}
     countL = 0;
     countR = 0;
  }

void checkRight()
  //checks if the right wheel is rotating slower than the right
{
  constrain(rightSpeed,10, 150);
   if (((countL >=3) && (countR >= 3))&&(countL > countR))
    {
     rightSpeed++;
      /*if ((rightSpeed >= 124) && (leftSpeed >0))
        {
          rightSpeed++;
        } 
       else
        {
        leftSpeed--;
        rightSpeed++;
        }
      */}
    countL = 0;
    countR = 0;
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
