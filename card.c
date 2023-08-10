/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : Card.c                           *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#include "card.h"

/**
 * @brief Backed-up array to store the entered month data.
 */
u8 Card_u8BackMonth[CARD_U8MAXMONTH];

/**
 * @brief Backed-up array to store the entered year data.
 */
u8 Card_u8BackYear[CARD_U8MAXYYEAR];


// This function validate and format card information.
extern Error_State_t card_Error_State_tCheckTheExpFormat(Card_Info_t *copy_Card_Info_tcardData)
{
    Error_State_t L_strFunctionState = RET_OK;

    if(copy_Card_Info_tcardData != NULL)
    {
        // Validate and separate the expiration data into month and year
        if(card_Error_State_tSetTheFormat(copy_Card_Info_tcardData->ExpirationData) == RET_NOK)
        {
            L_strFunctionState = RET_NOK;
        }
        else
        {
            L_strFunctionState = RET_OK;
        }
    }
    else
    {
        L_strFunctionState = RET_NULL_PTR;
    }

    return L_strFunctionState;
}

// This function validate the card holder's name length.
EN_cardError_t getCardHolderName(Card_Info_t *copy_Card_Info_tcardData)
{
    EN_cardError_t L_strFunctionState = OK;

    // Calculate the length of the card holder's name
    u32 L_u32NameCounter = 0;
    for(u32 i = 0; copy_Card_Info_tcardData->holderName[i] != '\0'; i++)
    {
        L_u32NameCounter++;
    }

    // Check if the name length is within the acceptable range
    if(L_u32NameCounter < 15 || L_u32NameCounter > 25)
    {
        L_strFunctionState = WRONG_NAME; // Name length is outside the acceptable range
    }
    else
    {
        // Name length is within the acceptable range
    }

    return L_strFunctionState;
}

// This function validate the card's PAN (Personal Account Number) length.
EN_cardError_t getCardPAN(Card_Info_t *copy_Card_Info_tcardData, u32 *copy_u32PAN_Counter)
{
    EN_cardError_t L_strFunctionState = OK;

    // Calculate the length of the card's PAN
    u32 L_u32NameCounter = 0;
    for(u32 i = 0; copy_Card_Info_tcardData->cardPAN[i] != '\0'; i++)
    {
        L_u32NameCounter++;
    }

    // Store the PAN length in the provided pointer
    *copy_u32PAN_Counter = L_u32NameCounter;

    // Check if the PAN length is within the acceptable range
    if(L_u32NameCounter < 16 || L_u32NameCounter > 19)
    {
        L_strFunctionState = WRONG_PAN; // PAN length is outside the acceptable range
    }
    else
    {
        // PAN length is within the acceptable range
    }

    return L_strFunctionState;
}

// This function compare the current date with the card's expiration date to check validity.
extern Error_State_t card_Error_State_tCheckTheExpirationData(void)
{
    Error_State_t L_strFunctionState = RET_NOK;

    // Arrays to store the system's current month and year
    u8 L_u8systemMon[3];
    u8 L_u8systemYear[5];

    // Get the current time of the system
    Time_Error_State_tGetTime(L_u8systemMon, L_u8systemYear);

    // Compare card's expiration year with system's current year
    if(strcmp(Card_u8BackYear, L_u8systemYear) > 0)
    {
        L_strFunctionState = RET_OK; // Card is valid
    }
    else if(strcmp(Card_u8BackYear, L_u8systemYear) == 0)
    {
        // Compare card's expiration month with system's current month
        if(strcmp(Card_u8BackMonth, L_u8systemMon) >= 0)
        {
            L_strFunctionState = RET_OK; // Card is valid
        }
        else
        {
            L_strFunctionState = RET_NOK; // Card is expired
        }
    }
    else
    {
        L_strFunctionState = RET_NOK; // Card is expired
    }

    return L_strFunctionState;
}

// This function set the format of the card's expiration date.
static Error_State_t card_Error_State_tSetTheFormat(u8 copy_u8cardData[])
{
    Error_State_t L_strFunctionState = RET_OK;

    // Check the validity of the card's month number
	L_strFunctionState = card_Error_State_tCheckTheMonthNo(copy_u8cardData);

    // Take the month after the check is done
    if(copy_u8cardData[1] == '/')
    {
        L_strFunctionState = RET_NOK;
    }
    else
    {
        // Extract the month
        Card_u8BackMonth[0] = copy_u8cardData[0];
        Card_u8BackMonth[1] = copy_u8cardData[1];
    }

    // Check the validity of the card's year
    if(copy_u8cardData[3] == '2' && copy_u8cardData[4] == '0' && copy_u8cardData[5] != '\0')
    {
        L_strFunctionState = RET_NOK;
    }
    else
    {
        // Extract the year
        Card_u8BackYear[0] = '2';
        Card_u8BackYear[1] = '0';
        Card_u8BackYear[2] = copy_u8cardData[3];
        Card_u8BackYear[3] = copy_u8cardData[4];

        if(copy_u8cardData[5] != '\0')
        {
            L_strFunctionState = RET_NOK;
        }
        else
        {
            // No further action needed for year extraction
        }
    }

    return L_strFunctionState; // Return the function state
}

// This function check the validity of the card's month number.
static Error_State_t card_Error_State_tCheckTheMonthNo(u8 copy_u8cardData[])
{
    Error_State_t L_strFunctionState = RET_OK;

    // Check if entered month is in valid format (e.g., "m/")
    if(copy_u8cardData[2] != '/' || copy_u8cardData[0] >= '1')
    {
        // Check if the month is "1X", where X is greater than 2
        if(copy_u8cardData[0] == '1' && copy_u8cardData[1] > '2')
        {
            L_strFunctionState = RET_NOK; // Invalid month
        }
        else
        {
            L_strFunctionState = RET_OK; // Valid month
        }
    }
    else
    {
        L_strFunctionState = RET_OK; // Valid month
    }

    return L_strFunctionState;
}