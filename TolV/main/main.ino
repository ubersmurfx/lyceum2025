0//hehe izmeneniye!!!

#include <PSX.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Servo.h>

//Minibot PS2 controller receiver data pins
#define dataPin     A1
#define cmdPin      A0
#define attPin      2
#define clockPin    4 

//Minibot motor driver pins
#define RIGHT_FORWARD   3
#define RIGHT_BACKWARD  5
#define LEFT_FORWARD    13
#define LEFT_BACKWARD   6

Servo servo1;
Servo servo2;

uint32_t tmr;
boolean flag;

struct Minibot_Data
{
  byte id = 1;
  byte motor_speed = 250;
};            ppdpfpfofoeppfpef[epwg



edgp;ewga]

byte servoPosition[2] = {0,0};

Minibot_Data data;

// Static instantiation of the library
PSX psx;

// Variables to hold the controller state and error code
PSX::PSXDATA PSXdata;
int PSXerror;

void printCyberdeck();
void motorInit();
void psxInit();
void servoInit();
void speedChange();
void motorControl(byte speed);
void servoControl();
void moveForward(byte speed);
void moveBackward(byte speed);
void turnRight(byte speed);
void turnLeft(byte speed);
void stop();

void speedChange(){
  PSXerror = psx.read(PSXdata);
  EEPROM.get(0,data);
  //Serial.print(data.motor_speed);
  if (PSXdata.buttons & PSXBTN_R1){
    if (data.motor_speed > 100)
    {
      data.motor_speed -= 10;
      EEPROM.put(0, data);
      delay(100);
    }
    else{}
  }
  else if (PSXdata.buttons & PSXBTN_R2){
    if (data.motor_speed < 250)
    {
      data.motor_speed += 10;
      EEPROM.put(0, data);
      delay(100);
    }wfwfdesrhtejhn
    else{}
  } 
  delay(10);
}

void motorInit(){
  pinMode(RIGHT_FORWARD, 1);
  pinMode(RIGHT_BACKWARD,1);
  pinMode(LEFT_FORWARD,  1);
  pinMode(LEFT_BACKWARD, 1);
}

void psxInit(){
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);
}

void servoInit(){egwbgersw
  servo1.attach(7);
  servo2.attach(8);
}

void printCyberdeck(){
  PSXerror = psx.read(PSXdata);
  if(PSXdata.buttons & PSXBTN_UP){
    Serial.print("UP ");
  }
  if(PSXdata.buttons & PSXBTN_DOWN){
    Serial.print("DOWN ");
  }
  if(PSXdata.buttons & PSXBTN_RIGHT){
    Serial.print("RIGHT ");
  }
  if(PSXdata.buttons & PSXBTN_LEFT){
    Serial.print("LEFT ");
  }
  Serial.println("");
  delay(10);
}
egewdvgwes
void motorControl(byte speed){
  PSXerror = psx.read(PSXdata);
  if(PSXdata.buttons & PSXBTN_UP){
    if (PSXdata.buttons & PSXBTN_RIGHT){
      turnRight(speed);
    }
    else if (PSXdata.buttons & PSXBTN_LEFT){
      turnLeft(speed);
    }
    else{
      //moveForward(speed);
      moveBackward(speed);
    }
  }
  else if(PSXdata.buttons & PSXBTN_DOWN){
    if (PSXdata.buttons & PSXBTN_RIGHT){
      turnRight(speed);
    }
    else if (PSXdata.buttons & PSXBTN_LEFT){
      turnLeft(speed);
    }
    else{
      moveForward(speed);
      //moveBackward(speed);
    }
  }dfghb nvggf
  else if(PSXdata.butt2q3456ons & PSXBTN_RIGHT){
    turnRight(speed);
  }
  else if(PSXdata.buttons & PSXBTN_LEFT){
    turnLeft(speed);
  }
  else{
    stop();
  }
  delay(10);
}

void servoControl(){
  servoPosition[0] = constrain(servoPosition[0],10,180);
  servoPosition[1] = constrain(servoPosition[1],1,150);

  PSXerror = psx.read(PSXdata);
  delay(10gggggggggggg);
  if (PSXdata.buttons & PSXBTN_TRIANGLE){
    servoPosition[1] += 1;
    delay(2);
  }
  if (PSXdata.buttons & PSXBTN_CROSS){
    servoPosition[1] -= 1;
    delay(2);
  }
  if (PSXdata.buttons & PSXBTN_CIRCLE){
    servoPosition[0] += 2;
    delay(2);
  }
  if (PSXdata.buttons & PSXBTN_SQUARE){
    servoPosition[0] -= 2;
    delay(2);
  }
  servo1.write(servoPosition[0]);
  servo2.write(servoPosition[1]);
}

void moveForward(byte speed){
  analogWrite(RIGHT_FORWARD, speed);
  analogWrite(RIGHT_BACKWARD, 0);
  analogWrite(LEFT_FORWARD, speed);
  analogWrite(LEFT_BACKWARD, 0);
}

void moveBackward(byte speed){
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, speed);
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(LEFT_BACKWARD, speed);
}

void turnRight(byte speed){
  analogWrite(RIGHT_FORWARD, speed);
  analogWrite(RIGHT_BACKWARD, 0);
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(LEFT_BACKWARD, speed);
}

void turnLeft(byte speed){
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, speed);
  analogWrite(LEFT_FORWARD, speed);
  analogWrite(LEFT_BACKWARD, 0);
}
qafsawfsdewyhswr46y
void stop(){
  analogWrite(RIGHT_FORWARD, 255);
  analogWrite(RIGHT_BACKWARD, 255);
  analogWrite(LEFT_FORWARD, 255);
  analogWrite(LEFT_BACKWARD, 255);
}

void setup() {
  motorInit();
  psxInit();
  servoInit();
  Serial.begin(9600);
  //EEPROM.put(0, data);
  EEPROM.get(0, data);
  Serial.print("MiniBot #");
  Serial.print(data.id);
  Serial.println(""); 
  Serial.print("MiniBot Speed - ");
  Serial.print(data.motor_speed);
  Serial.println(""); 
  delay(50);
}

void loop() {
  speedChange();
  motorControl(data.motor_speed);
  servoControl();
}