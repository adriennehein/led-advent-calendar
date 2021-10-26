
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const int BUTTON_PIN = 2;  // Connect the Button to pin 2 or change here
const int LED_PIN    = 6; // Connect the LED to pin 6 or change here
const int DEBOUNCE_DELAY = 50;   // the debounce time; increase if the output flickers

// Variables will change:
int lastSteadyState = LOW;       // the previous steady state from the input pin
int lastFlickerableState = LOW;  // the previous flickerable state from the input pin
int currentState;                // the current reading from the input pin

//boolean oldState = HIGH;
int PIXEL_INDEX = 0;
int BTN_COUNT = 0;
int pixels[] = {0, 2, 4, 6, 8, 9, 10, 12, 14, 16, 18, 21, 23, 25, 26, 27, 29, 31, 33, 34, 36, 38, 40, 42, 44, 45, 46}; // due to LED layout, these are the pixels that need to lit up

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(50, LED_PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP

}

void loop() {

  // Get current button state.
  currentState = digitalRead(BUTTON_PIN);

    // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch/button changed, due to noise or pressing:
  if (currentState != lastFlickerableState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if(lastSteadyState == HIGH && currentState == LOW) {
      Serial.println("The button is pressed");
        if (BTN_COUNT < 25) {
            strip.setPixelColor(pixels[PIXEL_INDEX], 10157824); //warm yellow
            strip.show();
            delay(50);
//          pixels.setPixelColor(PIXEL_INDEX, pixels.Color( 255,   204,   102));
//          pixels.show();  // Send the updated pixel colors to the hardware.
          PIXEL_INDEX = PIXEL_INDEX + 1; // increment index of pixel array
          Serial.println(BTN_COUNT);
        }
        if (BTN_COUNT == 25) {
            christmas(50);
        }
        if (BTN_COUNT >= 26) {
          // turn off pixels on 26th button press
          strip.clear();
          strip.show();
          BTN_COUNT = 0;
          PIXEL_INDEX = 0;
        }
        
        BTN_COUNT = BTN_COUNT + 1; // incrememnt btn presses to determine when 25 is reached for XMAS
        
    }
    else if(lastSteadyState == LOW && currentState == HIGH) {
      Serial.println("The button is released");
    }
    // save the the last steady state
    lastSteadyState = currentState;
  }

}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<PIXEL_INDEX; i = i+2) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void christmas(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  int arraySize = sizeof( pixels );
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<27; i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(pixels[i], strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
// void rainbow(int wait) {
//   // Hue of first pixel runs 3 complete loops through the color wheel.
//   // Color wheel has a range of 65536 but it's OK if we roll over, so
//   // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
//   // means we'll make 3*65536/256 = 768 passes through this outer loop:
//   for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
//     for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
//       // Offset pixel hue by an amount to make one full revolution of the
//       // color wheel (range of 65536) along the length of the strip
//       // (strip.numPixels() steps):
//       int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
//       // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
//       // optionally add saturation and value (brightness) (each 0 to 255).
//       // Here we're using just the single-argument hue variant. The result
//       // is passed through strip.gamma32() to provide 'truer' colors
//       // before assigning to each pixel:
//       strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
//     }
//     strip.show(); // Update strip with new contents
//     delay(wait);  // Pause for a moment
//   }
// }

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
//void theaterChaseRainbow(int wait) {
//  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
//  for(int a=0; a<30; a++) {  // Repeat 30 times...
//    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
//      strip.clear();         //   Set all pixels in RAM to 0 (off)
//      // 'c' counts up from 'b' to end of strip in increments of 3...
//      for(int c=b; c<strip.numPixels(); c += 3) {
//        // hue of pixel 'c' is offset by an amount to make one full
//        // revolution of the color wheel (range 65536) along the length
//        // of the strip (strip.numPixels() steps):
//        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
//        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
//        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
//      }
//      strip.show();                // Update strip with new contents
//      delay(wait);                 // Pause for a moment
//      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
//    }
//  }
//}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  if(WheelPos < 85) {
//   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//  } else if(WheelPos < 170) {
//   WheelPos -= 85;
//   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  } else {
//   WheelPos -= 170;
//   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//}