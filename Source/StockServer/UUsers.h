//---------------------------------------------------------------------------

#ifndef UUsersH
#define UUsersH

#include <Classes.hpp>
#include <iostream>
#include <fstream>
#include <vcl.h>
#include <vector.h>
#include "UPortofolio.h"
#include "UPortofolioArray.h"
#include "UStocks.h"
#include "UMyVector.h"

using namespace std;

class TUsers {
  public:
    /* Add User to the internal StringLists                                   */
    /* IP;USER;PASSWORD                                                       */
    bool add(String pip, String puser, String ppassword);

    /* Returns True if IP matches with User and Password else Returns False   */
    bool auth(String pip, String puser, String ppassword);

    /* Determine if a ip Exists already                                       */
    bool exist(String pip);

    /* Delete a User if IP matches with User and Password                     */
    bool del(String pip, String puser, String ppassword);

    /* Delete a User without confirmation                                     */
    bool Delete(String pip);

    /* Buy Stocks                                                             */
    /* Returns true if successfully                                           */
    /* Returns false if StockID doesn't exists or Quantity is not available   */
    bool buy(String pip, String pStockID, int pQuantity);

    /* Sell Stocks                                                            */
    /* Returns true if successfully                                           */
    /* Returns false if StockID doesn't exists or Quantity is not available   */
    bool sell(String pip, String pStockID, int pQuantity);

    /* Sell all Stocks with the name of the param pStockID                    */
    void sellStock(String pStockID);

    /* Returns a vector of Strings with the Stocks of a specific client       */
    /* Example: StockID1 100 500 20 StockID2 100 22 44 ...                    */
    /*          StockID OldPrice NewPrice Quantity StockID OldPrice NewPrice..*/
    vector<String> getStocks(String pip);

    /* Procedure to add all the Usersinformation into a StringGrid            */
    /* Passed by a Pointer                                                    */
		void addUsersToStringGrid(TStringGrid *grid);

    /* Returns the Same as the previous function just in form of a String     */
    /* to send it to the client with the prefix LISTME                        */
    String getLISTME(String pip);

    /* Returns a String containing all Users in the form:                     */
    /* IP USERNAME IP2 USERNAME2 IP3 USERNAME3...                             */
    String getLISTCLIENTS();

    /* Returns the same String as getLISTME(String pip) just with the prefix  */
    /* LISTCLIENT                                                             */
    String getLISTCLIENT(String pip);

    /* Saves the Clients of the StockExchange to a File(path) and also saves  */
    /* their portofolios                                                      */
    void SaveToFile(String path);

    /* Load the Clients from a File(path) and loads their portofolio          */
    void LoadFromFile(String path);

    /* Initialise the Class                                                   */
    /* Creation of the StringLists & Assign the pointer of TStocks to local   */
    TUsers(TStocks *pStocks);

    ~TUsers();
  private:
    /* StringLists to Store Client Information                                */
    TStringList *ip;
    TStringList *user;
    TStringList *password;

    /* Portofolio Array (Own Class to simplify)                               */
    /* Each Portofolio is associated the internal same index as the client    */
    /* Information                                                            */
    /* Index: 0 ---- IP1 - NAME1 - PW1 - PORTO1                               */
    /* Index: 1 ---- IP2 - NAME2 - PW2 - PORTO2                               */          
    TPArray Portofolios;
    
    /* Because Buy and Sell uses the New Price of a Stock                     */
    /* so a pointer to the stocks object needs to be stored for retreiving inf*/
    TStocks *Stocks;
};
//---------------------------------------------------------------------------
#endif
