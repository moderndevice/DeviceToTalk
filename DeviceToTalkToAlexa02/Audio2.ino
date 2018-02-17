void iLoveYou() {
  unsigned int startTime;
  int randomNo = random(3, 18) + 1;
 
  for (int i = 0; i < randomNo + 1; i++) {
    startTime = millis();
    while (peak > LOW_THRESHOLD && (millis() - startTime) < 30000 ) {
      readSensors();
    }
  }
}

void masterPlayer(){	
*functionArray[random(3)];
	
}

