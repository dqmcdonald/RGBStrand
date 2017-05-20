


#define RED_PIN A0
#define GREEN_PIN A1
#define BLUE_PIN A2

RGBMode::RGBMode() {

}


void RGBMode::setup( Adafruit_NeoPixel& strip) {

  pinMode(RED_PIN, INPUT );
  pinMode(GREEN_PIN, INPUT );
  pinMode(BLUE_PIN, INPUT );
  d_red_val = 0;
  d_green_val = 0;
  d_blue_val = 0;
}


void RGBMode::update( Adafruit_NeoPixel& strip) {

  int val;
  bool val_changed = false;

  val = analogRead( RED_PIN );
  if ( fabs(d_red_val - val) > 10 ) {
    d_red_val = val;
    val_changed = true;
    Serial.print("Red: ");
    Serial.println(d_red_val );

  }
  val = analogRead( GREEN_PIN );
  if ( fabs(d_green_val - val) > 10 ) {
    d_green_val = val;
    val_changed = true;
    Serial.print("Green: ");
    Serial.println(d_green_val );

  }
  val = analogRead( BLUE_PIN );
  if ( fabs( d_blue_val - val) > 10 ) {
    d_blue_val = val;
    val_changed = true;
    Serial.print("Blue: ");
    Serial.println(d_blue_val );
  }


  if ( val_changed ) {
    val_changed = false;
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, d_red_val / 4, d_green_val / 4, d_blue_val / 4 );

    }
    strip.show();

  }

}


