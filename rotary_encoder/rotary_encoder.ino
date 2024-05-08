#include <ezButton.h>

#define CLK_PIN 2
#define DT_PIN 3
#define SW_PIN 4

#define DIRECTION_CW 0
#define DIRECTION_CCW 1

volatile int counter = 0;
volatile int direction = DIRECTION_CW;
volatile unsigned long last_time;           //for debouncing
int prev_counter;

ezButton button(SW_PIN);

void INTERRUPT_handler(){
    if((millis()-last_time)<50)
        return;
    if(digitalRead(DT_PIN) == HIGH)
    {
        counter--;
        direction = DIRECTION_CCW;
    }else{
        counter++;
        direction = DIRECTION_CW;
    }
    last_time = millis();
}

void setup()
{
    Serial.begin(9600);
    pinMode(CLK_PIN,INPUT);
    pinMode(DT_PIN, INPUT);
    button.setDebounceTime(50);
    attachInterrupt(digitalPinToInterrupt(CLK_PIN),INTERRUPT_handler,RISING);
}

void loop()
{
    button.loop();

    if(prev_counter != counter)
    {
        Serial.print("Twisted direction: ");
        if(direction == DIRECTION_CW)
            Serial.print("CLOCKWISE");
        else
            Serial.print("ANTICLOCKWISE");

        Serial.print("- counter: ");
        Serial.print(counter);
    }

    if(button.isPressed())
    {
        Serial.println("The button is pressed");
    }
}
