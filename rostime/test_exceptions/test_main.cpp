#include <iostream>
#include <stdio.h>
#include "rostime_test.h"
#include "../include/ros/time.h"
using namespace ros;

int main () {
	TimeTest test;
	test.runAllTests();	
	TimeTest::showFinalResults();
	return 0;
}
