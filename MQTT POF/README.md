# MQTT POF
MQTT proof of concept program based on the Arduino Webserver example. The ethernet breakout board should be based on the ENC28J60 and should be connected as followed:

Pin 13 -> SCK
Pin 12 -> SO/MISO
Pin 11 -> SI/MOSI
Pin 10 -> SS

In case there is no SI label on the breakout board, it might be labeled as ST. This happens om some cheap Chinese breakout boards. 
<br/><br/>
Before the example can be used, all IP addresses have to be changed. The field "ip" has to be changed to a free IP address on the local network, and the address server has to be changed to the IP address of the MQTT server. If an external mqtt server is used, the server variable can be changed to the domain name in the following statement:
```c
client.begin(server, ethClient);
```