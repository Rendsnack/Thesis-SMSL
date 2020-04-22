#include "Rotator.h"

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
 
double anglePerStep = 1.8/micro_step;
double stepPerAngle = 0.556;  //Rounding error
double originDegrees = 0.0;
int originSteps = 0;
double currentPositionDegrees = 0;
int currentPositionSteps = 0;
bool isCalibrated = false;

double stepSizeDegrees = 1;
int stepSizeSteps = 1;

/*
 * Reset the currentPosition to origin.
 */
void Rotator::reset()
{
  if(abs(currentPositionSteps) < maxSteps/(2*stepSizeSteps) ) //return counter-clockwise
  {
    while( abs(currentPositionSteps) > 0 )
    {
      takeOneStepCounterCLKWise();
    }
  }
  else if(abs(currentPositionSteps) >= maxSteps/(2*stepSizeSteps) ) //return counter-clockwise
  {
    while( abs(currentPositionSteps) > 0 )
    {
      takeOneStepCLKWise();
    }
  }
}

/*
 * Set the current position as origin.
 */
void Rotator::calibrate()
{
  currentPositionDegrees = 0;
  currentPositionSteps = 0;
}

/*
 * Convert nrOfDegrees to amount of steps and call method setPositionInSteps.
 */
void Rotator::setPositionInDegrees(double nrOfDegrees)
{
  setPositionInSteps(degreesToSteps(nrOfDegrees));
}

/*
 * Keep taking a step until nrOf is reached.
 */
void Rotator::setPositionInSteps(int nrOfSteps)
{
  int stepSizeStepsMem = stepSizeSteps; //remember stepSizeSteps
  stepSizeSteps = 1;  //reset stepSizeSteps to 1

  if ( nrOfSteps > maxSteps)
  {
    nrOfSteps -= maxSteps;
  }

  while ( currentPositionSteps > nrOfSteps )
  {
    takeOneStepCounterCLKWise();
  }
  while ( currentPositionSteps < nrOfSteps )
  {
    takeOneStepCLKWise();
  }
  stepSizeSteps = stepSizeStepsMem; //restore stepSizeSteps
}

double Rotator::getPositionDegrees()
{
  return currentPositionDegrees;
}

int Rotator::getPositionInSteps()
{
  return currentPositionSteps;
}

/*
 * Returns the amount of steps for a full rotation.
 */
int Rotator::getMaxSteps()
{
  return maxSteps;
}

/*
 * Convert degrees to amount of steps.
 * Warning, rounding error
 */
int Rotator::degreesToSteps(double nrOfDegrees)
{
  int nrOfSteps = nrOfDegrees*stepPerAngle;
  return nrOfSteps;
}

/*
 * Convert steps to degrees.
 * Warning, rounding error
 */
double Rotator::stepsToDegrees(int nrOfSteps)
{
  double nrOfDegrees = nrOfSteps*anglePerStep;
  return nrOfDegrees;
}

/*
 * Change the default step size.
 */
void Rotator::setStepSizeInDegrees(double nrOfDegrees)
{
  stepSizeDegrees = nrOfDegrees;
  stepSizeSteps = degreesToSteps(nrOfDegrees);
}

/*
 * Change the default step size.
 */
void Rotator::setStepSizeInSteps(int nrOfSteps)
{
  if( currentPositionSteps != 0 )
  {
    return;
  }
  stepSizeDegrees = stepsToDegrees(nrOfSteps);
  stepSizeSteps = nrOfSteps;
}

/*
 * Get the step size in degrees.
 */ 
double Rotator::getStepSizeDegrees()
{
  return stepSizeDegrees;
}

/*
 * Get the step size in number of steps.
 */
int Rotator::getStepSizeSteps()
{
  return stepSizeSteps;
}

/*
 * Take one step in the clokwise direction.
 * A step is set to 1 by default but can be changed by setStepSizeInSteps and setStepSizeInDegrees.
 */
void Rotator::takeOneStepCLKWise()
{
  for (int i = 0; i < stepSizeSteps; i++)
  {
    digitalWrite(dirPin, HIGH);
    digitalWrite(stepPin, HIGH);
    delay(50);
    digitalWrite(stepPin, LOW);
    delay(50);
  }  
  currentPositionSteps++;
  if( currentPositionSteps >= maxSteps/stepSizeSteps )
  {
    currentPositionSteps = 0;
    currentPositionDegrees = 0;
  }
  currentPositionDegrees += anglePerStep;
}

/*
 * Take one step in the counter-clokwise direction.
 * A step is set to 1 by default but can be changed by setStepSizeInSteps and setStepSizeInDegrees.
 */
void Rotator::takeOneStepCounterCLKWise()
{
  for (int i = 0; i < stepSizeSteps; i++)
  {
    digitalWrite(dirPin, LOW);
    digitalWrite(stepPin, HIGH);
    delay(50);
    digitalWrite(stepPin, LOW);
    delay(50);
  } 
  currentPositionSteps--;
  if( currentPositionSteps < 0 )
  {
    currentPositionSteps = maxSteps/stepSizeSteps;
    currentPositionDegrees = 360;
  }
  currentPositionDegrees -= anglePerStep;
}

void Rotator::rotator() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}

void Rotator::init() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}
