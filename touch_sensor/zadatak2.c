/*ZADATAK 2. - PROVERA REFLEKSA KORISNIKA*/

#define TOUCH_PIN 4
#define LED_PIN 13
#define INTERVAL 1000

//touch oznacava da je dugme pritisnuto, a flag sluzi da
//se samo jednom udje u if petlju, tako da se belezi samo 
//prvo vreme pritiska dugmeta
bool touch_new, touch_old, flag;
unsigned long time_new, time_old, time_press, counter;
unsigned short reaction_time;
float average_time;


void setup()
{
        Serial.begin(9600);
        
        pinMode(TOUCH_PIN,INPUT);
        pinMode(LED_PIN,OUTPUT);

        touch_old = 0;
        touch_new = 0;
        counter = 0;
  		flag = 0;
        reaction_time = 0;

        time_old = millis();
  		Serial.println("Program je zapoceo sa radom ..... ");
}

void loop()
{
        time_new = millis();

        touch_new = digitalRead(TOUCH_PIN);
        if(digitalRead(LED_PIN) == HIGH)
        {
            if ( touch_new != touch_old )
            {
                if ( touch_new && flag == 0)
                {
                    time_press = time_new - time_old;
                    
                    //postavljanjem flega na 1 vise ne mozemo
                    //da udjemo u ovu petlju, te se pritisak 
                    //dugmeta registruje samo jednom
                    flag = 1;

                }
              	
            }
            if(time_press == 0)time_press = INTERVAL;   
        }
        
  
  		if ( time_new - time_old >= INTERVAL)
        {
            digitalWrite(LED_PIN,!digitalRead(LED_PIN));

            time_old = time_new;
            reaction_time += time_press;
            counter++;

          	time_press = 0;
          	flag = 0;

            if( counter == 20 )
            {
                Serial.print("Prosecno vreme reakcije je ");
                Serial.println(average_time = reaction_time/10);
                Serial.print("ms");

                counter = 0;
                reaction_time = 0;

            }
        }
}

