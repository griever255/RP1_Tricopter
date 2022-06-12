#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
void setup() {
SPI.begin();

Serial.begin(9600);
while(!Serial);
radio.begin();
radio.setDataRate( RF24_250KBPS );
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MIN);
radio.printPrettyDetails();
radio.startListening();
}
void loop() {
if (radio.available()) {
int trimValue;
radio.read(&trimValue, sizeof(trimValue));
Serial.println(trimValue);
}
}