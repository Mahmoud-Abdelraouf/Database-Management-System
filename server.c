/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : Server.c                         *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#include "server.h"

u8 server_u8Temp[SERVER_U8MAX_TEMP] = {0}; // Array to store temporary data
u32 counter = 1; // Initialize the line counter to 1

u32 terminal_u32Arr[SERVER_U32MAX_LINE_NO]; // Array to store terminal data

// This function counts the number of lines in the "Database.txt" file
Error_State_t server_Error_State_tGetTheLineOfTheTXT(void)
{
    Error_State_t L_strFunctionState = RET_OK; // Initialize the function's return status
    FILE *P_Fptr = NULL; // File pointer
    s8 Buffer = 0; // Variable to store characters read from the file

    P_Fptr = fopen("Database.txt", "r"); // Open "Database.txt" in read mode
    if (P_Fptr == NULL)
    {
        L_strFunctionState = RET_NOK; // Set status to error if file cannot be opened
    }
    else
    {
        for (u32 i = 0; Buffer != EOF; i++)
        {
            Buffer = getc(P_Fptr); // Read a character from the file
            if (Buffer == '\n')
            {
                counter++; // Increment the line counter when a newline character is encountered
            }
            else
            {
                // Do nothing for other characters
            }
        }
    }
    fclose(P_Fptr); // Close the file
    return L_strFunctionState; // Return the function's status
}

// This function checks if the provided PAN exists in the "Database.txt" file
Error_State_t server_Error_State_tCheckPANInFile(Card_Info_t *copy_Card_Info_tCard,
                                                 u32 *copy_u32counter, u32 copy_PAN_Counter)
{
    Error_State_t L_strFunctionState = RET_NOK; // Initialize the function's return status
    u8 L_Temp_PAN[SERVER_U8TEMP_PAN] = {0}; // Temporary array to store PAN
    FILE *P_Fptr = NULL; // File pointer

    P_Fptr = fopen("Database.txt", "r"); // Open "Database.txt" in read mode
    if (P_Fptr == NULL)
    {
        printf("Sorry!! We have some problems in the server...\n");
        exit(1); // Print error message and exit if file cannot be opened
    }
    else
    {
        server_Error_State_tGetTheLineOfTheTXT(); // Get the number of lines in the file

        // Loop through each line in the file
        for (u32 i = 0; i < counter; i++)
        {
            fscanf(P_Fptr, "\n%[^\n]%*c\n", server_u8Temp); // Read the whole line as a string
            for (u32 j = 0; j < copy_PAN_Counter; j++)
            {
                L_Temp_PAN[j] = server_u8Temp[j]; // Copy the PAN characters from the line
            }
            // Compare the copied PAN with the provided PAN
            if (strcmp(L_Temp_PAN, copy_Card_Info_tCard->cardPAN) == 0)
            {
                L_strFunctionState = RET_OK; // Set status to success
                *copy_u32counter = i; // Store the line number
                break; // Exit the loop
            }
            else
            {
                // Do nothing if PAN does not match
            }
        }
    }
    fclose(P_Fptr); // Close the file
    return L_strFunctionState; // Return the function's status
}


// This function check if the provided card holder name matches the stored name in the file
Error_State_t server_Error_State_tCheckNAMEInFile(Card_Info_t *copy_Card_Info_tCard, u32 copy_u32counter)
{
    Error_State_t L_strFunctionState = RET_OK; // Initialize function's return status
    u8 L_u32CardName[SERVER_U8MAX_CARDNAME] = {0}; // Array to store card holder name
    terminal_Error_State_tGetTheLine(); // Call function to get terminal line information
    u32 L_u32StepName = 21 + (terminal_u32Arr[copy_u32counter]); // Calculate step to card holder name in the file
    u32 L_u32Loop_Iter = 0; // Loop iteration variable
    FILE *P_Fptr = NULL; // File pointer

    P_Fptr = fopen("Database.txt", "r"); // Open "Database.txt" in read mode
    if (NULL == P_Fptr) // Check if the file is accessible
    {
        printf("Sorry!! We have some problems in the server...\n");
        exit(1); // Print error message and exit if file cannot be opened
    }
    else
    {
        fseek(P_Fptr, L_u32StepName, SEEK_CUR); // Move file pointer to the card holder name position
        for (L_u32Loop_Iter = 0; (L_u32CardName[L_u32Loop_Iter] = getc(P_Fptr)) != '\\'; L_u32Loop_Iter++)
        {
            // Loop through characters until '\\' delimiter is encountered
        }
        L_u32CardName[L_u32Loop_Iter] = 0; // Terminate the string to remove trailing '\\'

        // Compare the stored card holder name with the provided name
        if (strcmp(copy_Card_Info_tCard->holderName, L_u32CardName) == 0)
        {
            L_strFunctionState = RET_OK; // Set status to success if names match
        }
        else
        {
            L_strFunctionState = RET_NOK; // Set status to failure if names don't match
        }
    }
    fclose(P_Fptr); // Close the file
    return L_strFunctionState; // Return the function's status
}

// This function update the remaining money for a card in the file.
Error_State_t server_Error_State_tRestOfMoney(u32 copy_u32Rest, u32 copy_u32counter)
{
    Error_State_t L_strFunctionState = RET_OK; // Initialize function's return status
    u8 L_u8storeMoneyRest[10] = {0}; // Array to store the new money value as a string
    u32 L_u32StepMoney = 57 + (terminal_u32Arr[copy_u32counter]); // Calculate step to money value in the file
    FILE *P_Fptr = NULL; // File pointer

    P_Fptr = fopen("Database.txt", "r+"); // Open "Database.txt" in read and write mode
    if (NULL == P_Fptr) // Check if the file is accessible
    {
        printf("Sorry!! We have some problems in the server...\n");
        exit(1); // Print error message and exit if file cannot be opened
    }
    else
    {
        sprintf(L_u8storeMoneyRest, "%d", copy_u32Rest); // Convert the integer money value to a string

        fseek(P_Fptr, L_u32StepMoney, SEEK_SET); // Move file pointer to the money value position
        for (u32 i = 0; L_u8storeMoneyRest[i] != '\0'; i++)
        {
            fputc(L_u8storeMoneyRest[i], P_Fptr); // Write the new money value string to the file
        }
    }
    fclose(P_Fptr); // Close the file
    return L_strFunctionState; // Return the function's status
}
