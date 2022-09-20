#include "server.h"

u8 server_u8Temp[SERVER_U8MAX_TEMP] = {0};//SERVER_U8MAX_TEMP 100
u32 counter = 1; //this counter to know the number of lines in the database.txt file
u32 terminal_u32Arr[SERVER_U32MAX_LINE_NO];//SERVER_u32MAX_LINENO 100

/****
* this function don't take any parameters
* it just count the number of the line in the file database.txt
* it return the number of lines in file database.txt
****/
Error_State_t server_Error_State_tGetTheLineOfTheTXT(void)
{
	Error_State_t L_strFunctionState = RET_OK;
	FILE *P_Fptr = NULL;
	s8 Buffer = 0;
	P_Fptr = fopen("Database.txt","r");
	if(P_Fptr==NULL)
	{
		L_strFunctionState = RET_NOK;
	}
	else
	{
		for(u32 i = 0;Buffer!=EOF;i++)
		{
			Buffer=getc(P_Fptr);
			if(Buffer=='\n')
			{
				counter++;
			}else{}
		}
	}
	return L_strFunctionState;
}




/****
*this function take to parameter:
* 1) object from Card_Info_t: to can access the struct and read entered cardPAN to check if it's exist in the database.txt file or not
* 2) pointer to u32 counter: he is return  the number of the line he found the PAN in, then we use to move into the
* it return -> RET_OK if it found the PAN else -> RET_NOK
****/
Error_State_t server_Error_State_tCheckPANInFile(Card_Info_t *copy_Card_Info_tCard,u32 *copy_u32counter,u32 copy_PAN_Counter)
{
	Error_State_t L_strFunctionState = RET_NOK;
	u8 L_Temp_PAN[SERVER_U8TEMP_PAN] = {0};
	FILE *P_Fptr = NULL;
	P_Fptr = fopen("Database.txt","r");
	if(P_Fptr==NULL)
	{
		printf("Sorry!! We have some problems in the server...\n");
		exit(1);
	}
	else
	{
		server_Error_State_tGetTheLineOfTheTXT();//to know the number of line in the file database.txt
		for(u32 i =0;i<counter;i++)
		{
			fscanf(P_Fptr,"\n%[^\n]%*c\n",server_u8Temp);//get all string in the nth line
			for(u32 j = 0;j<copy_PAN_Counter;j++)
			{
				L_Temp_PAN[j]=server_u8Temp[j];
			}
			if(strcmp(L_Temp_PAN,copy_Card_Info_tCard->cardPAN)==0)
			{
				L_strFunctionState = RET_OK;
				*copy_u32counter =  i;
				break;
			}else{}



		}
	}
	fclose(P_Fptr);
	return L_strFunctionState;
}


/****
* this function take tow arguments:
* 1) object from card_info_t.
* 2) a counter which will be sent from -> the server_Error_State_tCheckPANInFile().
* but not in direct path it will be send from main() as a argument which will path to -> the server_Error_State_tCheckNAMEInFile() function.
* this function check if the Name wich the user have entered is corresponding to the PAN or not
* and it return RET_OK if they are identical and return RET_NOK if they are not identical.
****/
Error_State_t server_Error_State_tCheckNAMEInFile(Card_Info_t *copy_Card_Info_tCard,u32 copy_u32counter)
{
	Error_State_t L_strFunctionState = RET_OK;
	u8 L_u32CardName[SERVER_U8MAX_CARDNAME]={0};//SERVER_u8MAX_CARDNAME 35 //to store the name that i will get from database.txt to compare him with the entered name by the user
	terminal_Error_State_tGetTheLine();//
	//printf("%d\n",copy_u32counter);
	//printf("%d\n",L_u32Line);
	u32 L_u32StepName = 21+(terminal_u32Arr[copy_u32counter]);//this is the step that i specified inside my file database.txt,warning!! if you will change any spaces in file database you should recalculate this step in the new changes
	u32 L_u32Loop_Iter = 0;//loop iteration
	FILE *P_Fptr = NULL;
	P_Fptr = fopen("Database.txt","r");
	if(NULL==P_Fptr)//check if the file is exist or not
	{
		printf("Sorry!! We have some problems in the server...\n");
		exit(1);
	}
	else
	{
		fseek(P_Fptr,L_u32StepName,SEEK_CUR);
		for(L_u32Loop_Iter = 0;(L_u32CardName[L_u32Loop_Iter]=getc(P_Fptr))!= '\\';L_u32Loop_Iter++)
		{
			//printf("%c\n",L_u32CardName[L_u32Loop_Iter]);
		}
		L_u32CardName[L_u32Loop_Iter] = 0; //put zero in the last element to ignore the '\' at the end of each name to get the actual name without any extra
		/********* compare the two string to see if they are identical or not
		* if they are identical i will return RET_OK.
		* if they are not identical i will return RET_NOK.
		*********/
		if(strcmp(copy_Card_Info_tCard->holderName,L_u32CardName)==0)
		{
			L_strFunctionState = RET_OK;
		}
		else
		{
			L_strFunctionState = RET_NOK;
		}
	}
	fclose(P_Fptr);
	return L_strFunctionState;
}

Error_State_t server_Error_State_tRestOfMoney(u32 copy_u32Rest,u32 copy_u32counter)
{
	Error_State_t L_strFunctionState = RET_OK;
	u8 L_u8storeMoneyRest[10] ={0};//to store the new value of money as string
	u32 L_u32StepMoney = 57+(terminal_u32Arr[copy_u32counter]);
	u8 L_u8Buffer = 0;
	FILE *P_Fptr = NULL;
	P_Fptr = fopen("Database.txt","r+");//open file in append mode to store the new value of the money
	sprintf(L_u8storeMoneyRest,"%d",copy_u32Rest);//convert the int value of the money to string to store in file
	fseek(P_Fptr,L_u32StepMoney,SEEK_SET);
	for(u32 i = 0;L_u8storeMoneyRest[i]!='\0';i++)
	{
		fputc(L_u8storeMoneyRest[i],P_Fptr);
	}
	fclose(P_Fptr);
	return L_strFunctionState;
}

