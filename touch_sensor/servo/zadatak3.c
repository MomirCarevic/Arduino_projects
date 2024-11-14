/*ZADATAK 3. - Tri funkcionalnosti*/

#include <Servo.h>

#define TOUCH_PIN 4
#define SERVO_PIN 9

Servo servo;
int pos,stanje;
bool touch_old, touch_new;

int press_button();

void setup()
{
    Serial.begin(9600);
    pinMode(TOUCH_PIN,INPUT);

    servo.attach(SERVO_PIN);
    pos = 0;
    stanje = 3;

    servo.write(pos);
}

void loop()
{
  
    switch (stanje)
    {
    case 1:
        //LEVO
        while( pos < 180 )
        {
            servo.write(pos);
            delay(20);
            pos++;
          
            if(press_button())
            {
                stanje = 2;
              	break;
            }
        }
        stanje = 3;
      	break;

    case 2:
        //DESNO
      	while( pos > 0 )
        {
            servo.write(pos);
            delay(20);
            pos--;

            if(press_button())
            {
                stanje = 4;
                break;
            }
        }
        stanje = 4;
      	break;
    
    case 3:
        //stop pa desno
        delay(100);//sacekamo da se smiri debounce
      	if(press_button())
            {
                stanje = 2;
                break;
            }
      	break;
      
      case 4:
      //stop pa levo
        delay(100); //sacekamo da se smiri debounce
      	if(press_button())
            {
                stanje = 1;
                break;
            }
      	break;
    }
  
  	
}

int press_button()
{
    touch_new = digitalRead(TOUCH_PIN);
        
    if ( touch_new != touch_old )
    {
        if ( touch_new )
        {
            return 1;
        }

        touch_old = touch_new;
    }

    return 0;
}