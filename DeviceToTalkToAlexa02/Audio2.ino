

void loveYou() {
  unsigned int startTime;
  int randomNo = random(3, 6);
  for (int i = 0; i < randomNo; i++) {
    playSD.play(loveYouArr[random(3)]);
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 );
  }
}

void hateYou() {
  unsigned int startTime;
  int randomNo = random(2, 4);
  for (int i = 0; i < randomNo; i++) {
    playSD.play(hateYouArr[random(3)]);
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 );
  }
}

void happy() {
  unsigned int startTime;
  int randomNo = random(3, 5);
  for (int i = 0; i < randomNo; i++) {
    if (random(20) < 3) {
      playSD.play("whatSad.wav");
    }
    else {
      playSD.play("happy.wav");
    }
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 );
  }
}


void hi() {
  unsigned int startTime;
  int randomNo = random(3, 12);
  for (int i = 0; i < randomNo + 1; i++) {
    playSD.play(hiArr[random(5)]);
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 );
  }
}

void liar() {
  unsigned int startTime;
  int randomNo = random(2, 5);
  for (int i = 0; i < randomNo + 1; i++) {
    playSD.play(liarArr[random(3)]);
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 );
  }
}

void deals() {
  unsigned int startTime;
  int randomNo = random(2, 6);
  playSD.play("deals.wav");
  delay(2000);
  startTime = millis();
  do {
    readSensors();
  } while (peak > LOW_THRESHOLD && (millis() - startTime) < 16000 );

  for (int i = 0; i < randomNo; i++) {
    playSD.play("next.wav");
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 16000 );
  }

  playSD.play("cancel.wav");
  delay(3000);
}

void stopMusic() {
  playSD.play("stopMusc.wav");
  delay(2000);
}

void masterPlayer() {
//void (*functionArray[22])() {
//  clorox, norbertWiener, goatFacts, claudeShannon, minsky, toggleLights, harryNyquist
//  , anarchy, deals, loveYou, stopMusic, playMusic, hateYou, happy, hi
//  , liar, goatFacts, deals, toggleLights, goatFacts, playMusic, stopMusic
//};

  int randNo = randomHatFunctionPlayer(22); 
  (*functionArray[randNo])();
}


