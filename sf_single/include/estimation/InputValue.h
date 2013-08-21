/**
 * @file 
 * @author Denise Ratasich
 * @date 24.07.2013
 *
 * @brief Header file of the input value of an estimation algorithm.
 */

#ifndef ESTIMATION_INPUTVALUE_H
#define ESTIMATION_INPUTVALUE_H

#include <ctime>

namespace estimation 
{

  /**
   * Holds a data value to use for estimation of an entity.
   */
  class InputValue 
  { 
    /** Stores a data value of an entity. */
    double value;
    /** The jitter in ms from sensing till creating this instance. */
    unsigned int jitter_ms;

    /** Timestamp of creation (for updating the jitter when using this
     * value). */
    clock_t t_creation;

  public: 
    /**
     * Basic constructor.
     *
     * This constructor is only to create arrays of InputValue without
     * initializing.
     */
    InputValue(void);

    /**
     * Constructor of this class which should be used to create a new
     * value to pass to an estimation algorithm.
     *
     * @param value A data value of an entity.
     * @param jitter_ms The jitter from measuring the value till calling
     * this constructor.
     */
    InputValue(double value, unsigned int jitter_ms);

    // -----------------------------------------
    // getters and setters
    // -----------------------------------------
    /**
     * Returns the value.
     *
     * @return The data value.
     */
    double getValue(void);

    /**
     * Returns the jitter in ms between sensing and this function call.
     */
    unsigned int getJitter(void);

    /**
     * Sets the value.
     *
     * @param value The data value.
     */
    void setValue(double value);

    /**
     * Sets the jitter in ms between sensing and this function call.
     *
     * @param jitter_ms The jitter in ms.
     */
    void setJitter(unsigned int jitter_ms);

    // -----------------------------------------
    // overloading operators
    // -----------------------------------------
    /**
     * Swaps the data of two elements.
     */
    void swap(InputValue& first, InputValue& second);

    /**
     * Overloads the assign operator.
     */
    InputValue& operator=(InputValue right);

    /**
     * Overloads the == (equal) operator (compares the value
     * member).
     */
    bool operator==(const InputValue& rhs) const;

    /**
     * Overloads the != (not-equal) operator (compares the value
     * member).
     */
    bool operator!=(const InputValue& rhs) const;

    /**
     * Overloads the < (less-than) operator (compares the value
     * member).
     */
    bool operator<(const InputValue& rhs) const;

    /**
     * Overloads the > (greater-than) operator (compares the value
     * member).
     */
    bool operator>(const InputValue& rhs) const;

    /**
     * Overloads the <= (less-or-equal) operator (compares the value
     * member).
     */
    bool operator<=(const InputValue& rhs) const;

    /**
     * Overloads the >= (greater-or-equal) operator (compares the
     * value member).
     */
    bool operator>=(const InputValue& rhs) const;
  };

}

#endif