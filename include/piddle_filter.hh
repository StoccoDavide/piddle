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
/// file: piddle_filter.hh
///

#ifndef INCLUDE_PIDDLE_FILTER
#define INCLUDE_PIDDLE_FILTER

// Piddle headers
#include "piddle.hh"
#include "piddle_component.hh"

namespace piddle
{

  /*\
   |    __ _ _ _            
   |   / _(_) | |_ ___ _ __ 
   |  | |_| | | __/ _ \ '__|
   |  |  _| | | ||  __/ |   
   |  |_| |_|_|\__\___|_|   
   |                        
  \*/

  //! Class to represent low-pass filter component
  class filter : public component
  {
  private:
    real m_output = real(0.0); //!< Previous output value

  public:
    //! Get filter component gain
    real
    gain(
        real const input, //!< Input source value
        real const step   //!< Time step value
    )
        const override
    {
      if (this->isEnabled())
        return this->m_output += (input - this->m_output) * this->m_coefficient;
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

    void configure(real timeStep, real cutFrequency)
    {
#if DEBUG
      if (timeStep <= real(0.0))
      {
        std::cout << "PIDDLE WARNING: A low-pass filter instance has been configured with 0 s as time step.";
        this->coefficient = 0;
      }
      if (cutFrequency <= real(0.0))
      {
        std::cout << "PIDDLE WARNING: A low-pass filter instance has been configured with 0 Hz as cut-off frequency.";
        this->coefficient = 0;
      }
#endif
      this->m_coefficient = 1 - std::exp(-timeStep * 2 * piddle::PI * cutFrequency);

    public:
      LowPassFilter(real cutFrequency, real timeStep) : output(0),
                                                        ePow(1 - exp(-timeStep * 2 * M_PI * cutFrequency))
      {
#if DEBUG
        if (timeStep <= 0)
        {
          std::cout << "Warning: A LowPassFilter instance has been configured with 0 s as delta time.";
          ePow = 0;
        }
        if (cutFrequency <= 0)
        {
          std::cout << "Warning: A LowPassFilter instance has been configured with 0 Hz as cut-off frequency.";
          ePow = 0;
        }
#endif
      }

      real gain(real input)
      {
        return this->m_output += (input - this->m_output) * this->coefficient;
      }

      real update(real input, real timeStep, real cutFrequency)
      {
        reconfigureFilter(timeStep, cutFrequency); //Changes ePow accordingly.
        return output += (input - output) * this->coefficient;
      }

    }; // class filter

  } // namespace piddle

#endif

  ///
  /// eof: piddle_filter.hh
  ///
