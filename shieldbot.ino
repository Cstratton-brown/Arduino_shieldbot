#include <Shieldbot.h>

Shieldbot shieldbot = Shieldbot();

int rightSpeed = 50;  //sets the base speed for the right motor
int leftSpeed = 50;   //sets the base speed for the left motor                                  
int rightRead = 0;  //sets default value of right read to 0
int leftRead = 0;   //sets default value of left read to 0
int senseR; //initialize the right sensor
int senseL; //initialize the left sensor
int countR=0; //sets default value of count right to 0
int countL=0; //sets default value of count left to 0
int senseN; //initialize the sensor in the nose
int senseLeftN; //initialize the middle left sensor on the nose
int senseRightN;  //initialize the middle right sensor on the nose
int senseBackL; //initialize the back Left sensor on the nose
int senseBackR; //initialize the back right sensor on the nose
int noseRead = 0;
int noseReadL = 0;
int noseReadR = 0;
int backReadL = 0;
int backReadR = 0;
float countRevolution = 0;
int rev=0;

  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(rightRead,OUTPUT);
  pinMode(leftRead,OUTPUT);
  pinMode(noseRead,OUTPUT);
  pinMode(noseReadR,OUTPUT);
  pinMode(noseReadL,OUTPUT);
  pinMode(backReadR,OUTPUT);
  pinMode(backReadL,OUTPUT);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  leftRead = analogRead(A4); //sets the variable leftRead to be the value from pin A4
  rightRead =analogRead(A5); //sets the variable rightRead to be the value from pin A5
                             // pins where changed from A0 and A1 so that the sensors already attached to them can be used later to detect the edge of the course.
  backReadR = analogRead(A0);
  noseReadR = analogRead(A1);
  noseRead = analogRead(A2);
  noseReadL = analogRead(A3);
  //backReadL = analogRead(D4);
  
  
  rightWheel(); //calls void rightWheel
  leftWheel();  //calls void leftWheel
  //straight();   //calls void straight
  checkRight(); //calls void checkRight
  checkLeft();  //calls void checkLeft
  shieldbot.drive(leftSpeed,rightSpeed);  //sets the shieldbot to drive with the left and right motors rotation speed set to the values of variable leftSpeed and rightSpeed respectively
  delay(10); //delay of 10 miliseconds

}
void rightWheel()
{
// used to determine when the sensor is over a white or black segment of the right wheel
  
  if (rightRead>90) 
  {
    senseR=1; // black colour detected
    countR++; // increase value of countR by 1
    countRevolution = countR / 6;
    rev=int(countRevolution);
  }
  else if(rightRead<60)
  {
    senseR=0;// white colour detected
  }
  Serial.print("Right:"); //sets label for 1st variable for serial plotter
  Serial.print(senseR); // print value of senseR to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
  
}
void leftWheel(){
// used to determine when the sensor is over a white or black segment of the left wheel
   
  if (leftRead>90)
  {
    senseL=1; // black colour detected
    countL++; // increase value of countL by 1
  }
  else if(leftRead<60)
  {
    senseL=0;// white colour detected
  }
  Serial.print("Left:"); //label for the Left wheel sensor
  Serial.println(senseL); // print value of senseL to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
}
void checkLeft()
  //checks if the left wheel is rotating slower than the right
{  
  
  constrain(leftSpeed, -128, 127); // should theoretically constrain the variables value to be between the 2 values listed
  constrain(rightSpeed, -128, 127);// should theoretically constrain the variables value to be between the 2 values listed
   while ((countR > 10) && (countL > 10) && (countL < countR))  // while countL and countR are greater than 10 and countR is greater than countL, decrease right speed, increase left speed and reset count
    {     
      leftSpeed = leftSpeed + 5; //increase left speed
      rightSpeed = rightSpeed - 5; //decrease right speed          
      //countL = 0; //reset the counts
      //countR = 0;
    }  
}
void checkRight()
  //checks if the right wheel is rotating slower than the right
{  
  constrain(leftSpeed, -128, 127);  // should theoretically constrain the variables value to be between the 2 values listed
  constrain(rightSpeed, -128, 127); // should theoretically constrain the variables value to be between the 2 values listed
   while ((countL > 10) && (countR > 10) && (countL > countR))  // while countL and countR are greater than 10 and countL is greater than countR, decrease left speed, increase right speed and reset count
    {     
      leftSpeed = leftSpeed - 5;  //decrease left speed
      rightSpeed = rightSpeed + 5; //increase right speed         
      //countL = 0; //reset the counts
      //countR = 0;
    }  
}

//void straight()
//{
  //calls void checkRight and void checkLeft
 //checkRight();
 //checkLeft();

 //code use to make sure that the counts where increasing and that the speeds where changing, using the serial monitor
 /*
  Serial.print("countL"); //label for the Left wheel sensor
  Serial.println(countL); // print value of senseL to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
  Serial.print("countR:"); //label for the Left wheel sensor
  Serial.println(countR); // print value of senseL to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
  Serial.print("speedL:"); //label for the Left wheel sensor
  Serial.println(leftSpeed); // print value of senseL to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
  Serial.print("speedR:"); //label for the Left wheel sensor
  Serial.println(rightSpeed); // print value of senseL to serial plotter
  Serial.print(',');  // allows a 2nd variable and label to be added for printing to serial plotter
  Serial.print("Revolutions:"); //label for the Left wheel sensor
  Serial.println(rev); // print value of senseL to serial plotter
  */
  //}
