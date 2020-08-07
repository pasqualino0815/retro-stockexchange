//---------------------------------------------------------------------------

#ifndef UPortofolioH
#define UPortofolioH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <iostream>
#include <fstream>
#include "UStocks.h"

using namespace std;

class TPortofolio {
  public:
    /* Deletes and Destroys the entire Portofolio & Removes the file          */
    void Delete();
    /* Determine if a StockID already exists in Portofolio                    */
    /* Return True if exists else False                                       */
    bool exist(String pStockID);
    /* Delete a certain amount of Quantity from a StockID in the Portofolio   */
    /* Deletes the stock if new Quantity = 0                                  */
    /* Or Decrements only the Quantity                                        */
    /* Returns true if successfull                                            */
    /* Otherwise false if pQuantity > Quantity                                */
    bool deleteStock(String pStockID, int pQuantity);
    /* Add a Stock to the Portofolio                                          */
    void addStock(String pStockID, String pOldPrice, String pNewPrice, int
      pQuantity);
    /* Returns the actual number of actions for a specific Stock              */
    int getQuantityStock(String pStockID);
    /* Returns a String containing all the Stocks with their information      */
    /* Example: STID1 OLDPRICE1 NEWPRICE1 QUANTITY1 STDID2 OLDPRICE2 NEW...   */
    /* if param listme == true prefix will be LISTME else prefix will be      */
    /* LISTCLIENT                                                             */
    String getLISTME(bool listme);
    /* Saves the portofolio to file (Filename = IP)                           */
    bool SaveToFile();
    /* Load portofolio from File                                              */
    bool LoadFromFile();
    /* Constructor                                                            */
    /* pip = IP of the portofolio                                             */
    /* pStocks = Pointer to the Stocksclass for retreiving NewPrice when      */
    /* getLISTME()                                                            */
    TPortofolio(String pip, TStocks *pStocks);
    ~TPortofolio();
  private:
    /* Stores the IP of the Portofolio (Determine which portofolio belongs to */
    String ip;
    /* Pointer to the Stocksfile                                              */
    TStocks *Stocks;
    /* Stores the information about the stocks                                */
    TStringList *StockID,  *OldPrice,  *Quantity;
};

#endif
