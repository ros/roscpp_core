#define DO_CHECK(EXPR) check((EXPR), __FUNCTION__, __FILE__, __LINE__)
#include <iostream>
#include "rostime_test.h"
#include "../include/ros/time.h"
#include "../include/ros/duration.h"
#include <boost/date_time/posix_time/posix_time.hpp>

const uint64_t POW_32 = ((uint64_t)1 << 32);
const int64_t POW_31 = ((uint64_t)1 << 31);

void TimeTest::test_fromBoost() {
	boost::posix_time::time_duration td(1000000, 0, 0, 0);	
	bool flag = 0;
	
	try {	
		ros::Time t = ros::Time::fromBoost(td);			
	}
	catch(std::runtime_error &e) {
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_normalizeSecNSec() {
	uint64_t sec = POW_32 - 1, nsec = POW_32 - 1;

	bool flag = 0;
	
	try {	
		ros::normalizeSecNSec(sec, nsec);
	}
	catch(std::runtime_error &e) {
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_normalizeSecNSec32() {
	uint32_t sec = POW_32 - 1, nsec = POW_32 - 1;

	bool flag = 0;
	
	try {	
		ros::normalizeSecNSec(sec, nsec);
	}
	catch(std::runtime_error &e) {
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_normalizeSecNSecUnsigned() {
	int64_t sec = POW_32 - 1, nsec = POW_32 - 1;

	bool flag = 0;
	
	try {	
		ros::normalizeSecNSecUnsigned(sec, nsec);
	}
	catch(std::runtime_error &e) {
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_constructor() {
	bool flag = 0;
	
	try {	
		ros::Time(POW_32 - 1, POW_32 - 1);
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_fromSec() {
	bool flag = 0;
	
	try {	
		ros::Time t;		
		t.fromSec(5e9);
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_subtract() {
	bool flag = 0;
	
	try {	
		ros::Time t1(POW_32 - 1, 0), t2(10, 0);		
		t1 - t2;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_subtractDuration() {
	bool flag = 0;
	
	try {	
		ros::Time t1(10, 0);
		ros::Duration d(20, 0);	
		t1 - d;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_subtract_assignment() {
	bool flag = 0;
	
	try {	
		ros::Time t1(10, 0);
		ros::Duration d(20, 0);	
		t1 -= d;
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_sum() {
	bool flag = 0;
	
	try {	
		ros::Time t1(POW_32 - 1, 0);
		ros::Duration d(10, 0);		
		t1 + d;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Time_sum_assignment() {
	bool flag = 0;
	
	try {	
		ros::Time t1(POW_32 - 1, 0);
		ros::Duration d(10, 0);		
		t1 += d;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Duration_constructor() {
	bool flag = 0;
	
	try {	
		ros::Duration d(POW_31 - 1, POW_31 - 1);
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Duration_fromSec() {
	bool flag = 0;
	
	try {	
		ros::Duration d;		
		d.fromSec(4e9);
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Duration_fromNSec() {
	bool flag = 0;
	
	try {	
		ros::Duration d;		
		d.fromNSec((int64_t)4e9 * 1e9);
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Duration_sum() {
	bool flag = 0;
	
	try {	
		ros::Duration d1(POW_31 - 1, 0), d2(10, 0);		
		d1 + d2;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Duration_sum_assignment() {
	bool flag = 0;
	
	try {	
		ros::Duration d1(POW_31 - 1, 0), d2(10, 0);		
		d1 += d2;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}


void TimeTest::test_Duration_subtract() {
	bool flag = 0;
	
	try {	
		ros::Duration d1(-POW_31 + 2, 0), d2(10, 0);		
		d1 - d2;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}

void TimeTest::test_Duration_subtract_assignment() {
	bool flag = 0;
	
	try {	
		ros::Duration d1(-POW_31 + 2, 0), d2(10, 0);		
		d1 - d2;
		
	}
	catch(std::runtime_error &e) {	
		flag = 1;	
	}

	DO_CHECK(flag);
}


void TimeTest::runAllTests() {
	test_fromBoost();
	test_normalizeSecNSec();
	test_normalizeSecNSec32();
	test_normalizeSecNSecUnsigned();
	test_Time_constructor();
	test_Time_fromSec();
	test_Time_subtract();
	test_Time_subtractDuration();
	test_Time_subtract_assignment();
	test_Time_sum();
	test_Time_sum_assignment();
	test_Duration_constructor();
	test_Duration_fromSec();
	test_Duration_fromNSec();
	test_Duration_sum();
	test_Duration_sum_assignment();
	test_Duration_subtract();
	test_Duration_subtract_assignment();
}

