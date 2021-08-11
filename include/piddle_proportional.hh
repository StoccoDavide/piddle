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
/// file: piddle_proportional.hh
///

#ifndef INCLUDE_PIDDLE_PROPORTIONAL
#define INCLUDE_PIDDLE_PROPORTIONAL

// Piddle headers
#include "piddle.hh"
#include "piddle_component.hh"

namespace piddle
{

  /*\
   |   ____                             _   _                   _ 
   |  |  _ \ _ __ ___  _ __   ___  _ __| |_(_) ___  _ __   __ _| |
   |  | |_) | '__/ _ \| '_ \ / _ \| '__| __| |/ _ \| '_ \ / _` | |
   |  |  __/| | | (_) | |_) | (_) | |  | |_| | (_) | | | | (_| | |
   |  |_|   |_|  \___/| .__/ \___/|_|   \__|_|\___/|_| |_|\__,_|_|
   |                  |_|                                         
  \*/

  //! Class to represent proportional component
  class P : public component
  {
  public:
    //! Get proportional component gain
    real
    gain(
        real const input, //!< Input source value
        real const step   //!< Time step value
    )
        const override
    {
      if (this->isEnabled())
        return this->m_coefficient * input;
      else
        return real(0.0);
    }

    //! Reset proportional component
    real
    reset(void) override {};

  }; // class proportional

} // namespace piddle

#endif

///
/// eof: piddle_proportional.hh
///
