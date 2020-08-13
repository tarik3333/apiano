    
int piezo1;
int piezo2;
int piezo3;
int piezo4;
int piezo5;
#define bpm 96

#define noteGapPercentage 10
#define beatDuration (60.0 / bpm) * 1000000L
#define speakerPin 12
#define noteGap beatDuration * (noteGapPercentage / 100.0)

  
void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(speakerPin,OUTPUT);
}


void playNote(uint8_t keyNumber, uint8_t noteType) {
  long halfPeriod = getPeriodForKey(keyNumber) / 2;
  long noteDuration = beatDuration * (4.0 / noteType);
  long elapsed = 0;

 
  while(halfPeriod > 0 && elapsed < (noteDuration - noteGap)) {
    digitalWrite(speakerPin, HIGH);
    wait(halfPeriod);
    digitalWrite(speakerPin, LOW);
    wait(halfPeriod);
    elapsed += halfPeriod * 2;
  }

  wait(noteDuration - elapsed);
}


 
long getPeriodForKey(uint8_t keyNumber) {
  
  if(keyNumber >= 1 && keyNumber <= 88) {
    return 1000000L / (pow(2.0, (keyNumber - 49.0) / 12.0) * 440.0);
  }

  
  return 0;
}


void wait(long us) {
  delay(us / 1000);
  delayMicroseconds(us % 1000);
}

void loop() {
  piezo1 = digitalRead(2);
  piezo2 = digitalRead(3);
  piezo3 = digitalRead(4);
  piezo4 = digitalRead(5);
  piezo5 = digitalRead(6);   
  if(piezo1){
    playNote(88,4);
  }
  if(piezo2){
    playNote(42,4);
  }
  if(piezo3){
    playNote(44,4);
  }
  if(piezo4){
    playNote(40,4);
  }
  if(piezo5){
    playNote(39,4);
  }
    
}
