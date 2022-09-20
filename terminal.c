#include "terminal.h"

extern u32 terminal_u32Arr[SERVER_u8MAX_LINES];//SERVER_u8MAX_LINES 100
s8 terminal_u8Buffer = 0;
u32 terminal_u32counter = 0;
/****
*
*
****/
Error_State_t terminal_Error_State_tGetTheLine(void)
{
	Error_State_t L_strFunctionState = RET_OK;
	static u32 L_u32counter_J=0;
	FILE *P_Fptr = 0;
	P_Fptr = fopen("Database.txt","r");
	if(P_Fptr==NULL)
	{
		printf("Sorry!! We have some problems in the server...\n");
		exit(1);
	}
	else
	{
		for(u32 i=0;terminal_u8Buffer!=EOF;i++)
		{
			terminal_u8Buffer=getc(P_Fptr);
			if(terminal_u8Buffer=='.')
			{
				terminal_u32counter++;

				for(L_u32counter_J ;L_u32counter_J<terminal_u32counter;L_u32counter_J++)
				{
					terminal_u32Arr[L_u32counter_J+1]=i+L_u32counter_J+3;
				}
			}else{}
		}
	}
	fclose(P_Fptr);
	return L_strFunctionState;
}

Error_State_t terminal_Error_State_tGetMoney(Card_Info_t *copy_Card_Info_tCard,u32 copy_u32counter,u32 *copy_u32result)
{
	Error_State_t L_strFunctionState = RET_OK;
	u32 L_u32maxMoney = 0;
	u32 L_u32Loop_Iter = 0;
	u8 L_u32CardMoney[SERVER_u8MAX_CARDMONEY]={0};
	u32 L_u32StepName = 57+(terminal_u32Arr[copy_u32counter]);
	FILE *P_Fptr = 0;
	P_Fptr = fopen("Database.txt","r");
	if(P_Fptr==NULL)
	{
		printf("Sorry!! We have some problems in the server...\n");
		exit(1);
	}
	else
	{
		terminal_Error_State_tGetTheLine();
		fseek(P_Fptr,L_u32StepName,SEEK_CUR);
		for(L_u32Loop_Iter = 0;(L_u32CardMoney[L_u32Loop_Iter]=getc(P_Fptr))!='\\';L_u32Loop_Iter++)
		{
			//printf("%c\n",L_u32CardMoney[L_u32Loop_Iter]);
		}
		L_u32CardMoney[L_u32Loop_Iter]=0;
		L_u32maxMoney = atoi(L_u32CardMoney);
		if(copy_Card_Info_tCard->money > L_u32maxMoney)
		{
			L_strFunctionState = RET_NOK;
		}
		else
		{
			*copy_u32result=L_u32maxMoney-copy_Card_Info_tCard->money;
			L_strFunctionState=RET_OK;
		}
	}
	return L_strFunctionState;
}




