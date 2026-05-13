/* 
 
 Depends on MegaTinyCore for programming the ATTINY412
 http://drazzy.com/package_drazzy.com_index.json
 In tools:
  Board: megaTinyCore  --> ATiny412/402/212/202
  Clock: "1MHz internal".
  Programmer: "SerialUPDI - 230400 baud"
 
  ATTINY412 Control Pins for STuW81300:

  PA1 pin SDI 4  - ArduinoIDE 2 STuW DATA
  PA2 pin  LE 5  - ArduinoIDE 3 STuW LE
  PA3 pin CLK 7  - ArduinoIDE 4 STuW CLK

  PA6 pin     2  - ArduinoIDE 0 RF-DET
  PA7 pin PTT 3  - ArduinoIDE 1 PTT
  
 Dircect Port Programming megatinycore only
 ------------------------------------------
.PIN1_bm; = PA1
.PIN2_bm; = PA2
.PIN3_bm; = PA3
.PIN4_bm; = PA4 etc.

 ----------------------------------------------------------------
*/

/* STuW registers */
uint32_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;

uint32_t lastTX;

#define RFvox false

void setup(){

#if RFvox
  PORTA.DIR = 0b10111110;  // PA6 input, PA0 input
  PORTA.OUTSET = PIN7_bm;  // in RX
  analogReference(INTERNAL1V1);  
#else RFvox
  PORTA.DIR = 0b00111110;  // PA7 input, PA6 input, PA0 input
#endif RFvox 

  
  delay(4000);  // STuW PowerUp delay


/* Set PLL Frequency */ 

   set5328();
   
 
}

void loop(){
#if RFvox
  TestRF(50,200);  // threshold 50 15dBm at IF input, 200mS hang delay
#endif RFvox 
}


void TestRF(int threshold, uint32_t txHangMillis) {
  if (analogRead(PIN_A6) > threshold) {   // TX detected ?
    PORTA.OUTCLR = PIN7_bm;   // in TX
    lastTX = millis();
  }
  else { // RX detected
    if ((millis() - lastTX) > txHangMillis) { // Back to RX
      PORTA.OUTSET = PIN7_bm; // in RX
    }
  }
}

void write2PLL(uint32_t PLLword) {              // clocks 32 bits word  directly to the STuW81300
                                                // msb (b31) first, lsb (b0) last

 noInterrupts();                                // disable interrupts to keep accurate timing. 
  
  for (byte i=32; i>0; i--) {                   // PLL word 32 bits
     
    (PLLword & 0x80000000? PORTA.OUTSET = PIN1_bm : PORTA.OUTCLR = PIN1_bm);   // data on PA1
                                                                               
    PORTA.OUTSET = PIN3_bm;                     // clock in bit on rising edge of CLK (PA3 = 1)
    PORTA.OUTCLR = PIN3_bm;                     // CLK (PA3 = 0)      
    (PLLword <<= 1);                            // rotate left for next bit
    }
    PORTA.OUTSET = PIN2_bm;                     // latch in PLL word on rising edge of LE (PA2 = 1)
    PORTA.OUTCLR = PIN2_bm;                     // LE (PA2 = 0)  

 interrupts();                                  // enable interrupts
   
}



// Write data to STuW81300
//----------------------------------------------------------------------------------------
void set5328(){

/* Frequency set to 5328 Mhz for 432 Mhz IF, 40MHz ref
Target freq 5328000000.0
Ext. Ref 40000000.0
INT  133
actual freq 5328000000.0
delta 0.0
MOD  5
FRAC  1
RF1_SEL 0
RF1_OUT_PD 0
RF2_OUT_PD 1
PLL_SEL 1
uint32_t regSTuW[10] = {  0x3e00085 , 0x8400001 , 0x10000005 , 0x18008002 , 0x20039315 , 0x28000000 , 0x30001000 , 0x39000000 , 0x40000003 , 0x48000000 }; // 5328.0 MHz
*/

r9 = 0x48000000 ;
r8 = 0x40000003 ;
r7 = 0x39000000 ;
r6 = 0x30001000 ;
r5 = 0x28000000 ;
r4 = 0x20039315 ;
r3 = 0x18008002 ;
r2 = 0x10200005 ;
r1 = 0x8400001 ;
r0 = 0x3e00085 ;


   write2PLL(r9);
   delay(50);

   write2PLL(r0);    
   write2PLL(r8);
   write2PLL(r7);
   write2PLL(r6);
   write2PLL(r5);
   write2PLL(r4);
   write2PLL(r3);
   write2PLL(r2);
   write2PLL(r1);
   write2PLL(r0);  
}
