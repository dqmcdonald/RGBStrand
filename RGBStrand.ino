
/*
   Illuminate an RGB LED strand. There are several modes in which this can operate, modes are cycled by a pushbutton
   attached to pin 5. Modes are:

   Strand data line is attached to pin 6. Three pots set up as voltage dividers are connected to pins A0 to A2.

   RGB strand should be powered separately from robust 5V power supply (must supply at least 3A).

   Quentin McDonald
   May 2017
   Based on AdaFruit example code.

*/

#include "StrandMode.h"
#include "Bounce2.h"


// Pin definitions:
#define BUTTON_PIN 5
#define STRAND_PIN 6

// Parameter 1 = number of pixels in strand
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strand = Adafruit_NeoPixel(60, STRAND_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capac8tor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

// Set up the possible strand modes:

const int NUM_MODES = 3;
int current_mode = 0;

RGBMode rgb_mode = RGBMode();
CylonMode cylon_mode = CylonMode();
FireMode fire_mode = FireMode();
StrandMode* all_modes[NUM_MODES] = {
  &rgb_mode,
  &cylon_mode,
  &fire_mode
};


Bounce debouncer = Bounce();

void setup() {

  strand.begin();
  strand.show(); // Initialize all pixels to 'off'

  all_modes[current_mode]->setup(strand);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(20);


  Serial.begin(115200);
}


void loop() {

  
   all_modes[current_mode]->update(strand);
  

  debouncer.update();

  
  if ( debouncer.fell() ) {   
    Serial.println("Bouncer fell");
    current_mode++;
    if ( current_mode >= NUM_MODES) {
      current_mode = 0;
    }
      Serial.print("Current mode =");
      Serial.println(current_mode);
    all_modes[current_mode]->setup(strand);
  }



}



