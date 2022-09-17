#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData){
   char name[25];
    printf("Please enter your name:\n");
    scanf("%s", name);
    //name = "brgtfewt";
    if(strlen(name) > 24 || strlen(name) < 20 || name == NULL){
        return WRONG_NAME;
    }else{
        strcpy(cardData->cardHolderName, name);
        //printf("%s", cardData->cardHolderName);
        return CARD_OK;
    }
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){
    char expiryDate[20];
    printf("Enter card expiry date:\n");
    scanf("%s", expiryDate);
    if(strlen(expiryDate) != 5
       || expiryDate[2] != '/'
       || !(expiryDate[0] >= '0' && expiryDate[0] <= '1')
       || !(expiryDate[1] >= '0' && expiryDate[1] <= '9')
       || !(expiryDate[3] >= '0' && expiryDate[3] <= '3')
       || !(expiryDate[4] >= '0' && expiryDate[4] <= '9')
       ){
        return WRONG_EXP_DATE;
    }else{
        strcpy(cardData->cardExpirationDate, expiryDate);
        //printf("%s\n", cardData->cardExpirationDate);
        return CARD_OK;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData){
    char accNum[20];
    printf("Enter card's primary account number:\n");
    scanf("%s", accNum);
    if(strlen(accNum) >= 16 && strlen(accNum) <= 19){
        for(int i = 0; i < strlen(accNum); i++){
            if(accNum[i] >= 'A' && accNum[i] <= 'Z' || accNum[i] >= 'a' && accNum[i] <= 'z' || accNum[i] >= '0' && accNum[i] <= '9'){
                continue;
            }else{
                return WRONG_PAN;
            }
        }
        strcpy(cardData->primaryAccountNumber, accNum);
        //printf("%s\n", accNum);
        return CARD_OK;
    }else{
        return WRONG_PAN;
    }
}
