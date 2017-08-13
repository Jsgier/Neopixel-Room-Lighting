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
#define ON 1
#define OFF 0
#define DEFAULT_INTENSITY 100
#define DELAY_TIME 20
#define NUM_PIXELS_ON 6

#define RED '1'
#define MAGENTA '2'
#define BLUE '3'
#define CYAN '4'
#define GREEN '5'
#define YELLOW '6'
#define COLOR_OFF '7'


//enumerated type for state machine governing control program behavior
typedef enum {MENU, CHANGE_MODE, CHANGE_COLOR, CHANGE_INTENSITY, CHANGE_ON_OFF} KeyboardMenuState;
typedef enum {ALL_ON, PIXEL_BOUNCE} DisplayMode;



/*
 * ------------------------------------------------------------------------------
 *                                  Globals
 * ------------------------------------------------------------------------------
 */
 
//structure for neopixel color properties
typedef struct {
  uint8_t intensityRed, intensityGreen, intensityBlue, colorIntensity;
  char currentColor;
  int onState;
  DisplayMode currentMode;
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
    int SelectIntensity(char intensitySelection, PixelColorProperties& pixelColor);
    void ReflectChanges(PixelColorProperties& pixelColor);
 
 #endif

