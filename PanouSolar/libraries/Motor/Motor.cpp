#include "Arduino.h"
#include "Motor.h"

/*
 *   constructor for four-pin version
 */
Motor::Motor(int numberOfSteps, int motorPin_1, int motorPin_2, int motorPin_3, int motorPin_4) {
	this->StepNumber = 0;						// which step the motor is on
	this->direction = 0;						// motor direction
	this->lastStepTime = 0;						// time stamp in us of the last step taken
	this->numberOfSteps = numberOfSteps;		// total number of steps for this motor

	// Arduino pins for the motor control connection:
	this->motorPin_1 = motorPin_1;
	this->motorPin_2 = motorPin_2;
	this->motorPin_3 = motorPin_3;
	this->motorPin_4 = motorPin_4;

	// setup the pins on the microcontroller:
	pinMode(this->motorPin_1, OUTPUT);
	pinMode(this->motorPin_2, OUTPUT);
	pinMode(this->motorPin_3, OUTPUT);
	pinMode(this->motorPin_4, OUTPUT);

	// pinCount is used by the stepMotor() method:
	this->pinCount = 4;
}

/*
 * Sets the speed in revs per minute
 */
void Motor::setSpeed(long whatSpeed)
{
	// using L - declare long values
	this->stepDelay = 60L * 1000L * 1000L / this->numberOfSteps / whatSpeed;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void Motor::step(int steps_to_move)
{
	int steps_left = abs(steps_to_move);  // how many steps to take

	// determine direction based on whether steps_to_mode is + or -:
	if (steps_to_move > 0) { this->direction = 1; }
	if (steps_to_move < 0) { this->direction = 0; }


	// decrement the number of steps, moving one step each time:
	while (steps_left > 0) {
		unsigned long now = micros();
		// move only if the appropriate delay has passed:
		if (now - this->lastStepTime >= this->stepDelay)
		{
		// get the timeStamp of when you stepped:
		this->lastStepTime = now;
		// increment or decrement the step number,
		// depending on direction:
		if (this->direction == 1)
		{
			this->StepNumber++;
			if (this->StepNumber == this->numberOfSteps) {
			this->StepNumber = 0;
			}
		}
		else
		{
			if (this->StepNumber == 0) {
			this->StepNumber = this->numberOfSteps;
			}
			this->StepNumber--;
		}
		// decrement the steps left:
		steps_left--;
		// step the motor to step number 0, 1, ..., {3 or 10}
		if (this->pinCount == 5)
			stepMotor(this->StepNumber % 10);
		else
			stepMotor(this->StepNumber % 4);
		}
	}
}

/*
 * Moves the motor forward or backwards.
 */
void Motor::stepMotor(int thisStep)
{
  if (this->pinCount == 4) {
	switch (thisStep) {
	  case 0:  // 1010
		digitalWrite(motorPin_1, HIGH);
		digitalWrite(motorPin_2, LOW);
		digitalWrite(motorPin_3, HIGH);
		digitalWrite(motorPin_4, LOW);
	  break;
	  case 1:  // 0110
		digitalWrite(motorPin_1, LOW);
		digitalWrite(motorPin_2, HIGH);
		digitalWrite(motorPin_3, HIGH);
		digitalWrite(motorPin_4, LOW);
	  break;
	  case 2:  //0101
		digitalWrite(motorPin_1, LOW);
		digitalWrite(motorPin_2, HIGH);
		digitalWrite(motorPin_3, LOW);
		digitalWrite(motorPin_4, HIGH);
	  break;
	  case 3:  //1001
		digitalWrite(motorPin_1, HIGH);
		digitalWrite(motorPin_2, LOW);
		digitalWrite(motorPin_3, LOW);
		digitalWrite(motorPin_4, HIGH);
	  break;
	}
  }
}

/*
  version() returns the version of the library:
*/
int Motor::version(void)
{
	return 5;
}