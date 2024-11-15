/*ZADATAK 5. - implementacija funkcionalnosti stoperice*/
#include <Servo.h>

#define TOUCH_PIN 4
#define SERVO_PIN 9
#define INTERVAL 1000

Servo servo;
int pos,stanje, ugao, sat, minut, sekunda;
bool touch_old, touch_new, flag;
unsigned long press_startTime = 0, press_duration = 0,pocetak_sekunde,kraj_sekunde;

int press_button();
void time();

void setup()
{
    Serial.begin(9600);
    pinMode(TOUCH_PIN,INPUT);

    servo.attach(SERVO_PIN);
    pos = 0;
    ugao = 0;

    stanje = 1;
    pocetak_sekunde  = millis();

    servo.write(pos);
}

void loop()
{
    switch (stanje)
    {
    case 1: //inicijalno stanje - stoperica je zaustavljena

        kraj_sekunde = millis();

        if( kraj_sekunde - pocetak_sekunde >= INTERVAL )
        {
            Serial.println("STOP - 00:00:00");
            pocetak_sekunde = kraj_sekunde;
        }

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
                Serial.println("00:00:00");
                pocetak_sekunde = millis();
                break;
            }

            else // RESET KOMANDA
            {
                stanje = 3;
                break;
            }

        }
        break;
    
    case 2: //POCETAK RADA STOPERICE

        kraj_sekunde = millis();

        if(press_button() && flag == 0 )
        {
            press_startTime = millis();
            flag = 1;
        }

        else if ( digitalRead(TOUCH_PIN) == LOW && flag == 1)
        {
            press_duration = millis() - press_startTime;

            if( press_duration > 500 )
            {
                stanje = 3;
                break;
            }
        }
        
        if( kraj_sekunde-pocetak_sekunde >= INTERVAL && pos < 180)
        {
            while ( pos < 180 && ugao < 3 )
            {
                servo.write(pos);
                delay(20);
                pos ++;
                ugao ++;
            }
            time();
            pocetak_sekunde = kraj_sekunde-20;
            ugao = 0;
        }
        else if ( pos == 180 )
        {
            while( pos > 0 )
            {
                servo.write(pos);
                pos --;
            }
            
        }


        break;

    case 3: //RESET I POVRATAK U INICIJALNO STANJE
        while( pos > 0 )
        {
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

void time() //ispis vremena 
{
    sekunda++;

    if( sekunda > 59 )
    {
        minut ++;
        sekunda = 0;
    }
    if( minut > 59 )
    {
        sat++;
        minut = 0;
    }

    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", sat, minut, sekunda);
    Serial.println(buffer);
}