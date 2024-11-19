/*ZADATAK 3. - Tri funkcionalnosti*/

#include <Servo.h>

#define TOUCH_PIN 4
#define SERVO_PIN 9

Servo servo;
int pos,stanje,stanje_staro;
bool touch_old, touch_new,flag;
int interval;

int press_button();

void setup()
{
    Serial.begin(9600);
    pinMode(TOUCH_PIN,INPUT);

    servo.attach(SERVO_PIN);
    pos = 0;
  	flag = 0;
  	stanje_staro = 2;
  	stanje = 3;
    interval = millis();

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
            //Serial.println("OVDE SAM 1");
            servo.write(pos);
            delay(20);
            pos++;
          
            if(press_button() && flag == 1)
            {
                stanje_staro = stanje;
              	stanje = 4;
              	flag = 0;
                interval = millis();
              	break;
            }
          	flag = 1;
        }
        interval = millis();
        stanje = 4;
      	break;

    case 2:
        //DESNO
      	while( pos > 0 )
        {
            //Serial.println("OVDE SAM 2");
            servo.write(pos);
            delay(20);
            pos--;

            if(press_button() && flag == 1 )
            {	
              	stanje_staro = stanje;
                stanje = 3;
              	flag = 0;
                interval = millis();
                break;
            }
          	flag = 1;
        }
        interval = millis();
        stanje = 3;
      	break;
    
     case 3:
        //Serial.println("OVDE SAM 3");
      	if(press_button() && millis()-interval > 100 )
        {

        	if( stanje_staro == 2 )
            {
                stanje = 1;
                flag = 0;
                delay(100);
                break;
            }
        }
        break;

    case 4:
        //Serial.println("OVDE SAM 4");
        
        if(press_button() && millis()-interval > 100 )
        {

        	if( stanje_staro == 1 )
            {
                stanje = 2;
                flag = 0;
                delay(100);
                break;
            }
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
