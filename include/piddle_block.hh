/*
(***********************************************************************)
(*                                                                     *)
(* The PIDDLE project                                                  *)
(*                                                                     *)
(* Copyright (c) 2020-2021, Davide Stocco and Mattia Piazza.           *)
(*                                                                     *)
(* The PIDDLE project and its blocks are supplied under the terms  *)
(* of the open source BSD 3-Clause License. The contents of the PIDDLE *)
(* project and its blocks may not be copied or disclosed except in *)
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
/// file: piddle_block.hh
///

#ifndef INCLUDE_PIDDLE_BLOCK
#define INCLUDE_PIDDLE_BLOCK

// Piddle headers
#include "piddle.hh"

namespace piddle
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
  private:
    bool m_enable;                 //!< Block enable boolean
    real (*m_input)();             //!< Block input function pointer
    void (*m_output)(real output); //!< Block output function pointer
    unsigned long (*m_time)();     //!< System time function pointer

  public:
    //! block class destructor
    virtual ~block(){};

    //! block class constructor
    block(void)
        : m_enable(true){};

    //! Check if block is enabled
    bool
    isEnabled(void) const
    {
      return this->m_enable;
    }

    //! Check if block is disabled
    bool
    isDisabled(void) const
    {
      return !this->m_enable;
    }

    //! Enable/disable bool block const reference
    bool const &
    enablingState(void) const
    {
      return this->m_enable;
    }

    //! Enable/disable bool block reference
    bool &
    enablingState(void)
    {
      return this->m_enable;
    }

    //! Enable block
    void
    enable(void)
    {
      this->m_coefficient = false;
    }

    //! Disable block
    void
    disable(void)
    {
      this->m_coefficient = false;
    }

    /**
     * Sets the function pointer to the block input source.
     * Here is a usage example:
     *
     *    int inputFunction()
     *    {
     *        return data.read();
     *    }
     *    myBlock.input(inputFunction);
     *
     * @param (*inputFunction) A function pointer that retrieves block input.
     */
    void input(real (*inputFunction)())
    {
      this->m_input = inputFunction;
    }

    /**
     * Sets the function pointer to the block output.
     * Here is a usage example:
     *
     *    void outputFunction(int output)
     *    {
     *        myData.write(output);
     *    }
     *    myBlock.output(outputFunction);
     *
     * @param (*outputFunction) A function pointer that delivers block output.
     */
    void output(void (*outputFunction)(real output))
    {
      this->m_output = outputFunction;
    }

    /**
     *  Sets the function pointer to the system timing function
     *  systemTimeFunction().
     * 
     *    myBlock.time(systemTimeFunction);
     * 
     *    * Note that in this example, systemTimeFunction has no parentheses.
     *
     * @param (*systemTimeFunction) Pointer to a function that returns system time.
     */
    void time(unsigned long (*systemTimeFunction)())
    {
      m_time = systemTimeFunction;
    }

  }; // class block

} // namespace piddle

#endif

///
/// eof: piddle_block.hh
///
