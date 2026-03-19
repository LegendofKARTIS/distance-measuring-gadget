#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <VL53L1X.h>
#include <Fonts/FreeSans18pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
VL53L1X sensor;

float distance_cm = 0;

static const unsigned char PROGMEM image_menu_settings_gear_bits[] = {
0x03,0xc0,0x12,0x48,0x2c,0x34,0x40,0x02,
0x23,0xc4,0x24,0x24,0xc8,0x13,0x88,0x11,
0x88,0x11,0xc8,0x13,0x24,0x24,0x23,0xc4,
0x40,0x02,0x2c,0x34,0x12,0x48,0x03,0xc0
};



void drawScreen_1() {

  display.clearDisplay();

  display.drawRect(0,0,127,64,1);

  display.setTextColor(1);
  display.setTextSize(2);
  display.setCursor(99,32);
  display.print("cm");

  display.setFont(&FreeSans18pt7b);
  display.setTextSize(1);
  display.setCursor(10,46);
  display.print(distance_cm,1);

  display.setFont();
  display.setCursor(5,6);
  display.print("Distance:");

  display.drawBitmap(106,5,image_menu_settings_gear_bits,16,16,1);

  display.display();
}

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

void loop()
{
  int distance_mm = sensor.read();

if (!sensor.timeoutOccurred())
{
    distance_cm = distance_mm / 10.0;
}

  Serial.print("Distance: ");
  Serial.println(distance_cm);

  drawScreen_1();

  delay(100);
}