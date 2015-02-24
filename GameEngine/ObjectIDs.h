
#ifndef OBJECTIDS_H
#define OBJECTIDS_H

/*
IDs of rigid bodies needed for collisions.
noPysicsID static body.
noCollisionsID body with its own speed but without forces or collisions.
*/
class ObjectIDs
{
public:
	//body with its own speed but without forces or collisions
	static const int noCollisionsID = -2;
	//static body
	static const int staticID = -1;
	static const int defaultID = 0;
	static const int planeID = 1;
	static const int boxID = 2;
	static const int wheelID = 3;
	static const int carID = 4;
	static const int trackID = 5;
};

#endif