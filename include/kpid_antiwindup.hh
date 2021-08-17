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
/// file: kpid_antiwindup.hh
///

#ifndef INCLUDE_KPID_ANTIWINDUP
#define INCLUDE_KPID_ANTIWINDUP

// Piddle headers
#include "kpid_block.hh"

namespace kpid
{

  /*\
   |   _ _           _ _   
   |  | (_)_ __ ___ (_) |_ 
   |  | | | '_ ` _ \| | __|
   |  | | | | | | | | | |_ 
   |  |_|_|_| |_| |_|_|\__|
   |                       
  \*/

  //! Class to represent antiwindup block
  class antiwindup : public block
  {
  private:
    real m_upper;                   //!< Upper bound
    real m_lower;                   //!< Lower bound
    real m_integration = real(0.0); //!< Conditional integration scaling factor

  public:
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
    ) const
    {
      if (input > this->m_upper)
        return real(0.0);
      else if (input < this->m_lower)
        return real(0.0);
      else
        return real(1.0);
    }

    //! Setup antiwindup component
    real
    setup(
        real input, //!< Input value
        real dt     //!< Time step
    )
        const override
    {
      if (this->isEnabled())
      {
        if (input > this->m_upper)
          return this->m_upper;
        else if (input < this->m_lower)
          return this->m_lower;
        else
          return input;
      }
      else
      {
        return input;
      }
    }

    //! Reset antiwinduping (saturation) block components
    real
    reset(void)
        override
    {
    }

  }; // class antiwindup

} // namespace kpid

#endif

///
/// eof: kpid_antiwindup.hh
///
