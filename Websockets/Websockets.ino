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


#include <WSClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>
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
    void subscribe(String channel);
    const char* listen(String channel, String event);
//    std::vector<PusherChannel> channels;
    int channelIndex = 0;
};

const String Pusher::VERSION = "0.0.1";
const String Pusher::PROTOCOL = "7";
const String Pusher::AGENT = "pusher-ws-arduino";

const char* SUBSCRIPTION_SUCCEEDED = "pusher_internal:subscription_succeeded";
const char* CONNECTION_ESTABLISHED ="pusher:connection_established";

Pusher::Pusher(String k) : key(k) {
    path = "/app/" + key+ "?client="+ AGENT+ "&version="+VERSION+"&protocol=" + PROTOCOL;
    url = host + path;
}


void Pusher::connectViaEthernet(){
    Serial.println(F("connecting.."));
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
        Serial.println(F("Handshake successful"));
    }
    else {
        Serial.println(F("Handshake failed."));
        while(1) {
            // Hang on failure
        }
    }


}

void Pusher::subscribe(String channelName)
{
    
    StaticJsonBuffer<200> jsonBuffer;
    
    JsonObject& root = jsonBuffer.createObject();
    root["event"] = "pusher:subscribe";
    JsonObject& data = root.createNestedObject("data");
    data["channel"] = channelName.c_str();
    
    char buffer[200];
    
    root.printTo(buffer, sizeof(buffer));
    
    ws.sendData(buffer);
    Serial.println(F("Subscribed"));
}




const char* Pusher::listen(String channel, String event){
    String data;
    data = ws.getData();
    
    if (data.length() > 0) {
        
        StaticJsonBuffer<200> jsonBuffer;
        
        JsonObject& root = jsonBuffer.parseObject(&data[0]);
        
        const char* channelName = root["channel"];
        const char* eventName = root["event"];
        const char* eventData = root["data"];
        
        if (!strcmp(&channel[0], channelName) && !strcmp(&event[0], eventName)){
            return eventData;
        }

        
    } else {
        return NULL;
    }
}




//------ ARDUINO SHIZZZZ ---------



EthernetClient client;
byte mac[] = {
    0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };

Pusher pusher("112bcc871ae79ea6227a");

const int LED = 13;
const char* OFF = "off";
const char* ON = "on";

void setup() {
    
    pinMode(LED, OUTPUT);
    
    Serial.begin(9600);

    Ethernet.begin(mac);
    Serial.println(Ethernet.localIP());
    delay(1000);
    
    pusher.connect(client);
    pusher.subscribe("testing");
    
}


void loop() {


    const char* eventData = pusher.listen("testing", "new_event");
    
    if (eventData != NULL)
        Serial.println(eventData);
    
    
}




















