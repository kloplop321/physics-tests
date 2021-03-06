#pragma once
#include "lib/test.hpp"

class BallWallTestFactory : public TestFactory {
public:
	virtual TestInstance * instance(TestEnvironment*, float x, float y);
	virtual float width(){return 200;}
	virtual float length(){return 1000;}
	virtual const char * name() {return "Basic Test";}
    BallWallTestFactory();
};