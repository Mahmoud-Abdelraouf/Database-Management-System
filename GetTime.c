#include "GetTime.h"


Error_State_t Time_Error_State_tGetTime(u8 month[],u8 year[])
{
	Error_State_t L_strFunctionState = RET_OK;

	time_t timer;
    struct tm* tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(month, 3, "%m", tm_info);
    strftime(year, 5, "%Y", tm_info);
	return L_strFunctionState;
}
