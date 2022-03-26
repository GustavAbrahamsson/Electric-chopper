#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

uint8_t DIN = 10;
uint8_t numberOfLEDs = 21;
//uint8_t btnPin = 9;
//uint8_t numberOfStates = 1;

//volatile uint8_t lightingState = 0;

//unsigned long timeSinceBtnPress = 0;

volatile bool abortFunction = false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfLEDs, DIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void colorAllPixels(uint32_t color, uint8_t brightness){
  strip.setBrightness(brightness);
  for(int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, color);
  }
  strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    if(abortFunction) {
        abortFunction = false;
        return;
      }
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    if(abortFunction) {
        abortFunction = false;
        return;
      }
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
      if(abortFunction) {
        abortFunction = false;
        return;
      }

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}



//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();
      if(abortFunction) {
        abortFunction = false;
        return;
      }
      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void setup() {
  //pinMode(btnPin, INPUT_PULLDOWN);

  //attachInterrupt(btnPin, btnFunction, RISING);

  strip.begin();
  strip.setBrightness(255);
  strip.show();

}

void loop() {
  
  rainbowCycle(3);
  /*
  delay(10);
  switch(lightingState){
    case 0:
      rainbowCycle(3);
      break;
    case 1:
      theaterChaseRainbow(2);
      break;
    case 2:
      colorAllPixels(strip.Color(255,0,0),255);
      break;
    case 3:
      colorAllPixels(strip.Color(0,255,0),255);
      break;
    case 4:
      colorAllPixels(strip.Color(0,0,255),255);
      break;
    case 5:
      theaterChase(strip.Color(0,255,255),20);
      break;
      
  }*/
     
  /*
  if(digitalRead(btnPin) == true){
    theaterChaseRainbow(5);
  }
  else{
    rainbowCycle(0);
  }
  */
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
}
