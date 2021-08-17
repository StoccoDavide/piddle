/*
(***********************************************************************)
(*                                                                     *)
(* The KPID project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Mattia Piazza.           *)
(*                                                                     *)
(* The KPID project and its blocks are supplied under the terms        *)
(* of the open source BSD 3-Clause License. The contents of the KPID   *)
(* project and its blocks may not be copied or disclosed except in     *)
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
/// file: kpid_block.hh
///

#ifndef INCLUDE_KPID_BLOCK
#define INCLUDE_KPID_BLOCK

// Eigen libraries
#include <Eigen/Dense>

// Piddle headers
#include "kpid.hh"

namespace kpid
{

  /*\
   |   _     _            _    
   |  | |__ | | ___   ___| | __
   |  | '_ \| |/ _ \ / __| |/ /
   |  | |_) | | (_) | (__|   < 
   |  |_.__/|_|\___/ \___|_|\_\
   |                           
  \*/

  //! Class to represent a block
  class block
  {
  protected:
    bool m_enabled; //!< Block enable boolean

  public:
    //! block class destructor
    virtual ~block(){};

    //! Check if block is enabled
    bool
    isEnabled(void) const
    {
      return this->m_enabled;
    }

    //! Check if block is disabled
    bool
    isDisabled(void) const
    {
      return !this->m_enabled;
    }

    //! Enable/disable bool block const reference
    bool const &
    enablingState(void) const
    {
      return this->m_enabled;
    }

    //! Enable/disable bool block reference
    bool &
    enablingState(void)
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
        real input,   //!< Input value
        real dt //!< Time step
    ) const = 0;

    //! Reset block internal parameters
    virtual void
    reset(void) = 0;

  }; // class block

} // namespace kpid

#endif

///
/// eof: kpid_block.hh
///
