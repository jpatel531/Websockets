#include <WSClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WSClient.h>
#include <PusherWSArduino.h>


EthernetClient client;
byte mac[] = {
    0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };

Pusher pusher("112bcc871ae79ea6227a");

void setup() {
        
    Serial.begin(9600);

    Ethernet.begin(mac);
    delay(1000);
    
    pusher.connect(client);
    pusher.subscribe("testing");
    
}


void loop() {

  
    const char* eventData = pusher.listen("testing", "new_event");
    
    if (eventData != NULL)
    {
        Serial.println(eventData);
    }
    
}




















