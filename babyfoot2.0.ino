// #include <rgb_lcd.h>
#include <millisDelay.h>

int scoreRedLed;
int scoreBlueLed;

int scoreRedBtn;
int scoreBlueBtn;

int gamelleLed;

int gamelleRedBtn;
int gamelleBlueBtn;

int resetButton;

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

  resetButton = 2;

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
  pinMode(resetButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean scoreRedBtnStatus = digitalRead(scoreRedBtn);
  boolean scoreBlueBtnStatus = digitalRead(scoreBlueBtn);
  boolean resetButtonStatus = digitalRead(resetButton);
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
      Serial.println("gamelle rouge");
      delay(10);
    }
    gDelayRed.start(delayTime);
  }
   
 
  // Check IR Red captor is TRUE
  if(scoreRedBtnStatus == HIGH && isGamelleRed == true && gDelayRed.isFinished()==false) {
    isScoreRed = true;
    if(isScoreRed == true) {
      Serial.println("score rouge");
      delay(10);
    }
  }



  // Increment score
  if(isScoreRed == true && isGamelleRed == true) {
    scoreRed++;
    Serial.print("score bleu = ");
    Serial.println(scoreBlue);
    Serial.print("score red = ");
    Serial.println(scoreRed);
    delay(500);
    for(int i=0; i<scoreRed ;i++) {
      digitalWrite(scoreRedLed, HIGH);
      delay(500);
      digitalWrite(scoreRedLed, LOW);
      delay(250);
    }

    
    // Score needed to win the game
    if(scoreRed >= 3) {
      Serial.println("YOU WON!");
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
    }
    isGamelleRed = false;
    isScoreRed = false;
  }
  
//Decrement score
  if(isScoreRed == false && isGamelleRed == true && gDelayRed.isFinished()) {
    if(scoreBlue > 0 ){
      scoreBlue--;
    }
    Serial.print("score bleu = ");
    Serial.println(scoreBlue);
    Serial.print("score red = ");
    Serial.println(scoreRed);
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
      Serial.println("gamelle bleu");
      delay(10);
    }
    gDelayBlue.start(delayTime);
  }
   
 
  // Check IR Red captor is TRUE
  if(scoreBlueBtnStatus == HIGH && isGamelleBlue == true && gDelayBlue.isFinished()==false) {
    isScoreBlue = true;
    if(isScoreBlue == true) {
      Serial.println("score bleu");
      delay(10);
    }
  }



  // Increment score
  if(isScoreBlue == true && isGamelleBlue == true) {
    scoreBlue++;
    Serial.print("score bleu = ");
    Serial.println(scoreBlue);
    Serial.print("score red = ");
    Serial.println(scoreRed);
    delay(500);
    for(int i=0; i<scoreBlue ;i++) {
      digitalWrite(scoreBlueLed, HIGH);
      delay(500);
      digitalWrite(scoreBlueLed, LOW);
      delay(250);
    }

    
    // Score needed to win the game
    if(scoreBlue >= 3) {
      Serial.println("YOU WON!");
      delay(1000);
      for(int i=0; i<10; i++) {
        digitalWrite(scoreBlueLed, HIGH);
        delay(100);
        digitalWrite(scoreBlueLed, LOW);
        delay(100);
      }
    // Reset score and captors when there is a goal
    scoreBlue = 0;
    scoreRed = 0;
    }
    isGamelleBlue = false;
    isScoreBlue = false;
  }
  
//Decrement score
  if(isScoreBlue == false && isGamelleBlue == true && gDelayBlue.isFinished()) {
    if(scoreRed > 0 ){
      scoreRed--;
    }
    Serial.print("score rouge = ");
    Serial.println(scoreRed);
    Serial.print("score bleu = ");
    Serial.println(scoreBlue);
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
  if(resetButtonStatus == HIGH) {
    Serial.println("New game");
    scoreRed = 0;
    scoreBlue = 0;
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
