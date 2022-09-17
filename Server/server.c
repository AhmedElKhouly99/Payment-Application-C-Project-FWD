#include "server.h"
ST_accountsDB_t ST_accounts[255] = {{1000,"12345678910111213"}, {1200,"12345678910111214"}, {1000,"12345678910111215"}};
ST_transaction ST_transactions[255] = {0};
uint8_t tarnsactionsCount = -1;
uint8_t curruntTransaction = -1;

EN_transStat_t recieveTransactionData(ST_transaction *transData){
    EN_transStat_t status = 0;
    ///transData->transactionSequenceNumber
    if(isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND){
        transData->transState = DECLINED_STOLEN_CARD;
        status = DECLINED_STOLEN_CARD;
        ///return DECLINED_STOLEN_CARD;
    }else

    if(isAmountAvailable(&transData->terminalData) == LOW_BALANCE){
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        status = DECLINED_INSUFFECIENT_FUND;
        ///return DECLINED_INSUFFECIENT_FUND;
    }
    else {
        transData->transState = APPROVED;
        ST_accounts[curruntTransaction].balance -= transData->terminalData.transAmount;
    }

    

    if(saveTransaction(transData) == SAVING_FAILED){
        status = INTERNAL_SERVER_ERROR;
    }else{
        status = APPROVED;
    }
    return status;
}


EN_serverError_t isValidAccount(ST_cardData_t *cardData){
    for(uint8_t i = 0; i < 255; i++){
        if(strcmp(cardData->primaryAccountNumber, ST_accounts[i].primaryAccountNumber) == 0){
            curruntTransaction = i;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}


EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
    if(termData->transAmount > ST_accounts[curruntTransaction].balance){
        return LOW_BALANCE;
    }
    return SERVER_OK;
}


EN_serverError_t saveTransaction(ST_transaction *transData){
	if (transData->transState == APPROVED) {
		printf("APPROVED\n");
		transData->transactionSequenceNumber = ++tarnsactionsCount;
        ST_transactions[tarnsactionsCount] = *transData;
        return SERVER_OK;
	}
	else if (transData->transState == DECLINED_INSUFFECIENT_FUND) {
        printf("DECLINED_INSUFFECIENT_FUND\n");
		//return DECLINED_INSUFFECIENT_FUND;
	}
	else if (transData->transState == DECLINED_STOLEN_CARD) {
		printf("DECLINED_STOLEN_CARD\n");
	}
	return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction *transData){
    for(uint8_t i = 0; i < 255; i++){
        if(ST_transactions[i].transactionSequenceNumber == transactionSequenceNumber){
            transData = ST_transactions + i;
            return  SERVER_OK;
        }
    }
    return  TRANSACTION_NOT_FOUND;
 }
