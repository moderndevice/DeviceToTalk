

void loveYou() {
  unsigned int startTime;
  int randomNo = random(3, 18) + 1;
  // loveYouArr[]
  for (int i = 0; i < randomNo + 1; i++) {
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
  int randomNo = random(3, 7);
  // loveYouArr[]
  for (int i = 0; i < randomNo + 1; i++) {
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
  int randomNo = random(3, 9);
  // loveYouArr[]
  for (int i = 0; i < randomNo + 1; i++) {
    playSD.play("happy.wav");
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 );
  }
}


void hi() {
  unsigned int startTime;
  int randomNo = random(3, 9);
  // loveYouArr[]
  for (int i = 0; i < randomNo + 1; i++) {
    playSD.play(hiArr[random(4)]);
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
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 20000 );
 
  for (int i = 0; i < randomNo; i++) {
    playSD.play("next.wav");
    delay(2000);
    startTime = millis();
    do {
      readSensors();
    } while (peak > LOW_THRESHOLD && (millis() - startTime) < 20000 );
  }

   playSD.play("cancel.wav");
   delay(3000);
}

void masterPlayer() {
  *functionArray[random(3)];

}


