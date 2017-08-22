


#define FIRE_SPEED_PIN A0


FireMode::FireMode() {

}


void FireMode::setup( Adafruit_NeoPixel& strip) {

  pinMode(FIRE_SPEED_PIN, INPUT );
  
}


void FireMode::update( Adafruit_NeoPixel& strip) {

  int val;
  bool val_changed = false;
  int r = 255;
  int g = r - 40;
  int b = 40;

  for (uint16_t i = 0; i < strip.numPixels(); i++) {
  {
    int flicker = random(0, 100);
    int r1 = r - flicker;
    int g1 = g - flicker;
    int b1 = b - flicker;
    if (g1 < 0) g1 = 0;
    if (r1 < 0) r1 = 0;
    if (b1 < 0) b1 = 0;
    strip.setPixelColor(i, r1, g1, b1);
  }
  strip.show();
  
  int speed_val = analogRead( FIRE_SPEED_PIN );
   speed_val = 1023-speed_val;  // Invert the speed value so higher values give shorter delays
    

    delay(random(speed_val/20.0));

  }


}


