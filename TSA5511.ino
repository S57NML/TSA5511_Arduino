// Simple sketch for communication @I2C between TSA5511 PLL IC and Arduino
// For personal use and hamradio  :) only
//Tested with Z-comm VCO V110PC01 at 110MHz
//
//7/3/2017
//By Andrej - S57NML
//73 

#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(19200); //debug
}
void pll_setup(long frekvenc)
{
  char polje[5];
  long Quartz = 3200000; // 4Mhz or 3.2Mhz crystal
  long fReferenca = Quartz / 512; //Divider of Quartz fq/512 = 7.8125kHz (4MHz)  or 6.250kHz(3.2MHz)
  long fDivider = frekvenc/8; // RF frequency input divider 15bits
  long div = fDivider / fReferenca; // phase comparator calc

//byte Nr.0
  polje[0] = 0x61; // the address of TSA5511 0xC2 8bytes wire library!-->  7bytes=0x61
//byte Nr.1
  polje[1] = (div & 0xFF00) >> 8; //upper
//byte Nr.2
  polje[2] = div & 0x00FF; // lower
//byte Nr.3
  polje[3] = 0x8E; // 10001110, charge pumper
//byte Nr.4
  polje[4] = 0x00;//set pinouts etc
 Serial.println(polje[0],HEX);
  Serial.println(polje[1],HEX);
  Serial.println(polje[2],HEX);
  
   Serial.println(div,HEX);
   
 Wire.beginTransmission(0x61);
 Wire.write(&polje[1]);
 Wire.write(&polje[2]);
 Wire.write(&polje[3]);
 Wire.write(&polje[4]);
 Wire.endTransmission();
}

void loop(){
 long frekvenca1;
 Wire.begin();
 frekvenca1 = 134200000;  //example 134,2MHz
 pll_setup(frekvenca1); 
  
  delay(1500);
 // pll_setup(frekvenca1+2000000); //example 2 102mhz
    
  delay(1500);
  }
