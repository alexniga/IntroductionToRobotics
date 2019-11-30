#include <LiquidCrystal.h>

const int RSPin = 12;
const int EPin = 11;
const int D4Pin = 5;
const int D5Pin = 4;
const int D6Pin = 3;
const int D7Pin = 2;

const int buttonPin = 10;
const int xPin = A0;
const int yPin = A1;
int buttonValue = 0;
int xValue = 0;
int yValue = 0;

const int menu = 1;
const int inStart = 2;
const int inHighScore = 3;
const int inSettings = 4;
int whereIAm = 1;
int firstClear;

LiquidCrystal lcd(RSPin, EPin, D4Pin, D5Pin, D6Pin, D7Pin);

int lineArrow[2] = {0, 1};
int collumnArrow[2] = {0, 6};
int arrowPozCol = collumnArrow[0];
int arrowPozLin = lineArrow[0];
int col = 1;
// (col, lin)
// (0, 0) -> start
// (6, 0) -> HighScore
// (3, 1) -> Settings

int startingLevelSettings = 0;
int startingLevelValue = 0;
int highScore = 0;

long long lastChange = 0;
long long endGameTimer = 0;

boolean movedX = false;
boolean movedY = false;
boolean movedYSet = false;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void printArrow(int a, int b)
{
  lcd.setCursor(a, b);
  lcd.print(">");
}

void printLevelSetTo(int level)
{
  lcd.print(".");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set the level");
  lcd.setCursor(0, 1); lcd.print("<");
  lcd.setCursor(15, 1); lcd.print(">");
  lcd.setCursor(7, 1); lcd.print(level);
}

void loop()
{
  buttonValue = digitalRead(buttonPin);
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  if (buttonValue == 0 && whereIAm == menu)
  {
    firstClear = 0;
    if (arrowPozLin == 0 && arrowPozCol == 0)
    {
      whereIAm = inStart; startingLevelValue = startingLevelSettings; lastChange = millis(); endGameTimer = lastChange;
    }
    if (arrowPozLin == 0 && arrowPozCol == 6)
    {
      whereIAm = inHighScore;
    }
    else if (arrowPozLin == 1 && arrowPozCol == 3)
    {
      printLevelSetTo(startingLevelSettings);
      whereIAm = inSettings;
    }
  }

  Serial.println(whereIAm);

  if (whereIAm == inSettings)
  {
    if (yValue < 400)
    {
      if (movedYSet == false)
      {
        startingLevelSettings--;
        if (startingLevelSettings < 0)
          startingLevelSettings = 0;
        movedYSet = true;
        printLevelSetTo(startingLevelSettings);
      }
    }
    else
    {
      if (yValue > 600)
      {
        if (movedYSet == false)
        {
          startingLevelSettings++;
          if (startingLevelSettings > 5)
            startingLevelSettings = 5;
          movedYSet = true;
          printLevelSetTo(startingLevelSettings);
        }
      }
      else movedYSet = false;
    }
    if (xValue > 800)
      whereIAm = menu;
  }

  if (whereIAm == inHighScore)
  {
    if (firstClear == 0)
    { lcd.clear();
      firstClear = 1;
    }
    lcd.setCursor(1, 0);
    lcd.print("HighScore = "); lcd.print(highScore);
    if (xValue > 800)
      whereIAm = menu;
  }

  if (whereIAm == inStart)
  {
    if (firstClear == 0)
    {
      lcd.clear();
      firstClear = 1;
    }
    lcd.setCursor(1, 0);
    lcd.print("Lives: 3");
    lcd.setCursor(1, 1);
    lcd.print("Score = "); lcd.print(startingLevelValue * 3);

    if (millis() - lastChange >= 2000)
    {
      lcd.clear();
      startingLevelValue++;
      lastChange = millis();
    }

    if (millis() - endGameTimer >= 10000)
    {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Game Over!");
      delay(2000);
      whereIAm = menu;
      highScore = startingLevelValue * 3;
      lcd.clear();

    }

  }
  if (whereIAm == menu)
  {
    if (xValue < 400)
    {
      if (movedX == false)
      {
        lcd.clear();
        arrowPozLin++;
        if (arrowPozLin == 1)
          arrowPozCol = 3;
        else
        {
          arrowPozLin = 0;
          arrowPozCol = 0;
        }
        movedX = true;
      }
    }
    else
    {
      if (xValue > 600)
      {
        if (movedX == false)
        { lcd.clear();
          arrowPozLin--;
          if (arrowPozLin < 0)
          {
            arrowPozCol = 3;
            arrowPozLin = 1;
          }
          else
          {
            arrowPozLin = 0;
            arrowPozCol = 0;
          }
          movedX = true;
        }
      }
      else
      {
        movedX = false;
      }
    }
    if (yValue < 400)
    {
      if (movedY == false)
      { if (arrowPozLin == 0)
        {
          lcd.clear();
          col--;
          if (col < 0)
            col = 1;
          arrowPozCol = collumnArrow[col];
        }
        movedY = true;
      }
    }
    else
    {
      if (yValue > 600)
      {
        if (movedY == false)
        {
          if (arrowPozLin == 0)
          {
            lcd.clear();
            col++;
            if (col > 1)
              col = 0;
            arrowPozCol = collumnArrow[col];
          }
          movedY = true;
        }
      }
      else
      {
        movedY = false;
      }
    }

    printArrow(arrowPozCol, arrowPozLin);
    lcd.setCursor(1, 0);
    lcd.print("Start");
    lcd.setCursor(7, 0);
    lcd.print("HighScore");
    lcd.setCursor(4, 1);
    lcd.print("Settings");
  }
}
