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
/// file: Proportional.hh
///

#ifndef INCLUDE_PIDDLE_PROPORTIONAL
#define INCLUDE_PIDDLE_PROPORTIONAL

#include "Block.hxx"

namespace Piddle
{

  /*\
   |                                    _   _                   _
   |   _ __  _ __ ___  _ __   ___  _ __| |_(_) ___  _ __   __ _| |
   |  | '_ \| '__/ _ \| '_ \ / _ \| '__| __| |/ _ \| '_ \ / _` | |
   |  | |_) | | | (_) | |_) | (_) | |  | |_| | (_) | | | | (_| | |
   |  | .__/|_|  \___/| .__/ \___/|_|   \__|_|\___/|_| |_|\__,_|_|
   |  |_|             |_|
  \*/

  //! Class to represent proportional component
  class Proportional : public Block
  {
  private:
    real m_gain; //!< Proportional gain coefficient

  public:
    //! Class constructor
    Proportional(
      real gain = real(1.0) //!< Proportional gain coefficient
    )
      : m_gain(gain)
    {
    }

    //! Get proportional gain const reference
    real const &
    gain(void) const
    {
      return this->m_gain;
    }

    //! Get proportional gain reference
    real &
    gain(void)
    {
      return this->m_gain;
    }

    //! Setup proportional component
    real
    setup(
      real error, //!< Input source value
      real step   //!< Time step value
    )
    const override
    {
      if (this->is_enabled())
        return this->m_gain * error;
      else
        return real(0.0);
    }

    //! Reset proportional component
    real
    reset(void) override
    {
    }

  }; // class Proportional

} // namespace Piddle

#endif

///
/// eof: Proportional.hh
///
