/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : Terminal.h                       *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#ifndef __TERMINAL_H__
#define __TERMINAL_H__

// Including necessary header files
#include "STD_TYPES.h"             // Include for standard types
#include "ERROR_STATE.h"           // Include for error state values
#include "card.h"                  // Include for card information structure
#include "server.h"                // Include for server-related definitions

// Macro definitions for maximum values
#define SERVER_u8MAX_LINES 100      // Maximum number of lines
#define SERVER_u8MAX_CARDMONEY 15   // Maximum length of card money value

// Function declarations

/**
 * @brief Retrieve line information from the terminal lines in the file.
 *
 * This function reads the "Database.txt" file and identifies the positions of the terminal lines.
 * It populates the terminal_u32Arr array with the line positions indicated by '.' characters in the file.
 *
 * @return Error_State_t Returns RET_OK if the terminal lines are successfully retrieved, RET_NOK if errors occur.
 */
Error_State_t terminal_Error_State_tGetTheLine(void);

/**
 * @brief Get the remaining money for a card from the file and compare it.
 *
 * This function retrieves the remaining money for a card at the provided line counter
 * and compares it with the money value stored in the card information. If the card's
 * money value is greater than the stored remaining money, the function returns RET_NOK,
 * else it calculates the difference and stores it in copy_u32result and returns RET_OK.
 *
 * @param[in] copy_Card_Info_tCard Pointer to the Card_Info_t object with card information.
 * @param[in] copy_u32counter Line counter provided from server_Error_State_tCheckPANInFile.
 * @param[out] copy_u32result Pointer to store the difference between card money and remaining money.
 * @return Error_State_t Returns RET_OK if money comparison is successful, RET_NOK if comparison fails or errors occur.
 */
Error_State_t terminal_Error_State_tGetMoney(Card_Info_t *copy_Card_Info_tCard, u32 copy_u32counter, u32 *copy_u32result);

#endif /* __TERMINAL_H__ */
