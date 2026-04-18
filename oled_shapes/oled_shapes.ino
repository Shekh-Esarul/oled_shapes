#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

// I2C pins: SCK=GP3, SDA=GP5
#define I2C_SCL 3
#define I2C_SDA 5

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int frame = 0;

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;); // hang if OLED not found
  }

  display.clearDisplay();
  display.display();
  delay(500);
}

void loop() {
  display.clearDisplay();

  int t = frame % 128;

  // === 1. Bouncing Rectangle ===
  int rx = t;
  int ry = (t % 32);
  display.drawRect(rx % 100, ry, 28, 18, SSD1306_WHITE);

  // === 2. Pulsing Circle (center) ===
  int radius = 5 + (frame % 12);
  display.drawCircle(64, 32, radius, SSD1306_WHITE);

  // === 3. Rotating Triangle (approximated) ===
  float angle = (frame * 0.08);
  int cx = 100, cy = 45, r = 12;
  int x0 = cx + r * cos(angle);
  int y0 = cy + r * sin(angle);
  int x1 = cx + r * cos(angle + 2.094);
  int y1 = cy + r * sin(angle + 2.094);
  int x2 = cx + r * cos(angle + 4.188);
  int y2 = cy + r * sin(angle + 4.188);
  display.drawTriangle(x0, y0, x1, y1, x2, y2, SSD1306_WHITE);

  // === 4. Moving Line ===
  int lx = (frame * 2) % 128;
  display.drawLine(lx, 0, 128 - lx, 63, SSD1306_WHITE);

  // === 5. Corner Dots (blinking) ===
  if (frame % 10 < 5) {
    display.drawPixel(0, 0, SSD1306_WHITE);
    display.drawPixel(127, 0, SSD1306_WHITE);
    display.drawPixel(0, 63, SSD1306_WHITE);
    display.drawPixel(127, 63, SSD1306_WHITE);
  }

  display.display();
  frame++;
  delay(30); // ~33fps
}
