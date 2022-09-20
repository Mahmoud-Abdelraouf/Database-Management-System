#ifndef CARD_H
#define CARD_H

#define CARD_U8MAX_NAME 50
#define CARD_U8MAX_DATA 10
#define CARD_U8MAX_PAN  20
#define CARD_U8MAXTEMP  10
#define CARD_U8MAXMONTH 3
#define CARD_U8MAXYYEAR 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "GetTime.h"


typedef struct
{
    u8 holderName[CARD_U8MAX_NAME];
    u8 ExpirationData[CARD_U8MAX_DATA];
    u8 cardPAN[CARD_U8MAX_PAN];
	u32 money;
}Card_Info_t;


typedef enum EN_cardError_t
{
	OK,
	WRONG_NAME,
	WRONG_EXP_DATE,
	WRONG_PAN
}EN_cardError_t;



extern EN_cardError_t getCardHolderName(Card_Info_t *copy_Card_Info_tcardData);
extern EN_cardError_t getCardPAN(Card_Info_t *copy_Card_Info_tcardData,u32 *copy_u32PAN_Counter);
extern Error_State_t card_Error_State_tCheckTheExpirationData(void);
extern Error_State_t card_Error_State_tCheckTheExpFormat(Card_Info_t *copy_Card_Info_tCard);
static Error_State_t card_Error_State_tSetTheFormat(u8 copy_u8cardData[]);
static Error_State_t card_Error_State_tCheckTheMonthNo(u8 copy_u8cardData[]);





#endif
