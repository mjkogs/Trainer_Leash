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
  if(digitalRead(BUTTON_PIN) == HIGH) //This if statement is designed to detect if the button has been pushed
  {
    if(buttonFlag == false) //If the buttonFlag is false, then we know that the button was just pushed. If it was true, then the button is being held down.
    {
      colourIndex++;  //We increment the colourIndex in order to advance to the next colour in the colours array.
      if (colourIndex == 4)//If we reach an index of four, we reset the index to 0 which is the start of the colours array.
      {
        colourIndex = 0;
      }
      buttonFlag = true; //We don't want one button push to advance more than one colour in the array, if the button is being held down for example. This variable prevents this from happening.
    }
    delay(100);
  }
  else //This else statement occurs whenever the button is not being pushed or held down.
  {
    buttonFlag = false; //We reset the buttonFlag since we know that the button is not being held down.
    delay(100);
  }

  for(int i = 0; i < NUM_LEDS; i++) //This for loop goes through each individual LED on the strip and sets the colour of each LED based on colourIndex
  {
    leds[i] = colours[colourIndex]; 
    FastLED.show(); //This displays the current changes made to the leds array on the LED strip.
    delay(50); //Having a delay of 50ms allows the LEDS to light up in a blinking pattern.
  }
  resetLights(); 
  FastLED.show(); //This displays the current changes made to the leds array on the LED strip.
}
