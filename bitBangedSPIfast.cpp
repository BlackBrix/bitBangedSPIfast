/*
 
 Bit-banged SPI class - fast version
 Author: Nick Gammon
 Date:   30 March 2013

 
 PERMISSION TO DISTRIBUTE
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in 
 all copies or substantial portions of the Software.
 
 
 LIMITATION OF LIABILITY
 
 The software is provided "as is", without warranty of any kind, express or implied, 
 including but not limited to the warranties of merchantability, fitness for a particular 
 purpose and noninfringement. In no event shall the authors or copyright holders be liable 
 for any claim, damages or other liability, whether in an action of contract, 
 tort or otherwise, arising from, out of or in connection with the software 
 or the use or other dealings in the software. 

*/

#include <bitBangedSPIfast.h>

void bitBangedSPIfast::begin ()
  {
  if (mosiPort_)
    *mosiDDR_ |= mosiDDRBit_;    // output
  if (misoPin_)
    *misoDDR_ &= ~misoDDRBit_;   // input
  *sckDDR_ |= sckDDRBit_;        // output
  }   // end of bitBangedSPIfast::begin
  
  
// Bit Banged SPI transfer
byte bitBangedSPIfast::transfer (byte c)
{       
  // loop for each bit  
  for (byte bit = 0; bit < 8; bit++) 
    {
    // set up MOSI on falling edge of previous SCK (sampled on rising edge)
    if (mosiPort_)
      {
      if (c & 0x80)
        *mosiPort_ |= mosiBit_;
      else
        *mosiPort_ &= ~mosiBit_;
      }
    
    // finished with MS bit, get read to receive next bit      
    c <<= 1;
 
    // read MISO
    if (misoPin_)
      c |= (*misoPin_ & misoBit_) != 0;
 
    // clock high
    *sckPort_ |= sckBit_;
 
    // delay between rise and fall of clock
    delayMicroseconds (delayUs_);
 
    // clock low
    *sckPort_ &= ~sckBit_;

    // delay between rise and fall of clock
    delayMicroseconds (delayUs_);
    }  // end of for loop, for each bit
   
  return c;
  }  // end of bitBangedSPIfast::transfer  

