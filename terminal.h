#ifndef TERMINAL_H
#define TERMINAL_H

#define SERVER_u8MAX_LINES 100
#define SERVER_u8MAX_CARDMONEY 15


#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "card.h"
#include "server.h"

Error_State_t terminal_Error_State_tGetTheLine(void);
Error_State_t terminal_Error_State_tGetMoney(Card_Info_t *copy_Card_Info_tCard,u32 copy_u32counter,u32 *copy_u32result);






#endif
