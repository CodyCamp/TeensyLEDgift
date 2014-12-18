////////////////////////////////////////////////////////////////
////////////// button pins and output pins /////////////////////
////////////////////////////////////////////////////////////////
const int modeButton = 7;   //pin mode button is connected to

const int redButton = 8;      //pin connected to red button
const int greenButton = 9;    //pin connecte to green button
const int blueButton = 10;    //pib blue button is connected to

const int redPin = 21;        //RGB for strip one (top)
const int greenPin = 22;
const int bluePin = 23;

//const int redPinTwo         //RGB for strip two (bottom)
//const int greenPinTwo
//const int bluePinTwo

////////////////////////////////////////////////////////////////


int modeButtonState = 1;
int& mState = modeButtonState;

int redButtonState = 0;
int& rState = redButtonState;
int greenButtonState = 0;
int& gState = greenButtonState;
int blueButtonState = 0;
int& bState = blueButtonState;

void checkModeButton(int modeButton, int& modeButtonState);
void checkColorButton(int colorButton, int& colorButtonState);
int colorVal(int);
void colorFader();


void setup()   {                
  Serial.begin(38400);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}

void loop()                     
{
  
  while(modeButtonState == 1)        //Used as an off mode, sets LED's off.
  {
    Serial.println("1");  //debugging
    setColorRGB(0, 0, 0);
    
    delay(500);
    checkModeButton(modeButton, mState);
  }

  while(modeButtonState == 2)       //pick your own color using rgb buttons. 10 intensities of each color.
  {
    Serial.println("2");  //debugging
    
    int valRedLED, valGreenLED, valBlueLED;

    valRedLED = colorVal(redButtonState);
    valGreenLED = colorVal(greenButtonState);
    valBlueLED = colorVal(blueButtonState);

    setColorRGB(valRedLED, valGreenLED, valBlueLED);
    
    checkColorButton(redButton, rState);
    checkColorButton(greenButton, gState);
    checkColorButton(blueButton, bState);

    checkModeButton(modeButton, mState);
    delay(500);
  }
  
  while(modeButtonState == 3)      //color fade, pick how fast they fade w/ 3 pre-determined speeds
  {
    Serial.println("3");   //debugging
    
    colorFader();   //create input variable for delay

    checkModeButton(modeButton, mState);
    delay(500);
  }

  while(modeButtonState == 4)       //color fade different for each strip, pick speeds like above 
  {
    Serial.println("4");  //debugging
    
    checkModeButton(modeButton, mState);
    delay(500);
  }

  while(modeButtonState ==  5)      //color changes with music
  {
    Serial.println("5");  //debugging
    
    checkModeButton(modeButton, mState);
    delay(500);
  }

  checkModeButton(modeButton, mState);
  delay(500);
}

void setColorRGB(int red, int green, int blue) 
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

void checkModeButton(int modeButton, int& modeButtonState)
{
  if(digitalRead(modeButton) != HIGH && modeButtonState < 5)
    modeButtonState++;
  else if(digitalRead(modeButton) != HIGH)
    modeButtonState = 1;
  delay(5);
}

void checkColorButton(int colorButton, int& colorButtonState)
{
  if(digitalRead(colorButton) != HIGH && colorButtonState < 10)
    colorButtonState++;
  else if(digitalRead(colorButton) != HIGH)
    colorButtonState = 0;
  delay(5);
}

void colorFader()
{
  int rgbColor[3];
 
  // Start off with red.
  rgbColor[0] = 255;
  rgbColor[1] = 0;
  rgbColor[2] = 0;  
 
  // Choose the colours to increment and decrement.
  for (int decColor = 0; decColor < 3; decColor += 1) {
    int incColor = decColor == 2 ? 0 : decColor + 1;
 
    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColor[decColor] -= 1;
      rgbColor[incColor] += 1;
      
      setColorRGB(rgbColor[0], rgbColor[1], rgbColor[2]);
      
      checkModeButton(modeButton, mState);
      if(modeButtonState != 3)
        break;

      delay(5);
    }
    checkModeButton(modeButton, mState);
    if(modeButtonState != 3)
        break;
  }  
  checkModeButton(modeButton, mState);
}

int colorVal(int level)   //use array, 2 lines of code
{
  int colorValArray[] = {0, 25, 51, 77, 102, 128, 153, 179, 204, 230, 255};
  return colorValArray[level];
}

/*
example arduino button code

  State change detection (edge detection)
    
 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.
 
 This example shows how to detect when a button or button changes from off to on
 and on to off.
    
 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
   most Arduino boards)
 
 created  27 Sep 2005
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.
    
 http://arduino.cc/en/Tutorial/ButtonStateChange
 
 

// this constant won't change:
const int  buttonPin = 7;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off"); 
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;

  
  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
  
}

*/
