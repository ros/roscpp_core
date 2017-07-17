/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2010, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/
#ifndef ROSTIME_IMPL_DURATION_H_INCLUDED
#define ROSTIME_IMPL_DURATION_H_INCLUDED

#include <ros/duration.h>
#include <ros/rate.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace ros {
  //
  // DurationBase template member function implementation
  //
  template<class T>
  DurationBase<T>::DurationBase(int32_t _sec, int32_t _nsec)
  : sec(_sec), nsec(_nsec)
  {
    normalizeSecNSecSigned(sec, nsec);
  }

  //Cast from double can work incorrectly, if it takes too big values with big precision.
  //For example, fromSec(2147483647.999999999) will throw an exception, although it's correct value,
  template<class T>
  T& DurationBase<T>::fromSec(double d)
  {
    double secd = floor(d);
    if (secd - (double)INT_MIN < -1e-9  || secd - (double)INT_MAX > 1e-9)
      throw std::runtime_error("Duration is out of dual 32-bit range");

    sec = (int32_t)secd;
    nsec = (int32_t)((d - (double)sec)*1000000000);
    return *static_cast<T*>(this);
  }

  template<class T>
  T& DurationBase<T>::fromNSec(int64_t t)
  {
    int64_t sec64  = 0;
    int64_t nsec64 = t;

    //Throws an exception, if parameter out of 32-bit range.
    normalizeSecNSecSigned(sec64, nsec64);

    sec = (int32_t)sec64;
    nsec = (int32_t)nsec64;

    return *static_cast<T*>(this);
  }

  template<class T>
  T DurationBase<T>::operator+(const T &rhs) const
  {
    int64_t sec_sum  = (int64_t)sec  + (int64_t)rhs.sec;
    int64_t nsec_sum = (int64_t)nsec + (int64_t)rhs.nsec;

    // Throws an exception if we go out of 32-bit range.
    normalizeSecNSecSigned(sec_sum, nsec_sum);

    return T((int32_t)sec_sum, (int32_t)nsec_sum);
  }

  template<class T>
  T DurationBase<T>::operator*(double scale) const
  {
    return T(toSec() * scale);
  }

  template<class T>
  T DurationBase<T>::operator-(const T &rhs) const
  {
    int64_t sec_dif  = (int64_t)sec  - (int64_t)rhs.sec;
    int64_t nsec_dif = (int64_t)nsec - (int64_t)rhs.nsec;

    // Throws an exception if we go out of 32-bit range
    normalizeSecNSecSigned(sec_dif, nsec_dif);

    return T((int32_t)sec_dif, (int32_t)nsec_dif);
  }

//Duration values in range [-2147483648..2147483647.999999999].
//Question is: -(-2147483648) should throw an exception (as it does now it's correct),
//or should it be as c++ integer: -(-2147483648) == -2147483648 ???
  template<class T>
  T DurationBase<T>::operator-() const
  {
    int64_t sec64 = -(int64_t)sec;
    int64_t nsec64 = -(int64_t)nsec;

    normalizeSecNSecSigned(sec64, nsec64);

    return T(sec64, nsec64);
  }

  template<class T>
  T& DurationBase<T>::operator+=(const T &rhs)
  {
    *this = *this + rhs;
    return *static_cast<T*>(this);
  }

  template<class T>
  T& DurationBase<T>::operator-=(const T &rhs)
  {
    *this += (-rhs);
    return *static_cast<T*>(this);
  }

  template<class T>
  T& DurationBase<T>::operator*=(double scale)
  {
    fromSec(toSec() * scale);
    return *static_cast<T*>(this);
  }

  template<class T>
  bool DurationBase<T>::operator<(const T &rhs) const
  {
    if (sec < rhs.sec)
      return true;
    else if (sec == rhs.sec && nsec < rhs.nsec)
      return true;
    return false;
  }

  template<class T>
  bool DurationBase<T>::operator>(const T &rhs) const
  {
    if (sec > rhs.sec)
      return true;
    else if (sec == rhs.sec && nsec > rhs.nsec)
      return true;
    return false;
  }

  template<class T>
  bool DurationBase<T>::operator<=(const T &rhs) const
  {
    if (sec < rhs.sec)
      return true;
    else if (sec == rhs.sec && nsec <= rhs.nsec)
      return true;
    return false;
  }

  template<class T>
  bool DurationBase<T>::operator>=(const T &rhs) const
  {
    if (sec > rhs.sec)
      return true;
    else if (sec == rhs.sec && nsec >= rhs.nsec)
      return true;
    return false;
  }

  template<class T>
  bool DurationBase<T>::operator==(const T &rhs) const
  {
    return sec == rhs.sec && nsec == rhs.nsec;
  }

  template<class T>
  bool DurationBase<T>::isZero() const
  {
    return sec == 0 && nsec == 0;
  }

  template <class T>
  boost::posix_time::time_duration
  DurationBase<T>::toBoost() const
  {
    namespace bt = boost::posix_time;
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS)
    return bt::seconds(sec) + bt::nanoseconds(nsec);
#else
    return bt::seconds(sec) + bt::microseconds(nsec/1000.0);
#endif
  }
}
#endif
