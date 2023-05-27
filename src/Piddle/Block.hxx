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
/// file: Block.hh
///

#ifndef INCLUDE_PIDDLE_BLOCK
#define INCLUDE_PIDDLE_BLOCK

namespace Piddle
{

  /*\
   |   ____  _            _
   |  | __ )| | ___   ___| | __
   |  |  _ \| |/ _ \ / __| |/ /
   |  | |_) | | (_) | (__|   <
   |  |____/|_|\___/ \___|_|\_\
   |
  \*/

  //! Class to represent a block in a control system
  class Block
  {
  protected:
    bool m_enabled; //!< Block enable boolean

  public:
    //! Class destructor (virtual)
    virtual ~Block()
    {};

    //! Class constructor
    Block(void)
      : m_enabled(true)
    {};

    //! Class constructor
    Block(
      bool enabled //!< Block enable boolean
    ) : m_enabled(enabled)
    {};

    //! Check if block is enabled
    bool
    is_enabled(void) const
    {
      return this->m_enabled;
    }

    //! Check if block is disabled
    bool
    is_disabled(void) const
    {
      return !this->m_enabled;
    }

    //! Enable/disable bool block const reference
    bool const &
    enabling_state(void) const
    {
      return this->m_enabled;
    }

    //! Enable/disable bool block reference
    bool &
    enabling_state(void)
    {
      return this->m_enabled;
    }

    //! Enable block
    void
    enable(void)
    {
      this->m_enabled = false;
    }

    //! Disable block
    void
    disable(void)
    {
      this->m_enabled = false;
    }

    //! Setup block and calculate output
    virtual real
    setup(
      real input, //!< Input value
      real dt     //!< Time step
    ) const = 0;

    //! Reset block internal parameters
    virtual void
    reset(void) = 0;

  }; // class Block

} // namespace Piddle

#endif

///
/// eof: Block.hh
///
