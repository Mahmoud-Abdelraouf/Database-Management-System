/********************************************************************************************/
/********** Author   : Mahmoud Abdelraouf Mahmoud       *************************************/
/********** Date     : Sep 10, 2022                     *************************************/
/********** SWC      : Terminal.c                       *************************************/
/********** Version  : V02                              *************************************/
/********************************************************************************************/
#include "terminal.h"

extern u32 terminal_u32Arr[SERVER_u8MAX_LINES];  // Declaration of an array to store line positions
                                                 // The size is determined by SERVER_u8MAX_LINES

s8 terminal_u8Buffer = 0;                        // Declaration of a signed 8-bit variable to store buffer data

u32 terminal_u32counter = 0;                     // Declaration of an unsigned 32-bit variable to count terminal lines


// This function retrieve line information from the terminal lines in the file.
Error_State_t terminal_Error_State_tGetTheLine(void)
{
    Error_State_t L_strFunctionState = RET_OK; // Initialize function's return status
    static u32 L_u32counter_J = 0; // Static counter for array index
    FILE *P_Fptr = NULL; // File pointer

    P_Fptr = fopen("Database.txt", "r"); // Open "Database.txt" in read mode
    if (P_Fptr == NULL) // Check if the file is accessible
    {
        printf("Sorry!! We have some problems in the server...\n");
        exit(1); // Print error message and exit if file cannot be opened
    }
    else
    {
        for (u32 i = 0; terminal_u8Buffer != EOF; i++)
        {
            terminal_u8Buffer = getc(P_Fptr); // Read characters from the file
            if (terminal_u8Buffer == '.')
            {
                terminal_u32counter++; // Increment the terminal line counter

                // Populate the terminal line positions in the array
                for (L_u32counter_J; L_u32counter_J < terminal_u32counter; L_u32counter_J++)
                {
                    terminal_u32Arr[L_u32counter_J + 1] = i + L_u32counter_J + 3;
                }
            }
        }
    }
    fclose(P_Fptr); // Close the file
    return L_strFunctionState; // Return the function's status
}

// This function get the remaining money for a card from the file and compare it.
Error_State_t terminal_Error_State_tGetMoney(Card_Info_t *copy_Card_Info_tCard, u32 copy_u32counter, u32 *copy_u32result)
{
    Error_State_t L_strFunctionState = RET_OK; // Initialize function's return status
    u32 L_u32maxMoney = 0; // Variable to store the maximum money value
    u32 L_u32Loop_Iter = 0; // Loop iteration variable
    u8 L_u32CardMoney[SERVER_u8MAX_CARDMONEY] = {0}; // Array to store card money value as a string
    u32 L_u32StepName = 57 + (terminal_u32Arr[copy_u32counter]); // Calculate step to money value in the file
    FILE *P_Fptr = NULL; // File pointer

    P_Fptr = fopen("Database.txt", "r"); // Open "Database.txt" in read mode
    if (P_Fptr == NULL) // Check if the file is accessible
    {
        printf("Sorry!! We have some problems in the server...\n");
        exit(1); // Print error message and exit if file cannot be opened
    }
    else
    {
        terminal_Error_State_tGetTheLine(); // Retrieve terminal line positions
        fseek(P_Fptr, L_u32StepName, SEEK_CUR); // Move file pointer to the money value position
        for (L_u32Loop_Iter = 0; (L_u32CardMoney[L_u32Loop_Iter] = getc(P_Fptr)) != '\\'; L_u32Loop_Iter++)
        {
            // Loop through characters until '\\' delimiter is encountered
        }
        L_u32CardMoney[L_u32Loop_Iter] = 0; // Terminate the string

        L_u32maxMoney = atoi(L_u32CardMoney); // Convert the money value to an integer
        if (copy_Card_Info_tCard->money > L_u32maxMoney)
        {
            L_strFunctionState = RET_NOK; // Set status to failure if card money exceeds remaining money
        }
        else
        {
            *copy_u32result = L_u32maxMoney - copy_Card_Info_tCard->money; // Calculate the difference
            L_strFunctionState = RET_OK; // Set status to success
        }
    }
    fclose(P_Fptr); // Close the file
    return L_strFunctionState; // Return the function's status
}
