// #include <rgb_lcd.h>

int scoreLed;
int scorePin;
int gamelleLed;
int gamellePin;
int resetButton;

int score;

boolean isGamelle;
boolean isScore;

void setup() {
  // put your setup code here, to run once:
  scorePin = 2;
  scoreLed = 3;
  resetButton = 4;
  gamellePin = 5;
  gamelleLed = 6;
  
  score=0;
  
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
  }

  // Check IR captor is TRUE
  if(scoreButtonStatus == HIGH && isGamelle == true) {
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
    score++;
    Serial.print("score = ");
    Serial.println(score);
    delay(500);
    for(int i=0; i<score; i++) {
      digitalWrite(scoreLed, HIGH);
      delay(500);
      digitalWrite(scoreLed, LOW);
      delay(250);
    }

    // Score needed to win the game
    if(score >= 3) {
      Serial.println("YOU WON!");
      delay(1000);
      for(int i=0; i<10; i++) {
        digitalWrite(scoreLed, HIGH);
        delay(100);
        digitalWrite(scoreLed, LOW);
        delay(100);
      }
    // Reset score and captors when there is a goal
    score = 0;
    }
    isGamelle = false;
    isScore = false;
  }

  // New Game ==> Reset score
  if(resetButtonStatus == HIGH) {
    Serial.println("New game");
    score = 0;
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
