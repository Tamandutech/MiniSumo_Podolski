void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.print("\nDireita: ");
  Serial.println(analogRead(A0));
  Serial.print("Esquerda: ");
  Serial.println(analogRead(A1));
  delay(300);
}
