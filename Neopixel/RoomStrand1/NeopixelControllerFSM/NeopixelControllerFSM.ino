#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>
#include "NeopixelFunctions.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

/*
 * ------------------------------------------------------------------------------
 *                                  Defines
 * ------------------------------------------------------------------------------
 */


#define TWO_HZ 500000

/*
 * ------------------------------------------------------------------------------
 *                                  Globals
 * ------------------------------------------------------------------------------
 */

//declare instance of PixelColor Properties type struct, 
PixelColorProperties pixelColor;

char serialByteReceived;
String inputString;
int newIntensityVal;
 
 //declare instance of KeyboardMenuState
KeyboardMenuState CurrentState;  
/*
 * ------------------------------------------------------------------------------
 *                                  Function Headers
 * ------------------------------------------------------------------------------
 */


/*
 * ------------------------------------------------------------------------------
 *                                  Setup
 * ------------------------------------------------------------------------------
 */
 
void setup() {
  InitializeNeopixels(pixelColor);
  
  //Use Serial Communication
  Serial.begin(9600); 

  //Configure Timer 1 for 2Hz interrupts (0.5s) and Timer 2 for 1kHz interrupts (1ms)
  Timer1.initialize(TWO_HZ);
 
  
  //Print Welcome Message
  Serial.println("---Welcome to Neopixel Controller Program---");
  Serial.println();

  //Initialize the state machine, and display mode
  CurrentState = MENU;    
  pixelColor.currentMode = ALL_ON;
}


/*
 * ------------------------------------------------------------------------------
 *                                  Main
 * ------------------------------------------------------------------------------
 */

void loop() {

//NonBlocking Code: 2nd, State Machine Driven Iteration of Controller Program Menu
static int mainMenuGuardFlag = 0;
//SerialInput();

  switch(CurrentState){
    case MENU:
         //if main menu has yet to be displayed, display menu
         if(mainMenuGuardFlag==0){
           Serial.println("Please Select an option:");
           Serial.println("1 -- Mode");
           Serial.println("2 -- Color");
           Serial.println("3 -- Intensity");
           Serial.println("4 -- Delay");
           Serial.println("5 -- On/Off");
           Serial.println();
           mainMenuGuardFlag = 1;
         }
         //Check for Serial Input, storing in serialByteReceived.
         //Change state based on user selection, and display menu on invalid selection.
         if (Serial.available()>0){
          serialByteReceived = Serial.read();
          Serial.print(serialByteReceived);
          Serial.println();
          if(serialByteReceived == '1'){
            CurrentState = CHANGE_MODE;
            mainMenuGuardFlag = 0;
          }
          else if(serialByteReceived == '2'){
            CurrentState = CHANGE_COLOR;
            mainMenuGuardFlag = 0;
          }
          else if(serialByteReceived == '3'){
            CurrentState = CHANGE_INTENSITY;
            mainMenuGuardFlag = 0;
          }
          else if(serialByteReceived == '5'){
            CurrentState = CHANGE_ON_OFF;
            mainMenuGuardFlag = 0;
          }
          else{
            Serial.println("Invalid Selection");
            mainMenuGuardFlag=0;
          }
         }
         break;
         //end of MENU state
    case CHANGE_MODE:
         //display CHANGE_MODE menu, then wait for serial availability
         Serial.println("Available Modes:");
         Serial.println();
         Serial.println("1-All On");
         Serial.println("2-Bounce");
         Serial.println();
         Serial.println("Please Select an option:");   
         while (Serial.available()<=0){;}
         
         serialByteReceived = Serial.read();
         Serial.print(serialByteReceived);
         Serial.println();
  
         //Call neopixel mode display functions depending on user input
         if(serialByteReceived == '1'){
            Serial.println("Displaying All On Mode"); 
            pixelColor.currentMode = ALL_ON;
            ReflectChanges(pixelColor);
         }
         else if(serialByteReceived == '2'){
            Serial.println("Displaying Bounce Mode");
            pixelColor.currentMode = PIXEL_BOUNCE;
            ReflectChanges(pixelColor);
         }
         else{
           Serial.println("Invalid Selection");
         }
           
         CurrentState = MENU;
         //end of CHANGE_MODE state
         break;
         
    case CHANGE_COLOR:
         //display CHANGE_COLOR menu, then wait for serial availability
          Serial.println("Available Colors:");
          Serial.println();
          Serial.println("1-Red");
          Serial.println("2-Magenta");
          Serial.println("3-Blue");
          Serial.println("4-Cyan");
          Serial.println("5-Green");
          Serial.println("6-Yellow");
          Serial.println();
          Serial.println("Please Select an option:");
         while (Serial.available()<=0){;}
         
         serialByteReceived = Serial.read();
         Serial.print(serialByteReceived);
         Serial.println();
  
         //Change Color. Check for invalid input and display to user
         if(SelectColor(serialByteReceived, pixelColor) == -1){
           Serial.println("Invalid Selection");
         }
         else{
          ReflectChanges(pixelColor);
         }
         CurrentState = MENU;
         //end of CHANGE_COLOR state
         break;

         //Note: CHANGE_INTENSITY currently giving invalid input after all input
         //and polling for additional input until three characters are entered. 
    case CHANGE_INTENSITY:
         //display CHANGE_INTENSITY menu, then wait for serial availability
          Serial.println("Available Intensities:");
          Serial.println();
          Serial.println("1-Off");
          Serial.println("2-Low");
          Serial.println("3-Medium");
          Serial.println("4-High");
          Serial.println("5-Very High");
          Serial.println("Please Select an option:");
         while (Serial.available()<=0){;}

         serialByteReceived = Serial.read();
         Serial.print(serialByteReceived);
         Serial.println();

        if(SelectIntensity(serialByteReceived, pixelColor) != 1){
          Serial.println("Invalid Selection");
        }
        else{
          ReflectChanges(pixelColor);
        }
           
         CurrentState = MENU;
         break; 
         //end of CHANGE_INTENSITY state

    case CHANGE_ON_OFF:

         if(pixelColor.onState == ON){  //if on, turn off
          SelectIntensity('1', pixelColor);
          SelectColor(pixelColor.currentColor, pixelColor);
          UniformColor(pixelColor, NUM_PIXELS);
          pixelColor.onState = OFF;  
         }
         else{  //if off, turn on
          SelectIntensity('3', pixelColor);
          SelectColor(pixelColor.currentColor, pixelColor);
          UniformColor(pixelColor, NUM_PIXELS);
          pixelColor.onState = ON;
         }

         CurrentState = MENU;
         break;
         //end of ON_OFF state
        
  }//end of state machine
}//end of loop()
/*
 * ------------------------------------------------------------------------------
 *                                  Functions
 * ------------------------------------------------------------------------------
 */


 

