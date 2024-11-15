/*ZADATAK 5. - implementacija funkcionalnosti stoperice*/
#include <Servo.h>

#define TOUCH_PIN 4
#define SERVO_PIN 9

Servo servo;
int pos,stanje;
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
    case 1: //inicijalno stanje - stoperica je zaustavljena

        Serial.println("STOP - 00:00:00");

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
                break;
            }

            else // RESET KOMANDA
            {
                stanje = 3;
                break;
            }

            flag = 0;
        }
        break;
    
    case 2: //POCETAK RADA STOPERICE
        break;

    case 3: //RESET I POVRATAK U INICIJALNO STANJE
        while( pos > 0 )
            servo.write(pos);
            delay(20);
            pos--;
        }

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