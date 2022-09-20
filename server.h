#ifndef SERVER_H
#define SERVER_H

#define SERVER_U8MAX_TEMP 100
#define SERVER_U32MAX_LINE_NO 100
#define SERVER_U8MAX_CARDNAME 35
#define SERVER_U8TEMP_PAN 20

#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "card.h"
#include "terminal.h"



Error_State_t server_Error_State_tGetTheLineOfTheTXT(void);
Error_State_t server_Error_State_tCheckPANInFile(Card_Info_t *copy_Card_Info_tCard,u32 *copy_u32counter,u32 copy_PAN_Counter);
Error_State_t server_Error_State_tCheckNAMEInFile(Card_Info_t *copy_Card_Info_tCard,u32 copy_u32counter);
Error_State_t server_Error_State_tRestOfMoney(u32 copy_u32Rest,u32 copy_u32counter);




#endif
