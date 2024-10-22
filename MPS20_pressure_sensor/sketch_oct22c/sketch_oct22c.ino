#include "HX711.h"

// Pin connections for the HX711 to Arduino
const int LOADCELL_DOUT_PIN_1 = 3;  // DOUT pin for Sensor 1 (Static Pressure)
const int LOADCELL_SCK_PIN_1 = 2;   // SCK pin for Sensor 1
const int LOADCELL_DOUT_PIN_2 = 4;  // DOUT pin for Sensor 2 (Dynamic Pressure)
const int LOADCELL_SCK_PIN_2 = 5;   // SCK pin for Sensor 2

HX711 scale1; // First sensor (Static Pressure)
HX711 scale2; // Second sensor (Dynamic Pressure)

// Constants
const float MAX_PRESSURE = 40.0;   // Max pressure for MPS20N0040D in kilopascals (40 kPa)
const long ADC_MAX = 8388607;      // Max value for 24-bit ADC
const float NORMAL_AIR_PRESSURE = 101.325; // Normal atmospheric pressure in kPa
const float AIR_DENSITY = 1.225;   // Air density at sea level in kg/m³

void setup() {
  Serial.begin(9600);
  
  // Initialize the first sensor
  scale1.begin(LOADCELL_DOUT_PIN_1, LOADCELL_SCK_PIN_1);
  // Initialize the second sensor
  scale2.begin(LOADCELL_DOUT_PIN_2, LOADCELL_SCK_PIN_2);

  // Wait for sensors to stabilize and zero them
  Serial.println("Calibrating sensors...");
  delay(1000);
  
  // Get zero offsets for both sensors
  long zero_offset_1 = scale1.read_average(20);  // Get zero offset for Sensor 1
  long zero_offset_2 = scale2.read_average(20);  // Get zero offset for Sensor 2
  
  // Set the zero points
  scale1.set_offset(zero_offset_1);
  scale2.set_offset(zero_offset_2);

  Serial.println("Ready to read pressure from both sensors...");
}

void loop() {
  if (scale1.is_ready() && scale2.is_ready()) {
    // Read raw values from both sensors
    long raw_reading_1 = scale1.read();  // Static Pressure
    long raw_reading_2 = scale2.read();  // Dynamic Pressure
    
    // Convert to pressure in kPa for both sensors
    float pressure_kPa_1 = (float)(raw_reading_1) / ADC_MAX * MAX_PRESSURE;  // Static Pressure
    float pressure_kPa_2 = (float)(raw_reading_2) / ADC_MAX * MAX_PRESSURE;  // Dynamic Pressure

    // Calculate the difference from normal air pressure for both sensors
    float pressure_difference_1 = pressure_kPa_1 - NORMAL_AIR_PRESSURE;
    float pressure_difference_2 = pressure_kPa_2 - NORMAL_AIR_PRESSURE;

    // Calculate airspeed using Bernoulli's equation
    float dynamic_pressure = pressure_kPa_2;  // Dynamic pressure from the second sensor
    float airspeed = sqrt((2 * dynamic_pressure * 1000) / AIR_DENSITY);  // Convert kPa to Pa

    // Print readings for Sensor 1
    Serial.print("Sensor 1 Pressure (kPa): ");
    Serial.println(pressure_kPa_1);
    Serial.print("Sensor 1 Difference from normal air pressure (kPa): ");
    Serial.println(pressure_difference_1);

    // Print readings for Sensor 2
    Serial.print("Sensor 2 Pressure (kPa): ");
    Serial.println(pressure_kPa_2);
    Serial.print("Sensor 2 Difference from normal air pressure (kPa): ");
    Serial.println(pressure_difference_2);

    // Print airspeed
    Serial.print("Airspeed (m/s): ");
    Serial.println(airspeed);  // Airspeed in meters per second
  } else {
    Serial.println("One or both sensors are not ready.");
  }

  delay(1000);  // Wait 1 second between readings
}
