#pragma once
#include <cmath>

class Clock
{
protected:
	//Current time in seconds from start.
	double currentTime;
	double currentHour;
	double dayLength;
	double timeStep;

public:
	Clock();
	~Clock();

	double getCurrentTime();
	double getCurrentHour();
	//Set time step in seconds.
	void setTimeStep(double timeStep);
	//Set length of the day in hours.
	void setDayLength(double dayLength);
	void stepForward();
	void stepForward(double timeStep);
};

