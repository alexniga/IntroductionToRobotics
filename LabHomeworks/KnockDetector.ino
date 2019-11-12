const int buttonPin = 2;
const int ledPin = 13;
const int passiveBuzzerPin = A0;

const int activeBuzzerPin = 8;
const int debounceTime = 50;
const int startMusicThreshold = 50;
const int waitingTime = 5000;

const int noteLen = 8; // nr of notes
int currentNote = 0; // which note should I play

int pauseBetweenNotes;
int lastNoteTime;
int noteDuration;

int lastChange = 0;
bool lastState = LOW;
bool newState;
bool astReadState = LOW;
bool newReadState;
bool musicIsPlaying = false;

// notes in the melody:
int melody[noteLen] = {262, 196, 196, 220, 196, 0, 247, 262};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[noteLen] = {4, 8, 8, 4, 4, 4, 4, 4};

void setup() 
{
  Serial.begin(9600);
  pinMode (buttonPin, INPUT_PULLUP);
  pinMode (ledPin, OUTPUT);
  pinMode (passiveBuzzerPin, INPUT);
  pinMode (activeBuzzerPin, OUTPUT);
  digitalWrite (ledPin,HIGH);
  //Serial.println (analogRead (passiveBuzzerPin));
}

void playMusic()
{
  if (millis() < lastNoteTime + pauseBetweenNotes) 
  {// wait more
    return;
   } 
  // stop the tone playing:
  noTone(activeBuzzerPin);
  // to calculate the note duration, take one second divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  noteDuration = 1000 / noteDurations[currentNote];
  tone(activeBuzzerPin, melody[currentNote], noteDuration);
  Serial.println ("Note");
  lastNoteTime = millis();

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  pauseBetweenNotes = noteDuration * 1.30;
  currentNote = (currentNote + 1) % noteLen;
}

void stopMusicListener() // checks if the music should be stopped
{
  newReadState = !digitalRead (buttonPin);
  //Serial.println (newReadState);
  if (lastReadState != newReadState) {
    lastChange = millis();
    lastReadState = newReadState;
  }
  if (millis() > lastChange + debounceTime)
  {
    newState = newReadState;
    if (lastState != newState)
    {
      lastChange = millis();
      if (newState == HIGH)
      {
        noTone (activeBuzzerPin);
        Serial.println ("Music stopped");
        digitalWrite (ledPin, HIGH);
        musicIsPlaying = false;
      }
      lastState = newState;
    }
  }
}

void loop() 
{
  if (musicIsPlaying) {
    //Serial.println ("Note");
    playMusic();
    stopMusicListener();
  }
  else {
    startMusicListener();
  }
}

void startMusicListener() 
{
  //Serial.println (analogRead (passiveBuzzerPin));
  int buzzer = analogRead (passiveBuzzerPin);
  Serial.println(buzzer);
  if (analogRead (passiveBuzzerPin) > startMusicThreshold) 
  {
    Serial.println(buzzer);
    lastNoteTime = millis();
    Serial.println ("Wait for the Music");
    digitalWrite (ledPin, LOW);
    musicIsPlaying = true;
    currentNote = 0;
    pauseBetweenNotes = waitingTime;
  }
}
