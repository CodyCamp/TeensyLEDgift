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

int buttonStateMode = 0;
int lastButtonStateMode = 0;

int buttonStateColor = 0;
int lastButtonStateColor = 0;

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
  pinMode(13, HIGH);
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
    checkModeButton(modeButton, mState);
    checkColorButton(greenButton, gState);
    checkModeButton(modeButton, mState);
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
  buttonStateMode = digitalRead(modeButton);
  if (buttonStateMode != lastButtonStateMode) {
    if (buttonStateMode == HIGH) {
      modeButtonState++;
      if (modeButtonState > 5)
        modeButtonState = 1;
    } 
  }
  lastButtonStateMode = buttonStateMode;
}

void checkColorButton(int colorButton, int& colorButtonState) 
{
  buttonStateColor = digitalRead(colorButton);
  if (buttonStateColor != lastButtonStateColor) {
    if (buttonStateColor == HIGH) {
      colorButtonState++;
      if (colorButtonState > 5)
        colorButtonState = 1;
    } 
  }
  lastButtonStateColor = buttonStateColor;
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