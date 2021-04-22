#include <stdio.h>
#include <stdlib.h>
#include <FastLED.h>

#define BUTTON_PIN 10   // CHANGE THE NUMBER TO THE PIN NUMBER THAT YOU ARE USING ON THE FLORA FOR THE TACTILE BUTTON
#define LED_PIN 9       // CHANGE THE NUMBER TO THE PIN NUMBER THAT YOU ARE USING ON THE FLORA FOR THE LED STRIP
#define NUM_LEDS 16     // CHANGE THE NUMBER TO THE NUMBER OF LED'S ON YOUR STRIP

//These are all the CRGB objects that create the different colours on the LED strips
//Each object has RGB values that you can set in order to change the colour
CRGB red = CRGB(255,0,0);
CRGB green = CRGB(0,255,0);
CRGB blue = CRGB(0,0,255);
CRGB off = CRGB(0,0,0);

//I have created an array of the CRGB objects in order to cycle through all four colours
CRGB colours[] = {off,red,green,blue};

//This array is used to cycle through each individual LED on the LED strip
CRGB leds[NUM_LEDS];

int colourIndex = 0;  //This variable is used to keep track of which colour the LED strip is currently displaying

bool buttonFlag = false; //This bool variable keeps track of when the button is just pushed and also keep tracks of if the button is being held down.


void resetLights() //This function is used to in order to turn all the LED's off in the LED strip
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = off;
  } 
}


void setup() 
{
  // put your setup code here, to run once:
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}


void loop() { 
  if(digitalRead(BUTTON_PIN) == HIGH) //This if_statement
  {
    if(buttonFlag == false)
    {
      Serial.println("Button was just pushed");
      colourIndex++;
      if (colourIndex == 4)
      {
        colourIndex = 0;
      }
      buttonFlag = true;
      delay(100);
    }
    else
    {
      Serial.println("Buttons is being held down");
      delay(100);
    }
  }
  else
  {
    Serial.println("Buttons has not been pushed");
    buttonFlag = false; 
    delay(100);
  }

  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = colours[colourIndex];
    FastLED.show();
    delay(50);
  }
  resetLights();
  FastLED.show();
  Serial.println(colours[colourIndex]);
}
