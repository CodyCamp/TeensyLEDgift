void setup()   {                
  Serial.begin(38400);
  pinMode(7, INPUT);
  pinmode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
}

//////////////////// button pins ///////////////////////////////
const int modeButton = 7;   //pin mode button is connected to

const int redButton = 8;      //pin red button is connected to
const int greenButton = 9;    //pin green button is connected to
const int blueButton = 10;    //pib blue button is connected to

const int redPin = 21;
const int greenPin = 22;
const int bluePin = 23;

////////////////////////////////////////////////////////////////


int modeButtonState = 1;
int& mState = modeButtonState;

int redButtonState = 0;
int& rState = redButtonState;
int greenButtonState = 0;
int& gState = greenButtonState;
int blueButtonState = 0;
int& bState = blueButtonState;

void checkButton(int, int&);

void loop()                     
{
  while(modeButtonState == 1)        //Used as an off mode, sets LED's off.
  {
    Serial.println("1");
    setColorRGB(0, 0, 0);
    
    checkModeButton(modeButton, mState);
    delay(500);
  }
  while(modeButtonState == 2)       //pick your own color using rgb buttons. 10 intensities of each color.
  {
    Serial.println("2");
    setColorRGB((255*(redButtonState/10)),(255*(greenButtonState/10)),(255*(blueButtonState/10)));
    
    checkColorButton(redButton, rState);
    checkColorButton(greenButton, gState);
    checkColorButton(blueButton, bState);

    checkModeButton(modeButton, mState);
    delay(500);
  }
  
  while(modeButtonState == 3)      //color fade, pick how fast they fade w/ 3 pre-determined speeds
  {
    Serial.println("3");
    
    checkModeButton(modeButton, mState);
    delay(500);
  }
  while(modeButtonState == 4)       //color fade different for each strip, pick speeds like above 
  {
    Serial.println("4");
    
    checkModeButton(modeButton, mState);
    delay(500);
  }
  while(modeButtonState ==  5)      //color changes with music
  {
    Serial.println("5");
    
    checkModeButton(modeButton, mState);
    delay(500);
  }
  

  checkModeButton(modeButton, mState);
}

void setColorRGB(int red, int green, int blue) {
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
}

void checkColorButton(int colorButton, int& colorButtonState)
{
  if(digitalRead(colorButton) != HIGH && colorButtonState < 10)
    colorButtonState++;
  else if(digitalRead(colorButton) != HIGH)
    colorButtonState = 0;
}