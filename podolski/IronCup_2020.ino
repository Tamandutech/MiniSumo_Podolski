bool direcao;/*
  Define para qual direção o 
  robo ira buscar o seu adversario 
*/
int estrategia = 0;/*
  Define qual estrategia 
  inicial o robo ira executar
*/
int oponente = 0;/*
  Define qual posição 
  esta o oponente
*/

void setup() {
  //---Sensores de Linha---
    pinMode(A0,INPUT); //Direito
    pinMode(A1,INPUT); //Esquerdo
  //-----------------------

  //---Sensores de Distancia---
    pinMode(A2,INPUT); //Direito
    pinMode(A3,INPUT); //Frontal
    pinMode(A4,INPUT); //Esquerdo
  //-----------------------

  //---Motores---
    //Motor Esquerdo
    pinMode(11,OUTPUT); //pwmB
    pinMode(10,OUTPUT); //Bin
    pinMode(9,OUTPUT);  //Bin

    //Motor Direito
    pinMode(7,OUTPUT);  //Ain
    pinMode(6,OUTPUT);  //Ain
    pinMode(5,OUTPUT);  //pwmA

    //STBY
    pinMode(8,OUTPUT);
    digitalWrite(8,0); //Seta o STBY para desativado inicialmente
  //-----------------------

  //---DIP Switch:---
    pinMode(12,INPUT);// Chave 4
    //Direção de giro inicial da busca e/ou estrategia
    /*
      1 == Esquerda -- 0 == Direita
      como todas as estrategias iniciais 
      podem ser espelhadas utilizaremos 
      uma variavel para dizer qual a 
      direção que iremos seguir com esta estrategia
      
      as entradas do Switch abaixo combinadas 
      podem render até oito estrategias 
      iniciais diferentes de maneira binaria
    */
    pinMode(4,INPUT);// Chave 3
    pinMode(3,INPUT);// Chave 2
    pinMode(2,INPUT);// Chave 1
  //-----------------------

  pinMode(13,INPUT); //Botao de start (onofre)
  while(digitalRead(13)==1){} //Aguarda o botao onofre ser ativado

  digitalWrite(8,1); //Seta o STBY para ativado
  delay(2000); //Aguarda os 5 segunndos
  
  //executa_estrategia();
  //Começa o round efetivamente

  Serial.begin(9600);
  //mantido para ocasional debug
}

void loop() {
  while((analogRead(A1)>500) && (analogRead(A0)>500)){
    //enquanto estiver no preto
  //while(true){
    
    /*Serial.print("\nLinhas--->Esquerda: ");
    Serial.print(analogRead(A1));
    Serial.print("      Direita: ");
    Serial.print(analogRead(A0));*/


    busca_oponente();
    //Serial.println(oponente);
    switch (oponente) {
      // Vide Tabela de Conversão no void busca_oponente()
      case 0:
        if (direcao) {
          move('D','F', 75);
          move('E','T', 75);
        }else{
          move('D','T', 75);
          move('E','F', 75);
        }
          break;
      case 1:
        move('D','F', 25);
        move('E','F', 100);
        direcao = false;
        break;
      case 2:
        move('D','F', 100);
       /move('E','F', 100)
        break;
      case 3:
        move('D','F', 75);
        move('E','F', 100);
        direcao = false;
        break;
      case 4:
        move('D','F', 25);
        move('E','F', 100);
        direcao = true;
        break;
      case 5:
        move('D','F', 100);
        move('E','F', 100)
        break;
      case 6:
        move('D','F', 100);
        move('E','F', 75);
        direcao = true;
        break;
      case 7:
        move('D','F', 100);
        move('E','F', 100);
        break;
      default:
      //caso a variavel esteja com valor bugado apenas roda
        if (direcao) {
          move('D','F', 75);
          move('E','T', 75);
        }else{
          move('D','T', 75);
          move('E','F', 75);
        }
          break;
    }
  }
  //se sair do while executa a rotina de linha
  move('D','T', 200);
  move('E','T', 200);
  delay(400);
}

void move(char M, char S, int V) {
  /*
    M = qual motor 
    'D' -> motor direito || 'E' -> motor esquerdo

    S = quak sentido de rotação
    'F' -> frente || 'T' -> tras

    V = velocidade de rotação
    0 ~ 255
  */

  if ((M == 'D') and (S == 'T')) {
    digitalWrite(7,1);
    digitalWrite(6,0);
    analogWrite(5,V);
  }else if ((M == 'D') and (S == 'F')) {
    digitalWrite(7,0);
    digitalWrite(6,1);
    analogWrite(5,V);
  }else if ((M == 'E') and (S == 'F')) {
    digitalWrite(9,0);
    digitalWrite(10,1);
    analogWrite(11,V);
  }else if ((M == 'E') and (S == 'T')) {
    digitalWrite(9,1);
    digitalWrite(10,0);
    analogWrite(11,V);
  }
}

void executa_estrategia(){
  //Configurações iniciais
    //Estipula a direção
    if(digitalRead(12)==1){
      //Seta para girar para Esquerda
      direcao = true;
    }else{
      //Seta para girar para Direita
      direcao = false;
    }

    //Estipula a estrategia inicial atraves de uma soma binaria
    estrategia = 0;
    if (digitalRead(4)==1){ estrategia += 2^0; }
    if (digitalRead(3)==1){ estrategia += 2^1; }
    if (digitalRead(2)==1){ estrategia += 2^2; }
  //-----------------------




  //
  //
  //
  //
  //ainda será preenchido com as estrategias iniciais 
  //
  //
  //
  //
}

void busca_oponente(){
  /*
    Checa quais sensores de distancia estão 
    detectando o oponente e, apartir disso, estipula 
    um valor para a variavel oponente

    Da mesma maneira que é estipulada a estrategia
    inicial, será utilizado um somatorio binario para 
    combinar os resultaddos de leitura dos sensores de 
    distancia em um int [vide tabela de conversão]
  */

  oponente = 0;//zera a variavel para nova interação

  if (analogRead(A2)>40){ oponente += 2^0; }//direita
  if (analogRead(A3)>30){ oponente += 2^1; }//frontal
  if (analogRead(A4)>40){ oponente += 2^2; }//esquerda
  /*Serial.print("\nDistancia--->Esquerda: ");
  Serial.print(analogRead(A4));
  Serial.print("      Frente: ");
  Serial.print(analogRead(A3));
  Serial.print("      Direita: ");
  Serial.print(analogRead(A2));*/

  /*

  --------------TABELA DE CONVERSÃO----------------
  ________________________________________________
  |                     |                        |
  |  valor da variavel  |  situação do oponente  |
  |_____________________|________________________|
  |                     |                        |
  |          0          |     Fora de vista      |
  |_____________________|________________________|
  |                     |                        |
  |          1          |  Totalmete a direita   |
  |_____________________|________________________|
  |                     |                        |
  |          2          |    Longe e a frente    |
  |_____________________|________________________|
  |                     |                        |
  |          3          |   Um pouco a direita   |
  |_____________________|________________________|
  |                     |                        |
  |          4          |  Totalmete a esquerda  |
  |_____________________|________________________|
  |                     |                        |
  |                     |  Impossivel, somente   |
  |          5          |  laterais, sensor da   |
  |                     |   frente quebrou???    |
  |_____________________|________________________|
  |                     |                        |
  |          6          |   Um pouco a esquerda  |
  |_____________________|________________________|
  |                     |                        |
  |          7          |   Totalmete a frente   |
  |_____________________|________________________|

  */
}
