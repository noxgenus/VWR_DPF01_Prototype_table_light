/* 

TABLE LIGHT

VWR 'DPF01' Prototype table light
Victor Winters 2017

Color picker pen (Sender)
Sender hardware:
- Arduino Pro Mini 3V
- HC-11 on Channel C001
- Adafruit Flora TCS34725 with Led
- USB LiPo charger board
- 18650 Battery

Table light (Receiver)
Receiver Hardware:
- Adafruit Trinket Pro
- HC-11 on Channel C001
- Adafruit Dotstar Black (x144)
- 5V 3A regulated PSU Velleman

*/

#include <Adafruit_DotStar.h>
#include <SPI.h>
#define NUMPIXELS 144
#define DATAPIN    11
#define CLOCKPIN   12
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);

#include <SoftwareSerial.h>

SoftwareSerial SSerial(5, 6); // RX, TX

int r = 80;
int g = 40;
int b = 120;

int bright = 80;


// Colorpicker input
int userInput[3];    // raw input from serial buffer, 3 bytes
int startbyte;       // start byte, begin reading input
int colortype;         
int colorval;         
int i;               // iterator


void setup() {
    SSerial.begin(9600);
    Serial.begin(9600);

    // Trinket Pro settings
    #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
    #endif
    
    strip.begin();
    strip.show();


}

void loop() {

   if (SSerial.available() > 2) {

   startbyte = SSerial.read();

   if (startbyte == 255) {
     for (i=0;i<2;i++) {
       userInput[i] = SSerial.read();
     }
     colortype = userInput[0];
     colorval = userInput[1];
     if (colorval == 255) { 
      colortype = 255; 
      }
     
     switch (colortype) {
       case 1:
        r = colorval;
         break;
       case 2:
        g = colorval;      
         break;
       case 3:
        b = colorval;
         break;
     }
   }
   
 } //close if serial

Serial.print(r);
Serial.print(g);
Serial.print(b);
Serial.println(" ");

// square 1
for(byte x=0;x<144;x++) {
strip.setBrightness(bright); 
strip.setPixelColor(x, r, g, b);
}
strip.show(); 
delay(20);
//
//// square 2
//for(byte x=16;x<32;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 3
//for(byte x=32;x<48;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 4
//for(byte x=64;x<80;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 5
//for(byte x=80;x<96;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 6
//for(byte x=96;x<112;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 7
//for(byte x=112;x<130;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 8
//for(byte x=130;x<146;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);
//
////square 9
//for(byte x=146;x<162;x++) {
//strip.setBrightness(bright); 
//strip.setPixelColor(x, r, g, b);
//}
//strip.show(); 
//delay(200);


}
            
