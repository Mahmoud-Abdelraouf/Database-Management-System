/**
 * @file main.c
 *
 * @brief Main application for processing card payments.
 * This program validates and processes card payments using a card database and terminal communication.
 * Created on: Sep 10, 2022
 * Author: Mahmoud Abdelraouf Mahmoud
 */

#include "card.h"
#include "server.h"
#include "terminal.h"

/**
 * @brief Main function for processing card payments.
 * This function initializes card data, validates user input, checks expiration date, and processes payments.
 *
 * @return int The exit status of the program.
 */
int main() {
    Card_Info_t L_strCard; // Object to store card data
    u32 L_u32counter = 1;  // Line number indicator
    u32 L_u32MoneyResult = 0;  // Rest of money after payment
    u32 L_u32PAN_Counter = 0;  // Counter for PAN length
    u32 L_u32NAME_Counter = 0; // Counter for card holder's name length

    do {
        printf("Please, Enter the Cardholder Name: "); // Prompt for cardholder's name
        gets(L_strCard.holderName); // Get and store the cardholder's name
        strupr(L_strCard.holderName); // Convert name to uppercase for comparison
        if (getCardHolderName(&L_strCard) == WRONG_NAME) {
            printf("Error!! The name you entered is invalid. Please enter a name with 20-24 letters.\n");
        }
    } while (getCardHolderName(&L_strCard) != OK);

    printf("Please, Enter the Expiration Data : ");
    gets(L_strCard.ExpirationData); // Get and store the card's expiration data

    if (card_Error_State_tCheckTheExpFormat(&L_strCard) == RET_NOK) {
        do {
            printf("Error!! Please, Enter the Expiration Data in month/year format (e.g., 07/28): ");
            gets(L_strCard.ExpirationData);
        } while (card_Error_State_tCheckTheExpFormat(&L_strCard) != RET_OK);
    }

    if (card_Error_State_tCheckTheExpirationData() == RET_OK) {
        do {
            printf("Please, Enter the card PAN: ");
            gets(L_strCard.cardPAN);
            if (getCardPAN(&L_strCard, &L_u32PAN_Counter) == WRONG_PAN) {
                printf("Error!! The number you entered is invalid. Please enter a PAN with 16-19 characters.\n");
            }
        } while (getCardPAN(&L_strCard, &L_u32PAN_Counter) != OK);

        if (server_Error_State_tCheckPANInFile(&L_strCard, &L_u32counter, L_u32PAN_Counter) == RET_OK) {
            if (server_Error_State_tCheckNAMEInFile(&L_strCard, L_u32counter) == RET_OK) {
                printf("Enter the amount you want to pay: ");
                scanf("%d", &L_strCard.money);

                if (terminal_Error_State_tGetMoney(&L_strCard, L_u32counter, &L_u32MoneyResult) == RET_NOK) {
                    printf("Sorry!! Your current balance is not enough to complete this process...\n");
                } else {
                    printf("Payment completed successfully. Thank you!\n");
                    printf("Your current balance is: %d.\n", L_u32MoneyResult);
                    server_Error_State_tRestOfMoney(L_u32MoneyResult, L_u32counter);
                }
            } else {
                printf("Sorry!! This card holder's name is not on the system...\n");
            }
        } else {
            printf("Sorry!! This card PAN is not on the system...\n");
        }
    } else {
        printf("Sorry!! This card is expired...\n");
    }

    printf("__________________________________________________________\n");
    printf("Thanks for using THE PAYMENT APPLICATION.\n");
    printf("This APP is created by: Eng. Mahmoud Abdelraouf Mahmoud.\n");
    printf("                 GOOD BYE\n");
    printf("__________________________________________________________\n");

    while (1) {
        // Infinite loop to keep the program running
    }

    return 0; // Exit status
}
