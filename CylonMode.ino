
/* Cylon mode moves a red LED across the strip like a "BattleStar Galactica" cylon */

#define BRIGHTNESS_PIN A0
#define SPEED_PIN A1
#define RANDOMNESS_PIN A2


CylonMode::CylonMode() {

}


void CylonMode::setup( Adafruit_NeoPixel& strip) {

  pinMode(BRIGHTNESS_PIN, INPUT);
  pinMode(SPEED_PIN, INPUT );
  pinMode(RANDOMNESS_PIN,INPUT);
   d_next_update = millis() + d_period;

}

void CylonMode::update( Adafruit_NeoPixel& strip) {

    if ( d_next_update > millis())
      return;
    int brightness_val = analogRead( BRIGHTNESS_PIN );
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, brightness_val / 4, brightness_val / 4, brightness_val / 4 );
    }
  
    int speed_val = analogRead( SPEED_PIN );
    speed_val = 1023-speed_val;  // Invert the speed value so higher values give shorter delays
    d_period = map( speed_val, 0, 1023, 20, 500);

    // Set the current position to red:
    strip.setPixelColor(d_position, 200, 0, 0 );

    // Calculate the next position:
    d_position += d_direction;
    
    if ( d_position >= strip.numPixels() || d_position <= 0 ) {
      d_direction = - d_direction;
    }


    int randomness_val = analogRead(RANDOMNESS_PIN );
    double random_factor = randomness_val/1023.0 * random(d_period);
    d_next_update = millis() + d_period + random_factor;
  
    strip.show();

}


