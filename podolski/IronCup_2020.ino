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
  Serial.begin(9600);
  //Serial.print("oi");
  //mantido para ocasional debug

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
    pinMode(3,INPUT_PULLUP);// Chave 2
    pinMode(2,INPUT_PULLUP);// Chave 1
  //-----------------------

  pinMode(13,INPUT); //Botao de start (onofre)
  while(digitalRead(13)==1){} //Aguarda o botao onofre ser ativado

  digitalWrite(8,1); //Seta o STBY para ativado
  delay(2000); //Aguarda os 5 segunndos
  
  executa_estrategia();
  //Começa o round efetivamente

}

void loop() {
  /*while(true){ 
    //Debugsons-->descomente caso precise debubar e comente o outro
    Serial.print("\nLinhas--->Esquerda: ");
    Serial.print(analogRead(A1));
    Serial.print("      Direita: ");
    Serial.print(analogRead(A0));
    Serial.print("\nOponente---> ");
    Serial.println(oponente);
  }*/
  
  while((analogRead(A1)>400) && (analogRead(A0)>400)){
    //enquanto estiver no preto

    busca_oponente();
    switch (oponente) {
      // Vide Tabela de Conversão no void busca_oponente()
      case 0:
        if (direcao) {
          move('D','F', 150);
          move('E','T', 150);
        }else{
          move('D','T', 150);
          move('E','F', 150);
        }
        break;
      case 1:
        move('D','F', 50);
        move('E','F', 255);
        direcao = false;
        break;
      case 2:
        move('D','F', 255);
        move('E','F', 255);
        break;
      case 3:
        move('D','F', 200);
        move('E','F', 255);
        direcao = false;
        break;
      case 4:
        move('D','F', 255);
        move('E','F', 50);
        direcao = true;
        break;
      case 5:
        move('D','F', 255);
        move('E','F', 255);
        break;
      case 6:
        move('D','F', 255);
        move('E','F', 200);
        direcao = true;
        break;
      case 7:
        move('D','F', 255);
        move('E','F', 255);
        break;
      default:
      //caso a variavel esteja com valor bugado apenas roda
        if (direcao) {
          move('D','F', 150);
          move('E','T', 150);
        }else{
          move('D','T', 150);
          move('E','F', 150);
        }
        break;
    }
  }
  //se sair do while executa a rotina de linha
  move('D','T', 255);
  move('E','T', 255);
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
    if (digitalRead(4)==1){ estrategia += pow(2,0); }
    if (digitalRead(3)==1){ estrategia += pow(2,1); }
    if (digitalRead(2)==1){ estrategia += pow(2,2); }
    
    //Mais debug
    Serial.print("chave3: ");
    Serial.print(digitalRead(4));
    Serial.print("      chave2: ");
    Serial.print(digitalRead(3));
    Serial.print("      chave1: ");
    Serial.print(digitalRead(2));
    Serial.print("      chave4: ");
    Serial.print(digitalRead(12));
    Serial.print("      estrategia: ");
    Serial.print(estrategia);
    
  //-----------------------

  switch (estrategia){
    case 0:
      /*
        -->Frentão:
        Estrategia de ataque total,
        somente para de avançar se 
        percceber que o oponete esta 
        escapando para algum dos lados
      */
      while(((oponente != 1) && (oponente != 4)) && ((analogRead(A1)>400) && (analogRead(A0)>400))) {
        Serial.print("\nOponente---> ");
        Serial.println(oponente);
        switch (oponente){
          case 3:
            move('D','F', 200);
            move('E','F', 255);
            direcao = false;
            break;
          case 6:
            move('D','F', 255);
            move('E','F', 200);
            direcao = true;
            break;
          default:
            move('D','F', 255);
            move('E','F', 255);
            break;
        }
        busca_oponente();
      }
      break;
    case 1:
      /*
        -->Babaca:
        Estrategia de filho da put@.
        (inpirada nas da Maua)
        Posiconar o robo bem atras e reto, 
        quando ele inicia o robo se dirige 
        para um dos lado do dojo o mais 
        rapido possivel e aguarda ate que 
        o oponente passe em sua frente
      */

      //vira para o lado que ele vai aguardar
      if (direcao){
        move('D','F', 255);
      }else{
        move('E','F', 255);
      }
      delay(100);

      //avança ate a beirada
      move('D','F', 255);
      move('E','F', 255);
      delay(400);

      //vira de frente para o meio
      if (direcao){
        move('D','T', 255);
        move('E','F', 255);
      }else{
        move('D','F', 255);
        move('E','T', 255);
      }
      delay(200);
      //para 
      move('D','F', 0);
      move('E','T', 0);

      //aguarda perceber o oponente
      busca_oponente();
      while(oponente == 0){
        busca_oponente();
      }
      break;
    case 2:
      /*
        -->Babaca 2:
        Estrategia de filho da put@ tambem.
        (inpirada nas da Maua)
        Posiconar o robo bem a frente e
        torto uns 45°, quando ele inicia o 
        robo se dirige para a borda onde 
        esta apontando, vira e espera 
        encontrar o oponente
      */

      //avança ate a beirada
      move('D','F', 255);
      move('E','F', 255);
      delay(400);

      //vira de frente para o meio
      if (direcao){
        move('D','T', 255);
        move('E','F', 255);
      }else{
        move('D','F', 255);
        move('E','T', 255);
      }
      delay(250);
      //para 
      move('D','F', 0);
      move('E','T', 0);

      //aguarda perceber o oponente
      busca_oponente();
      while(oponente == 0){
        busca_oponente();
      }
      break;
    case 3:
      /*
        -->Costas:
        Caso de empate comessando
        de costas para o oponente.
        Vira 180° em velociade maxima.
      */
      if (direcao){
        move('D','F', 255);
        move('E','T', 255);
      }else{
        move('D','T', 255);
        move('E','F', 255);
      }
      delay(200);
      break;
    case 4:
      /*
        -->Correção:
        Corrige apenas um pouco
        para ficar exatamente de frente 
        para o oponente
      */
      if (direcao){
        move('D','F', 255);
        move('E','T', 255);
      }else{
        move('D','T', 255);
        move('E','F', 255);
      }
      delay(75);
      break;
    case 5:
      /*
        -->Baby_Shark:
        Fica virando d pouquinho em pouquinho 
        o robo enquanto busca o oponente.
        Posicionar o robo ao fundo do dojo.
      */
      busca_oponente();
      while(oponente == 0){
        busca_oponente();
        if (direcao){
          move('E','F', 150);
        }else{
          move('D','F', 150);
        }
        direcao = !direcao;
        delay(100);
      }

      //avança ate a beirada
      move('D','F', 255);
      move('E','F', 255);
      delay(400);

      //vira de frente para o meio
      delay(250);
      //para 
      move('D','F', 0);
      move('E','T', 0);

      //aguarda perceber o oponente
      break;
    case 6:
      break;
    case 7:
      /*
        -->Barra:
        Não faz nada, apenas inicia o loop de
        busca. Bom p dar aquela enganada, ou não, 
        as vezes acaba sendo o mais usado.
      */
      break;
    default:
      /*
        -->Deu merda:
        VAI QUE... se der alguma merda
        c a variavel apenas pula para 
        o loop geral tb.
      */
      break;
  }
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

  if (analogRead(A2)>40){ oponente += pow(2,0); }//direita
  if (analogRead(A3)>30){ oponente += pow(2,1); }//frontal
  if (analogRead(A4)>40){ oponente += pow(2,2); }//esquerda
  /*
  //Debug novamente:
  Serial.print("\nDistancia--->Esquerda: ");
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
