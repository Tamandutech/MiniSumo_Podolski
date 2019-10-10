#include <analogWrite.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
int servoPin = 5;

  #define irD 27
  #define irM 14
  #define irE 12
  #define irT 13
  
  #define ivD 4
  #define ivE 2
  #define ivT 15

  #define pwmB 23
  #define b1 25
  #define b2 1
  #define stby 3
  #define a1 26
  #define a2 19
  #define pwmA 18

  #define button 36

  #define dip1 33
  #define dip2 32
  #define dip3 35
  #define dip4 34
  
  #define scl 22
  #define sda 21

void setup() {
  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);

  pinMode(irD, INPUT);
  pinMode(irM, INPUT);
  pinMode(irE, INPUT);
  pinMode(irT, INPUT);
  
  pinMode(ivD, INPUT);
  pinMode(ivE, INPUT);
  pinMode(ivT, INPUT);

  pinMode(button, INPUT);

  pinMode(dip1, INPUT);
  pinMode(dip2, INPUT);
  pinMode(dip3, INPUT);
  pinMode(dip4, INPUT);

  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);

  myservo.attach(servoPin); //liga servo
  myservo.detach(); //desliga servo
  myservo.write(180); //move servo até xº de 0º até 180º

  while(digitalRead(button));
  digitalWrite(stby,1);
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, 100); //maximo 255
  analogWrite(pwmA, 100);
}
 
void loop() {
}
