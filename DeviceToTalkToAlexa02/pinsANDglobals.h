// Use these with the audio adaptor board
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

#define PIR1 2
#define PIR2 1
#define WalkAwayTimeout_Secs 15
#define DEFAUT_VOLUME 3


int gVolume = DEFAUT_VOLUME;  // global volume - this is alexa volume
const float RESET_AMOUNT = .001; // arbitrary units
// governs how fast the peak detector returns to zero
// smaller numbers are slower
const float SILENCE_THRESHOLD = 0.16; // threshold for audio detection
const float LOW_THRESHOLD = 0.12; // threshold for audio detection
const int SD_WAV_DELAY = 6;

#define TIMER_DEBUG

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


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

int gLightLvl = 0;  // 0, 1, 2
int gEnabled = 0, glastEnabled = 0;
int pir1, pir2; // pir variables for motion sensors
float  temp,  peak = 0; // audio volume
unsigned int lastMotionTime, noMotionTime_Secs, lastSoundTime,  lastRead;
float silenceTime_Secs;
unsigned int lastPIR1, lastPIR2;

char* musicArr[] = {"tempttns.wav", "supremes.wav", "johnCage.wav", "raviShkr.wav", "sunRa.wav",
                    "PubEnemy.wav", "artEnsCh.wav", "zappa.wav", "samCook.wav", "vogues.wav"
                   };

char* loveYouArr[] = {"iLoveYou.wav", "yourGrt.wav", "thebest.wav"};
char* hateYouArr[] = {"onlyThng.wav", "iHateYou.wav", "dissapnt.wav"};
char* hiArr[] = {"hi.wav", "hi2.wav", "goodDay.wav", "hello.wav", "wazUp.wav"};
char* liarArr[] = {"liar.wav", "liar2.wav", "liar3.wav"};


int maxMusicArrIndex = sizeof(musicArr) / sizeof(musicArr[0]);

// function prototypes - shouldn't really be neccessary
void myDelay(unsigned int intervalMS);
int randomHatMusic(int numberInHat);
void setVol(int vol);
int randomHatMusic(int numberInHat);
void readSensors(); void clorox(); void claudeShannon(); void anarchy();
void norbertWiener(); void minsky(); void harryNyquist(); void loveYou();
void hateYou(); void happy(); void hi(); void liar(); void playMusic();
void goatFacts(); void deals(); void toggleLights(); void stopMusic();
 void alexaCancel(); void doLights(int value); void masterPlayer();


// array of functions
void (*functionArray[22])() {
  clorox, norbertWiener, goatFacts, claudeShannon, minsky, toggleLights, harryNyquist
  , anarchy, deals, loveYou, stopMusic, playMusic, hateYou, happy, hi
  , liar, goatFacts, deals, toggleLights, goatFacts, playMusic, stopMusic
};




