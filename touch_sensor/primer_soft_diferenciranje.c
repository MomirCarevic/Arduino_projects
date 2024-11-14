#define TOUCH_PIN 4 

bool touch_old, touch_new; 
unsigned int counter; 

void setup()  
{
    Serial.begin(9600); 
    pinMode(TOUCH_PIN, INPUT); 
    
    touch_old = 0; 
    touch_new = 0; 
    counter = 0; 
    
    counterPrint(); 
} 
 
void loop()  
{ 
    touch_new = digitalRead(TOUCH_PIN); 
    
    if (touch_new != touch_old) 
    { 
        if (touch_new) 
        { 
            counter++; 
            counterPrint(); 
        } 
    touch_old = touch_new; 
    } 
} 
 
void counterPrint() 
{ 
    Serial.print("Brojac: "); 
    Serial.println(counter); 
} 