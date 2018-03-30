/*
 
 Bit-banged SPI class - fast versions
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

#include <Arduino.h>

class bitBangedSPIfast
  {
  // addresses of output ports - NULL if not applicable
  volatile byte * const mosiPort_;
  volatile byte * const misoPin_;
  volatile byte * const sckPort_;

  // bit masks for above
  const byte mosiBit_;
  const byte misoBit_;
  const byte sckBit_;

  // addresses of data direction register ports
  volatile byte * const mosiDDR_;
  volatile byte * const misoDDR_;
  volatile byte * const sckDDR_;
  
  // bit masks for above
  const byte mosiDDRBit_;
  const byte misoDDRBit_;
  const byte sckDDRBit_;

  // delay for clock being high
  unsigned long delayUs_;
  
  public:
    // constructor
    bitBangedSPIfast (
          // output ports
          volatile byte & mosiPort, 
          const    byte mosiBit,
          volatile byte & misoPin, 
          const    byte misoBit,
          volatile byte & sckPort,
          const    byte sckBit,
                      
          // data direction register ports
          volatile byte & mosiDDR, 
          const    byte mosiDDRBit,
          volatile byte & misoDDR, 
          const    byte misoDDRBit,
          volatile byte & sckDDR,
          const    byte sckDDRBit,
                      
          const unsigned long delayUs = 1)
       : 
         mosiPort_ (&mosiPort), 
         mosiBit_  (1 << mosiBit),
         misoPin_  (&misoPin), 
         misoBit_  (1 << misoBit), 
         sckPort_  (&sckPort), 
         sckBit_   (1 << sckBit), 

         mosiDDR_     (&mosiDDR), 
         mosiDDRBit_  (1 << mosiDDRBit),
         misoDDR_     (&misoDDR), 
         misoDDRBit_  (1 << misoDDRBit), 
         sckDDR_      (&sckDDR), 
         sckDDRBit_   (1 << sckDDRBit), 

        delayUs_ (delayUs) { }
    
    void begin ();
    byte transfer (byte input);
    
  };  // end of bitBangedSPIfast
