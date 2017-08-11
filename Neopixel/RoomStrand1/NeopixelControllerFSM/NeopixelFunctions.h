/*
 * @Created: 8/11/17 10:40AM Josh Gier
 * @File: NeopixelFunctions.h
 * @Description:  Header File, contains the functions used to control the neopixel
 * output. 
 * 
*/

  /*
 * ------------------------------------------------------------------------------
 *                                  Defines
 * ------------------------------------------------------------------------------
 */
 
#define PIN 6
#define NUM_PIXELS 240
#define OFF 0
#define DEFAULT_INTENSITY 100


/*
 * ------------------------------------------------------------------------------
 *                                  Globals
 * ------------------------------------------------------------------------------
 */
 
//structure for neopixel color properties
typedef struct {
  uint8_t intensityRed, intensityGreen, intensityBlue, colorIntensity, currentMode;
} PixelColorProperties;



  /*
 * ------------------------------------------------------------------------------
 *                                  Prototypes
 * ------------------------------------------------------------------------------
 */

 #ifndef HEADER_NEOPIXEL_FUNCTIONS
    #define HEADER_NEOPIXEL_FUNCTIONS
    //insert function prototypes used in NeopixelFunctions here
    void InitializeNeopixels(PixelColorProperties& pixelColor);
    void PixelBounce(int delayTime, PixelColorProperties& pixelColor, int numberPixelsOn, int numberPixels);
    void ColorProgression(PixelColorProperties& pixelColor);
    void UniformColor(PixelColorProperties& pixelColor, uint16_t numberPixelsOn);
    int SelectColor(char colorSelection, PixelColorProperties& pixelColor);
 
 #endif
