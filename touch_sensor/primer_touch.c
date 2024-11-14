#define TOUCH_PIN 4 

bool touch; 

void setup()  
{ 
    Serial.begin(9600); 
    pinMode(TOUCH_PIN, INPUT); 
    touch = 0; 
} 

void loop()  
{ 
    touch = digitalRead(TOUCH_PIN); 
    Serial.println(touch); 
} 
