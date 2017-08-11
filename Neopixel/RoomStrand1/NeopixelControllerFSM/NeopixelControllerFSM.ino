

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

#define NUM_PIXELS_ON 6
#define DELAY_TIME 20

/*
 * ------------------------------------------------------------------------------
 *                                  Globals
 * ------------------------------------------------------------------------------
 */

//enumerated type for state machine governing control program behavior
typedef enum {MENU, CHANGE_MODE, CHANGE_COLOR, CHANGE_INTENSITY} KeyboardMenuState;

//declare instance of PixelColor Properties type struct, 
PixelColorProperties pixelColor;

char serialByteReceived;
String inputString " ";
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
  
  //Print Welcome Message
  Serial.println("---Welcome to Neopixel Controller Program---");
  Serial.println();

  //Initialize the state machine
  CurrentState = MENU;    
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
            UniformColor(pixelColor, NUM_PIXELS);
         }
         else if(serialByteReceived == '2'){
            Serial.println("Displaying Bounce Mode");
            PixelBounce(DELAY_TIME, pixelColor, NUM_PIXELS_ON, NUM_PIXELS);
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
         CurrentState = MENU;
         //end of CHANGE_COLOR state
         break;
         
    case CHANGE_INTENSITY:
         //display CHANGE_INTENSITY menu, then wait for serial availability
          Serial.println("Please Enter a value from 1 to 255");
          Serial.println();
         while (Serial.available()<=0){;}

         //read 3 bytes from the serial port, to receive the maximum number.
         //Concatenate the input string, then convert to int newIntensityVal. 
         serialByteReceived = Serial.read();
         Serial.print(serialByteReceived);
         if(isDigit(serialByteReceived){
          inputString+=serialByteReceived;
         }
         while (Serial.available()<=0){;}
         serialByteReceived = Serial.read();
         Serial.print(serialByteReceived);
         if(isDigit(serialByteReceived){
          inputString+=serialByteReceived;
         }
         while (Serial.available()<=0){;}
         serialByteReceived = Serial.read();
         Serial.print(serialByteReceived);
         if(isDigit(serialByteReceived){
          inputString+=serialByteReceived;
         }
         Serial.println();

         newIntensityVal = inputString.toInt();
  
         //If in range, change pixelColor struct. Else, display error. 
         if((newIntensityVal>=1)&&(newIntensityVal<=255)){
          pixelColor.colorIntensity = (int)serialByteReceived;
         }
         else{
           Serial.println("Invalid Selection");
         }
           
         CurrentState = MENU;
         //end of CHANGE_INTENSITY state
         break;
  }//end of state machine
}//end of loop()
/*
 * ------------------------------------------------------------------------------
 *                                  Functions
 * ------------------------------------------------------------------------------
 */


 

