# Arduino_shieldbot
Arduino code for a shieldbot to drive through a track.
Arduino Shieldbot 1.2 is used: https://wiki.seeedstudio.com/Shield_Bot_V1.2/

Reflectance sensor PCB board includes an SFH9206 reflectance sensor IC 
The reflectance sensor has two parts:
	i)	an IR LED that sends out infrared light
	ii)	an IR phototransistor that detects incoming infrared light

The circuit is set up so that the output voltage is low (close to 0V) when an object is close to the IR LED and reflects the IR light back towards the phototransistor.  The output voltage is high (close to the supply voltage) when no IR light is reflected back towards the phototransistor.
Connect 5V to the 5V pin, 0V to the GND pin, and the OUT pin can be connected to an A/D converter