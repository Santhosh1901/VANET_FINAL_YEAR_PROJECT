// NodeMCU Coding

#include <SPI.h> // for SPI communication

#include <nRF24L01.h>

#include <RF24.h>

RF24 radio(4,2); // CE, CSN

const uint64_t rAddress1 = {0x7878787878LL};
const uint64_t rAddress2 = {0xB3B4B5B6CDLL};  
const uint64_t rAddress3 = {0xB3B4B5B6F1LL}; 
void setup() {
Serial.begin(9600);

radio.begin();

radio.openWritingPipe(rAddress3);
radio.openReadingPipe(0,rAddress1);
radio.openReadingPipe(1,rAddress2);
radio.setPALevel(RF24_PA_MIN);

radio.stopListening();

}

void loop() {

char text1[] = "NodeMCU"; // you can customize this text to your wish

radio.write(&text1, sizeof(text1));
delay(5);
byte pipenum;
radio.startListening();
if (radio.available(&pipenum) || !radio.available()) { // if nrf has any incoming data
if (pipenum == 0)
{
   char text2[100] = "";
   radio.read(&text2, sizeof(text2));
   delay(5);
   Serial.println(pipenum);
   Serial.println(text2);
   delay(5);
}
else 
{
  char text3[100] = "";
  radio.read(&text3, sizeof(text3));
  delay(5);
  Serial.println(pipenum);
  Serial.println(text3);
  delay(5);
}
radio.stopListening();
}
}
