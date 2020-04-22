#ifndef RTO
#define ROT

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define stepPin 2  //CLK+ is pin D2
#define dirPin 3 //CW+ is pin D3
#define maxSteps 200
#define micro_step 2

/*
  METHODS:
    0: reset
    1: calibrate
    2: takeOneStepCLKWise
    3: takeOneStepCounterCLKWise
    4: setPositionInDegrees - int
    5: setPositionInSteps - int
    6: setStepSizeInDegrees - int
    7: setStepSizeInSteps - int
    8: degreesToSteps
    9: stepsToDegrees
*/

class Rotator
{
  public:
  //concstructor
  void rotator();

  //method
  static void reset();

  static void calibrate();

  static void setPositionInDegrees(double nrOfDegrees);

  static void setPositionInSteps(int nrOfSteps);

  static double getPositionDegrees();

  static int getPositionInSteps();

  static int getMaxSteps();

  static int degreesToSteps(double nrOfDegrees);

  static double stepsToDegrees(int nrOfSteps);

  static void setStepSizeInDegrees(double nrOfDegrees);

  static void setStepSizeInSteps(int nrOfSteps);

  static double getStepSizeDegrees();

  static int getStepSizeSteps();

  static void takeOneStepCLKWise();

  static void takeOneStepCounterCLKWise();

  static void init();

  private: 
  //none
};



#endif
