#include <Servo.h>

Servo myservo;
const int del = 200;
const int rightpos = 0;
const int leftpos = 90;
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
const int servo_pin = 9;
bool lastMoveWasRight;
bool ezmode = false;

void setup() {
  myservo.attach(servo_pin);
  myservo.write(60);
  myservo.detach();
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
  int btn = digitalRead(SW_pin);
  int y = analogRead(Y_pin);

  Serial.print("btn: ");
  Serial.print(btn);
  Serial.print("\n");
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("\n");
  
  if(btn == 0){
     ezmode = !ezmode;
     delay(500);
  }
  
  if(y < 10){
    ezmode = false;
    move(true);
  }
    
  if(y > 650){
    ezmode = false;
    move(false); 
  }

  if(ezmode)
    move(!lastMoveWasRight);
}

void move(bool right){
  if(right ^ lastMoveWasRight){
    myservo.attach(servo_pin);
    if(right){
      myservo.write(rightpos);
    }else{
      myservo.write(leftpos);
    }
    delay(del);
    myservo.detach();
  }
  
  lastMoveWasRight = right;
}
