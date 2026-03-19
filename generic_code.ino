#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <VL53L1X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
VL53L1X sensor;

float distance_cm = 0;


void setup()
{
  Serial.begin(115200);
  Wire.begin(19,20);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
  {
    Serial.println("OLED fail");
    while(1);
  }

  sensor.setTimeout(500);

  if(!sensor.init())
  {
    Serial.println("VL53L1X fail");
    while(1);
  }

  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(100000);
  sensor.startContinuous(50);
}

void loop(){
  int distance_mm = sensor.read();

if (!sensor.timeoutOccurred()){
    distance_cm = distance_mm / 10.0;
}

  Serial.print("Distance: ");
  Serial.println(distance_cm);

  //drawScreen_1();

  delay(100);
}
