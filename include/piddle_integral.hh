/*
(***********************************************************************)
(*                                                                     *)
(* The PIDDLE project                                                  *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Mattia Piazza.           *)
(*                                                                     *)
(* The PIDDLE project and its components are supplied under the terms  *)
(* of the open source BSD 3-Clause License. The contents of the PIDDLE *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 3-Clause License.              *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Mattia Piazza                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: mattia.piazza@unitn.it                                   *)
(*                                                                     *)
(***********************************************************************)
*/

///
/// file: piddle_integral.hh
///

#ifndef INCLUDE_PIDDLE_INTEGRAL
#define INCLUDE_PIDDLE_INTEGRAL

// Piddle headers
#include "piddle.hh"
#include "piddle_component.hh"

namespace piddle
{

  /*\
   |   ____            _            _   _           
   |  |  _ \  ___ _ __(_)_   ____ _| |_(_)_   _____ 
   |  | | | |/ _ \ '__| \ \ / / _` | __| \ \ / / _ \
   |  | |_| |  __/ |  | |\ V / (_| | |_| |\ V /  __/
   |  |____/ \___|_|  |_| \_/ \__,_|\__|_| \_/ \___|
   |                                                
  \*/

  //! Class to represent integral component
  class I : public component
  {
  private:
    real m_integral = real(0.0); //!< Integral value
    real m_old = real(0.0);      //!< Previous input value

  public:
    //! Get integral component gain
    real
    gain(
        real const input, //!< Input source value
        real const step   //!< Time step value
    )
        const override
    {
      if (this->isEnabled())
        return this->m_coefficient * this->integral(input, step);
      else
        return real(0.0);
    }

    //! Reset integral component
    real
    reset(void)
        override
    {
      this->m_coefficient = real(0.0);
      this->m_old = real(0.0);
    };

  private:
    //! Get integral through trapezoidal formula
    real
    integral(
        real const input, //!< Input source value
        real const step   //!< Time step value
    )
    {
      this->m_integral += 0.5 * (input + this->m_old) * step;
      this->m_old = input;
      return m_integral;
    }

  }; // class derivative

} // namespace piddle

#endif

///
/// eof: piddle_integral.hh
///
