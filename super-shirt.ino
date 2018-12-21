#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            12
#define LED            8

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      4

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, LED, NEO_GRB + NEO_KHZ800);

//Constants
const int SUPER_HERO_DELAY = 5000;      // 5 seconds when you activate a super hero power
const int MAX_LED_BRIGHTNESS = 25;      // Max brightness for the onboard LED - mostly used for pulse
const int LED_PULSE_DELAY = 125;        // Controls the speed of the onboard pulse

const int STRENGTH_BUTTON_PIN = 10;     // the number of the strength power pin
const int FLY_BUTTON_PIN = 9;           // the number of the flying power pin
const int SPEED_BUTTON_PIN = 3;         // the number of the speed power pin
const int XRAY_BUTTON_PIN = 2;          // the number of the x-ray power pin

// Super Power Status
int strengthState = 0;                  // variable for reading the strength status
int flyState = 0;                       // variable for reading the fly status
int speedState = 0;                     // variable for reading the speed status
int xrayState = 0;                      // variable for reading the x-ray status

// Pulse Variables
int ledBrightness = 50;
bool ledBrightnessDown = true;

// State Variables
bool buttonPressed = false;
int currentStep = 0;

void setup() {
  // INPUTS
  pinMode(STRENGTH_BUTTON_PIN, INPUT_PULLUP);
  pinMode(FLY_BUTTON_PIN, INPUT_PULLUP);
  pinMode(SPEED_BUTTON_PIN, INPUT_PULLUP);
  pinMode(XRAY_BUTTON_PIN, INPUT_PULLUP);

  // OUTPUTS
  led.begin();    // This initializes onboard NeoPixel
  led.setPixelColor(0, led.Color(255,255,255)); // Set to white
  led.setBrightness(MAX_LED_BRIGHTNESS);
  led.show();
  
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50); 
}

void loop() {

  if (buttonPressed) {
    if (currentStep == NUMPIXELS) {     // button was pressed and this is the first loop
      currentStep--;
      Serial.print("first step  ");
      Serial.print(currentStep);
      delay(SUPER_HERO_DELAY);
    } else if (currentStep != 0) {      // turning off LEDs one by one
      pixels.setPixelColor(currentStep, pixels.Color(0,0,0));
      pixels.show(); 
      currentStep--;
      Serial.print("count down step  ");
      Serial.print(currentStep);
      delay(SUPER_HERO_DELAY);    
    } else {                            // all LEDs are off, reset buttonPressed state
      Serial.print("final step  ");
      Serial.print(currentStep);
      buttonPressed = false;    
    }
  } else {
  
    strengthState = digitalRead(STRENGTH_BUTTON_PIN);
    flyState = digitalRead(FLY_BUTTON_PIN);
    speedState = digitalRead(SPEED_BUTTON_PIN);
    xrayState = digitalRead(XRAY_BUTTON_PIN);
    
    
    if (strengthState == LOW) {
      for(int i=0;i<NUMPIXELS;i++){  
        pixels.setPixelColor(i, pixels.Color(0,150,0)); // Green
        pixels.show();
      }
      led.setPixelColor(0, pixels.Color(0, 150, 0));
      led.setBrightness(MAX_LED_BRIGHTNESS);
      led.show();
  
      buttonPressed = true;
      currentStep = NUMPIXELS;
    } else if (flyState == LOW) {
      for(int i=0;i<NUMPIXELS;i++){  
        pixels.setPixelColor(i, pixels.Color(0,0,150)); // Blue
        pixels.show(); 
      }
      led.setPixelColor(0, pixels.Color(0, 0, 150));
      led.setBrightness(MAX_LED_BRIGHTNESS);
      led.show();
  
      buttonPressed = true;
      currentStep = NUMPIXELS;
    } else if (speedState == LOW) {
       for(int i=0;i<NUMPIXELS;i++){  
        pixels.setPixelColor(i, pixels.Color(150,0,0)); // Red
        pixels.show(); 
      }
      led.setPixelColor(0, pixels.Color(150, 0, 0));
      led.setBrightness(MAX_LED_BRIGHTNESS);
      led.show();
  
      buttonPressed = true;
      currentStep = NUMPIXELS;
     } else if (xrayState == LOW) {
       for(int i=0;i<NUMPIXELS;i++){  
        pixels.setPixelColor(i, pixels.Color(255,255,0)); // Yellow
        pixels.show(); 
      }
      led.setPixelColor(0, pixels.Color(255,255,0));
      led.setBrightness(MAX_LED_BRIGHTNESS);
      led.show();
  
      buttonPressed = true;
      currentStep = NUMPIXELS;
    } else {
      for(int i=0;i<NUMPIXELS;i++) {
        pixels.setPixelColor(i, pixels.Color(0,0,0)); // Off
        pixels.show(); 
      }
      if (ledBrightness <= 1 && ledBrightnessDown) {
        ledBrightnessDown = false;
        ledBrightness = 2;
      } else if (ledBrightness >= MAX_LED_BRIGHTNESS && !ledBrightnessDown) {
        ledBrightnessDown = true;
        ledBrightness = MAX_LED_BRIGHTNESS - 1;
      } else if (ledBrightnessDown) {
        ledBrightness = ledBrightness - 1;  
      } else {
        ledBrightness = ledBrightness + 1;  
      }
      led.setPixelColor(0, pixels.Color(255,255,255));
      led.setBrightness(ledBrightness);
      led.show();
  
      delay(LED_PULSE_DELAY);
    }  
  }
}

void breathAll() {
  for (int i; i < 225 ; i++) {
    for(int j=0; j<led.numPixels(); j++) {
      led.setPixelColor(j, led.Color(i+15,i,0)); // yellow with a little extra red to make it warmer 
    }
    led.show();
    delay(10);
  }
  for (int i = 225; i > 0; i--) {
    for(int j=0; j<led.numPixels(); j++) {
      led.setPixelColor(j, led.Color(i+15,i,0));
    }
    led.show();
    delay(10);
  }
}
