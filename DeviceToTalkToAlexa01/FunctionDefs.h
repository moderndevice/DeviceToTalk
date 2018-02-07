extern int pir1, pir2, maxMusicArrIndex;
extern AudioPlaySdWav playSD;
extern unsigned int lastMotionTime, noMotionTime_Secs, lastSoundTime, lastRead;
extern float silenceTime_Secs;
extern AudioAnalyzePeak peak1;
extern const float RESET_AMOUNT, SILENCE_THRESHOLD;
extern float temp, peak;
extern char* musicArr[];
int lastPIR1, lastPIR2;
int randomHatMusic(int numberInHat);



void readSensors() {
  // peak detection seems to not work if you read peak too quickly //
  if ((millis() - lastRead) < 5) {
    // just bail out
  }
  else {
    lastRead = millis();
    pir1 = digitalRead(PIR1);
    pir2 = digitalRead(PIR2);

    if ((pir1 || pir2)) {              //(lastPIR1 || lastPIR2) && !
      lastMotionTime = millis();
      //            Serial.println("reset motion");
    }
    noMotionTime_Secs = (millis() - lastMotionTime) / 1000;
    lastPIR1 = pir1;
    lastPIR2 = pir2;
    // peak detector for peak !?
    temp = peak1.read();
    if (temp > peak) peak = temp; // slow down // peak += (temp - peak) / 3.0;
    peak = peak - RESET_AMOUNT;
    if (peak < 0) peak = 0;
    if (peak > SILENCE_THRESHOLD) {
      lastSoundTime = millis();
    }
    silenceTime_Secs = (millis() - lastSoundTime) / 1000;

#ifdef TIMER_DEBUG
    Serial.print(pir1); Serial.print(pir2); Serial.print("\t"); Serial.print(noMotionTime_Secs);
    Serial.print("\t"); Serial.print("\t");
    Serial.print(peak); Serial.print("\t"); Serial.println(silenceTime_Secs);
#endif
  }
}

void myDelay(int intervalMS) {
  unsigned int startTime;
  startTime = millis();
  while (millis() - startTime < intervalMS) {
    readSensors();
  }
}

void setVol(int vol) {
  if (!playSD.isPlaying()) {
    if (vol == 0) {
      playSD.play("vol0.wav");
    }
    if (vol == 1) {
      playSD.play("vol1.wav");
    }
    else if (vol == 2) {
      playSD.play("vol2.wav");
    }
    else if (vol == 3) {
      playSD.play("vol3.wav");
    }
    else if (vol == 4) {
      playSD.play("vol4.wav");
    }
    else if (vol == 5) {
      playSD.play("vol5.wav");
    }
    else if (vol == 6) {
      playSD.play("vol6.wav");
    }
    else if (vol == 7) {
      playSD.play("vol7.wav");
    }
    else if (vol == 8) {
      playSD.play("vol8.wav");
    }
    while (playSD.isPlaying()) {
      Serial.println("foo");
    }
    delay(10);
  }
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
   if (silenceTime_Secs < 1){
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
   if (silenceTime_Secs < 1){
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
  if (silenceTime_Secs < 1){
  	alexaCancel();
  	myDelay(3000);
  }
  if (playSD.isPlaying()) playSD.stop();
  playSD.play("nyquist.wav");
  delay(10);
  readSensors();
  myDelay(2000);
  startTime = millis();
  while (peak > LOW_THRESHOLD && (millis() - startTime) < 148000 ) {
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




