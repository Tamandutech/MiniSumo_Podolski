void frente(){
  digitalWrite(10,0);
  digitalWrite(9,1);
  digitalWrite(7,0);
  digitalWrite(6,1);
}

void tras(){
  digitalWrite(10,1);
  digitalWrite(9,0);
  digitalWrite(7,1);
  digitalWrite(6,0);
}

void giraDir(){
  digitalWrite(10,1);
  digitalWrite(9,0);
  digitalWrite(7,0);
  digitalWrite(6,1);
}

void giraEsq(){
  digitalWrite(10,0);
  digitalWrite(9,1);
  digitalWrite(7,1);
  digitalWrite(6,0);
}

void setup() {
  pinMode(A0,INPUT);  //IRDireito
  pinMode(A1,INPUT);  //IRMeio
  pinMode(A2,INPUT);  //IREsquerdo
  
  pinMode(A3,INPUT);  //LinhaDireito
  pinMode(A4,INPUT);  //LinhaEsquerdo
  
  pinMode(11,OUTPUT); //pwmB
  pinMode(10,OUTPUT); //Bin
  pinMode(9,OUTPUT);  //Bin
  pinMode(8,OUTPUT);  //STBY
  pinMode(7,OUTPUT);  //Ain
  pinMode(6,OUTPUT);  //Ain
  pinMode(5,OUTPUT);  //pwmA
  
  pinMode(4,INPUT); pinMode(3,INPUT); pinMode(2,INPUT); //DIP Switch
  pinMode(13,INPUT);  //Button

  digitalWrite(8,0);
  while(digitalRead(13)==1){}
}
  
void loop() {
  digitalWrite(8,1);
  analogWrite(11,70);
  analogWrite(5,70);
  giraDir();
}
