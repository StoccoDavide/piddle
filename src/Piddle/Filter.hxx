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
/// file: Filter.hh
///

#ifndef INCLUDE_PIDDLE_FILTER
#define INCLUDE_PIDDLE_FILTER

#include "Block.hxx"

namespace Piddle
{

  /*\
   |   _____ _ _ _
   |  |  ___(_) | |_ ___ _ __
   |  | |_  | | | __/ _ \ '__|
   |  |  _| | | | ||  __/ |
   |  |_|   |_|_|\__\___|_|
   |
  \*/

  //! Class to represent first order Butterworth low-pass filter.
  //! Transformation done using the matched-Z-transform method.
  class Filter : public Block
  {
  private:
    real m_cutoff_frequency;   //!< Cut-off frequency (Hz)
    real m_output = real(0.0); //!< Previous output value

  public:
    //! Class constructor
    Filter(
      real cutoff_frequency //!< Cut-off frequency (Hz)
    )
      : m_cutoff_frequency(cutoff_frequency)
    {
    }

    //! Get cut-off frequency const reference
    real const &
    cutoff_frequency(void) const
    {
      return this->m_cutoff_frequency;
    }

    //! Get cut-off frequency reference
    real &
    cutoff_frequency(void)
    {
      return this->m_cutoff_frequency;
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
      real input, //!< Input value
      real dt     //!< Time dt
    )
    const override
    {
      if (this->is_enabled())
        return this->m_output += (input - this->m_output) * (1.0 - std::exp(-dt * 2.0 * iddle::PI * this->frequency));
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

  }; // class Filter

} // namespace Piddle

#endif

///
/// eof: Filter.hh
///
