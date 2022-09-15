//Definitions
int neoPixelPin = A0;
int numPixels = 12;

//Initialize the LED ring
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);

//Functions that set the LED ring to the specified color:

void orange() { //Orange setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 255, 100, 0);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void red() { //Red setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 255, 0, 0);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void green() { //Green setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 0, 255, 0);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void blue() { //Blue setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 0, 0, 255);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void yellow() { //Yellow setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 255, 255, 0);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void purple() { //Purple setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 75, 0, 211);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void aqua() { //Red setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 0, 255, 255);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void lightsOut() { //Turns off lights
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void white() { //White setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 255, 255, 255);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void pink() { //Pink setting function
  for ( int i = 0; i < numPixels; i++ ) {
    strip.setPixelColor(i, 255, 0, 255);
    strip.show();
    strip.setBrightness(30);
  }
}
//---------------------------------------------------------------
void greenRed() { //Test
  for ( int i = 0; i < 6; i++ ) {
    for (int j = 6; j < 12; j++ ) {
      strip.setPixelColor(i, 255, 0, 0);
      strip.setPixelColor(j, 0, 255, 0);
      strip.show();
      strip.setBrightness(30);
    }
  }
}
//---------------------------------------------------------------
void orangeBlue() { //Test
  for ( int i = 0; i < 6; i++ ) {
    for (int j = 6; j < 12; j++ ) {
      strip.setPixelColor(i, 255, 100, 0);
      strip.setPixelColor(j, 0, 0, 255);
      strip.show();
      strip.setBrightness(30);
    }
  }
}
//---------------------------------------------------------------
void purpleWhite() { //Test
  for ( int i = 0; i < 6; i++ ) {
    for (int j = 6; j < 12; j++ ) {
      strip.setPixelColor(i, 75, 0, 211);
      strip.setPixelColor(j, 255, 255, 255);
      strip.show();
      strip.setBrightness(30);
    }
  }
}
//---------------------------------------------------------------
void redBlue() { //Test
  for ( int i = 0; i < 6; i++ ) {
    for (int j = 6; j < 12; j++ ) {
      strip.setPixelColor(i, 255, 0, 0);
      strip.setPixelColor(j, 0, 0, 255);
      strip.show();
      strip.setBrightness(30);
    }
  }
}
//---------------------------------------------------------------
