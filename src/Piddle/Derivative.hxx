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
/// file: Derivative.hh
///

#ifndef INCLUDE_PIDDLE_DERIVATIVE
#define INCLUDE_PIDDLE_DERIVATIVE

#include "Block.hxx"
#include "Filter.hxx"

namespace Piddle
{

  /*\
   |   ____            _            _   _
   |  |  _ \  ___ _ __(_)_   ____ _| |_(_)_   _____
   |  | | | |/ _ \ '__| \ \ / / _` | __| \ \ / / _ \
   |  | |_| |  __/ |  | |\ V / (_| | |_| |\ V /  __/
   |  |____/ \___|_|  |_| \_/ \__,_|\__|_| \_/ \___|
   |
  \*/

  //! Class to represent derivative component
  class Derivative : public Block
  {
  private:
    filter m_filter;                //!< Derivative output block low-pass filter
    real   m_gain;                  //!< Derivative gain coefficient
    real   m_error_old = real(0.0); //!< Previous error value

  public:
    //! Class constructor
    Derivative(
      real gain = real(1.0), //!< Derivative gain coefficient
      real fc = real(0.0)    //!< Derivative output block low-pass filter cutoff frequency
    )
      : m_gain(gain)
    {
      this->m_filter.cutoff_frequency(fc);
    }

    //! Class destructor


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
      real error, //!< Input error value
      real dt     //!< Time step
    )
    const override
    {
      if (this->is_enabled())
        return this->m_gain * this->differentiate(error, dt);
      else
        return real(0.0);
    }

    //! Reset derivative component
    void
    reset(void) override
    {
      this->m_old = real(0.0);
      this->m_filter.reset();
    };

  private:
    //! Get error derivative through backward Euler formula
    real
    differentiate(
      real error, //!< Input error value
      real dt     //!< Time step
    )
    {
      // Calculate derivative
      real diff = (error - this->m_error_old) / dt;

      // Perform derivative filtering
      if (this->m_filter.is_enabled())
      {
        diff = this->m_filter.setup(diff, dt);
      }

      this->m_error_old = error;
      return diff;
    }

  }; // class Derivative

} // namespace Piddle

#endif

///
/// eof: Derivative.hh
///
