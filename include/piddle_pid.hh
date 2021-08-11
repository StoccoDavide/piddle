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
/// file: piddle_pid.hh
///

#ifndef INCLUDE_PIDDLE_PID
#define INCLUDE_PIDDLE_PID

// Piddle headers
#include "piddle.hh"
#include "piddle_derivative.hh"
#include "piddle_integral.hh"
#include "piddle_proportional.hh"

namespace piddle
{

  /*\
   |   ____ ___ ____  
   |  |  _ \_ _|  _ \ 
   |  | |_) | || | | |
   |  |  __/| || |_| |
   |  |_|  |___|____/ 
   |                  
  \*/

  //! Class to represent proportional component
  class PID : public component
  {
  private:
    P m_proportional; //! Proportional component
    I m_integral;     //! Integral component
    D m_derivative;   //! Derivative component

  public:
    //! Get PID components gain
    real
    gain(
        real const input, //!< Input source value
        real const step   //!< Time step value
    )
        const override
    {
      if (this->isEnabled())
        return this->m_proportional.gain(input, step) +
               this->m_integral.gain(input, step) +
               this->m_derivative.gain(input, step);
      else
        return real(0.0);
    }

    //! Reset PID components
    real
    reset(void)
        override
    {
      this->m_proportional.reset();
      this->m_integral.reset();
      this->m_derivative.reset();
    };

  }; // class proportional

} // namespace piddle

#endif

///
/// eof: piddle_proportional.hh
///
