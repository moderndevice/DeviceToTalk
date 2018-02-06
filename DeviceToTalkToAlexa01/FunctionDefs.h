extern int pir1, pir2;
extern AudioPlaySdWav playSdWav1;

void readSensors() {
  pir1 = digitalRead(PIR1);
  pir2 = digitalRead(PIR2);
}

void setVol(int vol) {
  if (!playSdWav1.isPlaying()) {
    if (vol == 1) {
      playSdWav1.play("vol1.wav");
    }
    else if (vol == 2) {
      playSdWav1.play("vol2.wav");
    }
    else if (vol == 3) {
      playSdWav1.play("vol3.wav");
    }
    else if (vol == 4) {
      playSdWav1.play("vol4.wav");
    }
    else if (vol == 5) {
      playSdWav1.play("vol5.wav");
    }
    else if (vol == 6) {
      playSdWav1.play("vol6.wav");
    }
    else if (vol == 7) {
      playSdWav1.play("vol7.wav");
    }
    else if (vol == 8) {
      playSdWav1.play("vol8.wav");
    }
   while(playSdWav1.isPlaying());
  }
}

