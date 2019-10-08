bool direcao;

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
  
  //DIP Switch:
//---------------------Ajustar qual laddo é 1 e qual lado e 0------------------------ 
  pinMode(4,INPUT); //Direção de giro da busca-- 1 == XXX -- 0 == YYY
//-----------------------------------------------------------------------------------
  pinMode(3,INPUT); //Inicia retao quando 1
  pinMode(2,INPUT);   //Inicia fazendo um drift 
        //-----------IMPORTANTE-----------//
        //--ajustar corretamento o switc--//
        //----para a direção do drift-----//

  pinMode(13,INPUT);  //Botao de start 

  digitalWrite(8,0);  //Seta o STBY para desativado

  while(digitalRead(13)==1){} //Aguarda o botao onofre ser pressionado

  delay(5000);      //Aguarda os 5 segunndos 
  digitalWrite(8,1);    //Seta o STBY para ativado
//---------------------------------------------------------------------------------------
  analogWrite(11,100);  //perguntar pro Lucca pq setar o pwm dos motores aqui
  analogWrite(5,100);   //perguntar pro Lucca pq setar o pwm dos motores aqui
//---------------------------------------------------------------------------------------

  if(digitalRead(4)==1){    //--------------------------//
    direcao = true;     //-Seta para girar para XXX-//
  }else{            //--------------------------//
    direcao = false;    //-Seta para girar para YYY-//
  }             //--------------------------//

  if(digitalRead(3)==0){    
                //--------------------------//
    digitalWrite(10,0);   //--------------------------//
    digitalWrite(9,1);    //--------------------------//
    digitalWrite(7,0);    //----------COMEÇA----------//
    digitalWrite(6,1);    //-------PARA FRENTE--------//
    analogWrite(11,255);  //--------------------------//
    analogWrite(5,160);   //--------------------------//
    delay(500);       //--------------------------//

  }

  else if(digitalRead(2)==0){

    if (direcao) {
      analogWrite(11,255);
      analogWrite(5,255);
      digitalWrite(10,1);   //-----------------------//
      digitalWrite(9,0);    //-----------------------//
      digitalWrite(7,0);    //---------DRIFT---------//
      digitalWrite(6,1);
      delay(100);
      digitalWrite(10,0);   //-----------------------//
      digitalWrite(9,1);    //-----------------------//
      digitalWrite(7,0);    //---------DRIFT---------//
      digitalWrite(6,1);
      analogWrite(11,255);  //----------yyy----------//
      analogWrite(5,255);
      delay(80);
      analogWrite(11,255);  //----------yyy----------//
      analogWrite(5,140);
      delay(800);
    }else{
      analogWrite(11,255);
      analogWrite(5,255);
      digitalWrite(10,0);   //-----------------------//
      digitalWrite(9,1);    //-----------------------//
      digitalWrite(7,1);    //---------DRIFT---------//
      digitalWrite(6,0);
      delay(100);
      digitalWrite(10,0);   //-----------------------//
      digitalWrite(9,1);    //-----------------------//
      digitalWrite(7,0);    //---------DRIFT---------//
      digitalWrite(6,1);
      analogWrite(11,255);  //----------yyy----------//
      analogWrite(5,255);
      delay(80);
      analogWrite(11,150);  //----------yyy----------//
      analogWrite(5,255);
      delay(800);
    }
    direcao=!direcao;  
  }
}
  
void loop() {
  if(direcao){

        digitalWrite(10,1); //-----------------------//
        digitalWrite(9,0);  //-----------------------//
        digitalWrite(7,0);  //--------Procura--------//
        digitalWrite(6,1);  //----------XXX----------//
        analogWrite(11,90); //-----------------------//
        analogWrite(5,90);  //-----------------------//

      }else{

        digitalWrite(10,0); //-----------------------//
        digitalWrite(9,1);  //-----------------------//
        digitalWrite(7,1);  //--------Procura--------//
        digitalWrite(6,0);  //----------YYY----------//
        analogWrite(11,90); //-----------------------//
        analogWrite(5,90);  //-----------------------//
      }
/*  while(analogRead(A0)>500 && analogRead(A1)>500){

    if(analogRead(A3)>20){

      digitalWrite(10,0);   //-----------------------//
      digitalWrite(9,1);    //-----------------------//
      digitalWrite(7,0);    //--------Avança---------//
      digitalWrite(6,1);    //--------Frente---------//
      analogWrite(11,255);  //-----------------------//
      analogWrite(5,255);   //-----------------------//

    }else if(analogRead(A4)>20){

      digitalWrite(10,0);   //-----------------------//
      digitalWrite(9,1);    //-----------------------//
      digitalWrite(7,0);    //--------Avança---------//
      digitalWrite(6,1);    //-------Esquerda--------//
      analogWrite(11,250);  //-----------------------//
      analogWrite(5,90);    //-----------------------//

    }else if(analogRead(A2)>20){

      digitalWrite(10,0);   //-----------------------//
      digitalWrite(9,1);    //-----------------------//
      digitalWrite(7,0);    //--------Avança---------//
      digitalWrite(6,1);    //--------Direita--------//
      analogWrite(11,90);   //-----------------------//
      analogWrite(5,250);   //-----------------------//

    }else{

      if(direcao){

        digitalWrite(10,1); //-----------------------//
        digitalWrite(9,0);  //-----------------------//
        digitalWrite(7,0);  //--------Procura--------//
        digitalWrite(6,1);  //----------XXX----------//
        analogWrite(11,90); //-----------------------//
        analogWrite(5,90);  //-----------------------//

      }else{

        digitalWrite(10,0); //-----------------------//
        digitalWrite(9,1);  //-----------------------//
        digitalWrite(7,1);  //--------Procura--------//
        digitalWrite(6,0);  //----------YYY----------//
        analogWrite(11,90); //-----------------------//
        analogWrite(5,90);  //-----------------------//
      }
    }
  }   //se sair do while executa a rotina de linha

  digitalWrite(10,1);   //-----------------------//
  digitalWrite(9,0);    //-----------------------//
  digitalWrite(7,1);    //---------Foge----------//
  digitalWrite(6,0);    //----------da-----------//
  analogWrite(11,200);  //--------Linha----------//
  analogWrite(5,200);   //-----------------------//
  delay(400);       //-----------------------//
  */  
}
