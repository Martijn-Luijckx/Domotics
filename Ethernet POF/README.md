# Ethernet POF
Ethernet proof of concept program based on the Arduino Webserver example. The ethernet breakout board should be based on the ENC28J60 and should be connected as followed:

Pin 13 -> SCK
Pin 12 -> SO/MISO
Pin 11 -> SI/MOSI
Pin 10 -> SS

In case there is no SI label on the breakout board, it might be labeled as ST. This happens om some cheap Chinese breakout boards. 