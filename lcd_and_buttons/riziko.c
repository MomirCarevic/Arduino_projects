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
#define SET_FIRST_PLAYER 4
#define SET_SECOND_PLAYER 5
#define RESULTS 6
#define WINNER 7
#define RESET_GAME 8


int currentState = 0, touch_new = 0, touch_old = 0;
int kockicaCounter = 0, brojCounter = 1, x = 0, y = 0;
bool flag = 0;

int rezultat[11];
int player1rez = 0, player2rez = 0, which_player = 1, p1Score, p2Score;
int p1 = 5, p2 = 5;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//oblik tenka
byte tank[8] = {
    B00000, 
    B00100, 
    B11111, 
    B11111, 
    B01110, 
    B01110, 
    B11111, 
    B00000  
};

void setup() {
    lcd.begin(16, 2);
    lcd.createChar(0,tank);
  
  	currentState = POCETNO_STANJE;
}
void loop() 
{
    switch (currentState)
    {
    case POCETNO_STANJE:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Unesite broj");
        lcd.setCursor(0,1);
        lcd.print("kockica:");
        currentState = BIRANJE_BROJA_KOCKICA;
        break;

    case BIRANJE_BROJA_KOCKICA:
        
        touch_new = readButton();

        if( touch_new != touch_old )
        {
            if( touch_new == UP && kockicaCounter < 6 )
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
            else if ( touch_new == SELECT && kockicaCounter > 0 )
            {
                lcd.clear();
                if( flag == 0 )
                    currentState = SET_FIRST_PLAYER;
                else
                    currentState = SET_SECOND_PLAYER;
              	
                break;
            }
        }
      delay(100);
      	break;
    
    case BACANJE_KOCKICA:
      	delay(100); //zakomentarisi ovo kasnije 

        for(int i = 0 ; i < kockicaCounter ; i++ )
        {
            do
            {
                lcd.setCursor(x,y);
                lcd.print(brojCounter);
                brojCounter++;
                delay(100);
				              
                if(brojCounter == 7)
                    brojCounter = 1;
            
            }while(readButton() != SELECT);
            
            rezultat[i] = brojCounter - 1;
            x++;
        }
		
        if(which_player == 1)
        {
            lcd.setCursor(0,0);
            sort(rezultat,kockicaCounter); //sortiramo niz rezultata od najmanjeg ka najvecem pozivajuci funkciju koja radi BubbleSort
            p1Score = pronadjiPara(rezultat,kockicaCounter);//pozivamo funkciju koja prebrojava parove i zanemaruje brojeve koji nemaju para

            if ( flag == 0 )
            {
                currentState = SET_SECOND_PLAYER;
                break;
            }
            else
            {
                currentState = RESULTS;
                break;
            }
            break;
        }

        else if( which_player == 2 )
        {
            sort(rezultat,kockicaCounter);
            p2Score = pronadjiPara(rezultat,kockicaCounter);//pozivamo funkciju koja prebrojava parove i zanemaruje brojeve koji nemaju para

            if ( flag == 1 )
            {
                currentState = SET_FIRST_PLAYER;
                break;
            }
            else
            {
                currentState = RESULTS;
                break;
            }
            break;
        }
        break;

    case SET_FIRST_PLAYER:

        which_player = 1;
        x = 0;
        y = 0;

        currentState = BACANJE_KOCKICA;
        break;
    
    case SET_SECOND_PLAYER:

        which_player = 2;
        x = 0;
        y = 1;
        currentState = BACANJE_KOCKICA;
        break;

    case RESULTS:
        
        if( p1Score > p2Score )
        {
            p2--;
            lcd.setCursor(kockicaCounter,0);
            lcd.print("<-WIN");
        }
        else if ( p1Score < p2Score )
        {
            p1--;
            lcd.setCursor(kockicaCounter,1);
            lcd.print("<-WIN");
        }
        else if ( p1Score == p2Score )
        {
            if( which_player == 2 )
            {
                p1--;
                lcd.setCursor(kockicaCounter,1);
                lcd.print("<-WIN");
            }
            else
            {
                p2--;
                lcd.setCursor(kockicaCounter,0);
                lcd.print("<-WIN");
            }
        }

        

        lcd.setCursor(13,0);lcd.print(p1);
        lcd.setCursor(14,0);lcd.print("x");
        lcd.setCursor(15,0);lcd.write(byte(0));
        
        lcd.setCursor(13,1);lcd.print(p2);
        lcd.setCursor(14,1);lcd.print("x");
        lcd.setCursor(15,1);lcd.write(byte(0));
        delay(1000);

        if(p1 == 0 || p2 == 0 )
        {
            currentState = WINNER;
            lcd.clear();
            break;
        }
        else if( which_player == 2 )
        {
            flag = 1;
            currentState = BACANJE_KOCKICA;
            y = 1;
            setScreen();
            break;
        }
        else
        {
            flag = 0;
            currentState = BACANJE_KOCKICA;
            y = 0;
            setScreen();
            break;
        }
        currentState = BACANJE_KOCKICA;
        break;

    case WINNER:
        
        lcd.setCursor(1,0);

        if(p2 == 0)
            lcd.print("Player1 is the");
        else
            lcd.print("Player2 is the");

        lcd.setCursor(5,1);
        lcd.print("WINNER");
        

        if(readButton() == SELECT)
        {
            currentState = RESET_GAME;
            break;
        }
        break;

    case RESET_GAME:
        p1 = 5;
        p2 = 5;
        kockicaCounter = 0;
        currentState = POCETNO_STANJE;
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

void sort(int arr[], int n)  //implementacija BubbleSort-a
{
    for ( int i = 0 ; i < n ; i++ )
    {
        for ( int j = 0 ; j < n - i - 1 ; j++ )
        {
            if ( arr[j] > arr[i] + 1 )
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int pronadjiPara(int arr[], int n)
{
    int visited[n];
    int ukupnoParova = 0;

    for ( int i = 0 ; i < n ; i++ )
    {
        visited[i] = 0;
    }

    for( int i = 0 ; i < n ; i++ )
    {
        if(visited[i] == 1)
        {
            continue;
        }

        int count = 0;
        
        for ( int j = 0 ; j < n ; j++ )
        {
            if( arr[i] == arr[j] )
            {
                count++;
                visited[j] = 1;
            }
            
        }

        ukupnoParova += count / 2;
    }

    return ukupnoParova;
    
}

void setScreen()
{
    
    for ( int j = 0 ; j < 2 ; j++ )
    {
        for(int i = 0 ; i < 12 ; i++)
        {
            lcd.setCursor(i,j);lcd.print(" ");
        }
    }
    x = 0;
}