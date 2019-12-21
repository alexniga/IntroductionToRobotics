#include <LiquidCrystal.h>
#include "LedControl.h"
#include <EEPROM.h>

const int RSPin = 9;
const int EPin = 8;
const int D4Pin = 5;
const int D5Pin = 4;
const int D6Pin = 3;
const int D7Pin = 2;

LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No of drivers
LiquidCrystal lcd(RSPin, EPin, D4Pin, D5Pin, D6Pin, D7Pin);

const bool matrixStartGame1[8][8] {
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 1, 0, 1, 0, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 0, 0}
};

const bool matrixStartGame2[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 1, 1, 0, 1, 1, 0, 0}
};

const bool matrixArrowUp[8][8] {
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool matrixArrowDown[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};

const bool matrixArrowLeft[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool matrixArrowRight[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool matrixArrowUpLeft[8][8] {
  {1, 1, 1, 0, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 0, 0, 0},
  {1, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool matrixArrowUpRight[8][8] {
  {0, 0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const bool matrixArrowDownLeft[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {1, 0, 1, 0, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 0, 0}
};

const bool matrixArrowDownRight[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 1, 1, 1}
};

const bool matrixLevelWin[8][8] {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 1, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};

const int buttonPin = 7;
const int xPin = A0;
const int yPin = A1;
int buttonValue = 0;
int xValue = 0;
int yValue = 0;

const int menu = 1;
const int inStart = 2;
const int inHighScore = 3;
const int inSettings = 4;
const int inInfo = 5;
int whereIAm = 1;
int firstClear;

int delayLevel = 7;
long long animation = 0;


int lineArrow[2] = {0, 1};
int collumnArrow[2] = {0, 6};
int arrowPozCol = collumnArrow[0];
int arrowPozLin = lineArrow[0];
int col = 1;

// (col, lin)
// (0, 0) -> start
// (6, 0) -> HighScore
// (3, 1) -> Settings

int startingLevelSettings = 1;
int startingLevelValue = 0;
int highScore = 0;
int numberOfLives = 3;
int levelNumber = 1;

long lastChange = 0;
long endGameTimer = 0;

boolean movedX = false;
boolean movedY = false;
boolean movedYSet = false;

int waitSpeed = 1000;
int showInInfo = 1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
  long localMillis = millis() - 1;
  int StartingMessage = 1;
  lcd.clear();

  while (StartingMessage) {
    if (millis() - StartingMessage >= 4000) {
      StartingMessage = 0;
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print(" WELCOME   TO ");
      lcd.setCursor(0, 1);
      lcd.print("DANCING JOYSTICK ");
    }
  }
  lcd.clear();
}

int showUp() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowUp[row][col]);
      if (xValueL > 700 && yValueL < 700 && yValueL > 400) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (xValueL > 700 && yValueL < 700 && yValueL > 400) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showDown() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowDown[row][col]);
      if (xValueL < 400 && yValueL < 700 && yValueL > 400) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (xValueL < 400 && yValueL < 700 && yValueL > 400) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showLeft() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowLeft[row][col]);
      if (yValueL < 400 && xValueL < 700 && xValueL > 400) {
            goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (yValueL < 400 && xValueL < 700 && xValueL > 400) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showRight() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowRight[row][col]);
      if (yValueL > 700 && xValueL < 700 && xValueL > 400) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (yValueL > 700 && xValueL < 700 && xValueL > 400) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showCenter() {
  int buttonValueL = digitalRead(buttonPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, 0);
      if (row >= 3 && row <= 4 && col >= 3 && col <= 4) {
        lc.setLed(0, row, col, 1);
      }
      if (buttonValueL == 0) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    buttonValueL = digitalRead(buttonPin);
    if (buttonValueL == 0) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showUpLeft() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowUpLeft[row][col]);
      if (yValueL < 400 && xValueL > 700) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (yValueL < 400 && xValueL > 700) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showUpRight() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowUpRight[row][col]);
      if (yValueL > 700 && xValueL > 700) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (yValueL > 700 && xValueL > 700) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showDownLeft() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowDownLeft[row][col]);
      if (yValueL < 400 && xValueL < 400) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (yValueL < 400 && xValueL < 400) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

int showDownRight() {
  int xValueL = analogRead(xPin);
  int yValueL = analogRead(yPin);
  int goodMoved = 0;

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      lc.setLed(0, row, col, matrixArrowDownRight[row][col]);
      if (yValueL > 700 && xValueL < 400) {
        goodMoved = 1;
      }
      delay(delayLevel);
    }
  }

  long long localMillis = millis() - 1;
  int timeHasNotPassed = 1;

  while (timeHasNotPassed) {
    xValueL = analogRead(xPin);
    yValueL = analogRead(yPin);
    if (yValueL > 700 && xValueL < 400) {
        goodMoved = 1;
    }
    if (millis() - localMillis > waitSpeed) {
        timeHasNotPassed = 0;
    }
  }
  return goodMoved;
}

void printArrow(int col, int row) {
  lcd.setCursor(col, row);
  lcd.print(">");
}

void printLevelSetTo(int level) {
  lcd.print(".");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set the level");
  lcd.setCursor(0, 1);
  lcd.print("<");
  lcd.setCursor(15, 1);
  lcd.print(">");
  lcd.setCursor(7, 1);
  lcd.print(level);
}

int LevelIsDone(int levelNumber) {
  int lvlProd = 1;
  long lvlRandom, lvlRandomPrev;

  for (int i = 1; i <= levelNumber; i++) {
    lvlRandomPrev = lvlRandom;
    lvlRandom = random(1, 9);

    if (lvlProd == 0) {
        break;
    }
    if (lvlRandomPrev == lvlRandom) {
      if (lvlRandom == 1) {
        lvlRandom = 2 + random(0, 7);
      }
      else if (lvlRandom == 9) {
        lvlRandom = 8 - random(0, 7);
      }
      else {
        lvlRandom += 1;
      }
    }

    if (lvlRandom == 1) {
        lvlProd *= showUp();
    }
    else if (lvlRandom == 2) {
        lvlProd *= showDown();
    }
    else if (lvlRandom == 3) {
        lvlProd *= showLeft();
    }
    else if (lvlRandom == 4) {
        lvlProd *= showRight();
    }
    else if (lvlRandom == 5) {
        lvlProd *= showCenter();
    }
    else if (lvlRandom == 6) {
        lvlProd *= showUpLeft();
    }
    else if (lvlRandom == 7) {
        lvlProd *= showUpRight();
    }
    else if (lvlRandom == 8) {
        lvlProd *= showDownLeft();
    }
    else {
        lvlProd *= showDownRight();
    }
  }

  if (lvlProd == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("YOU HAVE WIN!");
    lcd.setCursor(0, 1);
    lcd.print("LEVEL: ");
    lcd.setCursor(8, 1);
    lcd.print(levelNumber);
    lcd.setCursor(11, 1);
    lcd.print("ENDED");
    long long localMillis = millis() - 1;

    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(0, row, col, matrixLevelWin[row][col]);
      }
    }

    int timeHasNotPassed = 1;

    while (timeHasNotPassed) {
      if (millis() - localMillis > 3000) {
        timeHasNotPassed = 0;
      }
    }
    return 1;
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("YOU HAVE LOST!");
    lcd.setCursor(0, 1);
    lcd.print("LEVEL: ");
    lcd.setCursor(8, 1);
    lcd.print(levelNumber);

    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        lc.setLed(0, row, col, 0);
        if (row == col || row + col == 7) {
            lc.setLed(0, row, col, 1);
        }
      }
    }

    long long localMillis = millis() - 1;
    int timeHasNotPassed = 1;

    while (timeHasNotPassed) {
      if (millis() - localMillis > 3000) {
        timeHasNotPassed = 0;
      }
    }
    return 0;
  }
}

void printTheInfo(int whatInfo) {
  if (whatInfo == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("^");
    lcd.print("Creator name:");
    lcd.setCursor(0, 1);
    lcd.print("^");
    lcd.print("Niga Alexandru");
  }
  else if (whatInfo == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("^");
    lcd.print("Github Link:");
    lcd.setCursor(0, 1);
    lcd.print("^");
    lcd.print("github.com/alexniga");
  }
  else if (whatInfo == 2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("^");
    lcd.print("Game name:");
    lcd.setCursor(0, 1);
    lcd.print("^");
    lcd.print("DANCING JOYSTICK");
  }
  else if (whatInfo == 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Project made for:");
    lcd.setCursor(0, 1);
    lcd.print("^");
    lcd.print("@UnibucRobotics");
  }

}

void loop() {
  buttonValue = digitalRead(buttonPin);
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  if (buttonValue == 0 && whereIAm == menu) {
    firstClear = 0;
    if (arrowPozLin == 0 && arrowPozCol == 0) {
      whereIAm = inStart;
      startingLevelValue = startingLevelSettings * 10;
      lastChange = millis();
      endGameTimer = lastChange;
      levelNumber = startingLevelSettings;
      waitSpeed = 2000;
      delayLevel = 7;
      numberOfLives = 3;
    }
    if (arrowPozLin == 0 && arrowPozCol == 6) {
      whereIAm = inHighScore;
    }
    else if (arrowPozLin == 1 && arrowPozCol == 0) {
      printLevelSetTo(startingLevelSettings);
      whereIAm = inSettings;
    }
    else if (arrowPozLin == 1 && arrowPozCol == 9) {
      yValue = 300;
      whereIAm = inInfo;
    }
  }

  if (whereIAm == inSettings) {
    if (yValue < 400) {
      if (movedYSet == false) {
        startingLevelSettings--;
        if (startingLevelSettings < 1) {
            startingLevelSettings = 1;
        }
        movedYSet = true;
        printLevelSetTo(startingLevelSettings);
      }
    }
    else {
      if (yValue > 600) {
        if (movedYSet == false) {
          startingLevelSettings++;
          if (startingLevelSettings > 5) {
            startingLevelSettings = 5;
          }
          movedYSet = true;
          printLevelSetTo(startingLevelSettings);
        }
      }
      else {
        movedYSet = false;
      }
    }
    if (xValue > 800) {
        whereIAm = menu;
    }
  }

  if (whereIAm == inHighScore) {
    if (firstClear == 0) {
      lcd.clear();
      firstClear = 1;
    }

    lcd.setCursor(0, 0);
    lcd.print("HighScore = ");
    highScore = EEPROM.read(0);
    lcd.print(highScore);

    if (xValue > 800) {
        whereIAm = menu;
    }
  }

  if (whereIAm == inStart){
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("The game starts");
    lcd.setCursor(5, 1);
    lcd.print("IN 3..2..1");
    delay(3000);
    lcd.clear();
    firstClear = 1;
    lcd.setCursor(1, 0);
    lcd.print("Lives: ");
    lcd.setCursor(9, 0);
    lcd.print(numberOfLives);
    lcd.setCursor(1, 1);
    lcd.print("Score = ");
    lcd.print(startingLevelValue);

    if (LevelIsDone(levelNumber) == 1) {
      levelNumber++;
      if (waitSpeed > 200) {
        waitSpeed -= 100;
      }
      else {
        waitSpeed -= 10;
      }
      startingLevelValue += 5 * levelNumber;
      if (delayLevel > 3) {
        delayLevel--;
      }
    }
    else {
        numberOfLives--;
    }

    if (numberOfLives == 0) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Game Over!"); lcd.print(startingLevelValue);

      if (startingLevelValue > highScore) {
        highScore = startingLevelValue;
        lcd.setCursor(0, 1);
        lcd.print("NEW HIGH SCORE!");

        for (int i = 0 ; i < EEPROM.length(); i++) {
          EEPROM.write(i, 0);
        }
        EEPROM.put(0, highScore);
      }
      else {
        lcd.setCursor(0, 1);
        lcd.print("Good try!");
      }

      int exitbuttonIsPressed = 0;

      while (exitbuttonIsPressed == 0) {
        int exitbuttonValue = analogRead(xPin);
        if (exitbuttonValue > 600) {
            exitbuttonIsPressed = 1;
        }
      }
      whereIAm = menu;
      lcd.clear();
    }
  }

  if (whereIAm == inInfo) {
    if (yValue < 400) {
      if (movedYSet == false) {
        showInInfo--;
        if (showInInfo < 0) {
            showInInfo = 3;
        }
        movedYSet = true;
        printTheInfo(showInInfo);
      }
    }
    else {
      if (yValue > 600) {
        if (movedYSet == false)
        {
          showInInfo++;
          if (showInInfo > 3) {
            showInInfo = 0;
          }
          movedYSet = true;
          printTheInfo(showInInfo);
        }
      }
      else {
        movedYSet = false;
      }
    }
    if (xValue > 800) {
        whereIAm = menu;
    }
  }

  if (whereIAm == menu) {
    if (xValue < 400) {
      if (movedX == false) {
        lcd.clear();
        arrowPozLin++;
        if (arrowPozLin == 1) {
          if (arrowPozCol == 0) {
            arrowPozCol = 0;
          }
          else {
            arrowPozCol = 9;
          }
        }
        else {
          arrowPozLin = 0;
          if (arrowPozCol == 0) {
            arrowPozCol = 0;
          }
          else {
            arrowPozCol = 6;
          }
        }
        movedX = true;
      }
    }
    else {
      if (xValue > 600) {
        if (movedX == false) {
          lcd.clear();
          arrowPozLin--;
          if (arrowPozLin < 0) {
            if (arrowPozCol == 0) {
                arrowPozCol = 0;
            }
            else {
                arrowPozCol = 9;
            }
            arrowPozLin = 1;
          }
          else {
            arrowPozLin = 0;
            if (arrowPozCol == 0) {
                arrowPozCol = 0;
            }
            else {
                arrowPozCol = 6;
            }
          }
          movedX = true;
        }
      }
      else {
        movedX = false;
      }
    }
    if (yValue < 400) {
      if (movedY == false) {
        if (arrowPozLin == 0) {
          lcd.clear();
          col--;
          if (col < 0) {
            col = 1;
          }
          arrowPozCol = collumnArrow[col];
        }
        else {
          lcd.clear();
          if (arrowPozCol == 0) {
            arrowPozCol = 9;
          }
          else {
            arrowPozCol = 0;
          }
        }
        movedY = true;
      }
    }
    else {
      if (yValue > 600) {
        if (movedY == false) {
          if (arrowPozLin == 0) {
            lcd.clear();
            col++;
            if (col > 1) {
                col = 0;
            }
            arrowPozCol = collumnArrow[col];
          }
          else {
            lcd.clear();
            if (arrowPozCol == 0) {
                arrowPozCol = 9;
            }
            else {
                arrowPozCol = 0;
            }
          }
          movedY = true;
        }
      }
      else {
        movedY = false;
      }
    }
    if (millis() - animation > 1500) {
      if (millis() - animation > 3000) {
        animation = millis();
      }
      for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
          lc.setLed(0, row, col, matrixStartGame1[row][col]);
        }
      }
    }
    else {
      for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
          lc.setLed(0, row, col, matrixStartGame2[row][col]);
        }
      }
    }

    printArrow(arrowPozCol, arrowPozLin);
    lcd.setCursor(1, 0);
    lcd.print("Start");
    lcd.setCursor(7, 0);
    lcd.print("HighScore");
    lcd.setCursor(1, 1);
    lcd.print("Settings");
    lcd.setCursor(10, 1);
    lcd.print("Info");
  }
}
