/*
 * main.c
 *
 *  Created on: Sep 10, 2022
 *      Author: Mahmoud Abdelraouf Mahmoud
 */

#include "main.h"
int main()
{
    Card_Info_t L_strCard; //it's object from the struct Card_Info_t to store the card data in
	u32 L_u32counter = 1;//to know the line number we are in
	u32 L_u32MoneyResult = 0;//to store the rest of the money after payment process
	u32 L_u32PAN_Counter = 0;// to count the numbers of PAN and see if they are in between 16-19
	u32 L_u32NAME_Counter = 0;//
	do
	{
		printf("Please, Enter the Carddholder Name: ");//get the name from the user
		gets(L_strCard.holderName);//get the Carddholder name and store in L_strCard.holderName
		strupr(L_strCard.holderName); //convert any text will be enter into uper case to can compare with the data in file database.txt
		if(getCardHolderName(&L_strCard)==WRONG_NAME)
		{
			printf("Error!! The name you entered is invalid, try again, noting that the number of letters in the name is from 20-24...\n");
		}else{}
	}
	while(getCardHolderName(&L_strCard)!=OK);

    printf("Please, Enter the Expiration Data : ");
    gets(L_strCard.ExpirationData);//get the Expiration Data and store it in L_strCard.ExpirationData
    if(card_Error_State_tCheckTheExpFormat(&L_strCard)==RET_NOK)//check if the user enter the Expiration Data in form month/last two digit in the year
    {
        do
        {
			printf("Error!! Please, Enter the Expiration Data in month/year format such as 07/28\n");
			/*get the Expiration Data*/
			printf("Please, Enter the Expiration Data : ");
			gets(L_strCard.ExpirationData);
        }
		while(card_Error_State_tCheckTheExpFormat(&L_strCard)!=RET_OK);
    }else{}
    if(card_Error_State_tCheckTheExpirationData()==RET_OK)//chech the validation of the Expiration Data by compare the system data with the entered data
    {
		do
		{
			printf("Please, Enter the card PAN        : ");//get the PAN from the user
            gets(L_strCard.cardPAN);//store the PAN in L_strCard.cardPAN as a string
			if(getCardPAN(&L_strCard,&L_u32PAN_Counter)==WRONG_PAN)
			{
				printf("Error!! The number you entered is invalid, try again, noting that the number consists of 16-19 characters...\n");
			}else{}
		}
		while(getCardPAN(&L_strCard,&L_u32PAN_Counter)!=OK);
		if(server_Error_State_tCheckPANInFile(&L_strCard,&L_u32counter,L_u32PAN_Counter)==RET_OK)//to check if the PAN is in the system database or not
		{
			//printf("i'm in line %d\n",L_u32counter+1);
			if(server_Error_State_tCheckNAMEInFile(&L_strCard,L_u32counter)==RET_OK)//after checking on the PAN we check the name corresponding to the PAN
			{
				printf("Enter the amount you want to pay  : ");//ask the user to enter the amount he want to withdraw
				scanf("%d",&L_strCard.money);//get the amount he want to pay
				if(terminal_Error_State_tGetMoney(&L_strCard,L_u32counter,&L_u32MoneyResult)==RET_NOK) //if his balance don't have the amount required will return RET_NOK
				{
					printf("Sorry!! Your current balance is not enough to complete this process...\n");
				}
				else
				{
					printf("Paymeny completed Successfully,Thank you...\n");//if his account have the required amount the program will print this message
					printf("Your current balance is: %d.\n",L_u32MoneyResult);//we will return the updated amount
                    server_Error_State_tRestOfMoney(L_u32MoneyResult,L_u32counter);//this function to write the new value of money in his account in the database
				}
			}
			else
			{
				printf("Sorry!! This card Holdername is not on the system...\n");//if the CheckNAMEInFile() return RET_NOK this mean it can't find the name corresponding to the  PAN in the system
			}
		}
		else
		{
			printf("Sorry!! This card PAN is not on the system...\n");//if the CheckPANInFile() return RET_NOK is mean this card not in the the sytem
		}

    }
    else
    {
        printf("Sorry!! This card is expired...\n");
    }
	printf("__________________________________________________________\n");
	printf("Thanks for using THE PAYMENT APPLICATION.\n");
    printf("This APP is created by: Eng.Mahmoud Abdelraoof Mahmoud.\n");
    printf("                 GOOD BYE\n");
    printf("__________________________________________________________\n");

    return 0;
}
