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
/// file: kpid_proportional.hh
///

#ifndef INCLUDE_KPID_PROPORTIONAL
#define INCLUDE_KPID_PROPORTIONAL

// Piddle headers
#include "kpid_block.hh"

namespace kpid
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
  class proportional : public block
  {
  private:
    real m_gain; //!< Proportional gain coefficient

  public:
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
      if (this->isEnabled())
        return this->m_gain * error;
      else
        return real(0.0);
    }

    //! Reset proportional component
    real
    reset(void)
        override
    {
    }

  }; // class proportional

} // namespace kpid

#endif

///
/// eof: kpid_proportional.hh
///
