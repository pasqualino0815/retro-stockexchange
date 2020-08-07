//---------------------------------------------------------------------------

#ifndef UCommandQueueH
#define UCommandQueueH
//---------------------------------------------------------------------------
#include <vector>
#include <Classes.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "UStocks.h"
#include "IdCmdTCPClient.hpp"

using namespace std;

/*
Status = 0   Not yet tryed and performed
Status = 1   Processing
Status = 2   Not enough Money
Status = 3   Connection Error
Status = 4   Succesfull Moved Money
Status = 5   Accomplished
*/

class TCommandQueue {
  public:
    /* function to do all non Processed Querys to the bank                    */
    void doCmds();
    /* Add a Transaction to the command queue                                 */
    void add(String pStockID, String pClientIP, int pAction, int pQuantity,
      String pBankIP, int pStatus, int pTime);
    /* Increments the timer for Querys with Processing Status                 */
    void nextCyle();
    /* get the Index of a Transaction by his Transaction number               */
    int searchTransaction(int pTransaction);
    /* Change the Status of a Transaction                                     */
    void changeStatus(int pTransaction, int pStatus);
    /* Get a Transaction                                                      */
    /* Returns so long true until no Transaction is available with status > 1 */
    /* Params passed by reference so that the stock server can retreive them  */
    bool getTransaction(int &pAction, String &pStockID, int &pQuantity, String
      &pClientIP, int &pStatus);
    /* deletes a particular transaction                                       */
    void del(int pTransaction);
    /* Delete all Tranaction where the time > ptime and status == 1           */
    void delOldCmds(int pTime);
    /* Constructor                                                            */
    /* pStocks = Pointer to the stock class of the server                     */
    /* pTemplate = Pointer to the Template connection to use for connections  */
    /*             to the Bank                                                */
    TCommandQueue(TStocks *pStocks, TIdCmdTCPClient *pTemplate);
    ~TCommandQueue();
  private:
    TStocks *Stocks;
    TIdCmdTCPClient *Connection;
    int count;
    vector < TIdCmdTCPClient * > Connections;
    vector < String > StockID;
    vector < String > ClientIP;
    vector < int > Transaction;
    vector < int > Time;
    vector < int > Quantity;
    vector < int > Action;
    vector < int > Status;
};


#endif
