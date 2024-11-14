#define DESIRED_INTERVAL 5000 
 
unsigned long time_old, time_new; 
 
void setup() 
{ 
    Serial.begin(9600);
     
    Serial.println("Program je zapoceo sa radom!"); 
    time_old = millis(); 
} 

void loop() 
{ 
time_new = millis(); 
    if (time_new - time_old >= DESIRED_INTERVAL) 
    { 
        Serial.println("Proslo je 5 sekundi!"); 
        time_old = time_new; 
    } 
} 
