/*
 * This Arduino Nano code was developed by newbiely.com
 *
 * This Arduino Nano code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/arduino-nano/arduino-nano-rotary-encoder
 */

#include <ezButton.h>  // The library to use for SW pin

#define CLK_PIN 5
#define DT_PIN 4
#define SW_PIN 3

#define DIRECTION_CW 0   // clockwise direction
#define DIRECTION_CCW 1  // anticlockwise direction

int counter = 0;
int direction = DIRECTION_CW;
int CLK_state;
int prev_CLK_state;

ezButton button(SW_PIN);

void setup() {
  Serial.begin(9600);


  // Configure encoder pins as inputs
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  button.setDebounceTime(50);  // set debounce time to 50 milliseconds

  // read the initial state of the rotary encoder's CLK pin
  prev_CLK_state = digitalRead(CLK_PIN);
}

void loop() {
  button.loop();  // MUST call the loop() function first

  // read the current state of the rotary encoder's CLK pin
  CLK_state = digitalRead(CLK_PIN);

  // If the state of CLK is changed, then pulse occurred
  // React to only the rising edge (from LOW to HIGH) to avoid double count
  if (CLK_state != prev_CLK_state && CLK_state == HIGH) {
    // if the DT state is HIGH
    // The encoder is rotating in anticlockwise direction => decrease the counter
    if (digitalRead(DT_PIN) == HIGH) {
      counter--;
      direction = DIRECTION_CCW;
    } else {
      // The encoder is rotating in clockwise direction => increase the counter
      counter++;
      direction = DIRECTION_CW;
    }

    Serial.print("Twisted direction: ");
    if (direction == DIRECTION_CW)
      Serial.print("CLOCKWISE");
    else
      Serial.print("ANTICLOCKWISE");

    Serial.print(" - counter: ");
    Serial.println(counter);
  }

  // save last CLK state
  prev_CLK_state = CLK_state;

  if (button.isPressed()) {
    Serial.println("The button is pressed");
  }
}
