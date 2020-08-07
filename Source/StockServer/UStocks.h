//---------------------------------------------------------------------------

#ifndef UStocksH
#define UStocksH

#include <Classes.hpp>
#include <iostream>
#include <fstream>
#include <vcl.h>
#include <vector.h>

using namespace std;

class TStocks{
	public:
    /* Returns a String Containing the current Price of a specific StockID    */
		String getNewPrice(String pStockID);
    /* Returns if a specific StockID exists or not                            */
		bool exist(String pStockID);
    /* Add a Stock to the local String Lists                                  */
    /* Returns false if StockID exists already                                */
    /* Returns true if successfull                                            */
		bool addStock(String pStockID, String pOldPrice, String pNewPrice, String pQuantity);
    /* Delete a Stock by his StockID                                          */
    /* Returns true if successfully false if not existing                     */
		bool deleteStock(String pStockID);
    /* Returns a vector of Strings containing all the Stocks with their info  */
    /* each Stock uses 4 indexes in the vector(4 informations per stock)      */
    vector<String> getStocks();
    /* Incremet the Quantity of a Stock                                       */
    /* Returns true if Stock Exists false if not                              */
		bool incQuantity(String pStockID, int pQuantity);
    /* Decrement the Quantity of a Stock                                      */
    /* Return true if successfully false if stock doesn't exist or the new    */
    /* Quantity will be less than zero                                        */
		bool decQuantity(String pStockID, int pQuantity);
    /* Procedure to add all the Stockinformation into a StringGrid            */
    /* Passed by a Pointer                                                    */
		void addStocksToStringGrid(TStringGrid *grid);
    /* Saves Stocks to a File                                                 */
		bool SaveToFile();
    /* Load Stocks from a File                                                */
		bool LoadFromFile();
    /* Returns a String with all the Information                              */
    /* Example: StockID1 OldPrice1 NewPrice1 Quantity1 StockID2 OldPrice2...  */
		String getLIST();

		TStocks();
		~TStocks();
	private:
    /* String Lists to Store the entire Stock information                     */
		TStringList *StockID, *OldPrice, *NewPrice, *Quantity;
		void Clear();
};



//---------------------------------------------------------------------------
#endif
