/*
  Device To Talk to Alexa
  2018 Paul Badger
  Teensy 3.2 based piece

  FMI:
  The audio board uses the following pins.
  6 - MEMCS 7 - MOSI 9 - BCLK 10 - SDCS 11 - MCLK 12 - MISO 13 - RX
  14 - SCLK 15 - VOL 18 - SDA 19 - SCL 22 - TX 23 - LRCLK
*/

#include "pinsANDglobals.h"

void setup() {

  Serial.begin(9600);
  while (!Serial && (millis() <= 3000));
  delay(4000);

  // Maximum memory usage was reported as 4
  // Proc = 9 (9),  Mem = 4 (4)
  AudioMemory(20); // just  a guess for max

  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.volume(0.50); // volume doesn't affect peak readings
  mixer1.gain( 0, 0.5);
  mixer2.gain( 0, 0.5);

  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);

  Serial.println("setup done");
  AudioProcessorUsageMaxReset();
  AudioMemoryUsageMaxReset();
  Serial.print("Proc = ");
  Serial.print(AudioProcessorUsage());
  Serial.print(" (");
  Serial.print(AudioProcessorUsageMax());
  Serial.print("),  Mem = ");
  Serial.print(AudioMemoryUsage());
  Serial.print("MaxMem = ");
  Serial.print(AudioMemoryUsageMax());
  Serial.println();

  // uses audio shield - SD card for samples
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      myDelay(500);
    }
  }

  lastRead = millis();
  readSensors();
  setVol(gVolume);
}

unsigned long last_time = millis();
/*************** loop ********************/
void loop()
{
  readSensors();

  //if (noMotionTime_Secs < 30) {
  if (!playSD.isPlaying()) {
  	deals();
 //	playSD.play("hello.wav");
   // (*functionArray[2])();
   
  }
  Serial.println("repeat");
  delay(2000);
  //  goatFacts();
}
