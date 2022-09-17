#include "terminal.h"
#include "time.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    uint8_t TransDate[11];
    /*printf("Please enter Transaction date:\n");
    scanf("%s", TransDate);
    if(strlen(TransDate) != 10 ||
        TransDate[2] != '/' ||
        TransDate[5] != '/' ||

        !(TransDate[0] >= '0' && TransDate[0] <= '3') ||
        !(TransDate[1] >= '0' && TransDate[1] <= '9') ||

        !(TransDate[3] >= '0' && TransDate[3] <= '1') ||
        !(TransDate[4] >= '0' && TransDate[4] <= '9') ||

        !(TransDate[6] >= '2' && TransDate[6] <= '0') ||
        !(TransDate[7] >= '0' && TransDate[7] <= '9') ||
        !(TransDate[8] >= '0' && TransDate[8] <= '9') ||
        !(TransDate[9] >= '0' && TransDate[9] <= '9') ||
       ){
        return WRONG_EXP_DATE;
    }else{
        strcpy(termData->transactionDate, TransDate);
        return EN_terminalError_t.OK1;
    }*/

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(TransDate, "%02d/%02d/%0004d", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
    strcpy(termData->transactionDate, TransDate);
    printf("Transaction date: %s\n", termData->transactionDate);
    return TERM_OK;
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData){
    //printf("card date: %s, exp date: %s\n", termData.transactionDate, cardData.cardExpirationDate);
    if (cardData.cardExpirationDate[3] < termData.transactionDate[8]) {
        return EXPIRED_CARD;
    }
    else if (cardData.cardExpirationDate[3] > termData.transactionDate[8]) {
        return TERM_OK;
    }


    if(cardData.cardExpirationDate[4] < termData.transactionDate[9]){
        return EXPIRED_CARD;
    }
    else if (cardData.cardExpirationDate[4] > termData.transactionDate[8]) {
        return TERM_OK;
    }


    if(cardData.cardExpirationDate[0] < termData.transactionDate[3]){     
        return EXPIRED_CARD;
    }
    if (cardData.cardExpirationDate[0] == termData.transactionDate[3] && cardData.cardExpirationDate[1] < termData.transactionDate[4]) {
        return EXPIRED_CARD;
    }
    return TERM_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
    float amount = 0.0;
    printf("Please enter the transaction amount: ");
    scanf("%f", &amount);
    if(amount <= 0){
        return INVALID_AMOUNT;
    }else{
        termData->transAmount = amount;
    }
    return TERM_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
    if(termData->transAmount > termData->maxTransAmount){
        return EXCEED_MAX_AMOUNT;
    }
    return TERM_OK;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
    float amount = 0.0;
    printf("Please enter the transaction max amount: ");
    scanf("%f", &amount);
    if(amount <= 0){
        return INVALID_MAX_AMOUNT;
    }
    termData->maxTransAmount = amount;
    return TERM_OK;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData){
    return TERM_OK;
}
