/*
 * @Created: 8/11/17 10:40AM Josh Gier
 * @File: NeopixelFunctions.cpp
 * @Description:  Source File, contains the functions used to control the neopixel
 * output. 
 * 
*/


 /*
 * ------------------------------------------------------------------------------
 *                                  Includes
 * ------------------------------------------------------------------------------
 */

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "NeopixelFunctions.h"

/*
 * ------------------------------------------------------------------------------
 *                                  Defines
 * ------------------------------------------------------------------------------
 */

 /*
 * ------------------------------------------------------------------------------
 *                                  Module Variables
 * ------------------------------------------------------------------------------
 */
//define pixels class instance
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);


 /*
 * ------------------------------------------------------------------------------
 *                                  Functions
 * ------------------------------------------------------------------------------
 */

 /*
 * @Created: 8/11/17 11:14AM Josh Gier
 * @Function: InitializeNeopixels
 * @Parameters: PixelColorProperties& pixelColor - struct containing color and intensity
 * of neopixels
 * @Return: void
 * @Description:  Initializes the neopixel library for use. Default color is red. Default  
 * intensity can be found in the header file. 
 */
void InitializeNeopixels(PixelColorProperties& pixelColor){
 pixels.begin(); // This initializes the NeoPixel library.
 
  //initalize pixel color to red, and intensity
  pixelColor.colorIntensity = DEFAULT_INTENSITY;
  pixelColor.currentColor = RED;    //Default to red
  
}

/*
 * @Created: 8/9/17 8:38PM Josh Gier
 * @Function: PixelBounce
 * @Parameters: int delayTime - Sets the delay between pixels
 *              int intensityRed,Green,Blue - sets input color parameters for pixels
 *              int numberPixelsOn - sets number of pixels on at a given time
 *              int numberPixels - total number of pixels
 * @Return: void
 * @Description:  Takes a static color value, delay time, and number of pixels on. Outputs 
 *                a bouncing group of pixels, going from the first pixels in the strip to 
 *                the last, and then back to the first. Relies on external function for 
 *                looping.   
 */
void PixelBounce(int delayTime, PixelColorProperties& pixelColor, int numberPixelsOn, int numberPixels){
    
    //For loop controlling the forward direction of pixels
    for(int i=0; i<(numberPixels+numberPixelsOn); i++){
      pixels.setPixelColor(i, pixels.Color(pixelColor.intensityRed,pixelColor.intensityGreen,pixelColor.intensityBlue)); 
      pixels.setPixelColor(i-numberPixelsOn, OFF);
      pixels.show();  
      ColorProgression(pixelColor);
      delay(delayTime); // Delay for a period of time (in milliseconds). Here is the blocking portion of this function
    }
    

    //For loop controlling the reverse direction of pixels
    for(int i=numberPixels; i>(-numberPixelsOn); i--){
      pixels.setPixelColor(i, pixels.Color(pixelColor.intensityRed,pixelColor.intensityGreen,pixelColor.intensityBlue)); 
      pixels.setPixelColor(i+numberPixelsOn, OFF);
      pixels.show();      
      ColorProgression(pixelColor);
      delay(delayTime); // Delay for a period of time (in milliseconds). Here is the blocking portion of this function
    }
}

/*
 * @Created: 8/10/17 12:16AM Josh Gier
 * @Function: ColorProgression
 * @Parameters:  struct PixelColorProperties - holds the current RGB values to be output to the neopixel
 *               as well as the intensity of color output to the neopixel
 * @Return: none - changes a global struct using pointers.
 * @Description:  Cycles between the 6 possible color outputs - red, magenta, blue, cyan, green, yellow. 
 *                Changes are reflected in the PixelColorProperties input struct. 
 */

 void ColorProgression(PixelColorProperties& pixelColor){

    if((pixelColor.intensityRed == 0) && (pixelColor.intensityBlue == 0) && (pixelColor.intensityGreen == 0)){  //initialization state
      pixelColor.intensityRed = pixelColor.colorIntensity;
    }
    else if((pixelColor.intensityRed != 0) && (pixelColor.intensityBlue == 0) && (pixelColor.intensityGreen == 0)){  //magenta
      pixelColor.intensityRed = pixelColor.colorIntensity/2;
      pixelColor.intensityBlue = pixelColor.colorIntensity/2;
    }
    else if ((pixelColor.intensityRed != 0) && (pixelColor.intensityBlue !=0) && (pixelColor.intensityGreen == 0)){   //blue
      pixelColor.intensityRed = 0;
      pixelColor.intensityBlue = pixelColor.colorIntensity;
    }
    else if((pixelColor.intensityRed == 0) && (pixelColor.intensityBlue != 0) && (pixelColor.intensityGreen == 0)){  //cyan
      pixelColor.intensityGreen = pixelColor.colorIntensity/2;
      pixelColor.intensityBlue = pixelColor.colorIntensity/2;
    }
    else if((pixelColor.intensityRed == 0) && (pixelColor.intensityBlue != 0) && (pixelColor.intensityGreen != 0)){  //green
      pixelColor.intensityGreen = pixelColor.colorIntensity;
      pixelColor.intensityBlue = 0;
    }
    else if((pixelColor.intensityRed == 0) && (pixelColor.intensityBlue == 0) && (pixelColor.intensityGreen != 0)){  //yellow
      pixelColor.intensityGreen = pixelColor.colorIntensity/2;
      pixelColor.intensityRed = pixelColor.colorIntensity/2;
    }
    else if((pixelColor.intensityRed != 0) && (pixelColor.intensityBlue == 0) && (pixelColor.intensityGreen != 0)){  //red
      pixelColor.intensityGreen = 0;
      pixelColor.intensityRed = pixelColor.colorIntensity;
    }
                     
 }

/*
 * @Created: 8/10/17 7:55PM Josh Gier
 * @Function: UniformColor
 * @Parameters:  struct PixelColorProperties - holds the current RGB values to be output to the neopixel
 *               as well as the intensity of color output to the neopixel
 * @Return: none - outputs color to light
 * @Description:  Changes color to one color, defined by input struct pixelColor. Intensity also defined in struct.
 */
 void UniformColor(PixelColorProperties& pixelColor, uint16_t numberPixelsOn){
  for(int i=0; i< numberPixelsOn; i++){
    pixels.setPixelColor(i, pixels.Color(pixelColor.intensityRed,pixelColor.intensityGreen,pixelColor.intensityBlue));
   }
    pixels.show();
 }

/*
 * @Created: 8/11/17 12:24PM Josh Gier
 * @Function: colorSelection
 * @Parameters:  char colorSelection - valid numbers are 1-6, corresponding to the following colors:
 *               1-Red 2-Magenta 3-Blue 4-Cyan 5-Green 6-Yellow
 *               PixelColorProperties& pixelColor - struct to be updated with selected color
 * @Return: Changes are made to struct. Returns 1 for success, -1 for error. 
 * @Description:  Changes color of pixels, defined in struct, to color selected via input parameter colorSelection.
 *                Relies on calling function to display error message to user. 
 */
 int SelectColor(char colorSelection, PixelColorProperties& pixelColor){
  if(colorSelection == RED){  //red
     pixelColor.intensityRed = pixelColor.colorIntensity;
     pixelColor.intensityBlue = 0;
     pixelColor.intensityGreen = 0; 
     pixelColor.currentColor = colorSelection;
     return 1;
  }
  else if(colorSelection == MAGENTA){  //magenta
     pixelColor.intensityRed = pixelColor.colorIntensity/2;
     pixelColor.intensityBlue = pixelColor.colorIntensity/2;
     pixelColor.intensityGreen = 0;
     pixelColor.currentColor = colorSelection;
     return 1;
  }
  else if(colorSelection == BLUE){  //blue
     pixelColor.intensityRed = 0;
     pixelColor.intensityBlue = pixelColor.colorIntensity;
     pixelColor.intensityGreen = 0;
     pixelColor.currentColor = colorSelection;
     return 1;
  }
  else if(colorSelection == CYAN){  //cyan
     pixelColor.intensityRed = 0;
     pixelColor.intensityBlue = pixelColor.colorIntensity/2;
     pixelColor.intensityGreen = pixelColor.colorIntensity/2;
     pixelColor.currentColor = colorSelection;
     return 1;
  }
  else if(colorSelection == GREEN){  //green
     pixelColor.intensityRed = 0;
     pixelColor.intensityBlue = 0;
     pixelColor.intensityGreen = pixelColor.colorIntensity;
     pixelColor.currentColor = colorSelection;
     return 1;
  }
  else if(colorSelection == YELLOW){  //yellow
     pixelColor.intensityRed = pixelColor.colorIntensity/2;
     pixelColor.intensityBlue = 0;
     pixelColor.intensityGreen = pixelColor.colorIntensity/2;
     pixelColor.currentColor = colorSelection;
     return 1;
  }
  else if(colorSelection == COLOR_OFF){  //magenta
     pixelColor.intensityRed = 0;
     pixelColor.intensityBlue = 0;
     pixelColor.intensityGreen = 0;
     pixelColor.currentColor = colorSelection;
     return 1;
  }

  else{return -1;}  //invalid input
  }

  /*
 * @Created: 8/11/17 12:24PM Josh Gier
 * @Function: SelectIntensity
 * @Parameters:  char intensitySelection - valid numbers are 1-5, corresponding to the following values:
 *               1-Off 2-Low 3-Medium 4-High 5-Very High
 *               PixelColorProperties& pixelColor - struct to be updated with selected intensity
 * @Return: Changes are made to struct. Returns 1 for success, -1 for error. 
 * @Description:  Changes intensity of pixels, defined in struct, to intensity selected via input parameter intensitySelection.
 *                Relies on calling function to display error message to user. 
 */
 int SelectIntensity(char intensitySelection, PixelColorProperties& pixelColor){
  if(intensitySelection == '1'){  //off
     pixelColor.colorIntensity = 0;
     SelectColor(pixelColor.currentColor, pixelColor); 
     return 1;
  }
  else if(intensitySelection == '2'){  //low
     pixelColor.colorIntensity = DEFAULT_INTENSITY/4;
     SelectColor(pixelColor.currentColor, pixelColor);  
     return 1;
  }
    else if(intensitySelection == '3'){  //medium
     pixelColor.colorIntensity = DEFAULT_INTENSITY/2;
     SelectColor(pixelColor.currentColor, pixelColor);  
     return 1;
  }
    else if(intensitySelection == '4'){  //high
     pixelColor.colorIntensity = DEFAULT_INTENSITY*(3/4);
     SelectColor(pixelColor.currentColor, pixelColor);  
     return 1;
  }
    else if(intensitySelection == '5'){  //very high
     pixelColor.colorIntensity = DEFAULT_INTENSITY;
     SelectColor(pixelColor.currentColor, pixelColor);  
     return 1;
  }

  else{return -1;}  //invalid input
  }

    /*
 * @Created: 8/13/17 10:39AM Josh Gier
 * @Function: ReflectChanges
 * @Parameters: PixelColorProperties& pixelColor - struct, contains currentMode enumerates type
 * @Return: none
 * @Description:  Helper function, uses current mode to display changes to neopixels given struct.  
 */ 
 void ReflectChanges(PixelColorProperties& pixelColor){

  if(pixelColor.currentMode == ALL_ON){
    UniformColor(pixelColor, NUM_PIXELS);
    }
  else if (pixelColor.currentMode == PIXEL_BOUNCE){
    PixelBounce(DELAY_TIME, pixelColor, NUM_PIXELS_ON, NUM_PIXELS);
    }
 
 }

