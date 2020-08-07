//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdCmdTCPServer"
#pragma link "IdCustomTCPServer"
#pragma link "IdCmdTCPServer"
#pragma link "IdCustomTCPServer"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TfrmMain::addLog(String log) {
	memLog->Lines->Add(getTime() + " " + log);
}

void __fastcall TfrmMain::idClientServerCommandHandlers0Command(
      TIdCommand *ASender)
{
	String p1 = ASender->Params->Strings[0];
	String p2 = ASender->Params->Strings[1];
	String p3 = "1000";
	String ip = ASender->Context->Connection->Socket->Binding->PeerIP;
	addLog("--> CREATE from " + ip);
	if(users.add(ip,p1,p2,p3)) {
		ASender->Context->Connection->Socket->WriteLn("ACKCREATE " + p1 + " " + p2);
		addLog("<-- ACKCREATE to " + ip);
	}else {
		ASender->Context->Connection->Socket->WriteLn("NACKCREATE " + p1 + " " + p2);
		addLog("<-- NACKCREATE to " + ip);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::idClientServerConnect(TIdContext *AContext)
{
	users.addUsersToListBox(lbClients, ! chkActiveUsers->Checked,40);
	addLog("--> New Connection from " + AContext->Connection->Socket->Binding->PeerIP);
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::idClientServerDisconnect(TIdContext *AContext)
{
	if(idClientServer->Active) {
		String ip = AContext->Connection->Socket->Binding->PeerIP;
		if(users.exist(ip)) {
			users.setActive(ip,"false");
			addLog("--- Disconnected " + ip);
			users.addUsersToListBox(lbClients, ! chkActiveUsers->Checked,40);
		}
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	users.LoadFromFile("users.txt");
	idStockServer->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
  users.SaveToFile("users.txt");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers1Command(
			TIdCommand *ASender)
{
	String ip = ASender->Context->Connection->Socket->Binding->PeerIP;
  String user = ASender->Params->Strings[0];
  String pw   = ASender->Params->Strings[1];
	String t = TimeToStr(GetTime());
	addLog(" --> DELETE from " + ip);
	if(users.del(ip,ASender->Params->Strings[0],ASender->Params->Strings[1])) {
		addLog(" --> SUCCESS DELETE from " + ip);
		ASender->Context->Connection->IOHandler->WriteLn("ACKDELETE " + user + " " + pw);
	}else {
	  ASender->Context->Connection->IOHandler->WriteLn("NACKDELETE " + user + " " + pw);
		addLog(" --> FAIL DELETE from " + ip);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers3Command(
			TIdCommand *ASender)
{
  /// DO dynamic error messages call by reference!!!
	String msg;
	if(users.auth(ASender->Context->Connection->Socket->Binding->PeerIP,ASender->Params->Strings[0],ASender->Params->Strings[1])) {
		ASender->Context->Connection->IOHandler->WriteLn("ACKLOGIN " + ASender->Params->Strings[0]);
		addLog("<-- ACKLOGIN to " + ASender->Context->Connection->Socket->Binding->PeerIP);
		users.addUsersToListBox(lbClients, ! chkActiveUsers->Checked,40);
	}else {
		ASender->Context->Connection->IOHandler->WriteLn("NACKLOGIN " + ASender->Params->Strings[0] + " " + ASender->Params->Strings[1]);
		addLog("<-- NACKLOGIN to " + ASender->Context->Connection->Socket->Binding->PeerIP);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers2Command(
      TIdCommand *ASender)
{
	String ip = ASender->Context->Connection->Socket->Binding->PeerIP;
	//addLog("--> GETAMOUNT from " +ip);
	String amount = users.getAmount(ASender->Context->Connection->Socket->Binding->PeerIP);
	if(amount != "") {
		ASender->Context->Connection->IOHandler->WriteLn("AMOUNT " + amount);
	 //	addLog("<-- AMOUNT " + amount + " to " +ip);
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::tmAmountsTimer(TObject *Sender)
{
	users.updateAmounts(upSalary->Position);
	users.addUsersToListBox(lbClients, ! chkActiveUsers->Checked,40);
  users.SaveToFile("users.txt");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnListenClick(TObject *Sender)
{
	if(btnListen->Caption == "Start Listening") {
		btnListen->Caption = "Stop Listening";
		idClientServer->DefaultPort = 12345;
		addLog("--- Start Listen Port 12345");
		idClientServer->Active = true;
		tmAmounts->Enabled = idClientServer->Active;
	}else {
		addLog("--- Stopped Listen Port " + idClientServer->DefaultPort);
		btnListen->Caption = "Start Listening";
		int i;
		idClientServer->Active = false;
		users.setAllInactive();
		tmAmounts->Enabled = false;
	}
}
//---------------------------------------------------------------------------

String TfrmMain::getTime() {
	return TimeToStr(GetTime());
}

void __fastcall TfrmMain::idClientServerCommandHandlers5Command(
      TIdCommand *ASender)
{
	String ip = ASender->Context->Connection->Socket->Binding->PeerIP;
	addLog("--> GETALLAMOUNTS from " + ip);
	ASender->Context->Connection->IOHandler->WriteLn("ALLAMOUNTS " + users.getAllAmounts());
	addLog("<-- ALLAMOUNTS to " + ip);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::chkActiveUsersClick(TObject *Sender)
{
	users.addUsersToListBox(lbClients, ! chkActiveUsers->Checked,40);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::idStockServerCommandHandlers0Command(
      TIdCommand *ASender)
{
// Command: GET

	float amount = StrToFloat(ASender->Params->Strings[0]);
	String ip = ASender->Params->Strings[ASender->Params->Count-2];
	String Transaction = ASender->Params->Strings[ASender->Params->Count-1];
	String tmp = Transaction + " " + ip;
	if(users.removeAmount(ip,amount)) {
		ASender->Context->Connection->IOHandler->WriteLn("ACKGET " + tmp);
		addLog("<-- ACKGET " + tmp);
	}else {
		ASender->Context->Connection->IOHandler->WriteLn("NACKGET " + tmp);
		addLog("<-- NACKGET " + tmp);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockServerCommandHandlers1Command(
      TIdCommand *ASender)
{
// Command: SET
	float amount = StrToFloat(ASender->Params->Strings[0]);
	String ip = ASender->Params->Strings[ASender->Params->Count-2];
	String Transaction = ASender->Params->Strings[ASender->Params->Count-1];
	String tmp = Transaction + " " + ip;
	if(users.setAmount(ip,amount)) {
		ASender->Context->Connection->IOHandler->WriteLn("ACKSET " + tmp);
		addLog("<-- ACKSET " + tmp);
	}else {
		ASender->Context->Connection->IOHandler->WriteLn("NACKSET " + tmp);
		addLog("<-- NACKSET " + tmp);
  }
}
//---------------------------------------------------------------------------




void __fastcall TfrmMain::upTimerClick(TObject *Sender, TUDBtnType Button)
{
  edtTimer->Text = IntToStr(upTimer->Position) + " s";
  tmAmounts->Interval = upTimer->Position * 1000;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::upSalaryClick(TObject *Sender, TUDBtnType Button)
{
  edtSalary->Text = IntToStr(upSalary->Position) + " €";
}
//---------------------------------------------------------------------------

