/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * The PIDDLE project                                                  *
 *                                                                     *
 * Copyright (c) 2020, Davide Stocco.                                  *
 *                                                                     *
 * The PIDDLE project and its components are supplied under the terms  *
 * of the open source BSD 3-Clause License. The contents of the PIDDLE *
 * project and its components may not be copied or disclosed except in *
 * accordance with the terms of the BSD 3-Clause License.              *
 *                                                                     *
 * URL: https://opensource.org/licenses/BSD-3-Clause                   *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: Piddle.hh
///

#ifndef INCLUDE_PIDDLE
#define INCLUDE_PIDDLE

// Print piddle errors
#ifndef PIDDLE_ERROR
#define PIDDLE_ERROR(MSG)                  \
  {                                      \
    std::ostringstream ost;              \
    ost << MSG;                          \
    throw std::runtime_error(ost.str()); \
  }
#endif

// Check for piddle errors
#ifndef PIDDLE_ASSERT
#define PIDDLE_ASSERT(COND, MSG) \
  if (!(COND))                 \
  PIDDLE_ERROR(MSG)
#endif

// Standard libraries
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

//! Namespace containing all piddle typedefs, classes and routines
namespace Piddle
{

  /*\
   |   _____                     _       __
   |  |_   _|   _ _ __   ___  __| | ___ / _|___
   |    | || | | | '_ \ / _ \/ _` |/ _ \ |_/ __|
   |    | || |_| | |_) |  __/ (_| |  __/  _\__ \
   |    |_| \__, | .__/ \___|\__,_|\___|_| |___/
   |        |___/|_|
  \*/

  typedef double real;             //!< Real number type
  typedef int integer;             //!< Integer number type
  typedef std::ostream out_stream; //!< Output stream type

  /*\
   |    ____                _              _
   |   / ___|___  _ __  ___| |_ __ _ _ __ | |_ ___
   |  | |   / _ \| '_ \/ __| __/ _` | '_ \| __/ __|
   |  | |__| (_) | | | \__ \ || (_| | | | | |_\__ \
   |   \____\___/|_| |_|___/\__\__,_|_| |_|\__|___/
   |
  \*/

  static real const EPSILON_MACHINE = std::numeric_limits<real>::epsilon(); //!< Machine epsilon epsilon static constant value
  static real const EPSILON_HIGH = 1.0E-16;                                 //!< High precision epsilon static constant value
  static real const EPSILON_MEDIUM = 1.0E-10;                               //!< Medium precision epsilon static constant value
  static real const EPSILON_LOW = 1.0E-07;                                  //!< Low precision epsilon static constant value
  static real const EPSILON = EPSILON_MEDIUM;                               //!< Standard precision epsilon static constant value
  static real const INFTY = std::numeric_limits<real>::infinity();          //!< Infinity static constant value
  static real const QUIET_NAN = std::numeric_limits<real>::quiet_NaN();     //!< Not-a-Number static constant value
  static real const PI = real(3.141592653589793238462643383279500);         //!< Pi static constant value
  static real const PIDIV180 = real(0.017453292519943295769236907684886);   //!< Pi/180 static constant value

} // namespace Piddle

#include "Piddle/Antiwindup.hxx"
#include "Piddle/Block.hxx"
#include "Piddle/Filter.hxx"
#include "Piddle/Integral.hxx"
#include "Piddle/Pid.hxx"
#include "Piddle/Proportional.hxx"

#endif

///
/// eof: Piddle.hh
///
