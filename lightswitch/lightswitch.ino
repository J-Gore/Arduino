#include <Servo.h>
#include "IRremote.h"

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int del = 400;
int inc = 5;
int receiver = 11;
bool on = true;
String lastPress;

IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void translateIR() // takes action based on IR code received
{
  switch (results.value)
  {
    case 0xFFA25D: Serial.println("POWER");
      on = !on;
      if (on) {
        LightOn();
      } else {
        LightOff();
      }
      break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE");    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");
      lastPress = "DOWN";
      pos = pos + inc;
      myservo.write(pos);
      //delay(500);
      break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");
      lastPress = "UP";
      pos = pos - inc;
      myservo.write(pos);
      //delay(500);
      break;
    case 0xFF9867: Serial.println("EQ");    break;
    case 0xFFB04F: Serial.println("ST/REPT");    break;
    case 0xFF6897: Serial.println("0");
      myservo.write(0);
      break;
    case 0xFF30CF: Serial.println("1");
      myservo.write(10);
      pos = 10;
      break;
    case 0xFF18E7: Serial.println("2");
      myservo.write(20);
      pos = 20;
      break;
    case 0xFF7A85: Serial.println("3");
      myservo.write(30);
      pos = 30;
      break;
    case 0xFF10EF: Serial.println("4");
      myservo.write(40);
      pos = 40;
      break;
    case 0xFF38C7: Serial.println("5");
      myservo.write(50);
      pos = 50;
      break;
    case 0xFF5AA5: Serial.println("6");
      myservo.write(60);
      pos = 60;
      break;
    case 0xFF42BD: Serial.println("7");
      myservo.write(70);
      pos = 70;
      break;
    case 0xFF4AB5: Serial.println("8");
      myservo.write(80);
      pos = 80;
      break;
    case 0xFF52AD: Serial.println("9");
      myservo.write(90);
      pos = 90;
      break;
    case 0xFFFFFFFF: Serial.println(" REPEAT");
      if (lastPress == "UP") {
        pos = pos - inc;
        myservo.write(pos);
      } else if (lastPress == "DOWN") {
        pos = pos + inc;
        myservo.write(pos);
      }
      break;

    default:
      Serial.println(" other button   ");

  }// End Case
  Serial.println(pos);
  delay(500); // Do not get immediate repeat


} //END translateIR

void LightOn() {
  myservo.attach(9);
  
  myservo.write(95);
  delay(del);
  myservo.write(60);
  delay(del);
  
  myservo.detach();
}

void LightOff() {
  myservo.attach(9);
  
  myservo.write(20);
  delay(del);
  myservo.write(60);
  delay(del);
  
  myservo.detach();
}

void setup() {
  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
  
  myservo.attach(9);
  myservo.write(60);
  myservo.detach();
}


void loop() {
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }

  //  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  //    // in steps of 1 degree
  //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(del);                       // waits 15ms for the servo to reach the position
  //  }
  //  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //    delay(del);                       // waits 15ms for the servo to reach the position
  //  }
}

