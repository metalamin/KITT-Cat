/*//////////////////// 
KIT Katt Bridge

Need the Software Serial Parity library
https://github.com/metalamin/SoftwareSerialPar

/////////////////////*/

#include <SoftwareSerialPar.h>

#define ledPin 13 // LED 
#define dataPin 8 // to IO pin
#define resetPin 2 // to Reset pin

SoftwareSerialPar mySerial(dataPin, dataPin); // same pin for RX and TX

const int bufferSize = 60;
int cardSpeed = 10752;      // Initial speed = Frecuency / 372 in the case for a 4Mhz reader
int interByteDelay = 200;   // Inter byte delay in microseconds
byte data[bufferSize];
int dataSize;

static byte ATR[14] = { 0x3B,0x83,0x00,0xAA,0xBB,0xCC };


void reset_change(){
  delay(500);
  pinMode(dataPin, OUTPUT);
  PutBytes(ATR,sizeof(ATR));
  pinMode(dataPin, INPUT_PULLUP);
}


void PutBytes(byte data[],int n){
  pinMode(dataPin, OUTPUT);
  for(uint16_t i=0; i < n; i++) {
    delayMicroseconds(interByteDelay);
    mySerial.write(data[i]);
  } 
  pinMode(dataPin, INPUT_PULLUP);
}

void setup()
{
  // Open serial communications
  Serial.begin(500000);
  Serial.setTimeout(1);
  
  mySerial.begin(cardSpeed); // set the data rate for the SmartCard
  attachInterrupt(digitalPinToInterrupt(resetPin),reset_change,RISING); //Interrupt for the ATR after the RESET
}

void loop() // run over and over
{
  
  if (mySerial.available()){
    Serial.write(mySerial.read());
  }

  if (Serial.available()){
    pinMode(dataPin, OUTPUT);       //Change the Data pin to OUTPUT mode
    dataSize=Serial.readBytes(data,bufferSize);
    PutBytes(data,dataSize);
    pinMode(dataPin, INPUT_PULLUP); //Change the Data pin to INPUT mode
  }
}

