// narwhal-tx: one-hand R/C controller

// Arduino pin numbers
const byte THUMBSTICK_X_PIN = A0; // analog pin on thumbstick X
const byte THUMBSTICK_Y_PIN = A1; // analog pin on thumbstick Y
const byte THUMBSTICK_SW_PIN = 2; // digital pin on thumbstick button
const byte INDEXSTICK_X_PIN = A2; // analog pin on indexstick X
const byte INDEXSTICK_Y_PIN = A3; // analog pin on indexstick Y
const byte INDEXSTICK_SW_PIN = 3; // digital pin on indexstick button
const byte LEFT_SW_PIN = 4; // digital pin on left switch
const byte RIGHT_SW_PIN = 5; // digital pin on right switch
const byte DIAGNOSTIC_LED_PIN = 12; // digital pin on diagnostic LED

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
byte thumbstickXMin = 255;
byte thumbstickYMin = 255;
byte indexstickXMin = 255;
byte indexstickYMin = 255;
byte thumbstickXCenter;
byte thumbstickYCenter;
byte indexstickXCenter;
byte indexstickYCenter;
boolean isCalibrated = false;


// Output variables
byte thumbstickXOutput; // default: roll
byte thumbstickYOutput; // default: pitch
byte indexstickXOutput; // default: yaw
byte indexstickYOutput; // default: throttle

void calibration() {
  Serial.println("Calibration started.");
  unsigned long startMillis = millis();
  diagnosticLEDState = HIGH;
  // enter calibration mode for 5 seconds
  while (millis() - startMillis < 5000) {
    thumbstickXInput = analogRead(THUMBSTICK_X_PIN);
    Serial.print("Thumbstick X Input: ");
    Serial.println(thumbstickXInput);
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
  isCalibrated = true;
  Serial.println("Calibration complete.");
  Serial.print("Thumbstick X Min: ");
  Serial.print(thumbstickXMin);
  Serial.print("  Thumbstick Y Max: ");
  Serial.println(thumbstickYMax);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Setup in progress.");
  pinMode(THUMBSTICK_SW_PIN, INPUT);
  digitalWrite(THUMBSTICK_SW_PIN, LOW);
  
  // Initial calibration, may be defined in a separate function later
  calibration();
  Serial.println("Setup complete.");
}

void loop() {
  // Updates joystick inputs
  thumbstickXInput = analogRead(THUMBSTICK_X_PIN);
  thumbstickYInput = analogRead(THUMBSTICK_Y_PIN);
  indexstickXInput = analogRead(INDEXSTICK_X_PIN);
  indexstickYInput = analogRead(INDEXSTICK_Y_PIN);
  // Updates joystick outputs
  thumbstickXOutput = map(thumbstickXInput, thumbstickXMin, thumbstickXMax, -128, 128);
  thumbstickYOutput = map(thumbstickYInput, thumbstickYMin, thumbstickYMax, -128, 128);
  indexstickXOutput = map(indexstickXInput, indexstickXMin, indexstickXMax, -128, 128);
  indexstickYOutput = map(indexstickYInput, indexstickYMin, indexstickYMax, 0, 256); 
  // Prints values to serial for debug purposes
  Serial.print("Thumbstick X Output: ");
  Serial.print(thumbstickXOutput);
  Serial.print("  Thumbstick Y Output: ");
  Serial.print(thumbstickYOutput);
  Serial.print("  Indexstick X Output: ");
  Serial.print(indexstickXOutput);
  Serial.print("  Indexstick Y Output: ");
  Serial.println(indexstickYOutput);
}
