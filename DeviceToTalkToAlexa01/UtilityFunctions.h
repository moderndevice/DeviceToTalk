#define randomHatStartNum 0  // starting number in hat
// #define randomHatEndNum 25    // ending number in hat - end has to be larger than start

int randomHat(int numberInHat) {
  int thePick;		//this is the return variable with the random number from the pool
  int theIndex;
  static int currentNumInHat = 0;


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



