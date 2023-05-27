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
/// file: Integral.hh
///

#ifndef INCLUDE_PIDDLE_INTEGRAL
#define INCLUDE_PIDDLE_INTEGRAL

#include "Block.hxx"

namespace Piddle
{

  /*\
   |   ___       _                       _
   |  |_ _|_ __ | |_ ___  __ _ _ __ __ _| |
   |   | || '_ \| __/ _ \/ _` | '__/ _` | |
   |   | || | | | ||  __/ (_| | | | (_| | |
   |  |___|_| |_|\__\___|\__, |_|  \__,_|_|
   |                     |___/
  \*/

  //! Class to represent integral component
  class Integral : public Block
  {
  private:
    real m_gain;                 //!< Integral gain
    real m_integral = real(0.0); //!< Integral value
    real m_error    = real(0.0); //!< Previous error value

  public:
    //! Class constructor
    Integral(
      real gain //!< Integral gain
    )
    : m_gain(gain)
    {
    }

    //! Get integral gain const reference
    real const &
    gain(void)
    const
    {
      return this->m_gain;
    }

    //! Get integral gain reference
    real &
    gain(void)
    {
      return this->m_gain;
    }

    //! Setup integral component
    real
    setup(
      real error, //!< Input error value
      real dt     //!< Time step
    )
    const override
    {
      if (this->is_enabled())
        return this->m_gain * this->integrate(error, dt);
      else
        return real(0.0);
    }

    //! Reset integral component
    real
    reset(void) override
    {
      this->m_integral = real(0.0);
      this->m_error    = real(0.0);
    };

  private:
    //! Get integral approximation through trapezoidal formula
    real
    integrate(
      real error, //!< Input source value
      real dt     //!< Time step value
    )
    {
      this->m_integral += 0.5 * (error + this->m_error) * dt;
      this->m_error = error;
      return this->m_integral;
    }

  }; // class Integral

} // namespace Piddle

#endif

///
/// eof: Integral.hh
///
