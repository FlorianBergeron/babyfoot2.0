// #include <rgb_lcd.h>
#include <millisDelay.h>

int scoreRedLed;
int scoreBlueLed;
int gamelleLed;

int scoreRedBtn;
int scoreBlueBtn;
int gamelleRedBtn;
int gamelleBlueBtn;
int resetBtn;

int scoreRed;
int scoreBlue;

int delayTime;

boolean isGamelleRed;
boolean isGamelleBlue;

boolean isScoreRed;
boolean isScoreBlue;

millisDelay gDelayRed;
millisDelay gDelayBlue;

void setup() {
  // put your setup code here, to run once:
  scoreRedLed = 3;
  scoreBlueLed = 8;
  gamelleLed = 6;

  scoreRedBtn = 5;
  scoreBlueBtn = 9;
  gamelleRedBtn = 4;
  gamelleBlueBtn = 7;
  resetBtn = 2;

  scoreRed = 0;
  scoreBlue = 0;

  isGamelleRed = false;
  isGamelleBlue = false;

  isScoreRed = false;
  isScoreBlue = false;

  delayTime = 2000; //delay time == 2 seconds

  pinMode(scoreRedLed, OUTPUT);
  pinMode(scoreBlueLed, OUTPUT);
  pinMode(gamelleLed, OUTPUT);
   
  pinMode(scoreRedBtn, INPUT);
  pinMode(scoreBlueBtn, INPUT);
  pinMode(gamelleRedBtn, INPUT);
  pinMode(gamelleBlueBtn, INPUT);
  pinMode(resetBtn, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean scoreRedBtnStatus = digitalRead(scoreRedBtn);
  boolean scoreBlueBtnStatus = digitalRead(scoreBlueBtn);
  boolean resetBtnStatus = digitalRead(resetBtn);
  boolean gamelleRedBtnStatus = digitalRead(gamelleRedBtn);
  boolean gamelleBlueBtnStatus = digitalRead(gamelleBlueBtn);
  
Serial.begin(115200);

  //RED TEAM
  // Check piezo Red captor is TRUE
  if(gamelleRedBtnStatus == HIGH) {
    isGamelleRed = true;
    delay(500);
    digitalWrite(gamelleLed, HIGH);
    delay(100);
    digitalWrite(gamelleLed, LOW);
    delay(100);
    digitalWrite(gamelleLed, HIGH);
    delay(100);
    digitalWrite(gamelleLed, LOW);
    if(isGamelleRed == true) {
      Serial.println("Gamelle rouge");
      delay(10);
    }
    gDelayRed.start(delayTime);
  }
   
  // Check IR Red captor is TRUE
  if(scoreRedBtnStatus == HIGH && isGamelleRed == true && gDelayRed.isFinished()==false) {
    isScoreRed = true;
    if(isScoreRed == true) {
      Serial.println("Score rouge");
      delay(10);
    }
  }

  // Increment score
  if(isScoreRed == true && isGamelleRed == true) {
    scoreRed++;
    Serial.print("SCORE RED = ");
    Serial.println(scoreRed);
    Serial.print("SCORE BLEU = ");
    Serial.println(scoreBlue);
    Serial.println("*****************");
    delay(500);
    for(int i=0; i<scoreRed ;i++) {
      digitalWrite(scoreRedLed, HIGH);
      delay(500);
      digitalWrite(scoreRedLed, LOW);
      delay(250);
    }
 
    // Score needed to win the game
    if(scoreRed >= 3) {
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("    YOU WON!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      delay(1000);
      for(int i=0; i<10; i++) {
        digitalWrite(scoreRedLed, HIGH);
        delay(100);
        digitalWrite(scoreRedLed, LOW);
        delay(100);
      }
    // Reset score and captors when there is a goal
    scoreRed = 0;
    scoreBlue = 0;
    isScoreRed = false;
    isGamelleRed = false;
    isScoreBlue = false;
    isGamelleBlue = false;
    }
  }
  
//Decrement score
  if(isScoreRed == false && isGamelleRed == true && gDelayRed.isFinished()) {
    if(scoreBlue > 0 ){
      scoreBlue--;
    }
    Serial.print("SCORE RED = ");
    Serial.println(scoreRed);
    Serial.print("SCORE BLEU = ");
    Serial.println(scoreBlue);
    Serial.println("*****************");
    delay(500);
    for(int i=0; i<scoreRed; i++) {
      digitalWrite(scoreRedLed, HIGH);
      delay(500);
      digitalWrite(scoreRedLed, LOW);
      delay(250);
    }
    isGamelleRed = false;
  }

  //------------------------------------------------------------------------------------------------------------------------------------------------------ 
  // BLUE TEAM
  // Check piezo Red captor is TRUE
  if(gamelleBlueBtnStatus == HIGH) {
    isGamelleBlue = true;
    delay(500);
    digitalWrite(gamelleLed, HIGH);
    delay(100);
    digitalWrite(gamelleLed, LOW);
    delay(100);
    digitalWrite(gamelleLed, HIGH);
    delay(100);
    digitalWrite(gamelleLed, LOW);
    if(isGamelleBlue == true) {
      Serial.println("Gamelle bleu");
      delay(10);
    }
    gDelayBlue.start(delayTime);
  }
  
  // Check IR Red captor is TRUE
  if(scoreBlueBtnStatus == HIGH && isGamelleBlue == true && gDelayBlue.isFinished()==false) {
    isScoreBlue = true;
    if(isScoreBlue == true) {
      Serial.println("Score bleu");
      delay(10);
    }
  }

  // Increment score
  if(isScoreBlue == true && isGamelleBlue == true) {
    scoreBlue++;
    Serial.print("SCORE RED = ");
    Serial.println(scoreRed);
    Serial.print("SCORE BLEU = ");
    Serial.println(scoreBlue);
    Serial.println("*****************");
    delay(500);
    for(int i=0; i<scoreBlue ;i++) {
      digitalWrite(scoreBlueLed, HIGH);
      delay(500);
      digitalWrite(scoreBlueLed, LOW);
      delay(250);
    }

    // Score needed to win the game
    if(scoreBlue >= 3) {
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("    YOU WON!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      Serial.println("!!!!!!!!!!!!!!!!!");
      delay(1000);
      for(int i=0; i<10; i++) {
        digitalWrite(scoreBlueLed, HIGH);
        delay(100);
        digitalWrite(scoreBlueLed, LOW);
        delay(100);
      }
    // Reset score and captors when there is a goal
    scoreRed = 0;
    scoreBlue = 0;
    isScoreRed = false;
    isGamelleRed = false;
    isScoreBlue = false;
    isGamelleBlue = false;
    }
  }
  
//Decrement score
  if(isScoreBlue == false && isGamelleBlue == true && gDelayBlue.isFinished()) {
    if(scoreRed > 0 ){
      scoreRed--;
    }
    Serial.print("SCORE RED = ");
    Serial.println(scoreRed);
    Serial.print("SCORE BLEU = ");
    Serial.println(scoreBlue);
    Serial.println("*****************");
    delay(500);
    for(int i=0; i<scoreBlue; i++) {
      digitalWrite(scoreBlueLed, HIGH);
      delay(500);
      digitalWrite(scoreBlueLed, LOW);
      delay(250);
    }
    isGamelleBlue = false;
  }

  //----------------------------------------------------------------------------------------------------------------------------------------------------------
  // New Game ==> Reset score
  if(resetBtnStatus == HIGH) {
    Serial.println(">>>>>>>>>>>>>>>>>");
    Serial.println("<<<<<<<<<<<<<<<<<");
    Serial.println("    NEW GAME");
    Serial.println("<<<<<<<<<<<<<<<<<");
    Serial.println(">>>>>>>>>>>>>>>>>");

    scoreRed = 0;
    scoreBlue = 0;

    isScoreRed = false;
    isGamelleRed = false;
    isScoreBlue = false;
    isGamelleBlue = false;

    delay(500);
    digitalWrite(scoreRedLed, HIGH);
    digitalWrite(scoreBlueLed, HIGH);
    delay(2000);
    digitalWrite(scoreRedLed, LOW);
    digitalWrite(scoreBlueLed, LOW);
  }
}

// TODO

// Gérer notion d'équipe.
// Gérer les demi? (appuyer sur reset button ==> demi (-1 score et prochain but ==> score = score +2)).
//                 (appuyer sur reset button pendant 3s ===> New Game function is call).