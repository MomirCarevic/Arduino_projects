/*ZADATAK 4. - KONTROLISANJE UGLA SERVO MOTORA POMOCU SENZORA DODIRA*/
#include <Servo.h>

#define TOUCH_PIN 4
#define SERVO_PIN 9

Servo servo;
int pos, ugao ,stanje;
bool touch_old, touch_new, flag;
unsigned long press_startTime = 0, press_duration = 0;

int press_button();

void setup()
{
    Serial.begin(9600);
    pinMode(TOUCH_PIN,INPUT);

    servo.attach(SERVO_PIN);
    pos = 0;
    ugao = 0;

    stanje = 1;

    servo.write(pos);
}

void loop()
{
    switch (stanje)
    {
    case 1:
        if(press_button() && flag == 0 )
        {
            press_startTime = millis();
            flag = 1;
        }

        else if ( digitalRead(TOUCH_PIN) == LOW && flag == 1)
        {
            press_duration = millis() - press_startTime;

            if( press_duration < 500 )
            {
                stanje = 2;
              	flag = 0;
                break;
            }

            else
            {
                stanje = 3;
              	flag = 0;
                break;
            }
        }

        break;
    
    case 2:
        //LEVO
        while( pos < 180 && ugao < 15)
        {
            servo.write(pos);
            delay(20);
            pos++;
            ugao ++;
        }
        ugao = 0;
        stanje = 1;
        break;

    case 3:
        //DESNO
        while( pos > 0 && ugao < 15)
        {
            servo.write(pos);
            delay(20);
            pos--;
            ugao ++;
        }
        ugao = 0;
        stanje = 1;
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