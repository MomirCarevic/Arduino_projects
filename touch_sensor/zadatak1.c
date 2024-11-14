/*ZADATAK 1. PROVERA BRZINE KORISNIKA */

#define TOUCH_PIN 4
#define INTERVAL 1000

bool touch_old, touch_new;
unsigned int brojac;
unsigned long time_old, time_new;

void setup()
{
        Serial.begin(9600);

        pinMode(TOUCH_PIN,INPUT);

        touch_old = 0;
        touch_new = 0;
        brojac = 0;

        time_old = millis();
  		Serial.println("Program je zapoceo sa radom ..... ");
}

void loop()
{
        time_new = millis();
  

        touch_new = digitalRead(TOUCH_PIN);
        
        if ( touch_new != touch_old )
        {
            if ( touch_new )
            {
                brojac ++;
            }

            touch_old = touch_new;

        }
  
  		if ( time_new - time_old >= INTERVAL)
        {
            Serial.print("Za 3 sekunde korisnik je napravio ");counterPrint();Serial.println(" dodira.");
            time_old = time_new;
          	brojac = 0;
        }
}

void counterPrint()
{
        Serial.print(brojac);
}
