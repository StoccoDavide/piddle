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
/// file: Antiwindup.hh
///

#ifndef INCLUDE_PIDDLE_ANTIWINDUP
#define INCLUDE_PIDDLE_ANTIWINDUP

#include "Block.hxx"

namespace Piddle
{

  /*\
   |      _          _   _          _           _
   |     / \   _ __ | |_(_)_      _(_)_ __   __| |_   _ _ __
   |    / _ \ | '_ \| __| \ \ /\ / / | '_ \ / _` | | | | '_ \
   |   / ___ \| | | | |_| |\ V  V /| | | | | (_| | |_| | |_) |
   |  /_/   \_\_| |_|\__|_| \_/\_/ |_|_| |_|\__,_|\__,_| .__/
   |                                                   |_|
  \*/

  //! Class to represent antiwindup block
  class Antiwindup : public Block
  {
  private:
    real m_upper;                   //!< Upper bound
    real m_lower;                   //!< Lower bound
    real m_integration = real(0.0); //!< Conditional integration scaling factor

  public:
    //! Class constructor
    Antiwindup(
      real upper, //!< Upper bound
      real lower  //!< Lower bound
    )
      : m_upper(upper), m_lower(lower)
    {
    }

    //! Get upper bound reference
    real &
    upper(void)
    {
      return this->m_upper;
    }

    //! Get upper bound const reference
    real const &
    upper(void) const
    {
      return this->m_upper;
    }

    //! Get lower bound reference
    real &
    lower(void)
    {
      return this->m_lower;
    }

    //! Get lower bound const reference
    real const &
    lower(void) const
    {
      return this->m_lower;
    }

    //! Get conditional integration
    real
    integration(
      real input //!< Input value
    )
    const
    {
      if (input > this->m_upper)
        return real(0.0);
      else if (input < this->m_lower)
        return real(0.0);
      else
        return real(1.0);
    }

    //! Setup anti-windup component
    real
    setup(
      real input, //!< Input value
      real dt     //!< Time step
    )
    const override
    {
      if (this->is_enabled())
      {
        if (input > this->m_upper)
        {
          return this->m_upper;
        }
        else if (input < this->m_lower)
        {
          return this->m_lower;
        }
        else
        {
          return input;
        }
      }
      else
      {
        return input;
      }
    }

    //! Reset anti-windup block components
    real
    reset(void) override
    {
    }

  }; // class Antiwindup

} // namespace Piddle

#endif

///
/// eof: Antiwindup.hh
///
