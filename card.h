/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : Card.h                           *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#ifndef __CARD_H__
#define __CARD_H__

/** @defgroup CardModule Card Module
 * This module provides structures and functions for card information and validation.
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "GetTime.h"

/**
 *  @brief Maximum length for the card holder's name. */
#define CARD_U8MAX_NAME 50

/** @brief Maximum length for expiration date data. */
#define CARD_U8MAX_DATA 10

/** @brief Maximum length for the card's PAN (Personal Account Number). */
#define CARD_U8MAX_PAN  20

/** @brief Maximum length for temporary storage. */
#define CARD_U8MAXTEMP  10

/** @brief Maximum length for month representation (MM). */
#define CARD_U8MAXMONTH 3

/** @brief Maximum length for year representation (YYYY). */
#define CARD_U8MAXYYEAR 5

/** @struct Card_Info_t
 * @brief Structure to hold card information.
 */
typedef struct
{
    u8 holderName[CARD_U8MAX_NAME];        /**< Card holder's name */
    u8 ExpirationData[CARD_U8MAX_DATA];    /**< Expiration date data (MM/YY) */
    u8 cardPAN[CARD_U8MAX_PAN];            /**< Card's PAN (Personal Account Number) */
    u32 money;                             /**< Money balance on the card */
} Card_Info_t;

/** @enum EN_cardError_t
 * @brief Enumeration of possible card-related error states.
 */
typedef enum EN_cardError_t
{
    OK,                 /**< No errors */
    WRONG_NAME,         /**< Invalid card holder's name */
    WRONG_EXP_DATE,     /**< Invalid expiration date */
    WRONG_PAN           /**< Invalid card PAN */
} EN_cardError_t;

/**
 * @brief Validate and format card information.
 *
 * This function gathers all information about the card including the holder's name,
 * expiration data, and PAN card number. It validates the expiration date format and separates
 * the month and year components.
 *
 * @param[in] copy_Card_Info_tcardData Pointer to a Card_Info_t structure containing card data.
 * @return Error_State_t indicating the result of the card information validation.
 */
extern Error_State_t card_Error_State_tCheckTheExpFormat(Card_Info_t *copy_Card_Info_tCard);

/**
 * @brief Validate the card holder's name length.
 *
 * This function validates the length of the card holder's name stored in the provided Card_Info_t structure.
 * It checks if the length falls within the acceptable range of 15 to 25 characters.
 *
 * @param copy_Card_Info_tcardData Pointer to a Card_Info_t structure containing card data.
 * @return EN_cardError_t indicating the result of the validation.
 *         Returns OK if the name length is within the acceptable range,
 *         or WRONG_NAME if the name length is outside the acceptable range.
 */
extern EN_cardError_t getCardHolderName(Card_Info_t *copy_Card_Info_tcardData);

/**
 * @brief Validate the card's PAN (Personal Account Number) length.
 *
 * This function validates the length of the card's PAN stored in the provided Card_Info_t structure.
 * It checks if the length falls within the acceptable range of 16 to 19 digits.
 *
 * @param copy_Card_Info_tcardData Pointer to a Card_Info_t structure containing card data.
 * @param copy_u32PAN_Counter Pointer to store the PAN length.
 * @return EN_cardError_t indicating the result of the validation.
 *         Returns OK if the PAN length is within the acceptable range,
 *         or WRONG_PAN if the PAN length is outside the acceptable range.
 */
extern EN_cardError_t getCardPAN(Card_Info_t *copy_Card_Info_tcardData, u32 *copy_u32PAN_Counter);

/**
 * @brief Compare the current date with the card's expiration date to check validity.
 *
 * This function compares the current date of the system with the expiration date of the card.
 * If the current date is greater than the expiration date, it indicates that the card is expired.
 * If the current date is less than or equal to the expiration date, the card is considered valid.
 *
 * @return Error_State_t indicating the result of the expiration date comparison.
 *         Returns RET_OK if the card is valid, and RET_NOK if the card is expired.
 */
extern Error_State_t card_Error_State_tCheckTheExpirationData(void);

/**
 * @brief Set the format of the card's expiration date.
 *
 * This function takes the expiration data from the card_Error_State_tGetCardInf function in the form of m/y
 * and separates the data into the month and year components, ignoring the backslash.
 *
 * @param[in] copy_u8cardData Array containing the card's expiration date data (m/y format).
 * @return Error_State_t indicating the result of the expiration date format setting.
 */
static Error_State_t card_Error_State_tSetTheFormat(u8 copy_u8cardData[]);

/**
 * @brief Check the validity of the card's month number.
 *
 * This function checks whether the entered month is greater than 12 or not.
 * It takes an array of characters containing the Expiration data to validate the month.
 *
 * @param[in] copy_u8cardData Array containing the card's expiration date data (m/y format).
 * @return Error_State_t indicating the result of the month number validation.
 *         Returns RET_OK if there are no problems, and RET_NOK if there are any problems.
 */
static Error_State_t card_Error_State_tCheckTheMonthNo(u8 copy_u8cardData[]);

/** @} */

#endif /* __CARD_H__ */
