/*The following program is allowing the ShieldBot to navigate through the track
 by setting the distances and angles for each section of the track
*/
#include <Shieldbot.h>

Shieldbot shieldbot = Shieldbot();

//declaring the variables to hold the sensor values
int rightSensorValue;
int leftSensorValue;

//initialises the counts for the 2 wheels used to adjust speed to 0
volatile int countRight= 0;
volatile int countLeft = 0;

//initialises the bool variables used to check for black and white on both wheels to true
bool lfBlackL = true; 
bool lfWhiteL = true;
bool lfBlackR = true; 
bool lfWhiteR = true;

//initialises the turning bool to false so the bot starts by going straight
bool straight1 = true;
bool straight2 = false;
bool straight3 = false;
bool straight4 = false;
bool straight5 = false;
bool straight6 = false;
//initialises first turn to true and the rest to false so the bot knows which turn it will have firsty
bool turning = false;
bool firstTurn = false;
bool secondTurn = false;
bool thirdTurn = false;
bool forthTurn = false;
bool fifthTurn = false;

//initialises the counts for going straight and turning to 0
int countStraightRight = 0;
int rightTurnCount = 0;
int leftTurnCount = 0;

//initialises starting distance for countCalculator and initialises the calculated count to 0
volatile float distance = 55.28;
int count=0;
//initialises starting angle for countCalculator and initialises the calculated countEncoder to 0
volatile float angle = 115.80;//first angle
int countEncoder=0;
//initialises variables used to calculate countEncoder in angleCalculator
const float axleLength = 8.00; //axle lenght of the ShieldBot
const float fullTurn = 360.00; //initialising the degree of a full turn
volatile int a=0;//initialising variable to take the return value from angleCalculator

//initialises variables used to calculate count in countCalculator
const float stepcount=6.00;//transition count in 1 revolution
const float diameter=4.40; //diameter of teh wheels
const float pi=3.14; //the number pi
float circumference = 0.00;
float revolution=0.00;
volatile int c=0;//initialising variable to take the return value from countCalculator

//initialises the starting speeds of the wheel used in check()
volatile int leftSpeed=50; 
volatile int rightSpeed=50; 
 
void setup() {
  // initialise serial communication at 9600 bits per second:
  Serial.begin(9600); 
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 5 from the sensor on the right wheel:
  rightSensorValue =analogRead(A5);
  // read the input on analog pin 4 from the sensor on the left wheel:
  leftSensorValue = analogRead(A4);
  
  leftEdge(); //calls the function leftEdge() to count the transitions on the position encoder on the Left Wheel
  rightEdge(); //calls the function rightEdge() to count the transitions on the position encoder on the Right Wheel

  //runs the check function to keep the bot driving straight
  check();//calls the function check() to adjust the speed of the wheels to drive in a straight line
  leftSpeed = constrain(leftSpeed, 48, 58);  // constrains the variables value to be between the 2 values listed
  rightSpeed = constrain(rightSpeed, 40, 52); // constrains the variables value to be between the 2 values listed
  
  c=countCalculator(distance);  // calls function countCalculator to calculate the distance in counts of the wheels detection of black
  a=angleCalculator(angle); //add  degrees extra due to an error with the position encoder
  driving();//calls the driving() function
  /* used for testing the speed
  Serial.print("Right:"); //label for the Right wheel sensor
  Serial.print(rightSpeed); //prints the output of the rightSpeed
  Serial.print(',');//used to seperate the labels on The Serial Monitor
  Serial.print("Left:"); //label for the Left wheel sensor
  Serial.println(leftSpeed); //prints the output of the leftSpeed
  */
}

void driving()
{
if(c>countStraightRight && straight1 ==true)//drives sraigth for 44cm
  { 
    shieldbot.drive(leftSpeed,rightSpeed);  //makes the bot drive forward  
  }
  //checks if the desired distance is reached and asigns new values to the variables so the next turn is taken
  else if(c<=countStraightRight && straight1 ==true)
  {
    //reasigning the speed values
    leftSpeed = 50;
    rightSpeed=50;
    firstTurn = true; //the variable "firstTurn" is set to true to allow the ShieldBot to take the first turn of 90 degrees
    straight1 = false;// the variable "straight1" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    turning= true; // the variable "turning" is set to true to allow the ShieldBot to take the next turn 
  }
  // completes 90 degree left turn
  if (rightTurnCount<a && firstTurn==true && turning ==true)
  {
    shieldbot.drive(0,50); //make a left turn 
  }
  //checks if the desired angle is reached and asigns new values to the variables so the next straight section is navigated
  else if (rightTurnCount>=a && firstTurn==true && turning ==true)
  {
    firstTurn = false;// the variable "firstTurn" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    straight2 = true;//the variable "straight2" is set to true to allow the ShieldBot to drive on the next straight section on the track
    turning = false;//turning set to false
    distance = 38.1106; //sets the distance for the next straight drive
  }
  //drives sraigth for 40 cm
  if(c>countStraightRight && straight2 ==true)
  {
    //reasigning the speed values
    leftSpeed = 50;
    rightSpeed=50;
    shieldbot.drive(leftSpeed,rightSpeed);  //makes the bot drive forward
  }
  //checks if the desired distance is reached and asigns new values to the variables so the next turn is navigated
  else if(c<=countStraightRight && straight2 ==true)
  {
    //reasigning the speed values
    leftSpeed = 50;
    rightSpeed=50;
    secondTurn=true; //the variable "seconTurn" is set to true to allow the ShieldBot to take the second turn
    straight2 = false;// the variable "straight2" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    turning= true; // the variable "turning" is set to true to allow the ShieldBot to take the next turn
    angle = 278.00; //the new angle for the next turn 
  }
  //takes a gradual left turn
  if (rightTurnCount<a && secondTurn==true && turning ==true)
  {
    shieldbot.drive(15,50); //make a left turn
  }
    //checks if the desired angle is reached and asigns new values to the variables so the next straight section is navigated
  else if (rightTurnCount>=a && secondTurn==true && turning ==true)
  {
    secondTurn = false;// the variable "secondTurn" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    straight3 = true;//the variable "straight3" is set to true to allow the ShieldBot to drive on the next straight section on the track
    turning = false;//turning set to false
    distance = 18.426206; //sets the distance for the next straight drive 
  }
  //completes the next straight section
  if(c>countStraightRight && straight3 ==true)
  {
    leftSpeed = 50;
    rightSpeed=50;
    shieldbot.drive(leftSpeed,rightSpeed);  //makes the bot drive forward  
  }
  else if(c<=countStraightRight && straight3 ==true)
  {
    //reasigning the speed values
    leftSpeed = 50;
    rightSpeed=50;
    thirdTurn=true; //the variable "thirdTurn" is set to true to allow the ShieldBot to take the first turn of 90 degrees
    straight3 = false;// the variable "straight3" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    turning= true; // the variable "turning" is set to true to allow the ShieldBot to take the next turn
    angle = 116.00; //the new angle for the next turn 116
  }
  //takes a right turn
  if (leftTurnCount<a && thirdTurn==true && turning ==true)
  {
    shieldbot.drive(50,0); //make a left turn
  }
  //checks if the desired angle is reached and asigns new values to the variables so the next straight section is navigated
  else if (leftTurnCount>=a && thirdTurn==true && turning ==true)
  {
    thirdTurn = false;// the variable "thirdTurn" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    straight4 = true;//the variable "straight4" is set to true to allow the ShieldBot to drive on the next straight section on the track
    turning = false;//turning set to false
    distance = 16.0312; //sets the distance for the next straight drive 18
  }
  //to allow to go straight in the next section
  if(c>countStraightRight && straight4 ==true)
  {
    leftSpeed = 50;
    rightSpeed=50;
    shieldbot.drive(leftSpeed,rightSpeed);  //makes the bot drive forward 
  }
  //checks if the desired distance is reached and asigns new values to the variables so the next turn is navigated
  else if(c<=countStraightRight && straight4 ==true)
  {
    //reinitialising the speed values
    leftSpeed = 50;
    rightSpeed=50;
    forthTurn=true; //the variable "forthTurn" is set to true to allow the ShieldBot to take the first turn of 90 degrees
    straight4 = false;// the variable "straight4" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    turning= true; // the variable "turning" is set to true to allow the ShieldBot to take the next turn
    angle = 90.00; //the new angle for the next turn
  }
    //takes a left turn
  if (rightTurnCount<a && forthTurn==true && turning ==true)
  {
    shieldbot.drive(0,50); //make a left turn
  }
  //checks if the desired angle is reached and asigns new values to the variables so the next straight section is navigated
  else if (rightTurnCount>=a && forthTurn==true && turning ==true)
  {
    forthTurn = false;// the variable "forthTurn" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    straight5 = true;//the variable "straight5" is set to true to allow the ShieldBot to drive on the next straight section on the track
    turning = false;
    distance = 27.64; //sets the distance for the next straight drive 32

  }
  //to allow to go straight in the next section
  if(c>countStraightRight && straight5 ==true)
  {
    //reinitialising the speed values
    leftSpeed = 50;
    rightSpeed=50;
    shieldbot.drive(leftSpeed,rightSpeed);  //makes the bot drive forward
  }
  //checks if the desired distance is reached and asigns new values to the variables so the next turn is navigated
  else if(c<=countStraightRight && straight5 ==true)
  {
    //reinitialising the speed values
    leftSpeed = 50;
    rightSpeed=50;
    fifthTurn=true; //the variable "fifthTurn" is set to true to allow the ShieldBot to take the first turn of 90 degrees
    straight5 = false;// the variable "straight5" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    turning= true; // the variable "turning" is set to true to allow the ShieldBot to take the next turn
    angle = 272.00; //the new angle for the next turn
  }
   //takes a left turn
   if (rightTurnCount<a && fifthTurn==true && turning ==true)
  {
    shieldbot.drive(15,50); //make a left turn 
  }
  //checks if the desired angle is reached and asigns new values to the variables so the next straight section is navigated
  else if (rightTurnCount>=a && fifthTurn==true && turning ==true)
  {
    fifthTurn = false;// the variable "fifthTurn" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    straight6 = true;//the variable "straight6" is set to true to allow the ShieldBot to drive on the next straight section on the track
    turning = false;
    distance = 78.313; //sets the distance for the next straight drive 76
    leftSpeed = 50;
    rightSpeed=50;
  }
  check();
  //to allow to go straight in the next section
  if(c>countStraightRight && straight6 ==true)
  { 
    //reinitialising the speed values
    leftSpeed =52;
    rightSpeed=50;
    shieldbot.drive(leftSpeed,rightSpeed);  //makes the bot drive forward 
  }
  //checks if the desired distance is reached and asigns new values to the variables so the next turn is navigated
  else if(c<=countStraightRight && straight6 ==true)
  {
    //reinitialising the speed values
    leftSpeed = 50;
    rightSpeed=50;
    straight6 = false;// the variable "straight6" is set to false to stop the program to execute this condition again until comleting the rest of the conditions
    straight1=true; 
    angle=116.00; //reassigning the angle value for the first turn
  }
}
/* The following function is counting when the sensor value is above 40 wich means that black is detected 
 *  and for a sensor value under 40, white colour is detected
 * The function checks for transition between the white and black sections on the right wheel using a bool variable to prevent it detecting the same black section before it transitions to white
 */
void rightEdge(){

  if (rightSensorValue>=40 && lfBlackR==true) //checks if black colour is detected and the sensor is looking for black
  {
     // black colour detected
    lfBlackR = false; // stops sensor looking for black
    lfWhiteR = true;  //starts sensor looking for white
    countRight++; //the counter of the right wheel is increased by 1, used to adjust speed
    
    if (turning == true) // if statement to check if the bot is turning or going straight
    {
      rightTurnCount++;   // turn counter is only increased when the bot is turning left otherwise it is sero
      countStraightRight = 0;
    }
    else if (turning == false)  //when bot is going straight countStraightRight is used to count distance, when the bot is turning it is sero
    {
      countStraightRight++;
      rightTurnCount = 0;
    }
  }
  else if(rightSensorValue<40 && lfWhiteR ==true) // checks if white is detected and the sensor is looking for white
  {
    // white colour detected
    lfBlackR=true;  //starts sensor looking for black
    lfWhiteR= false;  //stops sensor looking for white
  }
}
/*  The following function is counting when the sensor value is above 40 wich means that black is detected 
 *  and for a sensor value under 40, white colour is detected
 * The function checks for transition between the white and black sections on the right wheel using a bool variable to prevent it detecting the same black section before it transitions to white
 */
void leftEdge(){
  if (leftSensorValue>=40 && lfBlackL==true)  //checks if black colour is detected and the sensor is looking for black
  {
     // black colour detected
    lfBlackL = false; // stops sensor looking for black
    lfWhiteL = true;  //starts sensor looking for white
    countLeft++; //the counter of teh left wheel is increased by 1
    if (turning == true)  // if statement to check if the bot is turning or going straight
    {
      leftTurnCount++;  // turn counter is only increased when the bot is turning right
    }
    else if (turning == false)  
    {
      leftTurnCount = 0;  //when bot is going straight leftTurnCount is left at 0
    }
  }
  else if(leftSensorValue<40 && lfWhiteL ==true)  // checks if white is detected and the sensor is looking for white
  {
    // white colour detected
    lfBlackL=true;    //starts sensor looking for black
    lfWhiteL = false;   //stops sensor looking for white
  }
}
/*The function check() checks if there is a difference in transitions from black and white between the wheels
 * and accordingly decreases the speed on Left wheel and increases the speed on the Right Wheel
 */
 void check()
 {  
    //checks of the transitons on the right position encoder are 
    //greater than the transitions on the left position encoder
    if(countRight > countLeft)
    { 
      leftSpeed=leftSpeed+2;  //decrease left speed
      rightSpeed=rightSpeed-2; //increase right speed              
    }
    //checks of the transitons on the right position encoder are 
    //less than the transitions on the left position encoder
    if(countRight < countLeft)
    { 
      leftSpeed=leftSpeed-2;  //decrease left speed
      rightSpeed=rightSpeed+2; //increase right speed             
    }
 }
 //converts the desired distance to counts(number of transition from white to black on the wheel)required
int countCalculator(float distance)
{
  float b=0.00; //initialising b to calculate the transition on the wheel in float
  circumference=diameter*pi;//calculates the circumference in cm
  revolution=distance/circumference; //revolutions required to achieve the desired distance
  b = revolution*stepcount; //calculates the transitions in float
  count=(int)b; //converts to integer
  return count; //returns how many transitions are required to reach the distance set
}
//converts angle to a number of transitions on the position encoder required to take the turn
int angleCalculator(float angle)
{
  float circumference360=0.00; //initialising the circumference of 360 degree turn one one wheel
  float pulsesNeeded=0.00;//initialising the number of transitions required by the position encoder
  float numberOfRevolution=0.00;//initialising the number of revolutions for 360 degree turn
  float distanceTravelled=0.00;//initialising the distance travelled
  float pulses360=0.00;//initialising the transitions needed to do 360 degree turn
  circumference360=2*pi*axleLength;//calculates the circumference of 360 degree turn on one wheel;//calculates the circumference of 360 degree turn on one wheel 
  distanceTravelled=2*pi*(diameter/2); //calculates the distance travelled
  numberOfRevolution=circumference360/distanceTravelled;//calculates the number of revolutions for 360 degree turn
  pulses360=numberOfRevolution*stepcount; //transitions needed to do 360 degree turn
  pulsesNeeded=angle/fullTurn* pulses360;//calculates how many transitions are required by the position encoder
  countEncoder=(int)pulsesNeeded; //converts to integer
  return countEncoder; //returns how many transitions are required to make the turn 
}
