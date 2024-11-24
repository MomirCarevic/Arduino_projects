// Simple test application that displays pressed button on display
// every button has its own index that are defined whith macros
// you can controll backlight (brightness) of LCD with pwm on digital pin 10
// eg. pinMode(10,OUTPUT); analogWrite(10,255); // range 0-255
// contrast is set trough blue potentiometer
#include <LiquidCrystal.h>
#define SELECT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define RIGHT 5

#define BIRANJE_BROJA_KOCKICA 1
#define BACANJE_KOCKICA 2

// Digital pins used for display
// 8-RS, 9-E, 4-DB4, 5-DB5, 6-DB6, 7-DB7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
void setup() {
 // initialize display
 lcd.begin(16, 2);

}
void loop() 
{
    switch ()
    {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }


}

byte readButton()
{
 int tmp = analogRead(0); //read value of Analog input 0
 //depending on voltage, we can find out which switch was pressed
 if (tmp > 635 && tmp < 645) //SELECT
 	return SELECT;
 if (tmp > 405 && tmp < 415) //LEFT
 	return LEFT;
 if (tmp > 95 && tmp < 105) //UP
 	return UP;
 if (tmp > 252 && tmp < 262) //DOWN
 	return DOWN;
 if (tmp < 5) //RIGHT
 	return RIGHT;
 return 0; //NONE
}