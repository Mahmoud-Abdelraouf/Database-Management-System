/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : GetTime.c                        *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#include "GetTime.h"

// This function get the current system time.
Error_State_t Time_Error_State_tGetTime(u8 month[], u8 year[])
{
    Error_State_t L_strFunctionState = RET_OK;

    // Get the current system time
    time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);

    // Extract the month and year in MM and YYYY formats
    strftime(month, 3, "%m", tm_info);
    strftime(year, 5, "%Y", tm_info);

    return L_strFunctionState;
}
