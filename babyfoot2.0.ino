// #include <rgb_lcd.h>
#include <millisDelay.h>
#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    120
#define TIME        1

#define A0_PIN_BLUE_CAPTOR 0
#define A0_PIN_RED_CAPTOR 1

// LED
int scoreRedLed;
int scoreBlueLed;
int bowlLed;
int stripLed;

// int NUM_LEDS;
// int TIME;

CRGB leds[NUM_LEDS];

// BUTTON
int scoreRedIrCaptor;
int scoreBlueIrCaptor;
// int bowlRedBtn;
// int bowlBlueBtn;
int resetBtn;
int halfBtn;
int pissetteBtn;

// PIEZO
int piezoBlueVal;
int piezoRedVal;

//int resetBtnPushed;

// SCORE
int scoreRed;
int scoreBlue;
int goalValue;
int lastScore;

// DELAY
int delayTimeBowl;
int delayTimeHalf;
int delayTimeReset;

// OTHERS
boolean isbowlRed;
boolean isbowlBlue;

boolean isScoreRed;
boolean isScoreBlue;

boolean resetBtnStatus;
boolean halfBtnStatus;
boolean pissetteBtnStatus;

millisDelay gDelayRed;
millisDelay gDelayBlue;
millisDelay gDelayTimeHalf;
millisDelay gDelayTimeReset;

void blinking(int pin, int occurences, int duration);
void caterpillar(int occurences, int red, int green, int blue);

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  // LED
  scoreRedLed = 12;
  scoreBlueLed = 12;
  bowlLed = 10;
  // stripLed = 10;

  // PIEZO
  piezoBlueVal = 0;
  piezoRedVal = 1;

  // IR CAPTOR
  scoreRedIrCaptor = 8;
  scoreBlueIrCaptor = 13;

  
  // BUTTON
  // bowlRedBtn = 4;
  // bowlBlueBtn = 7;
  resetBtn = 2;
  halfBtn = 3;
  pissetteBtn = 4;
  
  //resetBtnPushed = 0;

  // SCORE
  scoreRed = 0;
  scoreBlue = 0;
  goalValue = 1;
  lastScore = -1;

  // DELAY
  delayTimeBowl = 2000; //delay time == 2 seconds
  delayTimeHalf = 1000;
  delayTimeReset = 3000;
  
  // OTHERS
  isbowlRed = false;
  isbowlBlue = false;

  isScoreRed = false;
  isScoreBlue = false;

  pinMode(scoreRedLed, OUTPUT);
  pinMode(scoreBlueLed, OUTPUT);
  pinMode(bowlLed, OUTPUT);

  pinMode(scoreRedIrCaptor, INPUT);
  pinMode(scoreBlueIrCaptor, INPUT);
  // pinMode(bowlRedBtn, INPUT);
  // pinMode(bowlBlueBtn, INPUT);
  pinMode(resetBtn, INPUT);
  pinMode(halfBtn, INPUT);
  pinMode(pissetteBtn, INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean scoreRedIrCaptorStatus = digitalRead(scoreRedIrCaptor);
  boolean scoreBlueIrCaptorStatus = digitalRead(scoreBlueIrCaptor);
  boolean resetBtnStatus = digitalRead(resetBtn);
  boolean halfBtnStatus = digitalRead(halfBtn);
  boolean pissetteBtnStatus = digitalRead(pissetteBtn);
 
  piezoBlueVal = analogRead(A0_PIN_BLUE_CAPTOR) ;
  piezoRedVal = analogRead(A0_PIN_RED_CAPTOR) ;

  //
  // If you want to use button to trigger half
  //
  // boolean bowlRedBtnStatus = digitalRead(bowlRedBtn);
  // boolean bowlBlueBtnStatus = digitalRead(bowlBlueBtn);
  

  //------------------------------------------------------------------------------------------------------------------------------------------------------ 
  // BLUE TEAM
  // Check piezo Blue captor is TRUE
  if (piezoBlueVal >= 1000) { // if(bowlBlueBtnStatus == HIGH) { ==> To trigger half with button
    isbowlBlue = true;
    delay(500);
    blinking(bowlLed, 2, 100);
    if (isbowlBlue == true) {
      Serial.println("-----------------");
      Serial.println("Blue bowl");
      delay(10);
    }
    gDelayBlue.start(delayTimeBowl);
  }
   
  // Check IR Blue captor is TRUE
  if (scoreBlueIrCaptorStatus == LOW && isbowlBlue == true && gDelayBlue.isFinished()==false) {
    isScoreBlue = true;
    if (isScoreBlue == true) {
      Serial.println("Blue Score");
      delay(10);
    }
  }

  // Increment score
  if (isScoreBlue == true && isbowlBlue == true) {
    scoreBlue += goalValue;
    goalValue = 1;
    lastScore = 0;
    Serial.println("*****************");
    Serial.print("Goal Value =");
    Serial.println(goalValue);
    Serial.print("Last Score =");
    Serial.println(lastScore);
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
    caterpillar(scoreBlue, 255, 0, 0);
    //for (int i=0; i<scoreBlue ;i++) {
    //  digitalWrite(scoreBlueLed, HIGH);
    //  delay(500);
    //  digitalWrite(scoreBlueLed, LOW);
    //  delay(250);
    

    // Score needed to win the game
    if (scoreBlue >= 10){
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("    YOU WON!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      delay(1000);
      caterpillar(10, 0, 255, 0);
    // blinking(scoreBlueLed, 10, 100);
    // Reset score and captors when there is a goal
    scoreRed = 0;
    scoreBlue = 0;
    }
    isScoreRed = false;
    isbowlRed = false;
    isScoreBlue = false;
    isbowlBlue = false;
  }
  
  //Decrement score
  if (isScoreBlue == false && isbowlBlue == true && gDelayBlue.isFinished()){
    if (scoreRed > 0 ){
      scoreRed--;
    }
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    Serial.println("*****************");
    delay(500);
    caterpillar(2, 255, 255, 0);
    for (int i=0; i<scoreBlue; i++) {
      digitalWrite(scoreBlueLed, HIGH);
      delay(500);
      digitalWrite(scoreBlueLed, LOW);
      delay(250);
    }
    isbowlBlue = false;
  }

  // --------------------------------------------------------------------------------------------------------------------------------------------------------
  //RED TEAM 
  // Check piezo Red captor is TRUE
  if (piezoRedVal >= 1000) { // if(bowlBlueBtnStatus == HIGH) { ==> To trigger half with button
    isbowlRed = true;
    delay(500);
    blinking(10, 2, 100);
    if (isbowlRed == true) {
      Serial.println("-----------------");
      Serial.println("Red bowl");
      delay(10);
    }
    gDelayRed.start(delayTimeBowl);
  }
   
  // Check IR Red captor is TRUE
  if (scoreRedIrCaptorStatus == LOW && isbowlRed == true && gDelayRed.isFinished()==false) {
    isScoreRed = true;
    if (isScoreRed == true) {
      Serial.println("Red Score");
      delay(10);
    }
  }

  // Increment score
  if (isScoreRed == true && isbowlRed == true) {
    scoreRed += goalValue;
    goalValue = 1;
    lastScore = 1;
    Serial.println("*****************");
    Serial.print("Goal Value =");
    Serial.println(goalValue);
    Serial.print("Last Score =");
    Serial.println(lastScore);
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
    caterpillar(scoreRed, 0, 0, 255); 
    //for (int i=0; i<scoreRed ;i++) {
    //  digitalWrite(scoreRedLed, HIGH);
    //  delay(500);
    //  digitalWrite(scoreRedLed, LOW);
    //  delay(250);
    
 
    // Score needed to win the game
    if (scoreRed >= 10) {
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("    YOU WON!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      delay(1000);
      caterpillar(2, 0, 255, 0);
      blinking(scoreRedLed, 10, 100);
    // Reset score and captors when there is a goal
    scoreRed = 0;
    scoreBlue = 0;
    }
    isScoreRed = false;
    isbowlRed = false;
    isScoreBlue = false;
    isbowlBlue = false;
  }
  
//Decrement score
  if(isScoreRed == false && isbowlRed == true && gDelayRed.isFinished()) {
    if (scoreBlue > 0 ){
      scoreBlue--;
    }
    Serial.println("*****************");
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
    caterpillar(2, 255, 255, 0);
    for (int i=0; i<scoreRed; i++) {
      digitalWrite(scoreRedLed, HIGH);
      delay(500);
      digitalWrite(scoreRedLed, LOW);
      delay(250);
    }
    isbowlRed = false;
  }

  //----------------------------------------------------------------------------------------------------------------------------------------------------------
  
  // Reset button is activaded
  // if (resetBtnStatus == HIGH){
  //   Serial.println("resetFunction()");
  //   resetFunction();
  //   delay(500);
  //   caterpillar(2, 0, 255, 255);
  // }

  // Half button is activaded
  // if (halfBtnStatus == HIGH){
  //   Serial.println("halfFunction()");
  //   delay(500);
  //   halfFunction();
  // }

/*
  // Pissette button is activaded
  if (pissetteBtnStatus == LOW){
    Serial.println("pissetteFunction()");
    delay(500);
    pissetteFunction();
  }*/

}
// FUNCTIONS --------------------------------------------------------------------------------------------------------------------

// Make blinking LED
void blinking(int pin, int occurences, int duration) {
  for(int i=0; i<occurences; i++) {
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);
    delay(duration);
  }
}

// Remove last point and iactive half function
void halfFunction(){
  if (lastScore == 1){
    scoreRed--;
    Serial.println("/////////////////");
    Serial.println("Red half");
    Serial.println("*****************");
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
  }
  else if (lastScore == 0){
    scoreBlue--;
    Serial.println("/////////////////");
    Serial.println("Blue half");
    Serial.println("*****************");
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
  }
  else
    return;
  goalValue = 2;
  lastScore = -1;
  return;
}

void resetFunction() {
  // New Game ==> Reset score
    Serial.println(">>>>>>>>>>>>>>>>>");
    Serial.println("<<<<<<<<<<<<<<<<<");
    Serial.println("    NEW GAME");
    Serial.println("<<<<<<<<<<<<<<<<<");
    Serial.println(">>>>>>>>>>>>>>>>>");

    scoreRed = 0;
    scoreBlue = 0;

    isScoreRed = false;
    isbowlRed = false;
    isScoreBlue = false;
    isbowlBlue = false;

    lastScore = -1;
    goalValue = 1;

    delay(500);
    digitalWrite(scoreRedLed, HIGH);
    digitalWrite(scoreBlueLed, HIGH);
    delay(2000);
    digitalWrite(scoreRedLed, LOW);
    digitalWrite(scoreBlueLed, LOW);
}


// Remove last point
void pissetteFunction(){
  if (lastScore == 1){
    scoreRed--;
    Serial.println("/////////////////");
    Serial.println("Red pissette");
    Serial.println("*****************");
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
  }
  else if (lastScore == 0){
    scoreBlue--;
    Serial.println("/////////////////");
    Serial.println("Blue pissette");
    Serial.println("*****************");
    Serial.print("RED SCORE = ");
    Serial.println(scoreRed);
    Serial.print("BLUE SCORE = ");
    Serial.println(scoreBlue);
    delay(500);
  }
  else
    return;
  lastScore = -1;
  return;
}
// LED pattern
void caterpillar(int occurences, int red, int green, int blue) {
  for(int i=0; i<occurences; i++) {
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(red, green, blue);
      FastLED.show();
      delay(TIME);
    }
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
      FastLED.show();
      delay(TIME);
    }
  }
}

// TODO

// Gérer les demi? (appuyer 2 fois sur reset button ==> demi (-1 score et prochain but ==> score = score +2)).
//                 (appuyer sur reset button pendant 3s ===> New Game function is call).

//----------------------------------------------------------------------------------------------------------------------------------------------------------
