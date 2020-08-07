//---------------------------------------------------------------------------


#pragma hdrstop

#include "UPortofolio.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TPortofolio::TPortofolio(String pip, TStocks *pStocks) {
	StockID  = new TStringList();
	OldPrice = new TStringList();
	Quantity = new TStringList();
	ip = pip;
	Stocks = pStocks;
}

TPortofolio::~TPortofolio() {
	StockID  -> Free();
	OldPrice -> Free();
	Quantity -> Free();
}

bool TPortofolio::SaveToFile() {
  // Open File portofolios/<Client IP>
	ofstream myfile(("portofolios/" + ip).c_str());
	int i;
	String s;
	if (myfile.is_open()) {
		for(i=0;i<StockID->Count;i++) {
			s = StockID->Strings[i] + ";" + OldPrice->Strings[i] + ";" + Quantity->Strings[i] + "\n";
			myfile << s.c_str();
		}
		myfile.close();
	}else return false;
	return true;
}

bool TPortofolio::LoadFromFile() {
	// Open File portofolios/<Client IP>
	ifstream myfile (("portofolios/" + ip).c_str());
	if (myfile.is_open()) {
		TStringList* lst = new TStringList();
		String line;
		char *ln=(char*)malloc(sizeof(char) * 1000);
		lst->Delimiter = ';';
		while (! myfile.eof() ) {
			myfile.getline(ln,1000);
			line=ln;
			lst->DelimitedText = line;
			if(line!="")
				this->addStock(lst->Strings[0],lst->Strings[1],"",StrToInt(lst->Strings[2]));
		}
		myfile.close();
		free(ln);
		lst->Free();
	}else return false;
	return true;
}

void TPortofolio::addStock(String pStockID, String pOldPrice, String pNewPrice, int pQuantity) {
	if(exist(pStockID)) {
		// If The desired Stock Allready Exists
		// Get Position of the Desired Added Stock
		int pos = StockID->IndexOf(pStockID);
		// Get Quantity from that Stock (for Update)
		int qua = StrToInt(Quantity->Strings[pos]);
		// Add Quantity to the Old Quantity
		Quantity->Strings[pos] = IntToStr(qua + pQuantity);
		// Overwrite Old Stock Price
		OldPrice->Strings[pos] = pNewPrice;
	}else {
		// If not Exist StockID
		// Just Add the desired Stock
		StockID->Add(pStockID);
		OldPrice->Add(pOldPrice);
		Quantity->Add(IntToStr(pQuantity));
	}
}

bool TPortofolio::exist(String pStockID) {
	return StockID->IndexOf(pStockID) > -1;
}

bool TPortofolio::deleteStock(String pStockID, int pQuantity) {
	if(exist(pStockID)) {
		// If The desired Stock Exists
		// Get Position of the Desired Updated Stock
		int pos = StockID->IndexOf(pStockID);
		// Get Quantity from that Stock (for Update)
		int qua = StrToInt(Quantity->Strings[pos]);
		// Calculate new Stock Quantity
		qua = qua - pQuantity;
		if(qua < 0)
			return false;
		else {
			if(qua == 0 || pQuantity == 0) {
				// If New Quantity = 0
				// No need of that stock anymore ==> Delete it
				StockID  -> Delete(pos);
				OldPrice -> Delete(pos);
				Quantity -> Delete(pos);
			}else {
				// If Quantity > 0
				// Just Update the Old Quantity
				Quantity -> Strings[pos] = IntToStr(qua);
			}
			return true;
    }
	}else return false;
}

int TPortofolio::getQuantityStock(String pStockID) {
	if(exist(pStockID)) {
		// Get Position of the Desired Stock Quantity
		int pos = StockID->IndexOf(pStockID);
		// return the quantity
		return StrToInt(Quantity->Strings[pos]);
	}else
		return 0;
}

String TPortofolio::getLISTME(bool listme) {
	// Temp String to Construct the Command Line for the command LISTME or LISTCLIENT
	String tmp;
	if(listme)
		tmp = "LISTME";
	else
		tmp = "LISTCLIENT";
	int i;
	for(i=0;i<StockID->Count;i++) {
		// Generate Command Line
		tmp = tmp + " " + StockID->Strings[i] + " " + OldPrice->Strings[i] + "  " + Stocks->getNewPrice(StockID->Strings[i]) + " " + Quantity->Strings[i];
	}
	return tmp;
}

void TPortofolio::Delete() {
  String path = "portofolios/" + ip;
  remove(path.c_str());
}


