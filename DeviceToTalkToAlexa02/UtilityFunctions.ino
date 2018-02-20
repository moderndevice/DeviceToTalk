
#define randomHatStartNum 0  // starting number in hat
#define randomHatEndNum 25    // ending number in hat - end has to be larger than start

int randomHatMusic(int numberInHat);
void setVol(int vol);

void readSensors() {
  static	unsigned int lastRead;
  // peak detection seems to not work if you read peak too quickly //
  if ((millis() - lastRead) < 5) {
    // just bail out
  }
  else {
    lastRead = millis();
    pir1 = digitalRead(PIR1);
    pir2 = digitalRead(PIR2);

    //  if ((pir1 || pir2)) {              //(lastPIR1 || lastPIR2) && !
    if ((pir2)) {              //(lastPIR1 || lastPIR2) && !

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

void randVol(){
	int i = random(3,6);
	setVol(i);
	Serial.println(i);
}

void setVol(int vol) { // sets Alexa volume
  if (gVolume != vol) {
    while (playSD.isPlaying()); // let any sample playing finish
    delay(500);
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
    delay(SD_WAV_DELAY);
    while (playSD.isPlaying());
    gVolume = vol;
  }
}



void myDelay(unsigned int intervalMS) {
  unsigned int startTime;
  startTime = millis();
  while (millis() - startTime < intervalMS) {
    readSensors();
  }
}

int randomHatMusic(int numberInHat) {
  int thePick;		//this is the return variable with the random number from the pool
  int theIndex;
  static int currentNumInHat = 0;
  static int randArray[20];

  if  (currentNumInHat == 0) {                  // hat is emply - all have been choosen - fill up array again
    for (int i = 0 ; i < numberInHat; i++) {    // Put 1 TO numberInHat in array - starting at address 0.
      if (randomHatStartNum < numberInHat) {
        randArray[i] = i;
      }
    }
    currentNumInHat = abs(numberInHat);   // reset current Number in Hat
    // Serial.print(" hat is empty ");
    // if something should happen when the hat is empty do it here
  }

  theIndex = random(currentNumInHat);	                 //choose a random index from number in hat
  thePick = randArray[theIndex];
  randArray[theIndex] =  randArray[currentNumInHat - 1]; // copy the last element in the array into the the empty slot
  //                                                     // as the the draw is random this works fine, and is faster
  //                                                     // the previous version. - from a reader suggestion on this page
  currentNumInHat--;    // decrement number in hat
  return thePick;
}



