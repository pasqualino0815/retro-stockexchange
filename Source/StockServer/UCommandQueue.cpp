//---------------------------------------------------------------------------


#pragma hdrstop

#include "UCommandQueue.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

/*
	Status = 0   Not yet tryed and performed
	Status = 1   Processing
	Status = 2   Not enough Money
	Status = 3   Connection Error
	Status = 4   Succesfull Moved Money
	Status = 5   Accomplished
*/

TCommandQueue::TCommandQueue(TStocks *pStocks, TIdCmdTCPClient *pTemplate) {
	Stocks = pStocks;
	Connection = pTemplate;
	count = 0;
}

TCommandQueue::~TCommandQueue() {
	int i;
	for(i=0;i<Transaction.size();i++) {
		Connections[i]->Disconnect(true);
		Connections[i]->Free();
  }
}

void TCommandQueue::nextCyle() {
	int i;
	for(i=0;i<Transaction.size();i++) {
		if(Status[i] == 0 || Status[i] == 1) {
			Time[i]++;
    }
  }
}

void TCommandQueue::add(String pStockID, String pClientIP, int pAction, int pQuantity, String pBankIP, int pStatus, int pTime) {
	Transaction.push_back(count);
	StockID    .push_back(pStockID);
	ClientIP   .push_back(pClientIP);
	Action     .push_back(pAction);
	Quantity   .push_back(pQuantity);
	Status     .push_back(pStatus);
	Time       .push_back(pTime);
	Connections.push_back(new TIdCmdTCPClient(*Connection));
	Connections.back()->Host = pBankIP;
	Connections.back()->Port = 12222;
  Connections.back()->Connect();
	count++;
	count = count % 2147483647;
}

void TCommandQueue::del(int pTransaction) {
	int p = searchTransaction(pTransaction);
  if(p > -1) {
		Transaction.erase(Transaction.begin()+p,Transaction.begin()+p+1);
		StockID.erase(StockID.begin()+p,StockID.begin()+p+1);
		ClientIP.erase(ClientIP.begin()+p,ClientIP.begin()+p+1);
		Action.erase(Action.begin()+p,Action.begin()+p+1);
		Quantity.erase(Quantity.begin()+p,Quantity.begin()+p+1);
		Status.erase(Status.begin()+p,Status.begin()+p+1);
		Time.erase(Time.begin()+p,Time.begin()+p+1);
		Connections[p]->Disconnect(true);
		Connections.erase(Connections.begin()+p,Connections.begin()+p+1);
	}
}

void TCommandQueue::delOldCmds(int pMaxTime) {
	int i;
	for(i=0;i<Transaction.size();i++) {
		if(Time[i] >= pMaxTime || Status[i] == 5) {
			del(Transaction[i]);
			i--;
		}
  }
}

void TCommandQueue::doCmds() {
	int i;
	String tmp="";
	float amount=0;
	for(i=0;i<Transaction.size();i++) {
		if(Status[i] == 0) {
			if(Connections[i]->Connected()) {
				amount = StrToFloat(Stocks->getNewPrice(StockID[i]));
				amount = amount * Quantity[i];
				tmp = tmp + FormatFloat("0.00",amount) + " ";
				tmp = tmp + ClientIP[i] + " ";
				tmp = tmp + Transaction[i];
				if(Action[i] == 0) {
					Connections[i]->IOHandler->WriteLn("GET " + tmp + " ");
				}else {
					Connections[i]->IOHandler->WriteLn("SET " + tmp + " ");
				}
				Status[i] = 1;
      }else {
				Status[i] = 3;
      }
    }
  }
}

int TCommandQueue::searchTransaction(int pTransaction) {
	int p = -1;
	for(p=0;p<Transaction.size();p++) {
		if(Transaction[p] == pTransaction)
			break;
	}
	return p;
}

void TCommandQueue::changeStatus(int pTransaction, int pStatus) {
	int p = searchTransaction(pTransaction);
	if(p > -1) {
    Status[p] = pStatus;
  }
}

bool TCommandQueue::getTransaction(int &pAction, String &pStockID, int &pQuantity, String &pClientIP, int &pStatus) {
	int i;
	for(i=0;i<Transaction.size();i++) {
		if(Status[i] == 4 || Status[i] == 2 || Status[i] == 3) {
			pAction = Action[i];
			pStockID = StockID[i];
			pQuantity = Quantity[i];
			pClientIP = ClientIP[i];
      pStatus = Status[i];
  		Status[i] = 5;
			return true;
    }
	}
	return false;
}


