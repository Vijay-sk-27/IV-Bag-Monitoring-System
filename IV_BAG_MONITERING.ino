#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HX711.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

HX711 scale;

#define LOADCELL_DOUT_PIN 4
#define LOADCELL_SCK_PIN  5
#define RELAY_PIN 18
#define BUZZER_PIN 19

float calibration_factor = -7050;   
float empty_weight = 10.0;          

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);   
  digitalWrite(BUZZER_PIN, LOW);

  
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }
  display.clearDisplay();

 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare();   
  displayText("IV BAG MONITOR", "Initializing...");
  delay(2000);
}

void loop() {
  float weight = scale.get_units(10);

  Serial.print("Weight: ");
  Serial.println(weight);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("IV Bag Monitoring");
  display.println("----------------");
  display.print("Weight: ");
  display.print(weight);
  display.println(" g");

  if (weight <= empty_weight) {
    digitalWrite(RELAY_PIN, LOW);     
    digitalWrite(BUZZER_PIN, HIGH);  

    display.setCursor(0, 45);
    display.println("STATUS: EMPTY");
  } else {
    digitalWrite(RELAY_PIN, HIGH);    
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(0, 45);
    display.println("STATUS: NORMAL");
  }

  display.display();
  delay(1000);
}

void displayText(String line1, String line2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println(line1);
  display.setCursor(0, 30);
  display.println(line2);
  display.display();
}
