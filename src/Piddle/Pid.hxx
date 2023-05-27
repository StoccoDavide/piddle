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
/// file: PID.hh
///

#ifndef INCLUDE_PIDDLE_PID
#define INCLUDE_PIDDLE_PID

#include "Block.hxx"
#include "Proportional.hxx"
#include "Integral.hxx"
#include "Derivative.hxx"
#include "Antiwindup.hxx"

namespace Piddle
{

  /*\
   |   ____ ___ ____
   |  |  _ \_ _|  _ \
   |  | |_) | || | | |
   |  |  __/| || |_| |
   |  |_|  |___|____/
   |
  \*/

  //! Class to represent pid block
  class PID : public Block
  {
  private:
    Proportional m_proportional; //!< Proportional block component
    Integral     m_integral;     //!< Integral block component
    Derivative   m_derivative;   //!< Derivative block component
    Antiwindup   m_antiwindup;   //!< Anti-windup block component

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
      if (this->is_enabled())
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

  }; // class PID

} // namespace Piddle

#endif

///
/// eof: PID.hh
///
