// #include <rgb_lcd.h>
#include <millisDelay.h>

int scoreLed;
int scorePin;
int gamelleLed;
int gamellePin;
int resetButton;

int scoreA;
int scoreB;

int delayTime;
boolean isGamelle;
boolean isScore;

millisDelay gDelay;

void setup() {
  // put your setup code here, to run once:
  scorePin = 2;
  scoreLed = 3;
  resetButton = 4;
  gamellePin = 5;
  gamelleLed = 6;
  
  scoreA=0;
  delayTime = 2000; //delay time == 2 seconds
  isGamelle = false;
  isScore = false;

  pinMode(scoreLed, OUTPUT);
  pinMode(scorePin, INPUT);
  pinMode(gamelleLed, OUTPUT);
  pinMode(gamellePin, INPUT);
  pinMode(resetButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean scoreButtonStatus = digitalRead(scorePin);
  boolean resetButtonStatus = digitalRead(resetButton);
  boolean gamelleButtonStatus = digitalRead(gamellePin);
  Serial.begin(115200);

  // Check piezo captor is TRUE
  if(gamelleButtonStatus == HIGH) {
    isGamelle = true;
    digitalWrite(gamelleLed, HIGH);
    delay(500);
    digitalWrite(gamelleLed, LOW);
    if(isGamelle == true) {
      Serial.println("gamelle");
      delay(10);
    }
    gDelay.start(delayTime);
  }
   
 
  // Check IR captor is TRUE
  if(scoreButtonStatus == HIGH && isGamelle == true && gDelay.isFinished()==false) {
    isScore = true;
    digitalWrite(gamelleLed, HIGH);
    delay(100);
    digitalWrite(gamelleLed, LOW);
    delay(100);
    digitalWrite(gamelleLed, HIGH);
    delay(100);
    digitalWrite(gamelleLed, LOW);
    if(isScore == true) {
      Serial.println("score");
      delay(10);
    }
  }



  // Increment score
  if(isScore == true && isGamelle == true) {
    scoreA++;
    Serial.print("score = ");
    Serial.println(scoreA);
    delay(500);
    for(int i=0; i<scoreA; i++) {
      digitalWrite(scoreLed, HIGH);
      delay(500);
      digitalWrite(scoreLed, LOW);
      delay(250);
    }

    
    // Score needed to win the game
    if(scoreA >= 3) {
      Serial.println("YOU WON!");
      delay(1000);
      for(int i=0; i<10; i++) {
        digitalWrite(scoreLed, HIGH);
        delay(100);
        digitalWrite(scoreLed, LOW);
        delay(100);
      }
    // Reset score and captors when there is a goal
    scoreA = 0;
    }
    isGamelle = false;
    isScore = false;
  }
  
//Decrement score
  if(isScore == false && isGamelle == true && gDelay.isFinished()) {
    if(scoreA > 0 ){
      scoreA--;
    }
    Serial.print("score = ");
    Serial.println(scoreA);
    delay(500);
    for(int i=0; i<scoreA; i++) {
      digitalWrite(scoreLed, HIGH);
      delay(500);
      digitalWrite(scoreLed, LOW);
      delay(250);
    }
    isGamelle = false;
  }
  // New Game ==> Reset score
  if(resetButtonStatus == HIGH) {
    Serial.println("New game");
    scoreA = 0;
    delay(500);
    digitalWrite(scoreLed, HIGH);
    delay(2000);
    digitalWrite(scoreLed, LOW);
  }
}

// TODO
// Gamelle ==> Décrementer score.
// Gérer notion d'équipe.
// Gérer les demi? (appuyer sur reset button ==> demi (-1 score et prochain but ==> score = score +2)).
//                 (appuyer sur reset button pendant 3s ===> New Game function is call).
