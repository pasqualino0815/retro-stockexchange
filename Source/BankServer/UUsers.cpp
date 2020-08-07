//---------------------------------------------------------------------------


#pragma hdrstop

#include "UUsers.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TUsers::TUsers() {
	ip = new TStringList();
	user = new TStringList();
	password = new TStringList();
	amount = new TStringList();
	active = new TStringList();
}

TUsers::~TUsers() {
	ip->Free();
	user->Free();
	password->Free();
	amount->Free();
	active->Free();
}

void TUsers::SaveToFile(String path) {
	ofstream myfile(path.c_str());
	int i;
	String s;
	if (myfile.is_open()) {
		for(i=0;i<ip->Count;i++) {
			s = ip->Strings[i] + ";" + user->Strings[i] + ";" + password->Strings[i] + ";" + amount->Strings[i] + "\n";
			myfile << s.c_str();
			active->Add("false");
		}
		myfile.close();
	}
	else ShowMessage("Unable to open file");
}

void TUsers::LoadFromFile(String path) {
	TStringList* lst = new TStringList();
	String line;
	char *ln=(char*)malloc(sizeof(char) * 1000);
	lst->Delimiter = ';';
	ifstream myfile (path.c_str());
	if (myfile.is_open()) {
		while (! myfile.eof() ) {
			myfile.getline(ln,1000);
			line=ln;
			lst->DelimitedText = line;
			if(line!="")
				this->add(lst->Strings[0],lst->Strings[1],lst->Strings[2],lst->Strings[3]);
    }
		myfile.close();
	}
	else ShowMessage("Unable to open file");
	free(ln);
	lst->Free();
}

bool TUsers::add(String pip, String puser, String ppassword, String pamount) {
	if(this->exist(pip))
		return false;
	ip->Add(pip);
	user->Add(puser);
	password->Add(ppassword);
	amount->Add(pamount);
	active->Add("false");
	return true;
}

bool TUsers::exist(String pip) {
	return ip->IndexOf(pip) > -1 || user->IndexOf(pip) > -1;
}

String TUsers::getAmount(String pip) {
	if(this->exist(pip))
		return amount->Strings[ip->IndexOf(pip)];
	else
		return "";
}

void TUsers::setActive(String pip, String pactive) {
	active->Strings[ip->IndexOf(pip)] = pactive;
}

void TUsers::addUsersToListBox(TListBox* lb, bool pactive, int len) {
	int i;
	lb->Clear();
	for(i=0;i<ip->Count;i++)
		if(! pactive)
			lb->Items->Add(formatString(ip->Strings[i],user->Strings[i],amount->Strings[i],len));
		else
			if(active->Strings[i] == "true")
				lb->Items->Add(formatString(ip->Strings[i],user->Strings[i],amount->Strings[i],len));
}

void TUsers::updateAmounts(float pamount) {
	int i;
	float a;
	for(i=0;i < ip->Count;i++) {
		if(active->Strings[i] == "true") {
			a = StrToFloat(amount->Strings[i]);
			a = a + pamount;
			amount->Strings[i] = FormatFloat("0.00",a);
		}
	}
}

bool TUsers::auth(String pip, String puser, String ppassword) {
	int p = ip->IndexOf(pip);
	if(p == -1)
		return false;
	if(password->Strings[p] == ppassword && user->Strings[p] == puser) {
		active->Strings[p] = "true";
		return true;
	}else
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
		amount->Delete(p);
		active->Delete(p);
		return true;
	}else
		return false;
}

bool TUsers::removeAmount(String pip, float pamount) {
	int p = ip->IndexOf(pip);
	if(p == -1)
		return false;
	float tmpAmount = StrToFloat(amount->Strings[p]) - pamount;
	if(tmpAmount < 0)
		return false;
	amount->Strings[p] = FormatFloat("0.00",tmpAmount);
	return true;
}

bool TUsers::setAmount(String pip, float pamount) {
	int p = ip->IndexOf(pip);
	if(p == -1)
		return false;
	amount->Strings[p] = FormatFloat("0.00",StrToFloat(amount->Strings[p]) + pamount);
	return true;
}

bool TUsers::moveAmount(String sip, String dip, float pamount) {
	int source = ip->IndexOf(sip);
	int dest = ip->IndexOf(dip);
	if(!this->exist(sip) || !this->exist(dip))
		return false;
	incAmount(dest,pamount);
	if(decAmount(source,pamount))
		return true;
	else {
		decAmount(source,pamount);
		return false;
	}
}

void TUsers::incAmount(int pos, float pamount) {
	int a;
	a = StrToFloat(amount->Strings[pos]);
	a = a + pamount;
	amount->Strings[pos] = FloatToStr(a);
}

bool TUsers::decAmount(int pos, float pAmount) {
	int a;
	a = StrToFloat(amount->Strings[pos]);
	a = a - pAmount;
	if(a < 0)
		return false;
	amount->Strings[pos] = FloatToStr(a);
	return true;
}

String TUsers::getAllAmounts() {
	int i;
	String s = "";
	for(i=0;i<ip->Count;i++) {
		s = s + user->Strings[i] + " " + amount->Strings[i] + " ";
	}
	return s;
}

String TUsers::formatString(String a, String b, String c, int len) {
	String t;
	int i;
	t = a + " " + b;
	int l = t.Length();
	for(i=l + c.Length();i < len;i++)
		t = t + " ";
	return t + c;
}

void TUsers::setAllInactive() {
	int i;
	for(i=0;i<ip->Count;i++) {
		active->Strings[i] = "false";
  }
}
