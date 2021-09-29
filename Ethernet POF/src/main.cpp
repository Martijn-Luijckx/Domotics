/*
Ethernet proof of concept program based on the Arduino Webserver program. The ethernet breakout board should be based on the ENCJ60 and should be connected as followed:

Pin 13 -> SCK
Pin 12 -> SO/MISO
Pin 11 -> SI/MOSI
Pin 10 -> SS

It seems that on some board it doesnt say SI. In that case it might say something like ST, which woulde be the SI pin. 
*/

#include <Arduino.h>
#include <SPI.h>
#include <EthernetENC.h>

// Pin 10 is used on most Arduino shields
#define slave_select_pin 10

byte mac[] = {
  	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 2, 177);

EthernetServer server(80);

void setup() 
{
	// Initialize Ethernet interface with selected SS pin.
  	Ethernet.init(slave_select_pin);  

	// Initialize Serial port for debugging
  	Serial.begin(115200);
  	Serial.println("Ethernet POF");

	// Start ethernet interface
  	Ethernet.begin(mac, ip);

	// Stop execution if there is not hardware detected
  	if (Ethernet.hardwareStatus() == EthernetNoHardware) {
  	  	Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
  	  	while (true) {
  	  		delay(1);
  	  	}
  	}

  	if (Ethernet.linkStatus() == LinkOFF) {
  	  	Serial.println("Ethernet cable is not connected.");
  	}

	// Start the web server
  	server.begin();
  	Serial.print("server is at ");
  	Serial.println(Ethernet.localIP());
}


void loop() 
{
	// Wait for a client to connect
  	EthernetClient client = server.available();

  	if (client) 
	{
    	Serial.println("new client");
    	boolean currentLineIsBlank = true;
    	while (client.connected()) 
		{
    		if (client.available()) 
			{
    			char c = client.read();
    			Serial.write(c);
		   		if (c == '\n' && currentLineIsBlank) 
				{
					// Send HTTP header with code 200
    				client.println("HTTP/1.1 200 OK");
    				client.println("Content-Type: text/html");
    				client.println("Connection: close");
    				client.println("Refresh: 5");
    				client.println();

					// Send the website contents, which is just Hello world! in this case.
    				client.println("<!DOCTYPE HTML>");
    				client.println("<html>");
					client.println("<p>Hello world!</p>");
    				client.println("</html>");
    				break;
    			}
    			if (c == '\n') 
				{
    			  	currentLineIsBlank = true;
    			} 
				else if (c != '\r') 
				{
    			  	currentLineIsBlank = false;
    			}
    		}
    	}

		// Give the client some time to handle connection and close the connection
    	delay(1);
    	client.stop();
    	Serial.println("client disconnected");
  	}
}
