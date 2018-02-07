/*
  Device To Talk to Alexa
  2018 Paul Badger
  Teensy 3.2 based piece

  FMI:
  The audio board uses the following pins.
  6 - MEMCS 7 - MOSI 9 - BCLK 10 - SDCS 11 - MCLK 12 - MISO 13 - RX
  14 - SCLK 15 - VOL 18 - SDA 19 - SCL 22 - TX 23 - LRCLK

*/

#include <Audio.h>
// Use these with the audio adaptor board
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

#define PIR1 2  // left from back view
#define PIR2 1
#define WalkAwayTimeout_Secs 15

const float RESET_AMOUNT = .001; // arbitrary units
// governs how fast the peak detector returns to zero
// smaller numbers are slower
const float SILENCE_THRESHOLD = 0.16; // threshold for audio detection

const float LOW_THRESHOLD = 0.12; // threshold for audio detection


#define TIMER_DEBUG

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "FunctionDefs.h"
#include "UtilityFunctions.h"

// GUItool: begin automatically generated code
AudioInputI2S            audioInput;           //xy=72.16667175292969,165
AudioPlaySdWav           playSD;     //xy=81.16667175292969,208.16668701171875
AudioAnalyzePeak         peak1;          //xy=270.1666717529297,124.99999237060547
AudioMixer4              mixer1;         //xy=436.16668701171875,180.99998474121094
AudioMixer4              mixer2;         //xy=436.16668701171875,253.99998474121094
AudioOutputI2S           i2s1;           //xy=625.1666870117188,208.99998474121094
AudioConnection          patchCord1(audioInput, 0, peak1, 0);
AudioConnection          patchCord2(playSD, 0, mixer1, 0);
AudioConnection          patchCord3(playSD, 1, mixer2, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 0);
AudioConnection          patchCord5(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     audioShield;     //xy=623.1666870117188,261
// GUItool: end automatically generated code


int pir1, pir2; // pir variables for motion sensors
float  temp,  peak = 0; // audio volume
unsigned int lastMotionTime, noMotionTime_Secs, lastSoundTime,  lastRead;
float silenceTime_Secs;

char* musicArr[] = {"tempttns.wav","supremes.wav","johnCage.wav","raviShkr.wav","sunRa.wav",
"PubEnemy.wav","artEnsCh.wav","zappa.wav","samCook.wav","vogues.wav"  };

int maxMusicArrIndex = sizeof(musicArr) / sizeof(musicArr[0]);

// function prototypes - shouldn't really be neccessary
void myDelay(int intervalMS);
int randomHatMusic(int numberInHat);

void setup() {

  Serial.begin(9600);
  while (!Serial && (millis() <= 3000));
  delay(1000);

  // Maximum memory usage was reported as 4
  // Proc = 9 (9),  Mem = 4 (4)
  AudioMemory(20); // just  a guess for max

  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.volume(0.40); // volume doesn't affect peak readings
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
  setVol(2);
}

unsigned long last_time = millis();
/*************** loop ********************/
void loop()
{
  readSensors();

  if (noMotionTime_Secs < 30) {
    harryNyquist();
    myDelay(2000);
  }
}
