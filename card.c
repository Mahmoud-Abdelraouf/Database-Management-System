#include "card.h"

u8 Card_u8BackMonth[CARD_U8MAXMONTH];//to back the entered month in
u8 Card_u8BackYear[CARD_U8MAXYYEAR]; //to back the entered year in


/**** this function get all information about the card
* it take the holdername as string.
* it take the Expiration Data as a string the it will be sended to the -> card_Error_State_tFormat function to separate
* the data.
* it take the PAN card as u32 no.
****/

extern Error_State_t card_Error_State_tCheckTheExpFormat(Card_Info_t *copy_Card_Info_tcardData)
{
    Error_State_t L_strFunctionState = RET_OK;
    if(copy_Card_Info_tcardData!=NULL)
    {
        /*get the month and the year separately*/
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



/**** this function take the expiration data from card_Error_State_tGetCardInf function  in the form of m/y then
* it separate the data to the month and the year after had ignored the back slash.
* it take the data from -> card_Error_State_tGetCardInf() function.
****/
static Error_State_t card_Error_State_tSetTheFormat(u8 copy_u8cardData[])
{
    Error_State_t L_strFunctionState = RET_OK;
	L_strFunctionState = card_Error_State_tCheckTheMonthNo(copy_u8cardData);//stored the return value in L_strFunctionState to sent into the main and use this data to make a certain decision
    /********to take the month after the check had done********/
	if(copy_u8cardData[1]=='/')
	{
		L_strFunctionState = RET_NOK;
	}
	else
	{
		/*month*/
		Card_u8BackMonth[0]=copy_u8cardData[0];
		Card_u8BackMonth[1]=copy_u8cardData[1];
	}
	/******to take the year after the check had done******/
	if(copy_u8cardData[3]=='2'&&copy_u8cardData[4]=='0'&&copy_u8cardData[5]!='\0')
    {
        L_strFunctionState = RET_NOK;
    }
    else
    {
        /*year*/
        Card_u8BackYear[0]='2';
        Card_u8BackYear[1]='0';
        Card_u8BackYear[2]=copy_u8cardData[3];
        Card_u8BackYear[3]=copy_u8cardData[4];
		if(copy_u8cardData[5]!='\0')
		{
			L_strFunctionState = RET_NOK;
		}else{}
    }
    return L_strFunctionState; //return the function state
}



/***********
 * this function is check if the entered month is greater than the 12 or not
 * it take an array of char which the Expiration data is stored in to check is valid month or not
 * it return OK if there are no problems and return NOK if there are any problems
 * *********/
static Error_State_t card_Error_State_tCheckTheMonthNo(u8 copy_u8cardData[])
{
    Error_State_t L_strFunctionState = RET_OK;
    /*to check if entered month is more than 12 months or not*/
    if( (copy_u8cardData[2]!='/')||(copy_u8cardData[0] >= '1'))
    {
        if(copy_u8cardData[0]=='1')
        {
            if(copy_u8cardData[1]>'2')
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
             L_strFunctionState = RET_NOK;
        }
    }
    else
    {
        L_strFunctionState = RET_OK;
    }
    return L_strFunctionState;
}




/*****
* this function compare the current date of the windows and the expiration date .
* it don't take any arguments -> take void
* if the current date is greater than the expiration date it will return NOK and this mean that the card is expired.
* if the current date is less than the expiration date it will return OK and this mean the card is avalid.
*****/
extern Error_State_t card_Error_State_tCheckTheExpirationData(void)
{
    Error_State_t L_strFunctionState = RET_NOK;
    u8 L_u8systemMon[3];
    u8 L_u8systemYear[5];
    /**** this function will get the time of the system and it will return it
    * the month of the system will be returned in L_u8systemMon
    * the year of the system will be returned in L_u8systemYear
    ****/
    Time_Error_State_tGetTime(L_u8systemMon,L_u8systemYear);
    /****
    * these steps will compare the data which the user entered and the system read
    * in case the user data valid the function will return RET_OK else the function will return RET_NOK
    ****/
    if(strcmp(Card_u8BackYear,L_u8systemYear) > 0)
    {
        L_strFunctionState = RET_OK;
    }
    else if(strcmp(Card_u8BackYear,L_u8systemYear) == 0)
    {
        if(strcmp(Card_u8BackMonth,L_u8systemMon)>= 0)
        {
            L_strFunctionState = RET_OK;
        }
        else
        {
            L_strFunctionState = RET_NOK;
        }
    }
    else
    {
        L_strFunctionState = RET_NOK;
    }

    return L_strFunctionState;
}



EN_cardError_t getCardHolderName(Card_Info_t *copy_Card_Info_tcardData)
{
	EN_cardError_t L_strFunctionState = OK;
	u32 L_u32NameCounter = 0;
	for(u32 i = 0; copy_Card_Info_tcardData->holderName[i]!='\0';i++)
	{
		L_u32NameCounter++;
	}
	if(L_u32NameCounter<15||L_u32NameCounter>25)
	{
		L_strFunctionState = WRONG_NAME;
	}
	else{}
	return L_strFunctionState;
}

EN_cardError_t getCardPAN(Card_Info_t *copy_Card_Info_tcardData,u32 *copy_u32PAN_Counter)
{
	EN_cardError_t L_strFunctionState = OK;
	u32 L_u32NameCounter = 0;
	for(u32 i = 0; copy_Card_Info_tcardData->cardPAN[i]!='\0';i++)
	{
		L_u32NameCounter++;
	}
	*copy_u32PAN_Counter = L_u32NameCounter;
	if(L_u32NameCounter<16||L_u32NameCounter>19)
	{
		L_strFunctionState = WRONG_PAN;
	}
	else{}
	return L_strFunctionState;
}




