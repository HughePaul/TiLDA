#include <SoftwareSerial.h>
#include "lights.h"
#include "pins.h"

Lights lights;


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10

RF24 radio(A0,A1);


// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipe = 0xFEFEFEFEE1LL;

//
// Setup
//

void setup(void)
{
  Serial.begin(57600);
  printf_begin();

  printf("\n\rRF24/Clock send/\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();
  radio.setChannel(0x69);
  radio.setPayloadSize(4);
  radio.disableCRC();

  radio.setRetries(15,15);
  radio.openWritingPipe(pipe);

  radio.printDetails();
}

//
// Loop
//

unsigned char brightness = 127;
float step = (2 * PI) / 20;
unsigned char color[3];
float i = 0;

void loop(void)
{

  i += step;
  if(i >= 2 * PI) i = 0;
  
  //color[0] = (unsigned char)( brightness + brightness * sin(i) );
  color[0] = (sin(i) > -0.5) ? 255 : 0;
  color[1] = (unsigned char)( brightness + brightness * sin(i + PI * 2 / 3) );
  color[2] = (unsigned char)( brightness + brightness * sin(i + PI * 4 / 3) );
    
  lights.set(PIN_LED_BOTH, color[0], color[1],  color[2]);

  radio.startListening();
  radio.stopListening();
  radio.write(color, 3);

  delay(100);
}







