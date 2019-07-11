// narwhal-tx: one-hand R/C controller

// Arduino pin numbers
const float thumbstick_x_pin = A0; // analog pin on thumbstick X
const float thumbstick_y_pin = A1; // analog pin on thumbstick Y
const int thumbstick_sw_pin = D2; // digital pin on thumbstick button
const float indexstick_x_pin = A2; // analog pin on indexstick X
const float indexstick_y_pin = A3; // analog pin on indexstick Y
const int indexstick_sw_pin = D3; // digital pin on indexstick button

// Calibration centers
float thumbstick_x_ctr;
float thumbstick_y_ctr;
float indexstick_x_ctr;
float indexstick_y_ctr;

// Output variables
float thumbstick_x_out;
float thumbstick_y_out;
float indexstick_x_out;
float indexstick_y_out;

void setup() {
  pinMode(thumbstick_sw_pin, INPUT);
  digitalWrite(thumbstick_sw_pin, LOW);
  Serial.begin(9600);
  // Initial calibration, may be defined in a separate function later
  thumbstick_x_ctr = analogRead(thumbstick_x_pin)-512;
  thumbstick_y_ctr = analogRead(thumbstick_y_pin)-512;
  indexstick_x_ctr = analogRead(indexstick_x_pin)-512;
  indexstick_y_ctr = analogRead(indexstick_y_pin)-512;

}

void loop() {
  // put your main code here, to run repeatedly:

}
