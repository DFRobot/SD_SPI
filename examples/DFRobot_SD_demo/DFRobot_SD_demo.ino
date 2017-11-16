/*
 SD card read/write
 created   Nov 2017

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD_SPI.h>

#ifdef __AVR__
uint8_t       pin_cs = 3;
#else
uint8_t       pin_cs = D3;
#endif

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println();
  Serial.println();
  if (!SD.begin(pin_cs)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  Serial.print("    file name:");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  SD.remove("test.txt");
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
    if(myFile) {
      Serial.println("file still have value");
    } else {
      Serial.println("file closed");
    }
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.print("    file name:");
    Serial.println(myFile.name());
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  myFile = SD.open("Floder/nText.txt");
  if (myFile) {
    Serial.println("Floder/nText.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Floder/nText.txt");
  }

  Serial.println("\ncreat direction");
  SD.mkdir("T1");
  SD.rmdir("T1");
  myFile = SD.open("T1");
  if(myFile) {
    Serial.println("del direction faild");
  } else {
    Serial.println("del direction successful");
  }
}

void loop() {
  // nothing happens after setup
}
