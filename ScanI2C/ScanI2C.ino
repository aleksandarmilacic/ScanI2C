/*
 Name:		ScanI2C.ino
 Created:	3/24/2024 9:13:39 PM
 Author:	Aleksandar
*/

#include <Wire.h>

void setup() {
    Wire.begin(); // Initialize the I2C bus
    Serial.begin(9600); // Start serial communication at 9600 baud rate
    while (!Serial); // Wait for serial port to connect
    Serial.println("\nI2C Scanner");
}

void loop() {
    byte error, address;
    int nDevices = 0;

    Serial.println("Scanning...");

    for (address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Serial.print("Checking address:");
        Serial.println(address);
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println("  !");
            nDevices++;
        }
        else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16) {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    }
    else {
        Serial.println("done\n");
    }
    delay(5000); // Wait 5 seconds for the next scan
}
