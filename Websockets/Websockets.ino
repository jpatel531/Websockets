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

class Pusher {
private:
    EthernetClient *ethernet;
    WSClient ws;
    String host = "ws.pusherapp.com";
    String path;
    String url;
    static const String VERSION;
    static const String PROTOCOL;
    static const String AGENT;
    int port = 80;
    void connectViaEthernet();
public:
    String key;
    Pusher (String);
    bool connected;
    void connect(EthernetClient &client);
//    Channel subscribe(String channel);
};

const String Pusher::VERSION = "0.0.1";
const String Pusher::PROTOCOL = "7";
const String Pusher::AGENT = "pusher-ws-arduino";

Pusher::Pusher(String k) : key(k) {
    path = "/app/" + key+ "?client="+ AGENT+ "&version="+VERSION+"&protocol=" + PROTOCOL;
    url = host + path;
}



void Pusher::connectViaEthernet(){
    Serial.println("connecting..");
    if (ethernet->connect(host.c_str(), port)) {
        Serial.println(ethernet->connected());
        Serial.println(F("Connected"));
    }
    else {
        Serial.println(F("Connection failed."));
        delay(2000);
        connectViaEthernet();
    }
}


void Pusher::connect(EthernetClient &client){
    ethernet = &client;
    connectViaEthernet();

    delay(1000);
    
    ws.path = &path[0];
    ws.host = &host[0];
//    
//    websocket.path = "/app/112bcc871ae79ea6227?client=pusher-ws-arduino&version=0.0.1&protocol=7";
//    websocket.host = "ws.pusherapp.com";
    
    //    Serial.flush();
    if (ws.handshake(client)) {
        Serial.println("Handshake successful");
    }
    else {
        Serial.println("Handshake failed.");
        while(1) {
            // Hang on failure
        }
    }

    

}

//void Pusher::subscribe(String channel){

//}

// Ethernet Configuration
EthernetClient client;
byte mac[] = {
    0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };


//IPAddress server(174,129,224,73);
char server[] = "ws.pusherapp.com";

// Websocket initialization
//WSClient websocket;

Pusher pusher("112bcc871ae79ea6227");

void setup() {
    
    
    Serial.begin(9600);
    
    Serial.println(F("Demo example on WSClient usage"));
    Ethernet.begin(mac); // initialize ethernet
    Serial.println(Ethernet.localIP()); // printout IP address for debug purposes
    delay(1000); // this is arduino baby ;-)
    
    
    pusher.connect(client);
    

    
    
}


void loop() {
//    String data;
//    
//    if (client.connected()) {
//        data = websocket.getData();
//        if (data.length() > 0) {
//            Serial.print("Received data: ");
//            Serial.println(data);
//        }
//        
//        Serial.println(F("")); Serial.println(F("Sending Data"));
//        websocket.sendData("{\"event\":\"pusher:subscribe\"}");
//    } else {
//        Serial.println("Client disconnected.");
//        while (1) {
//            // Hang on disconnect.
//        }
//    }
//    
//    delay(3000);  // wait to fully let the client disconnect
    
}