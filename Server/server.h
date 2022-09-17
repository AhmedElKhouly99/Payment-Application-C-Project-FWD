#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include <stdio.h>
#include "terminal.h"
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef enum EN_transState_t
{
APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

typedef enum EN_serverError_t
{
SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE
}EN_serverError_t ;

typedef struct ST_accountsDB_t
{
float balance;
uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

typedef struct ST_transaction_t
{
ST_cardData_t cardHolderData;
ST_terminalData_t terminalData;
EN_transStat_t transState;
uint32_t transactionSequenceNumber;
}ST_transaction;

extern  ST_accountsDB_t ST_accounts[255];
extern ST_transaction ST_transactions[255];
extern uint8_t tarnsactionsCount;
extern uint8_t curruntTransaction;

extern EN_transStat_t recieveTransactionData(ST_transaction *transData);
extern EN_serverError_t isValidAccount(ST_cardData_t *cardData);
extern EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
extern EN_serverError_t saveTransaction(ST_transaction *transData);
extern EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction *transData);

#endif // SERVER_H_INCLUDED
