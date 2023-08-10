/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : Server.h                         *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "card.h"
#include "terminal.h"

/**
 * @defgroup Server Server
 * @{
 */

/** @brief Maximum number of temporary elements in the server. */
#define SERVER_U8MAX_TEMP 100

/** @brief Maximum number of line elements in the server. */
#define SERVER_U32MAX_LINE_NO 100

/** @brief Maximum length of cardholder's name in the server. */
#define SERVER_U8MAX_CARDNAME 35

/** @brief Temporary PAN length in the server. */
#define SERVER_U8TEMP_PAN 20

/**
 * @brief Get the number of lines in the database text file.
 *
 * This function reads the "Database.txt" file and counts the number of lines.
 *
 * @return Error_State_t The function's execution status.
 */
Error_State_t server_Error_State_tGetTheLineOfTheTXT(void);

/**
 * @brief Check if the given PAN exists in the database file.
 *
 * This function checks if the provided PAN exists in the "Database.txt" file.
 * It also returns the line number where the PAN is found.
 *
 * @param copy_Card_Info_tCard Pointer to the card information structure.
 * @param copy_u32counter Pointer to store the line number with the PAN.
 * @param copy_PAN_Counter Length of the PAN to compare.
 * @return Error_State_t The function's execution status.
 */
Error_State_t server_Error_State_tCheckPANInFile(Card_Info_t *copy_Card_Info_tCard,
                                                 u32 *copy_u32counter, u32 copy_PAN_Counter);

/**
 * @brief Check if the provided card holder name matches the stored name in the file.
 *
 * This function checks if the card holder name corresponding to the given line counter
 * matches the provided card's holder name. It compares the two names and returns
 * RET_OK if they are identical, and RET_NOK if they are not.
 *
 * @param[in] copy_Card_Info_tCard Pointer to the Card_Info_t object with card information.
 * @param[in] copy_u32counter Line counter provided from server_Error_State_tCheckPANInFile.
 * @return Error_State_t Returns RET_OK if names match, RET_NOK if names don't match or errors occur.
 */
Error_State_t server_Error_State_tCheckNAMEInFile(Card_Info_t *copy_Card_Info_tCard,
                                                  u32 copy_u32counter);


/**
 * @brief Update the remaining money for a card in the file.
 *
 * This function updates the remaining money for a card at the provided line counter
 * with the new value. It converts the integer money value to a string and updates
 * the corresponding position in the file.
 *
 * @param[in] copy_u32Rest New remaining money value.
 * @param[in] copy_u32counter Line counter provided from server_Error_State_tCheckPANInFile.
 * @return Error_State_t Returns RET_OK if money is updated successfully, RET_NOK if errors occur.
 */
Error_State_t server_Error_State_tRestOfMoney(u32 copy_u32Rest, u32 copy_u32counter);

/**
 * @}
 */

#endif /* __SERVER_H__ */
