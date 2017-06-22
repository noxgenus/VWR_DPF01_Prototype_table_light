/* 

COLOR PICKER

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

#include <SoftwareSerial.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

// Soft Serial so you can debug through USB
SoftwareSerial SSerial(2, 3); // RX, TX

int colortype;
int colorval;

void setup() {
  
Serial.begin(9600);
SSerial.begin(9600);
  Serial.println("Color Picker Loaded!");
  if (tcs.begin()) {
    Serial.println("Found sensor!");
  } else {
    Serial.println("TCS34725 not found! ...check your wires mate");
    while (1); // halt! HAMMERZEIT.
  }

  // Convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
  
}
void loop(){
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false); // turn on LED
  delay(160);  // takes 50ms to read (on 16mHz!)
  
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED
  
    uint32_t sum = clear;
    float r, g, b;
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;
    
  // GAMMA CONVERTED VALUES FOR LED OUTPUTS THROUGH ANALOG
  // Serial.print("\tR:\t"); Serial.print(gammatable[(int)r]);
  // Serial.print("\tG:\t"); Serial.print(gammatable[(int)g]);
  // Serial.print("\tB:\t"); Serial.print(gammatable[(int)b]);
  // Serial.println(" ");
  
  // PLAIN RGB VALS OUTPUT
  Serial.print("\tR:\t"); Serial.print(r);
  Serial.print("\tG:\t"); Serial.print(g);
  Serial.print("\tB:\t"); Serial.print(b);
  Serial.println(" ");
  
 // HEX COLOR OUTPUT!
 // Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
 // Serial.println();
 
  //SEND RGB VALS TO SERIAL
  sendColor(1, r);
  sendColor(2, g);
  sendColor(3, b);
}
//SEND TO TX
void sendColor(int colortype, int colorval) {
       SSerial.write(char(255));
       SSerial.write(char(colortype));
       SSerial.write(char(colorval));
}

