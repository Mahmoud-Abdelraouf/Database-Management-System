/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : ERROR_STATE.h                    *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#ifndef __ERROR_STATE_H__
#define __ERROR_STATE_H__

/**
 * @brief Enumeration of error states.
 *
 * This enumeration defines different error states that can be returned by functions
 * to indicate the outcome of an operation.
 */
typedef enum
{
    RET_NOK,        /**< Indicates an operation resulted in an error. */
    RET_OK,         /**< Indicates a successful operation. */
    RET_NULL_PTR    /**< Indicates a null pointer error. */
} Error_State_t;

#endif /* __ERROR_STATE_H__ */
