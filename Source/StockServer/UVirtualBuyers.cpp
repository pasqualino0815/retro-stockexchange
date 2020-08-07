//---------------------------------------------------------------------------


#pragma hdrstop

#include "UVirtualBuyers.h"

//---------------------------------------------------------------------------
TVirtualBuyers::TVirtualBuyers(int nVirtualBuyers, int ActionPerCycle, TStocks *pStocks, TUsers *pUsers) {
	nBuyers         = nVirtualBuyers;
	nActionPerCycle = ActionPerCycle;
	Stocks = pStocks;
	Users = pUsers;
	srand(time(0));
	int i;
	for(i=0;i<nBuyers;i++) {
		if(!Users->exist(getIP(i)))
			Users->add(getIP(i),"VirtualBuyer" + IntToStr(i),"x");
	}
	Users->SaveToFile("users.txt");
}

TVirtualBuyers::~TVirtualBuyers() {

}

bool TVirtualBuyers::randomAction(int index, String &StockID, int &Quantity, bool &Buy) {
	String ip = getIP(index);
	Buy = rand() % 2 == 0;
	if(Buy) {
		// Get Random Stock
		vector<String> tmp = Stocks->getStocks();
		if(tmp.size() > 0) {
			// Get Random Quantity
			int i = rand() % (tmp.size() / 4);
			// Get Random Quantity
			if(StrToInt(tmp[i * 4 + 3]) > 0)
				Quantity = rand() % StrToInt(tmp[i * 4 + 3]) % 50 + 1;
			else return false;
			// Get StockID
			StockID = tmp[i * 4];
		}else return false;
	}else {
		// Get Own Stock
		vector<String> tmp = Users->getStocks(getIP(index));
		if(tmp.size() > 0) {
			int i = rand() % (tmp.size() / 4);
			// Get Random Quantity
			if(StrToInt(tmp[i * 4 + 3]) > 0)
				Quantity = rand() % StrToInt(tmp[i * 4 + 3]) + 1;
			else return false;
			// Get StockID
			StockID = tmp[i * 4];
		}else return false;
	}
	return true;
}

void TVirtualBuyers::doCycle() {
	String StockID;
	int Quantity , i, j;
	bool Buy;
	for(i=0;i<nBuyers;i++) {
		for(j=0;j<nActionPerCycle;j++) {
			if(randomAction(i, StockID, Quantity, Buy)) {
        if(Quantity > 0) {
          if(Buy) {
            Users->buy(getIP(i),StockID, Quantity);
          }else {
            Users->sell(getIP(i),StockID, Quantity);
          }
        }
      }
		}
	}
}

String TVirtualBuyers::getIP(int index) {
  return "0.0.0." + IntToStr(index);
}

void TVirtualBuyers::sellAll() {
	int i, j;
	for(i=0;i<nBuyers;i++) {
		vector<String> tmp = Users->getStocks(getIP(i));
		for(j=0;j<tmp.size();j = j + 4) {
			Users->sell(getIP(i),tmp[j],StrToInt(tmp[j+3]));
    }
	}
}

int TVirtualBuyers::getNumber() {
  return nBuyers;
}

int TVirtualBuyers::getCycle() {
  return nActionPerCycle;
}

void TVirtualBuyers::setNumber(int Number) {
  nBuyers = Number;
	int i;
	for(i=nBuyers;i<256;i++) {
		if(Users->exist(getIP(i)))
      Users->del(getIP(i),"VirtualBuyer" + IntToStr(i),"x");
	}
	for(i=0;i<nBuyers;i++) {
		if(!Users->exist(getIP(i)))
			Users->add(getIP(i),"VirtualBuyer" + IntToStr(i),"x");
	}  
}

void TVirtualBuyers::setCycle(int Cycle) {
  nActionPerCycle = Cycle;
}

#pragma package(smart_init)
