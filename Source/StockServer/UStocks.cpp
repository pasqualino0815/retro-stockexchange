//---------------------------------------------------------------------------


#pragma hdrstop

#include "UStocks.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

bool TStocks::exist(String pStockID) {
	return StockID->IndexOf(pStockID) > -1;
}

TStocks::TStocks() {
	StockID  = new TStringList();
	OldPrice = new TStringList();
	NewPrice = new TStringList();
	Quantity = new TStringList();
}
TStocks::~TStocks() {
	StockID  -> Free();
	OldPrice -> Free();
	NewPrice -> Free();
	Quantity -> Free();
}

String TStocks::getNewPrice(String pStockID) {
  if(exist(pStockID)) {
		int pos = StockID->IndexOf(pStockID);
		return NewPrice->Strings[pos];
	}else
		return "0";
}

bool TStocks::SaveToFile() {
	// Open File Stocks.txt
	String path = "stocks.txt";
	ofstream myfile(path.c_str());
	int i;
	String s;
	if (myfile.is_open()) {
		for(i=0;i<StockID->Count;i++) {
			s = StockID->Strings[i] + ";" + OldPrice->Strings[i] + ";" + NewPrice->Strings[i] + ";" + Quantity->Strings[i] + "\n";
			myfile << s.c_str();
		}
		myfile.close();
	}else return false;
	return true;
}

bool TStocks::addStock(String pStockID, String pOldPrice, String pNewPrice, String pQuantity) {
  if(!exist(pStockID)) {
		StockID->Add(pStockID);
		OldPrice->Add(FormatFloat("0.00",StrToFloat(pOldPrice)));
		NewPrice->Add(FormatFloat("0.00",StrToFloat(pNewPrice)));
		Quantity->Add(pQuantity);
		return true;
	}else
		return false;
}

void TStocks::Clear() {
	StockID->Clear();
	OldPrice->Clear();
	NewPrice->Clear();
	Quantity->Clear();
}

bool TStocks::LoadFromFile() {
  Clear();
	// Open File Stocks.txt/<Client IP>
	String path = "stocks.txt";
	ifstream myfile(path.c_str());
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
				this->addStock(lst->Strings[0],lst->Strings[1],lst->Strings[2],lst->Strings[3]);
		}
		myfile.close();
		free(ln);
		lst->Free();
	}else return false;
	return true;
}

bool TStocks::deleteStock(String pStockID) {
	if(exist(pStockID)) {
		int pos = StockID->IndexOf(pStockID);
		StockID->Delete(pos);
		OldPrice->Delete(pos);
		NewPrice->Delete(pos);
		Quantity->Delete(pos);
		return true;
	}else
		return false;
}

bool TStocks::incQuantity(String pStockID, int pQuantity) {
	if(exist(pStockID)) {
		int pos = StockID->IndexOf(pStockID);
		int qua = StrToInt(Quantity->Strings[pos]);
    float q = StrToFloat(Quantity->Strings[pos]);
    float oldprice = StrToFloat(OldPrice->Strings[pos]);
    if(pQuantity > 0) {
      float price = StrToFloat(NewPrice->Strings[pos]);
      price = price - oldprice * ((float)pQuantity / 1000);
      NewPrice->Strings[pos] = FormatFloat("0.00",price);
      Quantity->Strings[pos] = IntToStr(qua + pQuantity);
      return true;
    }else
      return false;
	}else
		return false;
}
bool TStocks::decQuantity(String pStockID, int pQuantity) {
  if(exist(pStockID)) {
		int pos = StockID->IndexOf(pStockID);
		int qua = StrToInt(Quantity->Strings[pos]);
    float q = StrToFloat(Quantity->Strings[pos]);
    float oldprice = StrToFloat(OldPrice->Strings[pos]);
		if(qua > 0 && pQuantity > 0 && qua >= pQuantity) {
			float price = StrToFloat(NewPrice->Strings[pos]);
			price = price + oldprice * ((float)pQuantity / 1000);
			NewPrice->Strings[pos] = FormatFloat("0.00",price);
			Quantity->Strings[pos] = IntToStr(qua - pQuantity);
			return true;
		}else
			return false;
	}else
		return false;
}

void TStocks::addStocksToStringGrid(TStringGrid *grid) {
	grid->Cells[0][0] = "Stock ID";
	grid->Cells[1][0] = "Actual";
	grid->Cells[2][0] = "Initial";
	grid->Cells[3][0] = "Quantity";
	grid->RowCount = StockID->Count + 1;
	int i;
	for(i=1;i<StockID->Count+1;i++) {
		grid->Cells[0][i] = StockID ->Strings[i-1];
		grid->Cells[1][i] = NewPrice->Strings[i-1];
		grid->Cells[2][i] = OldPrice->Strings[i-1];
		grid->Cells[3][i] = Quantity->Strings[i-1];
  }
}

String TStocks::getLIST() {
	String tmp="LIST";
	int i;
	for(i=0;i<StockID->Count;i++)
		tmp = tmp + " " + StockID->Strings[i] + " " + OldPrice->Strings[i] + " " + NewPrice->Strings[i] + " " + Quantity->Strings[i];
	return tmp;
}

vector<String> TStocks::getStocks() {
	vector<String> tmp;
	int i;
	TStringList *lb = new TStringList();
	lb->Delimiter = ' ';
	lb->DelimitedText = getLIST();
	for(i=1;i < lb->Count;i++) {
		tmp.push_back(lb->Strings[i]);
	}
	return tmp;
}





