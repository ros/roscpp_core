#ifndef __TIME_TEST_H__
#define __TIME_TEST_H__
#include "autotest.h"

class TimeTest : public Test {
public:
	void test_fromBoost();
	void test_normalizeSecNSec();
	void test_normalizeSecNSec32();
	void test_normalizeSecNSecUnsigned();
	void test_Time_constructor();
	void test_Time_fromSec();
	void test_Time_subtract();
	void test_Time_subtractDuration();
	void test_Time_subtract_assignment();
	void test_Time_sum();
	void test_Time_sum_assignment();
	void test_Duration_constructor();
	void test_Duration_fromSec();
	void test_Duration_fromNSec();
	void test_Duration_sum();
	void test_Duration_sum_assignment();
	void test_Duration_subtract();
	void test_Duration_subtract_assignment();

	void runAllTests();
};

#endif