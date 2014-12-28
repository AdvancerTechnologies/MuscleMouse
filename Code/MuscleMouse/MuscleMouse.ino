/*****************************************************************************
 **  COPYRIGHT (C) 2013, ADVANCER TECHNOLOGIES, ALL RIGHTS RESERVED.
 *****************************************************************************/

//***********************************************
// Arduino Muscle Controller - 5May2012
// Sends game control keys to game device using iCade mapping
//
// Developed by Brian E. Kaminski - Advancer Technologies
// www.AdvancerTechnologies.com
//***********************************************

void setup();
void loop();
boolean UpdateSensorState();
void SendSensors();

//Setup serial key to signify a mouse left click
byte MOUSE_LEFT_CLICK = 0x1; 

const int sensorPin = A0;
const int ledPin = 10; //5

int iThreshold = 100;
boolean bPrevSensorState=false;
boolean bCurrSensorState=false; 

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  Serial.begin(115200);
  delay(100);
}

void loop()
{  
    UpdateState();
    SendSerial();  
}
//-----------------------------------------------------------------------------------------------------------------------------------
//
//	METHOD: UpdateState
//
//	@desc	This method reads the muscle sensor's state. If the muscle is flexed, it will change the sensor's
//		state to true. If not, it will change the sensor's state to false.
//
//	@return true if a sensor state has changed from previous state
//-----------------------------------------------------------------------------------------------------------------------------------
void UpdateState()
{
  //SENSOR - RIGHT
  int val = analogRead(sensorPin);    
  if(val >= iThreshold)
  {
    bPrevSensorState = bCurrSensorState;
    bCurrSensorState = true;
  }
  else
  {
    bPrevSensorState = bCurrSensorState;
    bCurrSensorState = false;
  }
  
  delay(10);
}

//-----------------------------------------------------------------------------------------------------------------------------------
//
//	METHOD: SendSerial
//
//	@desc	This method checks the state of each sensor. If the state equals true, then it will send the appropriate
//		key to the serial comm to signify a left click and turn the LED on. If false, it will check the previous sensor state. If the 
//		previous sensor state was true, then it will turn the LED off. 
//
//-----------------------------------------------------------------------------------------------------------------------------------
void SendSerial()
{
  byte press[7] = {0xFD,0x05,0x02,0x01,0x00,0x00,0x00}; 
  byte release[7] = {0xFD,0x05,0x02,0x00,0x00,0x00,0x00}; 

  if(bCurrSensorState && !bPrevSensorState)
  {
    digitalWrite(ledPin, HIGH);
    Serial.write(press, 7);
  }
  else if(!bCurrSensorState && bPrevSensorState)
  {
    digitalWrite(ledPin, LOW);
    Serial.write(release, 7);
  }
}


