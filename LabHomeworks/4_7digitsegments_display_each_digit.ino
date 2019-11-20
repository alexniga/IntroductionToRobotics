// declare all the joystick pins
const int pinSW = A2; // digital pin connected to switch output
const int pinX = A0; // A0 - analog pin connected to X output
const int pinY = A1; // A1 - analog pin connected to Y output

// declare all the segments pins
const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;

// dp on or off
int dpState = LOW;

// states of the button press
int swState = LOW;
int lastSwState = LOW;
int btnValue = 0;
int switchValue;
int xValue = 0;
int yValue = 0;
int dpValue = 0;

bool joyMoved = false;
int digit = 0;
int minThreshold= 400;
int maxThreshold= 600;

// store the pins in an array for easier access
// segments array, similar to before

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// digits array, to switch between them easily

int digits[noOfDisplays] = {
  pinD1, pinD2, pinD3, pinD4
 };   
 
byte digitMatrix[noOfDigits + 1][segSize] = {
//  a  b  c  d  e  f  g
  { 1, 1, 1, 1, 1, 1, 0, 0},  // 0
  { 0, 1, 1, 0, 0, 0, 0, 0},  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0},  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0},  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0},  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0},  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0},  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0},  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0},  // 8
  { 1, 1, 1, 1, 0, 1, 1, 0},  // 9
  { 0, 0, 0, 0, 0, 0, 0, 1}   // .
};

// activate the display no. received as param
void showDigit(int num) {
  for (int i = 0; i < noOfDisplays; i++) {
  digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[num], LOW);
}

void setup() {
  // initialize all the pins
  for (int i = 0; i < segSize - 1; i++)
  {
  pinMode(segments[i], OUTPUT);  
  }
  for (int i = 0; i < noOfDisplays; i++)
  {
  pinMode(digits[i], OUTPUT);  
  }
  pinMode(pinSW, INPUT_PULLUP);
  Serial.begin(9600);
  displayNumber(digit, dpState); // initial value displayed. Choose any value
}

void loop() {
  yValue = analogRead(pinY);
   Serial.println(yValue);
  btnValue = digitalRead(pinSW);
  Serial.println(btnValue);

  if (btnValue == 1)
{
 // On Ox axis, if the value is lower than a chosen min threshold, then
 // decrease by 1 the digit value.
  if (yValue < minThreshold && joyMoved == false) {
  if (digit > 0) {
      digit--;
  } else {
      digit = 9;
  }
  joyMoved = true;
  }

 // On Ox axis, if the value is bigger than a chosen max threshold, then
 // increase by 1 the digit value
  if (yValue > maxThreshold && joyMoved == false) {
  if (digit < 9) {
      digit++;
  } else {
      digit = 0;
  }
  joyMoved = true;
  }

  if (yValue >= minThreshold && yValue <= maxThreshold) {
  joyMoved = false;
  }

  // simple state change detector. Ideally, use debounce.
  swState = digitalRead(pinSW);
  if (swState !=  lastSwState) {
  if (swState == LOW) {
      dpState = !dpState;
  }
  }
  lastSwState = swState;
 
  displayNumber(digit, dpState);
  delay(1);
}

else
{
  xValue = analogRead(pinX);
  Serial.print(" X AXIS: ");
  Serial.println(xValue);

    if (xValue < minThreshold && joyMoved == false) {
  if (dpValue > 0) {
      dpValue--;
  } else {
      dpValue = 3;
  }
  joyMoved = true;
  }

 // On Ox axis, if the value is bigger than a chosen max threshold, then
 // increase by 1 the digit value
  if (xValue > maxThreshold && joyMoved == false) {
  if (dpValue < 3) {
      dpValue++;
  } else {
      dpValue = 0;
  }
  joyMoved = true;
  }

  if (xValue >= minThreshold && xValue <= maxThreshold) {
  joyMoved = false;
  }

  // simple state change detector. Ideally, use debounce.
  swState = digitalRead(pinSW);
  if (swState !=  lastSwState) {
  if (swState == LOW) {
      dpState = !dpState;
  }
  }
  lastSwState = swState;

  showDigit(dpValue);
  displayDot(dpValue, dpState);
  delay(1);
}

}

///

void displayNumber(byte digit, byte decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
  digitalWrite(segments[i], digitMatrix[digit][i]);
  }

  // write the decimalPoint to DP pin
  digitalWrite(segments[segSize - 1], decimalPoint);
}

void displayDot(byte dpValue, byte decimalPoint){

 // digitalWrite(segments[], digitMatrix[digit][i]);
  digitalWrite(segments[segSize - 1], HIGH);
}
