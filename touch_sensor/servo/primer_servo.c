#include <Servo.h> 

#define SERVO_PIN 9 

Servo servo; 
int pos; 

void setup() 
{ 
    servo.attach(SERVO_PIN); 
    pos = 0; 
    servo.write(pos); 
} 

void loop() 
{ 
    while(pos < 180) 
    { 
        servo.write(pos); 
        delay(20); 
        pos++; 
    } 
    
    while(pos > 0) 
    { 
        servo.write(pos); 
        delay(20); 
        pos--; 
    } 
}