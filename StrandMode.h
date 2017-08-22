#ifndef __RGBSTRANDMODE__
#define __RGBSTRANDMODE__

#include <Adafruit_NeoPixel.h>

/* 
 *  Abstract base class which defines interface for all strand modes 
 */
class StrandMode {
  public:
    StrandMode() { };
    virtual void setup( Adafruit_NeoPixel& Strand);
    virtual void update( Adafruit_NeoPixel& Strand) = 0;
};



/*
 * RGBMode - set the entire Strand to a value indicated by the Red, Green and Blue pots
 */
class RGBMode : public StrandMode {
  public:
    RGBMode();
    void setup( Adafruit_NeoPixel& Strand) override;
    void update( Adafruit_NeoPixel& Strand) override;
  private:
    int d_red_val = 0;
    int d_blue_val = 0;
    int d_green_val = 0;
};

/* Cylon Mode - a red LED appears to move from left to right across the Strand. Controls are:
 *  Red pot - brightness of background.
 *  Green pot - speed of movement.
 *  Blue pot - apparent randomness in movement.
 */
class CylonMode : public StrandMode {
  public:
    CylonMode();
    void setup( Adafruit_NeoPixel& Strand) override;
    void update( Adafruit_NeoPixel& Strand) override;
  private:
    long unsigned int d_next_update;   // Time in millis to next update
    unsigned int d_position = 0;     // Current position of red LED
    long int d_period = 50; 
    int d_direction = 1;
};

/* Fire Mode - Appears to flicker like a fire
 *  Red pot - speed of flicker

 */
class FireMode : public StrandMode {
  public:
    FireMode();
    void setup( Adafruit_NeoPixel& Strand) override;
    void update( Adafruit_NeoPixel& Strand) override; 
};




// Don't add anything after this #endif
#endif
