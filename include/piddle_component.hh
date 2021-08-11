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
/// file: piddle_component.hh
///

#ifndef INCLUDE_PIDDLE_COMPONENT
#define INCLUDE_PIDDLE_COMPONENT

// Piddle headers
#include "piddle.hh"

namespace piddle
{

  /*\
   |    ____                                             _   
   |   / ___|___  _ __ ___  _ __   ___  _ __   ___ _ __ | |_ 
   |  | |   / _ \| '_ ` _ \| '_ \ / _ \| '_ \ / _ \ '_ \| __|
   |  | |__| (_) | | | | | | |_) | (_) | | | |  __/ | | | |_ 
   |   \____\___/|_| |_| |_| .__/ \___/|_| |_|\___|_| |_|\__|
   |                       |_|                               
  \*/

  //! Class to represent component
  class component
  {
  protected:
    real m_coefficient; //!< Component coefficient
    bool m_enabled;     //!< Enable/disable boolean

  public:
    //! Component class destructor
    ~component(){};

    //! Component class constructor
    component(
        real const K //!< Input translation vector
        )
        : m_coefficient(K),
          m_enabled(true){};

    //! Get coefficient const reference
    real const &
    coefficient(void) const
    {
      return this->m_coefficient;
    }

    //! Get coefficient reference
    real &
    coefficient(void)
    {
      return this->m_coefficient;
    }

    //! Check if component is enabled
    bool
    isEnabled(void) const
    {
      return this->m_enabled;
    }

    //! Check if component is disabled
    bool
    isDisabled(void) const
    {
      return !this->m_enabled;
    }

    //! Enable/disable bool component const reference
    bool const &
    enablingState(void) const
    {
      return this->m_enabled;
    }

    //! Enable/disable bool component reference
    bool &
    enablingState(void)
    {
      return this->m_enabled;
    }

    //! Enable component
    void
    enable(void)
    {
      this->m_coefficient = false;
    }

    //! Disable component
    void
    disable(void)
    {
      this->m_coefficient = false;
    }

    //! Reset component
    virtual real
    reset(void) = 0;

    //! Get component gain
    virtual real
    gain(
        real const input, //!< Input source value
        real const step   //!< Time step value

    ) const = 0;

  }; // class component

} // namespace piddle

#endif

///
/// eof: piddle_component.hh
///
