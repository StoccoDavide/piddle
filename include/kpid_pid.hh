/*
(***********************************************************************)
(*                                                                     *)
(* The KPID project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Mattia Piazza.           *)
(*                                                                     *)
(* The KPID project and its components are supplied under the terms    *)
(* of the open source BSD 3-Clause License. The contents of the KPID   *)
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
/// file: kpid_pid.hh
///

#ifndef INCLUDE_KPID_PID
#define INCLUDE_KPID_PID

// Piddle headers
#include "kpid_antiwindup.hh"
#include "kpid_derivative.hh"
#include "kpid_integral.hh"
#include "kpid_proportional.hh"

namespace kpid
{

  /*\
   |         _     _ 
   |   _ __ (_) __| |
   |  | '_ \| |/ _` |
   |  | |_) | | (_| |
   |  | .__/|_|\__,_|
   |  |_|             
  \*/

  //! Class to represent pid block
  class pid : public block
  {
  private:
    proportional m_proportional; //!< Proportional component
    integral m_integral;         //!< Integral component
    derivative m_derivative;     //!< Derivative component
    antiwindup m_antiwindup;     //!< Anti-windup component

  public:
    //! Setup pid component
    real
    setup(
        real error, //!< Input error value
        real dt     //!< Time step
    )
        const override
    {
      // Calculate pid components
      if (this->isEnabled())
      {
        // Unsaturated output
        real output = this->m_proportional.setup(error, dt) +
                      this->m_integral.setup(this->m_antiwindup.integration() * error, dt) +
                      this->m_derivative.setup(error, dt);
        // Anti-windup routine setup
        output = this->m_antiwindup.setup(output, dt);
        return output;
      }
      else
      {
        return real(0.0)
      }
    }

    //! Reset pid components
    real
    reset(void)
        override
    {
      this->m_filter.reset();
      this->m_proportional.reset();
      this->m_integral.reset();
      this->m_derivative.reset();
    }

  }; // class proportional

} // namespace kpid

#endif

///
/// eof: kpid_proportional.hh
///
