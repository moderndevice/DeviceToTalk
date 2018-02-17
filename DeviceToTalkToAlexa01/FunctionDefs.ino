//#include "DeviceToTalkToAlexa01.ino"
// extern int pir1, pir2, maxMusicArrIndex;
#include <Audio.h>
extern AudioPlaySdWav playSD;
extern unsigned int lastMotionTime, noMotionTime_Secs, lastSoundTime, lastRead;
extern float silenceTime_Secs;
extern AudioAnalyzePeak peak1;
extern const float RESET_AMOUNT, SILENCE_THRESHOLD, LOW_THRESHOLD;
extern float temp, peak;
extern char* musicArr[];
void setVol(int vol);
extern void readSensors();
extern void myDelay(int intervalMS);
//int maxMusicArrIndex;




void doLights(int value){

	// light20.wav
// light2.wav
}

void alexaCancel() {
  if (playSD.isPlaying()) playSD.stop();
  playSD.play("cancel.wav");
  delay(10);
}

void anarchy() {
  unsigned int startTime, state = 0;
  float timer;
  if (silenceTime_Secs < 2) alexaCancel();
  if (playSD.isPlaying()) playSD.stop();
  delay(1000);
  setVol(2);
  delay(2000);
  playSD.play("anarchy.wav");
  delay(10);
  startTime = millis();
  do {
    Serial.println(timer);
    readSensors();
    timer = (millis() - startTime) / 1000;
    if (timer > 19 && state == 0) {
      setVol(3);
      state = 1;
    }
    else if (timer > 32.0 && state == 1) {
      setVol(2);
      state = 2;
    }
    else if (timer > 44.0 && state == 2) {
      setVol(3);
      state = 3;
    }
    if (timer > 56.0) {
      alexaCancel();
      break;
    }
  } while (1);
}



void clorox() {
  unsigned int startTime;
  setVol(2);
  delay(2000);
  playSD.play("clorox.wav");
  delay(10);
  myDelay(2000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 20000 ) {
    readSensors();
  }
  playSD.play("start.wav");
  delay(10);
  myDelay(2000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 20000 ) {
    readSensors();
  }
  playSD.play("continue.wav");
  delay(10);
  myDelay(2000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 40000 ) {
    readSensors();
  }
  playSD.play("cancel.wav");
  delay(10);
}

void norbertWiener() {
  unsigned int startTime;
  if (silenceTime_Secs < 1) {
    alexaCancel();
    myDelay(3000);
  }
  if (playSD.isPlaying()) playSD.stop();
  playSD.play("aWiener.wav");
  delay(10);
  readSensors();
  myDelay(8000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 18000 ) {
    readSensors();
  }
  playSD.play("readMore.wav");
  delay(10);
  myDelay(3000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 40000 ) {
    readSensors();
  }
  playSD.play("nWiener.wav");
  delay(10);
  myDelay(100);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 20000 ) {
    readSensors();
  }
}

void claudeShannon() {
  unsigned int startTime;
  if (silenceTime_Secs < 1) alexaCancel();
  if (playSD.isPlaying()) playSD.stop();
  playSD.play("aShan.wav");
  delay(10);
  readSensors();
  myDelay(8000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 18000 ) {
    readSensors();
  }
  playSD.play("readMore.wav");
  delay(10);
  myDelay(3000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 40000 ) {
    readSensors();
  }
}

void playMusic() {
  unsigned int startTime, randNo, fileRepeat, listenTime, fileNum;
  fileRepeat = random(4) + 1;
  Serial.print("  fileRepeat ");
  Serial.println(fileRepeat );
  delay(10000);
  if (silenceTime_Secs < 1) {
    alexaCancel();
    myDelay(3000);
  }
  if (playSD.isPlaying()) playSD.stop();
  fileNum = randomHatMusic(maxMusicArrIndex);
  playSD.play(musicArr[fileNum]);
  delay(10);
  startTime = millis();
  listenTime = 10000 + random(40000);
  for (int i = 0; i < fileRepeat; i++) {
    while ((millis() - startTime) < listenTime ) {
      readSensors();
    }
    startTime = millis();
    listenTime = 10000 + random(40000);
    playSD.play("AlxaNext.wav");
    delay(10);
    myDelay(1000);
  }
  playSD.play("cancel.wav");
  delay(10);
  myDelay(1000);
}

void harryNyquist() {
  unsigned int startTime;
  if (silenceTime_Secs < 1) {
    alexaCancel();
    myDelay(3000);
  }
  if (playSD.isPlaying()) playSD.stop();
  playSD.play("nyquist.wav");
  delay(10);
  readSensors();
  myDelay(2000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 14000 ) {
    readSensors();
  }
  playSD.play("nyqLimit.wav");
  delay(10);
  myDelay(3000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 14000 ) {
    readSensors();
  }
}

void goatFacts() {
  unsigned int startTime;
  int randomPlay;
  randomPlay = random(3) + 1;
  Serial.print("  randomPlay ");
  Serial.println(randomPlay );
  delay(4000);
  if (silenceTime_Secs < 1) {
    myDelay(2000);
  }
  if (playSD.isPlaying()) playSD.stop();
  startTime = millis();
  for (int i = 0; i < randomPlay; i++) {
    playSD.play("goatFact.wav");
    delay(10);
    myDelay(6000);
    while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 ) {
      readSensors();
    }
    startTime = millis();
  }
}




