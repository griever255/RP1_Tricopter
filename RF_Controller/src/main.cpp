#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

int TRIM_PIN = 14;

void setup() {

  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(TRIM_PIN, INPUT);
}

int trimValue;

void loop() {
  trimValue = analogRead(TRIM_PIN);
  trimValue = map(trimValue, 0, 1023, 1500, 1600);
  radio.write(&trimValue, sizeof(trimValue));
  delay(1000);
}