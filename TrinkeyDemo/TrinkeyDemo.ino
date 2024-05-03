/*
  Keyboard Message test
  For the Adafruit Neo Trinkey
*/

#include <Adafruit_NeoPixel.h>
#include "Adafruit_FreeTouch.h"
#include "Keyboard.h"

// Create the neopixel strip with the built in definitions NUM_NEOPIXEL and PIN_NEOPIXEL
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_NEOPIXEL, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Create the two touch pads on pins 1 and 2:
Adafruit_FreeTouch qt_1 = Adafruit_FreeTouch(1, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_FreeTouch qt_2 = Adafruit_FreeTouch(2, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

// Initialize our variables.
bool previousTouch1State = false;   // for checking the state of touch 1
bool previousTouch2State = false;   // for checking the state of touch 1
int touch1counter = 0;              // touch 1 counter
uint16_t i = 0;
uint16_t j = 0;

void setup() {
  // Set baud rate for Trinkey board.
  Serial.begin(9600);
  // Delay for serial to startup, if necessary.
  //while (!Serial) delay(10);
  
  strip.begin(); // start pixels
  // Sets brightness to roughly 75%, maximum is 32, min is 0.
  strip.setBrightness(20);
  strip.show(); // Initialize all pixels to 'off'

  // Initialize our touch library.
  if (! qt_1.begin())  
    Serial.println("Failed to begin qt on pin 1");
  if (! qt_2.begin())  
    Serial.println("Failed to begin qt on pin 2");
    
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  
  // Measure the captouches
  uint16_t touch1 = qt_1.measure();
  uint16_t touch2 = qt_2.measure();
  // whether we think they are being touched
  bool Touch1State, Touch2State;

  // print out the touch readings
  Serial.print("QT 1: "); Serial.print(touch1);
  Serial.print("\t\tQT 2: "); Serial.println(touch2);

  // If the first pad is touched, turn on the #2 and #3 pixel red
  // These are the two LEDs that are "inline" with the touch pad.
  if (touch1 > 500) {
    Touch1State = true;  // is touched
    strip.setPixelColor(2, 0xFF5500);
    strip.setPixelColor(3, 0xFF5500);
  } 
  else {
    // turn them off
    Touch1State = false;  // is not touched
    strip.setPixelColor(2, 0x0);
    strip.setPixelColor(3, 0x0);    
  }


  // If the second pad is touched, turn on the #0 and #1 pixel blue
  // These are the LEDs that are "inline" wih the second touch pad.
  if (touch2 > 500) {
    Touch2State = true;  // is touched
    strip.setPixelColor(0, 0x00FFF1);
    strip.setPixelColor(1, 0x00FFA1);
  } 
  else {
    // turn them off
    Touch2State = false;  // is not touched
    strip.setPixelColor(0, 0x0);
    strip.setPixelColor(1, 0x0);
  }
  
  strip.show(); // display pixel changes

  // If we are now touching #1, and we weren't before...
  if (Touch1State and !previousTouch1State) {
    // As long as we hold down the key, send the key code, for OPTION.
    previousTouch1State = Touch1State;
    Keyboard.press(KEY_LEFT_ALT);
  }

  // If #1 was just released, and Touch 2 is not being pressed...
  if (!Touch1State and previousTouch1State and !Touch2State) {
    // Release any held keys.
    Keyboard.releaseAll();
  }

  // If we are now touching #2, and we weren't before...
  if (Touch2State and !previousTouch2State) {
    // Here is where we can set things for the second touch pad to do!
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_DELETE);
  }

  // If touch 2 has been released and touch 1 is not being pressed...
  if (!Touch2State and previousTouch2State and !Touch1State) {
    // Release any held keys.
    Keyboard.releaseAll();
  }

  // Save the current touch state for comparison next time.
  previousTouch1State = Touch1State;
  // Save the current touch state for comparison next time.
  previousTouch2State = Touch2State;
  // Small delay so we don't spam keys too badly.
  delay(10);
}
