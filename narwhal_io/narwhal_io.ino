// narwhal-tx: one-hand R/C controller

// Arduino pin numbers
const byte THUMBSTICK_X_PIN = A0; // analog pin on thumbstick X
const byte THUMBSTICK_Y_PIN = A1; // analog pin on thumbstick Y
const byte THUMBSTICK_SW_PIN = D2; // digital pin on thumbstick button
const byte INDEXSTICK_X_PIN = A2; // analog pin on indexstick X
const byte INDEXSTICK_Y_PIN = A3; // analog pin on indexstick Y
const byte INDEXSTICK_SW_PIN = D3; // digital pin on indexstick button
const byte LEFT_SW_PIN = D4; // digital pin on left switch
const byte RIGHT_SW_PIN = D5; // digital pin on right switch
const byte DIAGNOSTIC_LED_PIN = D12; // digital pin on diagnostic LED

// Variables
byte thumbstickXInput;
byte thumbstickYInput;
byte indexstickXInput;
byte indexstickYInput;
int diagnosticLEDState = LOW;

// Calibration variables
byte thumbstickXMax = 0;
byte thumbstickYMax = 0;
byte indexstickXMax = 0;
byte indexstickYMax = 0;
byte thumbstickXMin = 1023;
byte thumbstickYMin = 1023;
byte indexstickXMin = 1023;
byte indexstickYMin = 1023;
byte thumbstickXCenter = 512;
byte thumbstickYCenter = 512;
byte indexstickXCenter = 512;
byte indexstickYCenter = 512;
boolean isCalibrated = false;


// Output variables
byte thumbstickXOutput; // default: roll
byte thumbstickYOutput; // default: pitch
byte indexstickXOutput; // default: yaw
byte indexsticYOutput; // default: throttle

void calibration() {
  unsigned long startMillis = millis();
  // enter calibration mode for 5 seconds
  while (millis() - startMillis < 5000) {
    thumbstickXInput = analogRead(THUMBSTICK_X_PIN);
    thumbstickYInput = analogRead(THUMBSTICK_Y_PIN);
    indexstickXInput = analogRead(INDEXSTICK_X_PIN);
    indexstickYInput = analogRead(INDEXSTICK_Y_PIN);
    // blink diagnostic LED to indicate calibration pinMode
    if (millis() - startMillis % 200) {
      if (diagnosticLEDState == LOW) {
        diagnosticLEDState = HIGH;
      } else {
        diagnosticLEDState = LOW;
      }
    }
    // record maximum joystick values
    if (thumbstickXInput > thumbstickXMax) {
      thumbstickXMax = thumbstickXInput;
    }
    if (thumbstickYInput > thumbstickYMax) {
      thumbstickYMax = thumbstickYInput;
    }
    if (indexstickXInput > indexstickXMax) {
      indexstickXMax = indexstickXInput;
    }
    if (indexstickYInput > indexstickXMax) {
      indexstickXMax = indexstickXInput;
    }
    // record minimum joystick values
    if (thumbstickXInput < thumbstickXMin) {
      thumbstickXMin = thumbstickXInput;
    }
    if (thumbstickYInput < thumbstickYMin) {
      thumbstickYMin = thumbstickYInput;
    }
    if (indexstickXInput < indexstickXMin) {
      indexstickXMin = indexstickXInput;
    }
    if (indexstickYInput < indexstickYMin) {
      indexstickYMin = indexstickYInput;
    }
  }
  // signal end of calibration
  diagnosticLEDState = LOW;
}

void setup() {
  Serial.begin(9600);
  pinMode(THUMBSTICK_SW_PIN, INPUT);
  digitalWrite(THUMBSTICK_SW_PIN, LOW);
  
  // Initial calibration, may be defined in a separate function later
  thumbstick_x_ctr = analogRead(THUMBSTICK_X_PIN)-512;
  thumbstick_y_ctr = analogRead(THUMBSTICK_Y_PIN)-512;
  indexstick_x_ctr = analogRead(INDEXSTICK_X_PIN)-512;
  indexstick_y_ctr = analogRead(INDEXSTICK_Y_PIN)-512;

}

void loop() {
  // put your main code here, to run repeatedly:

}
