#include "Clock.h"


Clock::Clock()
{
	currentTime = 0.0;
	dayLength = 1.0;
	timeStep = 1.0;
}


Clock::~Clock()
{
}


double Clock::getCurrentTime()
{
	return currentTime;
}


double Clock::getCurrentHour()
{
	return currentHour;
}


void Clock::setTimeStep(double ts)
{
	timeStep = ts;
}


void Clock::setDayLength(double dl)
{
	dayLength = dl;
}


void Clock::stepForward()
{
	currentTime += timeStep;
	currentHour += timeStep;
	currentHour = std::fmod(currentHour, dayLength);
}


void Clock::stepForward(double time)
{
	currentTime += time;
	currentHour += time;
	currentHour = std::fmod(currentHour, dayLength);
}
