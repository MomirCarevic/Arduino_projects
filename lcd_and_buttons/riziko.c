// Simple test application that displays pressed button on display
// every button has its own index that are defined whith macros
// you can controll backlight (brightness) of LCD with pwm on digital pin 10
// eg. pinMode(10,OUTPUT); analogWrite(10,255); // range 0-255
// contrast is set trough blue potentiometer
#include <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

#define POCETNO_STANJE 0
#define BIRANJE_BROJA_KOCKICA 1
#define BACANJE_KOCKICA 2
#define SABERI_REZULTAT 3
#define SET_SECOND_PLAYER 4

int currentState = 0, touch_new = 0, touch_old = 0;
int kockicaCounter = 0, brojCounter = 0, n=0;

int rezultat[11];
int player1rez = 0, player2rez = 0, which_player = 0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {

    Serial.begin(9600);

    lcd.begin(16, 2);
  
  	currentState = POCETNO_STANJE;
}
void loop() 
{
    switch (currentState)
    {
    case POCETNO_STANJE:
        lcd.print("Unesite broj");
        lcd.setCursor(0,1);
        lcd.print("kockica:");
        currentState = BIRANJE_BROJA_KOCKICA;
        break;

    case BIRANJE_BROJA_KOCKICA:
        
        touch_new = readButton();

        if( touch_new != touch_old )
        {
            if( touch_new == UP && kockicaCounter < 5 )
            {
              	lcd.setCursor(9,1);
                kockicaCounter++;
                lcd.print(kockicaCounter);
              	delay(50);
            }
            else if ( touch_new == DOWN && kockicaCounter > 1 )
            {
              	lcd.setCursor(9,1);
                kockicaCounter--;
                lcd.print(kockicaCounter);
              	delay(50);
            }
            else if ( touch_new == SELECT )
            {
                currentState = BACANJE_KOCKICA;
              	lcd.clear();
                break;
            }
        }
      	break;
    
    case BACANJE_KOCKICA:
      	delay(100);
        
        which_player = 1;
        
        for(int i = 0 ; i < kockicaCounter ; i++ )
        {
            do
            {
                lcd.setCursor(n,0);
                lcd.print(brojCounter);
                brojCounter++;
                delay(100);
				              
                if(brojCounter == 6)
                    brojCounter = 0;
            
            }while(readButton() != SELECT);
            
            rezultat[i] = brojCounter - 1;
            n++;
        }
		
        if(which_player == 1 )
        {
            for (int i = 0 ; i < kockicaCounter + 1 ; i++)
            {
              	Serial.println(rezultat[i]);
                player1rez = player1rez + rezultat[i];
            }
          	Serial.print("Rezultat:");
          	Serial.println(player1rez);

            currentState = SET_SECOND_PLAYER;
            break;
        }
        else if( which_player == 2 )
        {
            for (int i = 0 ; i < kockicaCounter ; i++)
            {
                player2rez = player2rez + rezultat[i];
            }
        }

        break;

    default:
        break;
    }


}

byte readButton()
{
 int tmp = analogRead(0); //read value of Analog input 0
 //depending on voltage, we can find out which switch was pressed
 if (tmp > 635 && tmp < 645) //SELECT
 	return SELECT;
 if (tmp > 405 && tmp < 415) //LEFT
 	return LEFT;
 if (tmp > 95 && tmp < 105) //UP
 	return UP;
 if (tmp > 252 && tmp < 262) //DOWN
 	return DOWN;
 if (tmp < 5) //RIGHT
 	return RIGHT;
 return 0; //NONE
}