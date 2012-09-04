#ifndef LIGHTS_H
#define LIGHTS_H

#include "Arduino.h"
#include "pins.h"

class Lights {
  public:
  Lights();
  void set(int light, unsigned char red, unsigned char green, unsigned char blue);
};

#endif // LIGHTS_H
