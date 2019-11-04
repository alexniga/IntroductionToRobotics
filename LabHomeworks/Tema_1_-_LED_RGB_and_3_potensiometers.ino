// analog output
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;

//analog read
const int potPinRed = A0;
const int potPinGreen = A1;
const int potPinBlue = A2;

void setup() {
  // put your setup code here, to run once:

// led states
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
// potensiometers inputs 
  pinMode(potPinRed, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinBlue, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //red values
  int potValRed = analogRead(potPinRed);
  int ledValRed = map(potValRed, 0, 1023, 0, 255);
  // green values
  int potValGreen = analogRead(potPinGreen);
  int ledValGreen = map(potValGreen, 0, 1023, 0, 255);
  // blue values
  int potValBlue = analogRead(potPinBlue);
  int ledValBlue = map(potValBlue, 0, 1023, 0, 255);
  
  // write the intensity of the colors
  setColor(ledValRed, ledValGreen, ledValBlue);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
