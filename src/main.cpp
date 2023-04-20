#include <Arduino.h>
#include <iostream>
#include <Ticker.h>
#include <queue>
using namespace std;

// CURRENTLY UNUSED DEFS
// int delayTime = 10;
// int pwmState = 3;
// int commands[4];                            // Create command array
// Ticker turnDelay;                           // Create ticker for interrupts
// unsigned long int start, ppm, result;       // Establish RC receiver PPM signal bounds
// unsigned long int ppmMid = 780000;           // Default middle value for ch1
// unsigned long int ppmMax = ppmMid + 400000;
// unsigned long int ppmMin = ppmMid - 200000;
// #define rightTurn stepperFL, CW, 20, 90;  // Definitions for common commands
// queue<int*> actQueue;                     // Create queue

#define stepperF 1                        // Define command words
#define stepperB 2
#define motorL 3
#define motorR 4
#define STOP 2
#define CW 1
#define CCW 0
const int stepsPerRevolution = 200;    // Define variables
const int pwmLMotor = 19, pwmRMotor = 22;
const int dirLMotor = 21, dirRMotor = 23;
const int dirFR = 13, stepFR = 12;
const int dirBR = 33, stepBR = 32;
const int dirFL = 26, stepFL = 25;
const int dirBL = 14, stepBL = 27;
const int stepperInput = 35, motorInput = 34;
int messageFlag = 0;

void turn(int dir, int pwm){   // Turn Function
  digitalWrite(dirFR, dir);    // TODO: Replace w/ port manipulation
  digitalWrite(dirBR, dir);   // TODO: Use proper PWM signals for drive/turn based on analog in
  digitalWrite(dirFL, dir);    // TODO: Fix serial print statements
  digitalWrite(dirBL, dir);   // TODO: Make functions into ISRs
  pinMode(stepFR, OUTPUT);     // TODO: Add drive 0-degree turning function (using btn?)
  pinMode(stepBR, OUTPUT);     // TODO: Push to rovercontrol git repository
  pinMode(stepFL, OUTPUT);
  pinMode(stepBL, OUTPUT);
  digitalWrite(stepFR, HIGH);
  digitalWrite(stepBR, HIGH);
  digitalWrite(stepFL, LOW);
  digitalWrite(stepBL, LOW);
  delay(pwm);
  digitalWrite(stepFR, LOW);
  digitalWrite(stepBR, LOW);
  digitalWrite(stepFL, HIGH);
  digitalWrite(stepBL, HIGH);
  delay(pwm);
  if(!messageFlag){
    Serial.println("TURNING");
    messageFlag = 1;
  }
}

void drive(int dir, int pwm){     // Drive Function
  digitalWrite(dirLMotor, dir);
  digitalWrite(dirRMotor, !dir);
  digitalWrite(pwmLMotor, LOW);
  digitalWrite(pwmRMotor, LOW);
  if(!messageFlag){
    Serial.println("DRIVING");
    messageFlag = 1;
  }
  //Serial.println(analogRead(motorInput));
}

void read(){
  while(analogRead(stepperInput)>2500){   // LEFT
    turn(CW, 15);
  }
  while(analogRead(stepperInput)<1500){   // RIGHT
    turn(CCW, 15);
  }
  while(analogRead(motorInput)<1700){   // FORWARD
    drive(CW, 0);
  }  
  while(analogRead(motorInput)>2000){   // BACKWARD
    drive(CCW, 0);
  }                       
  digitalWrite(pwmLMotor, HIGH);          // STOPPED
  digitalWrite(pwmRMotor, HIGH);          // STOPPED
  if(messageFlag){
    Serial.println("STOPPED");
    messageFlag = 0;
  }
}
                                                                                                                                                                        
void setup() {
  pinMode(dirFL, OUTPUT);       // Set GPIO Modes
  pinMode(dirBL, OUTPUT);
  pinMode(dirFR, OUTPUT);
  pinMode(dirBR, OUTPUT);
  pinMode(stepFL, OUTPUT);
  pinMode(stepBL, OUTPUT);
  pinMode(stepFR, OUTPUT);
  pinMode(stepBR, OUTPUT);
  pinMode(pwmLMotor, OUTPUT);
  pinMode(pwmRMotor, OUTPUT);
  pinMode(dirLMotor, OUTPUT);
  pinMode(dirRMotor, OUTPUT);
  pinMode(stepperInput, INPUT);
  pinMode(motorInput, INPUT);
  Serial.begin(115200);         // Begin serial communication
  delay(1000);
}

void loop() {
  read();
  delay(50);  
}