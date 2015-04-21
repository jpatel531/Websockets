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
#include <ArduinoJson.h>
#include <Ethernet.h>
#include <SPI.h>
#include <WSClient.h>
#include <vector>
#include <functional>


typedef void (*EventHandler)(String data);

class PusherChannel {
public:
    PusherChannel (String);
    String name;
    bool subscribed;
    void bind(String, EventHandler);
};

PusherChannel::PusherChannel(String n): name(n){}


void PusherChannel::bind(String event, EventHandler eventHandler){
    
}



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
    PusherChannel subscribe(String channel);
    void listen();
    std::vector<PusherChannel> channels;
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
    
    Serial.flush();
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

PusherChannel Pusher::subscribe(String channel)
{
    
    StaticJsonBuffer<200> jsonBuffer;
    
    JsonObject& root = jsonBuffer.createObject();
    root["event"] = "pusher:subscribe";
    JsonObject& data = root.createNestedObject("data");
    data["channel"] = channel.c_str();
    
    char buffer[256];
    
    root.printTo(buffer, sizeof(buffer));
    
    PusherChannel newChannel(channel);
    
    channels.push_back(newChannel);
    
    Serial.println(F("")); Serial.println(F("Sending Data"));
    ws.sendData(buffer);
    
    return newChannel;
}
                
void Pusher::listen(){
    while(true){
        String data;
        data = ws.getData();
        if (data.length() > 0) {
            
            StaticJsonBuffer<200> jsonBuffer;
            
            JsonObject& root = jsonBuffer.parseObject(&data[0]);
            
            if (!root.success())
            {
                Serial.println("parseObject() failed");
                return;
            }
            
            const char* event = root["event"];
            
        
            if (!strcmp(event, "pusher_internal:subscription_succeeded")){
                const char* channelSubscribed = root["channel"];
                
                for (std::vector<PusherChannel>::iterator itr = channels.begin(); itr != channels.end(); itr++ ){
                    String channelName = itr->name;
                    if (!(strcmp(channelSubscribed, &channelName[0])))
                        itr->subscribed = true;
                }
                
                
                Serial.println(event);
                Serial.println("Yes");
            } else {
                Serial.println(event);
                Serial.println("nope");
            }
            
            
            
        }
    }
}
            

// Ethernet Configuration
EthernetClient client;
byte mac[] = {
    0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };


//IPAddress server(174,129,224,73);
char server[] = "ws.pusherapp.com";

// Websocket initialization
//WSClient websocket;

Pusher pusher("112bcc871ae79ea6227a");

void logEvent(String data){
    Serial.println(data);
}

void setup() {
    
    
    Serial.begin(9600);
    
    Serial.println(F("Demo example on WSClient usage"));
    Ethernet.begin(mac); // initialize ethernet
    Serial.println(Ethernet.localIP()); // printout IP address for debug purposes
    delay(1000); // this is arduino baby ;-)
    
    
    pusher.connect(client);
    

    PusherChannel testingChannel = pusher.subscribe("testing");
    
    testingChannel.bind("new_event", logEvent);
    
}


void loop() {
    pusher.listen();
}