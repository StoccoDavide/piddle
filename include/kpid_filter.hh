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
/// file: kpid_filter.hh
///

#ifndef INCLUDE_KPID_FILTER
#define INCLUDE_KPID_FILTER

// Piddle headers
#include "kpid_block.hh"

namespace kpid
{

  /*\
   |    __ _ _ _            
   |   / _(_) | |_ ___ _ __ 
   |  | |_| | | __/ _ \ '__|
   |  |  _| | | ||  __/ |   
   |  |_| |_|_|\__\___|_|   
   |                        
  \*/

  //! Class to represent first order Butterworth low-pass filter.
  //! Transformation done using the matched-Z-transform method.
  class filter : public block
  {
  private:
    real m_frequency;          //!< Cut-off frequency (Hz)
    real m_output = real(0.0); //!< Previous output value

  public:
    //! Get cut-off frequency const reference
    real const &
    frequency(void) const
    {
      return this->m_frequency;
    }

    //! Get cut-off frequency reference
    real &
    frequency(void)
    {
      return this->m_frequency;
    }

    //! Get output value const reference
    real const &
    output(void) const
    {
      return this->m_output;
    }

    //! Get output value reference
    real &
    output(void)
    {
      return this->m_output;
    }

    //! Setup low-pass filter component
    real
    setup(
        real input,   //!< Input value
        real dt //!< Time dt
    )
        const override
    {
      if (this->isEnabled())
        return this->m_output += (input - this->m_output) * (1.0 - std::exp(-dt * 2.0 * kpid::PI * this->frequency));
      else
        return real(0.0);
    }

    //! Reset filter component
    real
    reset(void)
        override
    {
      this->m_output = real(0.0);
    };

  }; // class filter

} // namespace kpid

#endif

///
/// eof: kpid_filter.hh
///
