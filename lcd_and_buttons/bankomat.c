#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int broj_cifara, i, stanje = 0, k = 1;
int taster_novo = 0, taster_staro = 0;
int brojac = 0, x, flag = 0;

unsigned long min, max, pin_rand = 0;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  randomSeed(analogRead(1));

  lcd.setCursor(0, 0);
  lcd.cursor();
}

void loop() 
{
    switch (stanje) 
    {
        case 0:
            Serial.println("Unesite broj cifara PIN koda (3-6): ");

            while (Serial.available() == 0);
                delay(100);

            broj_cifara = Serial.parseInt();
            Serial.println(broj_cifara);

            stanje = 1;
        break;

        case 1:
            if (broj_cifara >= 3 && broj_cifara < 7) 
            {
                Serial.println("Generisan PIN kod: ");

                min = pow ( 10, broj_cifara - 1 );
                max = pow ( 10, broj_cifara) - 1 ;
                pin_rand = random( min , max + 1 );

                Serial.println(pin_rand);
            } 
            else 
            {
                Serial.println("Neispravan unos!");
            }

            /*
            for ( int i = broj_cifara - 1 ; i >= 0 ; i++ )
            {
                pin[i] = pin_rand%10;  
                pin_rand /= 10; 
            }
            */

            stanje = 2;
        break;

        case 2:

        if (flag == 0) 
        {
            for ( x = 0 ; x < broj_cifara ; x++ ) 
            {
                lcd.setCursor(x, 0);
                lcd.print(brojac);
            }

            flag = 1;
            x = 0;
            lcd.setCursor(x, 0);
        }

        taster_novo = ocitaj_taster();

        if (taster_novo != taster_staro) 
        {
            switch (taster_novo) 
            {
            case 1:  //SELECT
                break;
            case 2:  //LEFT
                if (x != 0)
                    x--;
                lcd.setCursor(x, 0);
                break;
            case 3:  //UP
                brojac++;
                
                lcd.print(brojac);
                lcd.setCursor(x, 0);
                
                /*
                lcd_niz[i]   =  { 0 , 0 , 0 , 0 , 0 , 0 }

                lcd_pin[x]++;
                lcd.print(lcd_pin[x]);
                
                */

                break;
            case 4:  //DOWN
                brojac--;
                //lcd.setCursor(x, 0);
                lcd.print(brojac);
                lcd.setCursor(x, 0);
                break;
            case 5:  //RIGHT
                if (x != broj_cifara - 1 )
                    x++;

                lcd.setCursor(x, 0);
                break;
            default:
                break;
            }
            taster_staro = taster_novo;
        }
        break;
    }
}

byte ocitaj_taster() {
    int tmp = analogRead(0);  //stanje tastera se ocitava preko
    //analognog ulaza 0
    if (tmp > 635 && tmp < 645)  //SELECT
        return 1;
    if (tmp > 405 && tmp < 415)  //LEFT
        return 2;
    if (tmp > 95 && tmp < 105)  //UP
        return 3;
    if (tmp > 252 && tmp < 262)  //DOWN
        return 4;
    if (tmp < 5)  //RIGHT
        return 5;
    return 0;  //nije pritisnut nijedan od tastera
}