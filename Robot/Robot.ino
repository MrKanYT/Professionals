#include "MeMegaPi.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Ultrasonic.h>
#include <SoftServo.h>

#define GRN A15
#define YEL A14
#define BTN A9

#define LEFT_RM A13
#define RIGHT_RM A12
#define LINE A11

#define ECHO A6
#define TRIG A10

#define GRAB_SERVO A8
#define SCAN_SERVO A7

#define UP 190
#define MID 140
#define DOWN 125

Adafruit_SH1106 display(4);
SoftServo myservo;

Ultrasonic ultrasonic(TRIG, ECHO);

MeMegaPiDCMotor motorL(PORT1B);
MeMegaPiDCMotor motorR(PORT2B);
MeMegaPiDCMotor grabber(PORT3B);

void setup() {
  pinMode(GRN, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(BTN, INPUT);
  Serial3.begin(9600);
  Serial.begin(9600);

  myservo.attach(A8);
  myservo.write(DOWN);
}
bool start = 1;
void yield() {
  myservo.tick();
}
void loop() {
  myservo.tick();
  Serial.println(ultrasonic.read());
  if (start) {
    grabber.run(-100);
    myservo.write(DOWN);
    delay(2000);
    grabber.stop();

    motorR.run(102);
    motorL.run(-100);
    delay(500);
    motorR.stop();
    motorL.stop();

    grabber.run(100);
    delay(1000);
    grabber.stop();

    myservo.write(MID);
    delay(500);

    motorR.run(-100);
    motorL.run(102);
    delay(1500);
    motorR.stop();
    motorL.stop();

    myservo.write(UP);
    delay(500);

    motorR.run(-100);
    motorL.run(-100);
    delay(500);
    motorR.stop();
    motorL.stop();

    motorR.run(102);
    motorL.run(-100);
    delay(500);
    motorR.stop();
    motorL.stop();

    grabber.run(-100);
    delay(1000);
    grabber.stop();

    start = 0;}
}