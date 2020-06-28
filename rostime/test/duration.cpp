/*
 * Copyright (c) 2016, Open Source Robotics Foundation, Inc..
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <gtest/gtest.h>
#include <ros/duration.h>
#include <ros/time.h>

using namespace ros;

TEST(Duration, sleepWithSimTime)
{
  ros::Time::init();

  Time start = Time::now();
  start -= Duration(2.0);
  Time::setNow(start);

  Time::shutdown();

  Duration d(1.0);
  bool rc = d.sleep();
  ASSERT_FALSE(rc);
}

TEST(Duration, castFromDoubleExceptions)
{
  ros::Time::init();

  Duration d1, d2, d3, d4;
  // Valid values to cast, must not throw exceptions
  EXPECT_NO_THROW(d1.fromSec(-2147483648.0));
  EXPECT_NO_THROW(d2.fromSec(-2147483647.999999));
  EXPECT_NO_THROW(d3.fromSec(2147483647.0));
  EXPECT_NO_THROW(d4.fromSec(2147483647.999999));

  // The next casts all incorrect.
  EXPECT_THROW(d1.fromSec(2147483648.0), std::runtime_error);
  EXPECT_THROW(d2.fromSec(6442450943.0), std::runtime_error);  // It's 2^31 - 1 + 2^32, and it could pass the test.
  EXPECT_THROW(d3.fromSec(-2147483648.001), std::runtime_error);
  EXPECT_THROW(d4.fromSec(-6442450943.0), std::runtime_error);
}

TEST(Duration, castFromInt64Exceptions)
{
  ros::Time::init();

  Duration d1, d2, d3, d4;
  // Valid values to cast, must not throw exceptions
  EXPECT_NO_THROW(d1.fromNSec(-2147483648000000000));
  EXPECT_NO_THROW(d2.fromNSec(-2147483647999999999));
  EXPECT_NO_THROW(d3.fromNSec(2147483647000000000));
  EXPECT_NO_THROW(d4.fromNSec(2147483647999999999));

  // The next casts all incorrect.
  EXPECT_THROW(d1.fromSec(2147483648000000000), std::runtime_error);
  EXPECT_THROW(d2.fromSec(4294967296000000000), std::runtime_error);
  EXPECT_THROW(d3.fromSec(-2147483648000000001), std::runtime_error);
  EXPECT_THROW(d4.fromSec(-6442450943000000000), std::runtime_error);
}

TEST(Duration, arithmeticExceptions)
{
  ros::Time::init();

  Duration d1(2147483647, 0);
  Duration d2(2147483647, NSecInSec - 1);
  EXPECT_THROW(d1 + d2, std::runtime_error);

  Duration d3(-2147483648, 0);
  Duration d4(2147483647, 0);
  EXPECT_THROW(d3 - d4, std::runtime_error);
  EXPECT_THROW(d4 - d3, std::runtime_error);

  Duration d5(-2147483647, 1);
  Duration d6(-2, NSecInSec - 1);
  Duration d7;
  EXPECT_NO_THROW(d7 = d5 + d6);
  EXPECT_EQ(-2147483648000000000, d7.toNSec());
}

TEST(Duration, negativeSignExceptions)
{
  ros::Time::init();

  Duration d1(2147483647, 0);
  Duration d2(2147483647, NSecInSec - 1);
  Duration d3;
  EXPECT_NO_THROW(d3 = -d1);
  EXPECT_EQ(-2147483647000000000, d3.toNSec());
  EXPECT_NO_THROW(d3 = -d2);
  EXPECT_EQ(-2147483647999999999, d3.toNSec());

  Duration d4(-2147483647, 0);
  Duration d5(-2147483648, NSecInSec - 1);
  Duration d6(-2147483648, 2);
  Duration d7;
  EXPECT_NO_THROW(d7 = -d4);
  EXPECT_EQ(2147483647000000000, d7.toNSec());
  EXPECT_NO_THROW(d7 = -d5);
  EXPECT_EQ(2147483647000000001, d7.toNSec());
  EXPECT_NO_THROW(d7 = -d6);
  EXPECT_EQ(2147483647999999998, d7.toNSec());
}

TEST(Duration, rounding)
{
  ros::Time::init();

  Duration d1(49.0000000004);
  EXPECT_EQ(49, d1.sec);
  EXPECT_EQ(0, d1.nsec);
  Duration d2(-49.0000000004);
  EXPECT_EQ(-49, d2.sec);
  EXPECT_EQ(0, d2.nsec);

  Duration d3(49.0000000006);
  EXPECT_EQ(49, d3.sec);
  EXPECT_EQ(1, d3.nsec);
  Duration d4(-49.0000000006);
  EXPECT_EQ(-50, d4.sec);
  EXPECT_EQ(NSecInSec - 1, d4.nsec);

  Duration d5(49.9999999994);
  EXPECT_EQ(49, d5.sec);
  EXPECT_EQ(NSecInSec - 1, d5.nsec);
  Duration d6(-49.9999999994);
  EXPECT_EQ(-50, d6.sec);
  EXPECT_EQ(1, d6.nsec);

  Duration d7(49.9999999996);
  EXPECT_EQ(50, d7.sec);
  EXPECT_EQ(0, d7.nsec);
  Duration d8(-49.9999999996);
  EXPECT_EQ(-50, d8.sec);
  EXPECT_EQ(0, d8.nsec);
}

TEST(Duration, construct)
{
  ros::Time::init();

  EXPECT_EQ(Duration().fromSec(2.0), Duration(2, 0));
  EXPECT_EQ(Duration().fromSec(-2.0), Duration(-2, 0));
  EXPECT_EQ(Duration().fromSec(2), Duration(2, 0));
  EXPECT_EQ(Duration().fromSec(-2), Duration(-2, 0));
  EXPECT_EQ(Duration().fromMSec(2), Duration(0, 2 * NSecInMSec));
  EXPECT_EQ(Duration().fromMSec(-2), Duration(0, -2 * NSecInMSec));
  EXPECT_EQ(Duration().fromUSec(2), Duration(0, 2 * NSecInUSec));
  EXPECT_EQ(Duration().fromUSec(-2), Duration(0, -2 * NSecInUSec));

  EXPECT_EQ(WallDuration().fromSec(2.0), WallDuration(2, 0));
  EXPECT_EQ(WallDuration().fromSec(-2.0), WallDuration(-2, 0));
  EXPECT_EQ(WallDuration().fromSec(2), WallDuration(2, 0));
  EXPECT_EQ(WallDuration().fromSec(-2), WallDuration(-2, 0));
  EXPECT_EQ(WallDuration().fromMSec(2), WallDuration(0, 2 * NSecInMSec));
  EXPECT_EQ(WallDuration().fromMSec(-2), WallDuration(0, -2 * NSecInMSec));
  EXPECT_EQ(WallDuration().fromUSec(2), WallDuration(0, 2 * NSecInUSec));
  EXPECT_EQ(WallDuration().fromUSec(-2), WallDuration(0, -2 * NSecInUSec));
}

TEST(Duration, toDouble)
{
  ros::Time::init();

  EXPECT_NEAR(Duration(2, 0).toSec(), 2.0, 1e-9);
  EXPECT_NEAR(Duration(-2, 0).toSec(), -2.0, 1e-9);
  EXPECT_NEAR(Duration(0, 2 * NSecInMSec).toSec(), 0.002, 1e-9);
  EXPECT_NEAR(Duration(0, -2 * NSecInMSec).toSec(), -0.002, 1e-9);
  EXPECT_NEAR(Duration(0, 2 * NSecInUSec).toSec(), 0.000002, 1e-9);
  EXPECT_NEAR(Duration(0, -2 * NSecInUSec).toSec(), -0.000002, 1e-9);
  EXPECT_NEAR(Duration(0, 2).toSec(), 0.000000002, 1e-12);
  EXPECT_NEAR(Duration(0, -2).toSec(), -0.000000002, 1e-12);

  EXPECT_NEAR(Duration(2, 0).toMSec(), 2000.0, 1e-9);
  EXPECT_NEAR(Duration(-2, 0).toMSec(), -2000.0, 1e-9);
  EXPECT_NEAR(Duration(0, 2 * NSecInMSec).toMSec(), 2.0, 1e-9);
  EXPECT_NEAR(Duration(0, -2 * NSecInMSec).toMSec(), -2.0, 1e-9);
  EXPECT_NEAR(Duration(0, 2 * NSecInUSec).toMSec(), 0.002, 1e-9);
  EXPECT_NEAR(Duration(0, -2 * NSecInUSec).toMSec(), -0.002, 1e-9);
  EXPECT_NEAR(Duration(0, 2).toMSec(), 0.000002, 1e-9);
  EXPECT_NEAR(Duration(0, -2).toMSec(), -0.000002, 1e-9);

  EXPECT_NEAR(Duration(2, 0).toUSec(), 2000000.0, 1e-9);
  EXPECT_NEAR(Duration(-2, 0).toUSec(), -2000000.0, 1e-9);
  EXPECT_NEAR(Duration(0, 2 * NSecInMSec).toUSec(), 2000.0, 1e-9);
  EXPECT_NEAR(Duration(0, -2 * NSecInMSec).toUSec(), -2000.0, 1e-9);
  EXPECT_NEAR(Duration(0, 2 * NSecInUSec).toUSec(), 2.0, 1e-9);
  EXPECT_NEAR(Duration(0, -2 * NSecInUSec).toUSec(), -2.0, 1e-9);
  EXPECT_NEAR(Duration(0, 2).toUSec(), 0.002, 1e-9);
  EXPECT_NEAR(Duration(0, -2).toUSec(), -0.002, 1e-9);

  EXPECT_EQ(Duration(2, 0).toNSec(), 2000000000LL);
  EXPECT_EQ(Duration(-2, 0).toNSec(), -2000000000LL);
  EXPECT_EQ(Duration(0, 2 * NSecInMSec).toNSec(), 2000000LL);
  EXPECT_EQ(Duration(0, -2 * NSecInMSec).toNSec(), -2000000LL);
  EXPECT_EQ(Duration(0, 2 * NSecInUSec).toNSec(), 2000LL);
  EXPECT_EQ(Duration(0, -2 * NSecInUSec).toNSec(), -2000LL);
  EXPECT_EQ(Duration(0, 2).toNSec(), 2LL);
  EXPECT_EQ(Duration(0, -2).toNSec(), -2LL);

  EXPECT_NEAR(WallDuration(2, 0).toSec(), 2.0, 1e-9);
  EXPECT_NEAR(WallDuration(-2, 0).toSec(), -2.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2 * NSecInMSec).toSec(), 0.002, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2 * NSecInMSec).toSec(), -0.002, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2 * NSecInUSec).toSec(), 0.000002, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2 * NSecInUSec).toSec(), -0.000002, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2).toSec(), 0.000000002, 1e-12);
  EXPECT_NEAR(WallDuration(0, -2).toSec(), -0.000000002, 1e-12);

  EXPECT_NEAR(WallDuration(2, 0).toMSec(), 2000.0, 1e-9);
  EXPECT_NEAR(WallDuration(-2, 0).toMSec(), -2000.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2 * NSecInMSec).toMSec(), 2.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2 * NSecInMSec).toMSec(), -2.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2 * NSecInUSec).toMSec(), 0.002, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2 * NSecInUSec).toMSec(), -0.002, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2).toMSec(), 0.000002, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2).toMSec(), -0.000002, 1e-9);

  EXPECT_NEAR(WallDuration(2, 0).toUSec(), 2000000.0, 1e-9);
  EXPECT_NEAR(WallDuration(-2, 0).toUSec(), -2000000.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2 * NSecInMSec).toUSec(), 2000.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2 * NSecInMSec).toUSec(), -2000.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2 * NSecInUSec).toUSec(), 2.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2 * NSecInUSec).toUSec(), -2.0, 1e-9);
  EXPECT_NEAR(WallDuration(0, 2).toUSec(), 0.002, 1e-9);
  EXPECT_NEAR(WallDuration(0, -2).toUSec(), -0.002, 1e-9);

  EXPECT_EQ(WallDuration(2, 0).toNSec(), 2000000000LL);
  EXPECT_EQ(WallDuration(-2, 0).toNSec(), -2000000000LL);
  EXPECT_EQ(WallDuration(0, 2 * NSecInMSec).toNSec(), 2000000LL);
  EXPECT_EQ(WallDuration(0, -2 * NSecInMSec).toNSec(), -2000000LL);
  EXPECT_EQ(WallDuration(0, 2 * NSecInUSec).toNSec(), 2000LL);
  EXPECT_EQ(WallDuration(0, -2 * NSecInUSec).toNSec(), -2000LL);
  EXPECT_EQ(WallDuration(0, 2).toNSec(), 2LL);
  EXPECT_EQ(WallDuration(0, -2).toNSec(), -2LL);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
