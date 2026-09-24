#include <Arduino.h>
#include "config.h"
#include "motor_control.h"
#include "throttle_sensor.h"
#include "encoder.h"
 
void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("=== ESP32 ECU - Motor + Throttle + Encoder ===");
 
  initMotor();
  initThrottle();
  initEncoder();
}
 
void loop() {
  int throttlePercent = readThrottlePercent();
  setMotor(throttlePercent);   // mo phong gas tien ti le theo bien tro 
 
  updateSpeed();
 
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 200) {
    lastPrint = millis();
    Serial.print("Throttle: ");
    Serial.print(throttlePercent);
    Serial.print("%  |  RPM (truc ra): ");
    Serial.print(getRPM());
    Serial.print("  |  Chieu: ");
    Serial.println(getDirection() > 0 ? "TIEN" : "LUI");
  }
 
  delay(10);
}