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
/// file: kpid_derivative.hh
///

#ifndef INCLUDE_KPID_DERIVATIVE
#define INCLUDE_KPID_DERIVATIVE

// Piddle headers
#include "kpid_block.hh"
#include "kpid_filter.hh"

namespace kpid
{

  /*\
   |       _           _            _   _           
   |    __| | ___ _ __(_)_   ____ _| |_(_)_   _____ 
   |   / _` |/ _ \ '__| \ \ / / _` | __| \ \ / / _ \
   |  | (_| |  __/ |  | |\ V / (_| | |_| |\ V /  __/
   |   \__,_|\___|_|  |_| \_/ \__,_|\__|_| \_/ \___|
   |                                                
  \*/

  //! Class to represent derivative component
  class derivative : public block
  {
  private:
    filter m_filter;             //!< Derivative output block low-pass filter
    real m_gain;                 //!< Derivative gain coefficient
    real m_errorOld = real(0.0); //!< Previous error value

  public:
    //! Get derivative gain const reference
    real const &
    gain(void) const
    {
      return this->m_gain;
    }

    //! Get derivative gain reference
    real &
    gain(void)
    {
      return this->m_gain;
    }

    //! Setup derivative component
    real
    setup(
        real error,   //!< Input error value
        real dt //!< Time step
    )
        const override
    {
      if (this->isEnabled())
        return this->m_gain * this->differentiate(error, dt);
      else
        return real(0.0);
    }

    //! Reset derivative component
    void
    reset(void)
        override
    {
      this->m_old = real(0.0);
      this->m_filter.reset();
    };

  private:
    //! Get error derivative through backward Euler formula
    real
    differentiate(
        real error,   //!< Input error value
        real dt //!< Time step
    )
    {
      // Calculate derivative
      real diff = (error - this->m_errorOld) / dt;

      // Perform derivative filtering
      if (this->m_filter.isEnabled())
        diff = this->m_filter.setup(diff, dt);

      this->m_errorOld = error;
      return diff;
    }

  }; // class derivative

} // namespace kpid

#endif

///
/// eof: kpid_derivative.hh
///
