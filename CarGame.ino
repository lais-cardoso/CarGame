#include <SparkFunColorLCDShield.h>
#include <Crescer.h>

#define BACKGROUND  WHITE
#define BACKGROUNDWHITE  WHITE 
#define C_COLOR  RED  
#define H_COLOR  BLUE 
#define M_COLOR  GREEN  
#define S_COLOR  YELLOW  

#define joystick_y A8 //Joystick


int x = 70;
int i = 0; //Contador para os obstáculos

int positions_x[] = {22,70,118};
char colors[] = {PINK, YELLOW, RED, ORANGE, BLACK};
int positions_y[] = {39,56,73,90,107,124};

//Formato do carro
const char PROGMEM cart[] =
{
B00011111,B11110000,
B00011111,B11110000,
B01111001,B00111100,
B01111001,B00111100,
B01111001,B00111100,
B00011011,B10110000,
B00011000,B00110000,
B00011000,B00110000,
B00011010,B10110000,
B01111010,B10111100,
B01111011,B10111100,
B01111000,B00111100,
B00011111,B11110000,
B00011111,B11110000,
B00000000,B00000000,
};

LCDShield lcd;

int buttonPins[3] = {3, 4, 5};

int flag=0;

unsigned long startTime;  // Variável para armazenar o tempo inicial
unsigned long elapsedTime; // Variável para armazenar o tempo decorrido

void resetTimer() {
  startTime = millis(); // Define o tempo inicial como o tempo atual
}


void displayMyCar(int x){    
  //-------------Desenha o carro na cor roxa----------------//
  lcd.setChar(*cart,124 ,x , BACKGROUND, PURPLE);
}

void GAME(){
    elapsedTime = millis() - startTime;  
    //POSIÇÃO E COR DO OBSTÁCULO 1
    char color = colors[random(0,5)];
    int positions = positions_x[random(0,3)];
    //POSIÇÃO E COR DO OBSTÁCULO 2
    char color_2 = colors[random(0,5)];
    int positions_2 = positions_x[random(0,3)];
    //POSIÇÃO E COR DO OBSTÁCULO 3
    char color_3 = colors[random(0,5)];
    int positions_3 = positions_x[random(0,3)];
    
    for(i=0;i<10;i++){
      //              Lê o joystick
      int pos = analogRead(joystick_y);
      //          APAGA RASTRO DO CARRO
      lcd.setChar(*cart,124 ,x, BACKGROUND, BACKGROUND);
   
      //           MOVIMENTO DO CARRO
      //-> Desloca o carro para a direita <-
        if (pos > 600) { 
           x=x+48; 
   
        if(x>118) x =118; 
        } 
     // -> Desloca o carro para a esquerda <-
        if (pos < 400) { 
          x=x-48;
        if(x<22) x =22; 
        }
     //---------------------------------------------- 

      //OBSTÁCULO 1
      if(i>0 && i<6){
      lcd.setChar(*cart,positions_y[i-1] , positions , BACKGROUND, BACKGROUND);
      }
      if(i<6){
      lcd.setChar(*cart, positions_y[i] , positions , BACKGROUND, color);
      }

      //OBSTÁCULO 2
       if(i>=2 && i<8){
     
        lcd.setChar(*cart, positions_y[i-2] , positions_2 , BACKGROUND, color_2);
        
        }
       if(i>2 && i<8){
         lcd.setChar(*cart, positions_y[i-3] , positions_2 , BACKGROUND, BACKGROUND);
        }
        
      //OBSTÁCULO 3
      if(i>=4){
        lcd.setChar(*cart, positions_y[i-4] , positions_3 , BACKGROUND, color_3);
        }
      if(i>4){
        lcd.setChar(*cart,positions_y[i-5] , positions_3 , BACKGROUND, BACKGROUND);
        }
      
      //Desenha o carro do jogador na tela
      if(flag!=2){
      displayMyCar(x);
      }      
      delay(200);

      //Verificação de colisão
      if(x==positions && positions_y[i] == 124){
        flag = 2; //SAI DO GAME        
        gameOver();
        break;        
      }
      if(x==positions_2 && positions_y[i-2]==124){
        flag = 2; //SAI DO GAME
        gameOver();
        break;        

      }
      if(x==positions_3 && positions_y[i-4]==124){
        flag = 2; //SAI DO GAME
       gameOver();
       break;        

      }

      //RESETA OBSTÁCULO 1
      if(positions_y[i]==124){
      lcd.setChar(*cart,positions_y[i] , positions , BACKGROUND, BACKGROUND);
      }
      //RESETA OBSTÁCULO 2
      if(positions_y[i-2]==124){
        lcd.setChar(*cart, positions_y[i-2] , positions_2 , BACKGROUND, BACKGROUND);
        }
       //RESETA OBSTÁCULO 3
      if(positions_y[i-4]==124){
        lcd.setChar(*cart, positions_y[i-4] , positions_3 , BACKGROUND, BACKGROUND);
        }

      

}
}

//---------Desenha pista------------
void drawRoad(){
  /* Initialize the LCD, set the contrast, clear the screen */
  lcd.init(PHILIPS);
  lcd.contrast(-63);
  lcd.clear(BACKGROUND);

  lcd.setRect(0, 2, 131, 6, 1, YELLOW);
  lcd.setRect(0, 6, 131, 18, 1, WHITE);

  lcd.setRect(0, 21, 131, 35, 1, WHITE);
  lcd.setRect(0, 35, 131, 51, 1, YELLOW);
  lcd.setRect(0, 51, 131, 66, 1, WHITE);

  lcd.setRect(0, 69, 131, 83, 1, WHITE);
  lcd.setRect(0, 83, 131, 99, 1, YELLOW);
  lcd.setRect(0, 99, 131, 114, 1, WHITE);

  lcd.setRect(0, 117, 131, 126, 1, WHITE);
  lcd.setRect(0, 127, 131, 131, 1, YELLOW);
}

void homePage(){  
  lcd.init(PHILIPS);
  lcd.contrast(-63);
  lcd.clear(BACKGROUNDWHITE);

  //frase
  lcd.setStr("PRESS START", 14, 20, BLACK, WHITE);

  //bordas
  lcd.setRect(125, 0, 131, 131, 1, YELLOW);
  lcd.setRect(-131, 125, 131, 131, 1, YELLOW);
  lcd.setRect(-131, 0, 131, 6, 1, YELLOW);
  lcd.setRect(0, 0, 6, 131, 1, YELLOW);

  //carrinho
  lcd.setRect(65, 20, 80, 110, 1, BLUE);
  lcd.setRect(50, 30, 65, 98, 1, BLUE);
  //rodas
  lcd.setRect(75, 33, 85, 43, 1, BLACK);
  lcd.setRect(75, 85, 85, 95, 1, BLACK);

  //janelas
  lcd.setRect(55, 35, 62, 55, 1, WHITE);
  lcd.setRect(55, 65, 62, 93, 1, WHITE);

}

void gameOver(){
  lcd.init(PHILIPS);
  lcd.contrast(-63);
  lcd.clear(WHITE);

//frase
  lcd.setStr("GAME OVER", 50, 30, BLACK, WHITE);
  lcd.setStr("PRESS START", 80, 20, BLACK, WHITE);
  char myChar[50];
  int division = elapsedTime/1000;
  sprintf(myChar, "POINTS: %d", division);
  Serial.println(myChar);
  
  lcd.setStr(myChar, 17, 25, BLACK, WHITE);
  Serial.print("Tempo decorrido (ms): ");
  Serial.println(elapsedTime);
  resetTimer();
  flag = 0;
}


int Ler_joystick() 
{ 
  return(analogRead(A8)); 
}


//--- INICIA O DISPLAY LCD, DEFINE OS BOTÕES COMO PERIFÉRICOS DE ENTRADA, DESENHA A PISTA NA TELA E DESENHA O CARRO LOGO DE INÍCIO

 int button1 = 0;
 int button2 = 0;

void setup(){
  Serial.begin(9600);
  resetTimer();
 
  for (int j=0; j<3; j++)
   {
    pinMode(buttonPins[j], INPUT);
     digitalWrite(buttonPins[j], HIGH);
   }
  pinMode(joystick_y, INPUT);

  pinMode(buttonPins[0], INPUT);
  pinMode(buttonPins[1], INPUT);
  homePage();
}

void loop(){
  unsigned long time;
  button1 = digitalRead(buttonPins[0]);
  button2 = digitalRead(buttonPins[1]);

  if(!digitalRead(buttonPins[2]) && flag == 0){
    drawRoad();
    displayMyCar(x);        
    flag = 1;

    } 
  if (flag==1){
    GAME();
  }

  delay(1000);
  }