#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <movingAvg.h>

uint16_t adc0;
Adafruit_ADS1115 ads;

int conssecutivecount = 0;

volatile bool flaginitADC = false;

// #define EMG_Visualizer

void setup()
{
  Serial.begin(115200);

  if (!ads.begin())
  {
    // Serial.println("Failed to initialize ADS.");
    while (1)
      ;
  }
}

void loop()
{

  uint16_t currentValue = ads.readADC_SingleEnded(0);

#ifdef EMG_Visualizer

  Serial.print(">AD0:");
  Serial.println(currentValue);

#else

  if (currentValue > 250)
  {

    flaginitADC = true;
  }

  if (flaginitADC)
  {

    Serial.write((uint8_t *)&currentValue, sizeof(currentValue));

    if (currentValue < 200)
    {
      conssecutivecount++;

      if (conssecutivecount >= 20)
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
#endif
}
