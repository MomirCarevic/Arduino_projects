#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int taster_novo, taster_staro;
char rec[7];
int duzina, i;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
 
  //taster_novo = 0;
  //taster_staro = 0;

  Serial.println("Unesite rec: ");
}

void loop()
{
  while(Serial.available() == 0);
    delay(100);

  duzina = Serial.available();
  Serial.readBytes(rec, duzina);
  rec[duzina] = 0;

  lcd.print(rec);

  if( duzina > 8)
  {
    Serial.println("Rec moze imati maksimalnu duzinu 8 slova!");
  }

  taster_novo = ocitaj_taster();
    Serial.print("ovde sam pre ifa");

  if(taster_novo != taster_staro)
  {
    Serial.print("ovde sam");
    switch(taster_novo)
    {
      case 1: //SELECT
        break;
      case 2: //LEFT
        break;
      case 3: //UP
      Serial.print(rec);
        for(i = 0; i < duzina; i++)
        {
          if(rec[i] >= 'a' && rec[i] <= 'z')
          {
            rec[i] -= 32;
          }
        }
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(rec);
        break;
      case 4: //DOWN
        for(i = 0; i < duzina; i++)
        {
          if(rec[i] >= 'A' && rec[i] <= 'Z')
          {
            rec[i] += 32;
          }
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(rec);
        break;
      case 5: //RIGHT
        break;
      default:
        break;
    }
  }
  taster_staro = taster_novo;
}

byte ocitaj_taster()
{
int tmp = analogRead(0); //stanje tastera se ocitava preko
//analognog ulaza 0
if (tmp > 635 && tmp < 645) //SELECT
return 1;
if (tmp > 405 && tmp < 415) //LEFT
return 2;
if (tmp > 95 && tmp < 105) //UP
return 3;
if (tmp > 252 && tmp < 262) //DOWN
return 4;
if (tmp < 5) //RIGHT
return 5;
return 0; //nije pritisnut nijedan od tastera
}
