//---------------------------------------------------------------------------


#pragma hdrstop

#include "UUsers.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TUsers::TUsers(TStocks *pStocks) {
	ip       = new TStringList();
	user     = new TStringList();
	password = new TStringList();
	Stocks = pStocks;
}

TUsers::~TUsers() {
	ip       -> Free();
	user     -> Free();
	password -> Free();
}

void TUsers::SaveToFile(String path) {
	ofstream myfile(path.c_str());
	int i;
	String s;
	if (myfile.is_open()) {
		for(i=0;i<ip->Count;i++) {
			s = ip->Strings[i] + ";" + user->Strings[i] + ";" + password->Strings[i] + "\n";
			myfile << s.c_str();
		}
		myfile.close();
		for(i=0;i<Portofolios.Count();i++) {
			Portofolios[i]->SaveToFile();
		}
	}
	else ShowMessage("Unable to open file");
}

void TUsers::LoadFromFile(String path) {
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
				this->add(lst->Strings[0],lst->Strings[1],lst->Strings[2]);
		}
		myfile.close();
		free(ln);
		lst->Free();
	}
	else ShowMessage("Unable to open file " + path);
}

bool TUsers::add(String pip, String puser, String ppassword) {
	if(this->exist(pip))
		return false;
	ip->Add(pip);
	user->Add(puser);
	password->Add(ppassword);
	TPortofolio *porto = new TPortofolio(pip,Stocks);
	porto->LoadFromFile();
	Portofolios.Add(porto);
	Portofolios[Portofolios.Count()-1]->SaveToFile();
	return true;
}

bool TUsers::exist(String pip) {
	return ip->IndexOf(pip) > -1 || user->IndexOf(pip) > -1;
}

bool TUsers::auth(String pip, String puser, String ppassword) {
	int p = ip->IndexOf(pip);
	if(p == -1)
		return false;
	if(password->Strings[p] == ppassword && user->Strings[p] == puser)
		return true;
	else
		return false;
}

bool TUsers::del(String pip, String puser, String ppassword) {
	int p = ip->IndexOf(pip);
	if(p == -1)
		return false;
	if(user->Strings[p] == puser &&  password->Strings[p] == ppassword) {
		ip->Delete(p);
		user->Delete(p);
		password->Delete(p);
    Portofolios[p]->Delete();
    Portofolios.Delete(p);
		return true;
	}else
		return false;
}


bool TUsers::Delete(String pip) {
	int p = ip->IndexOf(pip);
	if(p == -1)
		return false;
  int i;
  vector<String> tmp = this->getStocks(ip->Strings[p]);
  for(i=0;i<tmp.size();i=i+4) {
    this->sell(ip->Strings[p],tmp[i],StrToInt(tmp[i+3]));
  }
  ip->Delete(p);
  user->Delete(p);
  password->Delete(p);
  Portofolios[p]->Delete();
  Portofolios.Delete(p);
}

bool TUsers::buy(String pip, String pStockID, int pQuantity) {
	if(exist(pip)) {
		int pos = ip->IndexOf(pip);
		String newPrice = Stocks->getNewPrice(pStockID);
    if(Stocks->decQuantity(pStockID,pQuantity)) {
      Portofolios[pos]->addStock(pStockID,newPrice,newPrice,pQuantity);
      return true;
    }
    else
      return false;
	}else {
		return false;
	}
}

bool TUsers::sell(String pip, String pStockID, int pQuantity) {
	if(exist(pip)) {
		int pos = ip->IndexOf(pip);
		String newPrice = Stocks->getNewPrice(pStockID);
		Portofolios[pos]->deleteStock(pStockID,pQuantity);
		Stocks->incQuantity(pStockID,pQuantity);
		return true;
	}else {
		return false;
	}
}


String TUsers::getLISTME(String pip) {
	int p = ip->IndexOf(pip);
	if(p > -1) {
		return Portofolios[p]->getLISTME(true);
	}
	return "";
}

String TUsers::getLISTCLIENTS() {
	String tmp = "LISTCLIENTS ";
	int i;
	for(i=0;i<ip->Count;i++) {
		tmp = tmp + ip->Strings[i] + " " + user->Strings[i] + " ";
	}
	return tmp;
}

String TUsers::getLISTCLIENT(String pip) {
	int p = ip->IndexOf(pip);
	if(p > -1) {
		return Portofolios[p]->getLISTME(false);
	}
	return "";
}

vector<String> TUsers::getStocks(String pip) {
	int p = ip->IndexOf(pip);
	vector<String> tmp;
	if(p > -1) {
		int i;
		TStringList *lb = new TStringList();
		lb->Delimiter = ' ';
		lb->DelimitedText = Portofolios[p]->getLISTME(false);
		for(i=1;i < lb->Count;i++) {
			tmp.push_back(lb->Strings[i]);
		}
	}
	return tmp;
}

void TUsers::sellStock(String pStockID) {
  int i;
  for(i=0;i<ip->Count;i++) {
    this->sell(ip->Strings[i],pStockID,0);
  }
}

void TUsers::addUsersToStringGrid(TStringGrid *grid) {
	grid->Cells[0][0] = "IP";
	grid->Cells[1][0] = "Name";
  if(ip->Count + 1 < 2) {
	  grid->RowCount = 2;
   	grid->Cells[0][1] = "";
    grid->Cells[1][1] = "";
  }else
    grid->RowCount = ip->Count + 1;

	int i;
	for(i=1;i<ip->Count+1;i++) {
		grid->Cells[0][i] = ip   ->Strings[i-1];
		grid->Cells[1][i] = user ->Strings[i-1];
  }
}




