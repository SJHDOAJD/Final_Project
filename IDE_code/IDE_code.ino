#include <Wire.h>
#include "Si115X.h"
Si115X si1151;
float VIS;
float IR;

void setup() {
  Serial.begin(115200);
  // Initialising sensor
  if (!si1151.Begin()) {
        Serial.println("Si1151 is not ready!");
        while (1) {
            delay(1000);
            Serial.print(".");
        };
    }
    else {
        Serial.println("Si1151 is ready!");
    }
  // set pin as output
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  // Initialise pin state to high
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
}

void loop() {
  // Start IR2 and collect data
  digitalWrite(8, LOW);
  collectAndPrintDuringInterval("IR2", 10000);  // collect data for 10 seconds
  digitalWrite(8, HIGH);  // close IR2
  
  // Start IR3 and collect data
  digitalWrite(9, LOW);
  collectAndPrintDuringInterval("IR3", 10000);  // collect data for 10 seconds
  digitalWrite(9, HIGH);  // close IR3
  
  // Start IR4
  digitalWrite(10, LOW);
  collectAndPrintDuringInterval("IR4", 10000);  // collect data for 10 seconds
  digitalWrite(10, HIGH);  // close IR4
  
  // Start IR5
  digitalWrite(11, LOW);
  collectAndPrintDuringInterval("IR5", 10000);  // collect data for 10 seconds
  digitalWrite(11, HIGH);  // close IR5
  
  // Start IR6
  digitalWrite(12, LOW);
  collectAndPrintDuringInterval("IR6", 10000);  // collect data for 10 seconds
  digitalWrite(12, HIGH);  // close IR6
  
  // wait 10s after each loop
  delay(10000);
}

void collectAndPrintDuringInterval(String ledName, int durationMs) {
  int intervalMs = 100;  // interval of 0.1 second (100 ms)
  int iterations = durationMs / intervalMs;  // calculate number of iterations
  
  for (int i = 0; i < iterations; i++) {
    collectAndPrintData(ledName);  // collect and print data
    delay(intervalMs);  // wait for the next interval
  }
}

void collectAndPrintData(String ledName) {
  int VIS = si1151.ReadVisible();
  int IR = si1151.ReadIR();
  
  Serial.print(ledName);
  Serial.print("- VIS:");
  Serial.print(VIS);
  Serial.print(", IR:");
  Serial.println(IR);
}