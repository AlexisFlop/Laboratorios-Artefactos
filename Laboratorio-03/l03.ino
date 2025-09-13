

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define I2C_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int PIN_LM35 = A0;
const unsigned long msInterval = 1000;
unsigned long lastTemp = 0;

const float VREF = 5.0;
void setup()
{
    Serial.begin(9600);
    delay(100);
    initOled();
    initMessagge("Iniciando...");
    Serial.println(F("LM35 - Temperatura en C"));
}

void loop()
{
    unsigned long currentTemp = millis();

    if (currentTemp - lastTemp < msInterval)
        return;

    lastTemp = currentTemp;
    int incomingSignal = analogRead(PIN_LM35);
    float voltage = incomingSignal * (VREF / 1023.0);
    float toPrintTemp = voltage * 100.0;

    Serial.print(F("Temperatura: "));
    Serial.print(toPrintTemp, 2);
    Serial.println(F(" °C"));
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("LM35 - Lectura"));
    display.setTextSize(2);
    display.setCursor(0, 42);
    display.print(toPrintTemp, 1);
    display.print((char)247);
    display.print(F("C"));
    display.display();
}

void initOled()
{
    display.begin(I2C_ADDRESS, true);
    display.setContrast(255);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
}

void initMessagge(string msg)
{
    display.setCursor(0, 0);
    display.println(msg);
    display.display();
    delay(800);
}