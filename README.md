# bitBangedSPIfast
fast soft-SPI for Arduino AVR (by [Nick Gammon](https://github.com/nickgammon))
  
----  
  
The library below uses direct port manipulations to speed up the bit-banged SPI. It is a bit fiddlier to use, because you need to look up the ports/pins/data-direction registers for the appropriate pins. However, it is faster.  
  
Download:  
  
http://www.gammon.com.au/Arduino/bitBangedSPIfast.zip  
  
Example of use:  

````C++
#include <bitBangedSPIfast.h>

bitBangedSPIfast bbSPI (PORTD,  5, PIND,  6, PORTD, 7,    // MOSI port (D5), MISO pin (D6), SCK port (D7)
                        DDRD,   5, DDRD,  6, DDRD,  7);   // MOSI ddr  (D5), MISO ddr (D6), SCK ddr  (D7)
const byte mySS =  8;  // slave select

void setup (void)
  {
  bbSPI.begin ();
  pinMode (mySS, OUTPUT);
  }  // end of setup

void loop (void)
  {
  char c;
  
  // enable Slave Select
  digitalWrite(mySS, LOW); 
  
  // send test string
  for (const char * p = "Hello, world!" ; c = *p; p++)
    bbSPI.transfer (c);

  // disable Slave Select
  digitalWrite(mySS, HIGH);

  delay (100); 
  }  // end of loop
````
  
This takes about 52 uS to transfer one byte.  
  
Both of these are somewhat slower than hardware SPI, but could come in handy where you are using the hardware SPI for other purposes, and just want to draw to an LCD screen, or update some LEDS, where speed is not really of the essence.  
