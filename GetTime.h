/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : GetTime.h                        *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#ifndef __GET_TIME_H__
#define __GET_TIME_H__

#include <stdio.h>
#include <time.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"

/**
 * @brief Get the current system time.
 *
 * This function retrieves the current system time and extracts the month and year.
 * The extracted month and year are returned through the provided arrays.
 *
 * @param[out] month Array to store the extracted month (MM format).
 * @param[out] year Array to store the extracted year (YYYY format).
 * @return Error_State_t indicating the result of getting the time.
 *         Returns RET_OK if the time was successfully retrieved.
 */
extern Error_State_t Time_Error_State_tGetTime(u8 month[], u8 year[]);

#endif /* __GET_TIME_H__ */
