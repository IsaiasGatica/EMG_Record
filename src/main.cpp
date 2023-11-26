#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <movingAvg.h>

uint16_t adc0;
Adafruit_ADS1115 ads;

int conssecutivecount = 0;

volatile bool flaginitADC = false;

void setup()
{
  Serial.begin(115200);

  if (!ads.begin())
  {
    // Serial.println("Failed to initialize ADS.");
    while (1)
      ;
  }
  // Serial.println("Initialize ADS.");
}

void loop()
{
  uint16_t currentValue = ads.readADC_SingleEnded(0);

  if (currentValue > 250)
  {

    flaginitADC = true;
  }

  if (flaginitADC)
  {

    Serial.write((uint8_t *)&currentValue, sizeof(currentValue));
    // Serial.println(currentValue);

    if (currentValue < 250)
    {
      conssecutivecount++;

      if (conssecutivecount >= 4)
      {
        flaginitADC = false;
        Serial.write(0x04);
        conssecutivecount = 0;
      }
    }
    else
    {
      conssecutivecount = 0;
    }
  }
}
