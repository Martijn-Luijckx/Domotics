#include <Arduino.h>
#include <EthernetENC.h>
#include <MQTT.h>

byte mac[] = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xDD };
IPAddress ip(192, 168, 2, 178);
IPAddress server(192, 168, 2, 173);

EthernetClient ethClient;
MQTTClient client;
unsigned long nextExecMillis = 0;

void setupEthernet()
{
	// Ethernet.init(10);
	// Ethernet.begin(mac, 10000, 10000);
	Ethernet.begin(mac, ip);

	if (Ethernet.hardwareStatus() == EthernetNoHardware) {
  	  	Serial.println(F("Ethernet shield was not found.  Sorry, can't run without hardware. :("));
  	  	while (true) ;
  	}

	delay(100);

  	if (Ethernet.linkStatus() == LinkOFF) {
  	  	Serial.println(F("Ethernet cable is not connected."));
  	}

	Serial.println(F("Connected via ethernet!"));
	Serial.println(Ethernet.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  	// handle message arrived
}

void setup()
{
	Serial.begin(115200);
	setupEthernet();

	delay(100);

	client.begin(server, ethClient);
	while(!client.connect("ArduinoClient123")) {
		Serial.print(".");
		delay(1000);
	}

	Serial.println("Connected to broker");
	
	nextExecMillis = millis() + 1000;
}
	
void loop()
{
	static int i = 0;
	static char buff[16];
	client.loop();
	if(millis() >= nextExecMillis)
	{
		sprintf(buff, "%d", i++);
		if(client.publish("home/bedroom/temperature", buff))
			Serial.println("Publication succesfull");
		else
		{
			Serial.println("Publication failed");
			Serial.println(client.lastError());
		}

		Serial.println(client.returnCode());
		nextExecMillis = millis() + 1000;
	}
}