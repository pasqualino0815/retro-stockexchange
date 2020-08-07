//---------------------------------------------------------------------------

#ifndef UVirtualBuyersH
#define UVirtualBuyersH

#include <vector>
#include "UStocks.h"
#include "UUsers.h"
#include <iostream>

using namespace std;

class TVirtualBuyers {
  public:
    /* Constructor generates nVirtualBuyers Users in the Users class          */
    TVirtualBuyers(int nVirtualBuyers, int ActionPerCycle, TStocks *pStocks,
      TUsers *pUsers);
    ~TVirtualBuyers();
    /* Creates a random Action to perform                                     */
    /* index is the last number of the virtual buyer IP                       */
    /* Example: 0.0.0.1 where 1 is the index                                  */
    bool randomAction(int index, String &StockID, int &Quantity, bool &Buy);
    /* Generate and execute nActionsPerCycle Buy/Sell Actions                 */
    void doCycle();
    /* Sell all bought Stocks                                                 */
    void sellAll();

    int getNumber();
    int getCycle();
    void setNumber(int Number);
    void setCycle(int Cycle);
  private:
    /* Returns the corresponding ip to an index                               */
    /* Example: index = 3  ==> 0.0.0.3                                        */
    String getIP(int index);
    /* How many Virtual Buyers                                                */
    int nBuyers;
    /* How many SELL/BUY actions per cycle                                    */
    int nActionPerCycle;
    /* Pointer to the user class of the server                                */
    TUsers *Users;
    /* Pointer to the stocksfile of the server                                */
    TStocks *Stocks;
};


//---------------------------------------------------------------------------
#endif
