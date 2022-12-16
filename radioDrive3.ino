/* This program allows the robot to receive commands from radio and 
   follow the user's directions.*/

#include <Wire.h>
#include <Zumo32U4.h>
#include <RH_ASK.h>
#include <SPI.h>

#define RH_ASK_ADRUINO_USE_TIMER3
RH_ASK driver(2000, 11, 12, 13, false);; // Pin 13 is timer3 digital capture pin

//RH_ASK driver; // D11
Zumo32U4Motors motors;
//Zumo32U4ButtonA buttonA;

const int16_t motorSpeed = 200; // Speed of mtors
char lib[100];
int i = 0;
int trace = NULL;

/* Command to move the robot forward for 5 seconds */
void forward(){
  //Serial.println("Turning on motors");
  motors.setSpeeds(motorSpeed, motorSpeed);
  delay(5000);
  //Serial.println("Turning off Motors");
  motors.setSpeeds(0,0);
  delay(2500);
  /* Records the command if 'start' was said previously */
  if (trace == true){
    lib[i] = 'b';
    i += 1;
  }
}

/* Moves the robot backward for 5 seconds */
void backward(){
  //Serial.println("Turning on motors");
  motors.setSpeeds(-motorSpeed, -motorSpeed);
  delay(5000);
  //Serial.println("Turning off Motors");
  motors.setSpeeds(0,0);
  delay(2500);
  /* Records command if 'start' was read earlier */
  if (trace == true){
    lib[i] = 'f';
    i += 1;
  }

}

/* Turns the robot right 90 degrees */
void turnRight(){
  motors.setSpeeds(motorSpeed, -motorSpeed);
  delay(425);
  motors.setSpeeds(0,0);
  /* Records command if 'start' was read earlier */
  if (trace == true){
    lib[i] = 'l';
    i += 1;
  }

}
/* Turns the robot left 90 degrees */
void turnLeft(){
  motors.setSpeeds(-motorSpeed, motorSpeed);
  delay(375); // Bot turns left a little faster
  motors.setSpeeds(0,0);
  /* Records command if 'start' was read earlier */
  if (trace == true){
    lib[i] = 'r';
    i += 1;
  }
}

/* Makes the robot go back to its original position */
void reset(){
  if (trace == true){
    for(i; i>0; i--){
      if (lib[i] == 'f') forward;
      if (lib[i] == 'b') backward;
      if (lib[i] == 'r') turnRight;
      if (lib[i] == 'l') turnLeft;
      if (lib[i] == 'p') stop;
    }
  }
  /* Resets its parameters */
  trace = false;
  char lib[100];
}
/* Begins logging movement of robot */
void start(){
  trace = true;
}

void setup()
{
  // Uncomment if necessary to correct motor directions:
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);

  // Wait for the user to press button A.
  //buttonA.waitForButton();

  // Delay so that the robot does not move away while the user is
  // still touching it.
  Serial.begin(9600);
  if (!driver.init()) Serial.println("init failed");
  //forward();
  delay(5000);
}

void loop()
{
    
    char buf[1]; // Initalize 
    //char test = 'f';
    uint8_t buflen = sizeof(buf);

    //forward();
    
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      /* Functions used when testing receiver input */
      Serial.print("Message: ");
      Serial.println(buf);
      //if (buf[0] == 'f') Serial.println("YES!YES!YES!");
      //if (buf[0] == 'f') Serial.println("f: compared!");
      //if (buf[0] == 'b') Serial.println("b: compared!");
      /* If chain to read commands for robot */
      if (buf[0] == 'f') forward();    
      if (buf[0] == 'b') backward();
      if (buf[0] == 'r') turnRight();
      if (buf[0] == 'l') turnLeft();
      if (buf[0] == 'p') stop();
      if (buf[0] == 'x') reset();
      if (buf[0] == 's') start();
      
      //Serial.println("Caught");

    }

    //Serial.println("Standby");
}
