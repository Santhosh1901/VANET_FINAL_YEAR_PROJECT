#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications.
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {  //   Initialize SD card Module
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("void.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Final year project on Inter vehicle communication on VANET");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening void.txt");
  }

  
}

void loop() {
  // nothing happens after setup
}
