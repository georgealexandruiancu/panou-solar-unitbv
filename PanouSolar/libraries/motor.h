// ensure this library description is only included once
#ifndef Motor_h
#define Motor_h

// library interface description
class Motor {
  public:
	// constructors:
	Motor(int numberOfSteps, int motorPin_1, int motorPin_2, int motorPin_3, int motorPin_4);

	// speed setter method:
	void setSpeed(long whatSpeed);

	// mover method:
	void step(int numberOfSteps);

	int version(void);

  private:
	void stepMotor(int this_step);

	int direction;				// Direction of rotation
	unsigned long stepDelay;	// delay between steps, in ms, based on speed
	int numberOfSteps;			// total number of steps this motor can take
	int pinCount;				// how many pins are in use.
	int StepNumber;				// which step the motor is on

	// motor pin numbers:
	int motorPin_1;
	int motorPin_2;
	int motorPin_3;
	int motorPin_4;

	unsigned long lastStepTime; // time stamp in us of when the last step was taken
};

#endif
