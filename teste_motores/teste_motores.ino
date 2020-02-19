void setup() {
  pinMode(11,OUTPUT); //pwmB
  pinMode(10,OUTPUT); //Bin
  pinMode(9,OUTPUT);  //Bin
  pinMode(8,OUTPUT);  //STBY
  pinMode(7,OUTPUT);  //Ain
  pinMode(6,OUTPUT);  //Ain
  pinMode(5,OUTPUT);  //pwmA
}
  
void loop() {
  digitalWrite(8,1);
  digitalWrite(10,0);
  digitalWrite(9,1);
  digitalWrite(7,0);
  digitalWrite(6,1);
  analogWrite(11,100);
  analogWrite(5,100);
  delay(1000);
  digitalWrite(10,1);
  digitalWrite(9,0);
  digitalWrite(7,1);
  digitalWrite(6,0);
  delay(1000);
}
