#include "lights.h"

int pins[] = {PIN_LED_RIGHT, PIN_LED_LEFT, PIN_LED_BLUE, PIN_LED_GREEN, PIN_LED_RED};

// Calibration for LED colour issues
const float calibration[] = {1, 1, 1};
bool led_stop = false;

Lights::Lights() {
  for (int i = 0; i < 6; i++) {
      pinMode(pins[i], OUTPUT);
      digitalWrite(pins[i], HIGH);
  }
}

unsigned logScale(float value) {
  return (unsigned char)((log(255 - value) / log(255)) * 255);
}

void Lights::set(int light, unsigned char red, unsigned char green, unsigned char blue) {
  analogWrite(PIN_LED_RED, logScale(red * calibration[0]));
  analogWrite(PIN_LED_GREEN, logScale(green * calibration[1]));
  analogWrite(PIN_LED_BLUE, logScale(blue * calibration[2]));
  if (light == PIN_LED_RIGHT) {
    digitalWrite(PIN_LED_RIGHT, HIGH);
    digitalWrite(PIN_LED_LEFT, LOW);
  } else if (light == PIN_LED_LEFT) {
    digitalWrite(PIN_LED_LEFT, HIGH);
    digitalWrite(PIN_LED_RIGHT, LOW);
  } else if (light == PIN_LED_BOTH) {
    digitalWrite(PIN_LED_LEFT, HIGH);
    digitalWrite(PIN_LED_RIGHT, HIGH);
  }
}

void led_cycle(Lights *lights, int light, int time) {
  unsigned char red = 0, green = 0, blue = 0;
  unsigned char brightness = 128;
  float step = (2 * PI) / time;
  for (float i = 0; i < 2 * PI; i += step) {
    red =   (unsigned char)( brightness + brightness * sin(i) );
    green = (unsigned char)( brightness + brightness * sin(i + PI * 2 / 3) );
    blue =  (unsigned char)( brightness + brightness * sin(i + PI * 4 / 3) );
    if(led_stop) {
      led_stop = false;
      break;
    }
    lights->set(light, red, green, blue);
    delay(1);
  }
}

void led_stop_cycle() {
  led_stop = true;
}

