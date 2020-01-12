// !!!!!!!!!!!!!!!!
// CONNECT red to +5V
// CONTECT black to GND
// !!!!!!!!!!!!!!!!

// Arduino stepper motor control code
#include <Stepper.h>

// Change this to the number of steps on your motor
#define STEPS 32

// Constants
const int AnalogResistorOne = A1; // Photoresistor at Arduino analog pin A1 (grey wire, left side)
const int AnalogResistorTwo = A2; // Photoresistor at Arduino analog pin A2 (green wire, right side)

// -------------- CHECK THIS --------------
// pin 8 - yellow wire - to IN1
// pin 9 - orange wire - to IN2
// pin 10 - white wire - to IN3
// pin 11 - purple wire - to IN4
Stepper stepper(STEPS, 8, 10, 9, 11); // Define stepper and pins for connection

const int stepperRatio = 100; // diff from left to right
// -----------------------------------------

// Variables
int resistorOne, resistorTwo;// Store value from photoresistor (0-1023)
int valStepperLeft = 40; // Init value for stepper left move
int valStepperRight = -40; // Init value for stepper right move
int checkMovement = 0; // Init value for diff from left and right

void setup(){
 pinMode(AnalogResistorOne, INPUT); // Set Resistor - A1 pin as an input (optional)
 pinMode(AnalogResistorTwo, INPUT); // Set Resistor - A2 pin as an input (optional)

 Serial.begin(9600); // Little trick to write messages in console.
 stepper.setSpeed(200); // Set speed for stepper
}

// Returns true if x is in range [low..high], else false
bool inRange(unsigned low, unsigned high, unsigned x)
{
		return  ((x-low) <= (high-low));
}

void loop(){
	resistorOne = analogRead(AnalogResistorOne); // Get data from AnalogResistorOne
	resistorTwo = analogRead(AnalogResistorTwo); // Get data from AnalogResistorTwo
	// Show data for debugging
	Serial.print("Data Resistor One: ");
	Serial.print(resistorOne);
	Serial.print(" ----- Data Resistor Two: ");
	Serial.print(resistorTwo);
	Serial.println();

	checkMovement = resistorOne - resistorTwo;
	// - check if it's in range for luminiscience
	int isInRange = inRange(0, stepperRatio, checkMovement);

	Serial.println(isInRange); // for debugging
	Serial.println(checkMovement); // for debugging

	// this will rotate from left to right and otherwise if the value is to much diff
	// from interval (0 and stepperRation) please debug for any changes
	if( !isInRange ){
			if(checkMovement > stepperRatio) {

				 stepper.step(valStepperLeft);
				 Serial.println(valStepperLeft); //for debugging

			} else {

				 stepper.step(valStepperRight);
				 Serial.println(valStepperRight); //for debugging

			}
	}
}
