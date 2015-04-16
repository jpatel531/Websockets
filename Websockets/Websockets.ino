///
/// @mainpage	Websockets
///
/// @details	Playing about with websockets
/// @n
/// @n
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Jamie Patel
/// @author		Jamie Patel
/// @date		15/04/2015 22:39
/// @version	<#version#>
///
/// @copyright	(c) Jamie Patel, 2015
/// @copyright	Licence
///
/// @see		ReadMe.txt for references
///


///
/// @file		Websockets.ino
/// @brief		Main sketch
///
/// @details	<#details#>
/// @n @a		Developed with [embedXcode+](http://embedXcode.weebly.com)
///
/// @author		Jamie Patel
/// @author		Jamie Patel
/// @date		15/04/2015 22:39
/// @version	<#version#>
///
/// @copyright	(c) Jamie Patel, 2015
/// @copyright	Licence
///
/// @see		ReadMe.txt for references
/// @n
///


// Core library for code-sense - IDE-based
#if defined(WIRING) // Wiring specific
#include "Wiring.h"
#elif defined(MAPLE_IDE) // Maple specific
#include "WProgram.h"
#elif defined(ROBOTIS) // Robotis specific
#include "libpandora_types.h"
#include "pandora.h"
#elif defined(MPIDE) // chipKIT specific
#include "WProgram.h"
#elif defined(DIGISPARK) // Digispark specific
#include "Arduino.h"
#elif defined(ENERGIA) // LaunchPad specific
#include "Energia.h"
#elif defined(LITTLEROBOTFRIENDS) // LittleRobotFriends specific
#include "LRF.h"
#elif defined(MICRODUINO) // Microduino specific
#include "Arduino.h"
#elif defined(TEENSYDUINO) // Teensy specific
#include "Arduino.h"
#elif defined(REDBEARLAB) // RedBearLab specific
#include "Arduino.h"
#elif defined(RFDUINO) // RFduino specific
#include "Arduino.h"
#elif defined(SPARK) // Spark specific
#include "application.h"
#elif defined(ESP8266) // ESP8266 specific
#include "Arduino.h"
#elif defined(ARDUINO) // Arduino 1.0 and 1.5 specific
#include "Arduino.h"
#else // error
#error Platform not defined
#endif // end IDE

// Include application, user and local libraries


// Prototypes


// Define variables and constants


/*
 Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <Ethernet.h>
#include <SPI.h>
#include <WebSocketClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "192.168.0.5:4567";
WebSocketClient client;
IPAddress ip(192, 168, 0, 177);
char path[] = "/";
int port = 80;

void dataArrived(WebSocketClient client, String data) {
    Serial.println("Data Arrived: " + data);
}

void setup() {
    Serial.begin(9600);
    Ethernet.begin(mac);
    
    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0) {
        Serial.println("Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, ip);
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
    Serial.println("connecting...");
    
    Serial.println("yolo");
    if (client.connect(server, path, port)) {
        Serial.println("connected to ws server");
    } else {
        Serial.println("failed to connect");
    }
    
    client.setDataArrivedDelegate(dataArrived);
    delay(3000);
    client.send("Hello World!");
}

void loop() {
    client.monitor();
}
