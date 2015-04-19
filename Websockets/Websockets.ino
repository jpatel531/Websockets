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


#include <Base64.h>
#include <global.h>
#include <MD5.h>
#include <sha1.h>
#include <WSClient.h>

#include <Ethernet.h>
#include <SPI.h>
#include <WSClient.h>

// Ethernet Configuration
EthernetClient client;
byte mac[] = {
    0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };

IPAddress server(174,129,224,73);

// Websocket initialization
WSClient websocket;

void connectToServer(EthernetClient& client){
    Serial.println("connecting..");
    if (client.connect(server, 80)) {
        Serial.println(client.connected());
        Serial.println("Connected");
    }
    else {
        Serial.println("Connection failed.");
        delay(2000);
        connectToServer(client);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println(F("Demo example on WSClient usage"));
    Ethernet.begin(mac); // initialize ethernet
    Serial.println(Ethernet.localIP()); // printout IP address for debug purposes
    delay(1000); // this is arduino baby ;-)
    
    // Connect and test websocket server connectivity
    
    connectToServer(client);
    
    // Define path and host for Handshaking with the server
    websocket.path = "/";
    websocket.host = "echo.websocket.org";
    
    if (websocket.handshake(client)) {
        Serial.println("Handshake successful");
    }
    else {
        Serial.println("Handshake failed.");
        while(1) {
            // Hang on failure
        }
    }
    
}


void loop() {
    String data;
    
    if (client.connected()) {
        data = websocket.getData();
        if (data.length() > 0) {
            Serial.print("Received data: ");
            Serial.println(data);
        }
        
        Serial.println(F("")); Serial.println(F("Sending Data"));
        websocket.sendData("echo test");
    } else {
        Serial.println("Client disconnected.");
        while (1) {
            // Hang on disconnect.
        }
    }
    
    delay(3000);  // wait to fully let the client disconnect
    
}