const uint8_t xPin = A0;
const uint8_t yPin = A1;
const uint8_t joyButton_pushPin = A2;

int xValue;
int yValue;
int minTreshold = 400;
int maxTreshold = 600;
bool pushButtonValue;
bool joyButton_moved = false;
uint32_t joyButton_lastDebounce = 0;
bool joyButton_lastPushValue;
uint32_t joyButton_pushDebounceInterval = 10;

//4 digit 7 segment display

const uint8_t pinA = 12;
const uint8_t pinB = 8;
const uint8_t pinC = 5;
const uint8_t pinD = 3;
const uint8_t pinE = 2;
const uint8_t pinF = 11;
const uint8_t pinG = 6;
const uint8_t pinDP = 4;
const uint8_t pinD1 = 7;
const uint8_t pinD2 = 9;
const uint8_t pinD3 = 10;
const uint8_t pinD4 = 13;
const uint8_t segSize = 8;
const uint8_t noOfDisplays = 4;
const uint8_t noOfDigits = 10;
bool dpState;

// segments array, similar to before
uint8_t segments[segSize] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP };

// digits array, to switch between them easily
uint8_t digits[noOfDisplays] = { pinD1, pinD2, pinD3, pinD4 };

uint8_t currentDigitsValues[noOfDisplays] = { 0, 0, 0, 0 };

uint8_t currentDigit = 0;
uint32_t flushInterval = 1;
uint32_t lastFlush = 0;
uint8_t selectedDigit = noOfDisplays;
uint8_t digitToEdit = noOfDisplays - 1;

byte digitMatrix[noOfDigits][segSize - 1] = {
//   a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayDigit(int num, byte digit, byte decimalPoint) {
  showDigit(num);
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}

// activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

// clears the display no. received as param
void clearDigit(int num) {
  showDigit(num);
  for (uint8_t i = 0; i < segSize; ++i) {
    digitalWrite(segments[i], LOW);
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(joyButton_pushPin, INPUT_PULLUP);
  for (uint8_t i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  for (uint8_t i = 0; i < noOfDisplays; i++) {
    pinMode(digits[i], OUTPUT);
  }
  Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop()
{
  if (selectedDigit == noOfDisplays)
  {
    //no digit is selected => blinking mode
    xValue = analogRead(xPin);
    if (xValue < minTreshold && joyButton_moved == false)
    {
      //change digit to the left
      if (digitToEdit > 0)
        --digitToEdit;
      else
        digitToEdit = noOfDisplays - 1;
      joyButton_moved = true;
    }

    if (xValue > maxTreshold&& joyButton_moved == false)
    {
      //change digit to the right
      if (digitToEdit < noOfDisplays - 1)
        ++digitToEdit;
      else
        digitToEdit = 0;
      joyButton_moved = true;
    }

    if (xValue >= minTreshold && xValue <= maxTreshold) //idle joybutton position
      joyButton_moved = false;

    if (millis() - lastFlush >= flushInterval)
    {
      //use the display digits (this is the alternative to using delay()
      displayDigit(currentDigit, currentDigitsValues[currentDigit], false);
      lastFlush = millis();
      if (currentDigit == noOfDisplays - 1)
        currentDigit = 0;
      else
        ++currentDigit;
    }
  }
  else {
    //some digit is selected
    yValue = analogRead(yPin);

    if (yValue < minTreshold && joyButton_moved == false)
    {
      //decrease selected digit's value
      if (currentDigitsValues[selectedDigit] > 0)
        --currentDigitsValues[selectedDigit];
      else
        currentDigitsValues[selectedDigit] = noOfDigits - 1;
      joyButton_moved = true;
    }

    if (yValue > maxTreshold&& joyButton_moved == false)
    {
      //incresease selected digit's value
      if (currentDigitsValues[selectedDigit] < noOfDigits - 1)
        ++currentDigitsValues[selectedDigit];
      else
        currentDigitsValues[selectedDigit] = 0;
      joyButton_moved = true;
    }

    if (yValue >= minTreshold && yValue <= maxTreshold) //idle joybutton position
      joyButton_moved = false;

    if (millis() - lastFlush >= flushInterval)
    {
      //use the display digits 
      if (currentDigit == selectedDigit)
        displayDigit(currentDigit, currentDigitsValues[currentDigit], true);
      else
        displayDigit(currentDigit, currentDigitsValues[currentDigit], false);

      lastFlush = millis();
      if (currentDigit == noOfDisplays - 1)
        currentDigit = 0;
      else
        ++currentDigit;
    }
  }

  if(millis() - joyButton_lastDebounce >= joyButton_pushDebounceInterval)
  {
    joyButton_lastDebounce = millis();
    pushButtonValue = !digitalRead(joyButton_pushPin);

    if (pushButtonValue != joyButton_lastPushValue)
    {
      //check for pushes of the joybutton
      if (pushButtonValue == true)
      {
        Serial.println(pushButtonValue);
        if (selectedDigit == noOfDisplays)
        { //if there is no digit selected, select the current
          selectedDigit = digitToEdit;
          digitToEdit = noOfDisplays;
        }
        else
        {
          //otherwise, deselect the selected digit
          digitToEdit = selectedDigit;
          selectedDigit = noOfDisplays;
        }
      }
    joyButton_lastPushValue = pushButtonValue;
    }
  }
}
