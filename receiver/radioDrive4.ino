/* This example drives each motor on the Zumo forward, then
backward.  The yellow user LED is on when a motor should be
running forward and off when a motor should be running backward.
If a motor on your Zumo has been flipped, you can correct its
direction by uncommenting the call to flipLeftMotor() or
flipRightMotor() in the setup() function. */

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

void forward(){
  //Serial.println("Turning on motors");
  motors.setSpeeds(motorSpeed, motorSpeed);
  delay(5000);
  //Serial.println("Turning off Motors");
  motors.setSpeeds(0,0);
  delay(5000);
}

void backward(){
  //Serial.println("Turning on motors");
  motors.setSpeeds(-motorSpeed, -motorSpeed);
  delay(5000);
  //Serial.println("Turning off Motors");
  motors.setSpeeds(0,0);
  delay(5000);
}

void turnRight(){
  motors.setSpeeds(motorSpeed, -motorSpeed);
  delay(400);
  stop();
}

void turnLeft(){
  motors.setSpeeds(-motorSpeed, motorSpeed);
  delay(350); // Bot turns left a little faster
  stop();
}

void stop(){
  motors.setSpeeds(0, 0);
}

void reset(){

}

void start(){

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
      Serial.print("Message: ");
      Serial.println(buf);
      
      
      //if (buf[0] == 'f') Serial.println("YES!YES!YES!");
      //if (buf[0] == 'f') Serial.println("f: compared!");
      //if (buf[0] == 'b') Serial.println("b: compared!");
    
      
      if (buf[0] == 'f'){
         Serial.println("Turning on motors");
         motors.setSpeeds(motorSpeed, motorSpeed);
         delay(5000);
         Serial.println("Turning off Motors");
         motors.setSpeeds(0,0);
         delay(5000);
      }
      
      if (buf[0] == 'b') backward();
      if (buf[0] == 'r') turnRight();
      if (buf[0] == 'l') turnLeft();
      if (buf[0] == 'p') stop();
      if (buf[0] == 'x') reset();
      if (buf[0] == 's') start();
      
      Serial.println("Caught");

    }

    //Serial.println("Standby");
}
