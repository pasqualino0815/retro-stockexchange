//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdCmdTCPClient"
#pragma link "IdCmdTCPServer"
#pragma link "IdCustomTCPServer"
#pragma link "IdCmdTCPClient"
#pragma link "IdCmdTCPServer"
#pragma link "IdCustomTCPServer"
#pragma link "IdCmdTCPClient"
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
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	Stocks = new TStocks();
	Users = new TUsers(Stocks);
	Cmds = new TCommandQueue(Stocks,idBankClient);
	Stocks->LoadFromFile();
	Users->LoadFromFile("users.txt");
	vBuyers = new TVirtualBuyers(0,0,Stocks, Users);
	Stocks->addStocksToStringGrid(sgStocks);
  Users->addUsersToStringGrid(sgUsers);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	//vBuyers->sellAll();
	Users->SaveToFile("users.txt");
	Stocks->SaveToFile();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnListenClick(TObject *Sender)
{
	if(btnListen->Caption == "Start Listening") {
		tmRound->Enabled = true;
		btnListen->Caption = "Stop Listening";
		idClientServer->DefaultPort = 12000;
		idClientServer->Active = true;
	}else {
		btnListen->Caption = "Start Listening";
		idClientServer->Active = false;
		tmRound->Enabled = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::idClientServerCommandHandlers3Command(
      TIdCommand *ASender)
{
// Command: LIST
	ASender->Context->Connection->IOHandler->WriteLn(Stocks->getLIST());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers4Command(
      TIdCommand *ASender)
{
// Command: LISTME
	String ip = ASender->Context->Connection->Socket->Binding->PeerIP;
	ASender->Context->Connection->IOHandler->WriteLn(Users->getLISTME(ip));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers5Command(
      TIdCommand *ASender)
{
// Command: LISTCLIENTS
	ASender->Context->Connection->IOHandler->WriteLn(Users->getLISTCLIENTS());
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers6Command(
      TIdCommand *ASender)
{
// Command: LISTCLIENT
	String ip = ASender->Params->Strings[0];
	ASender->Context->Connection->IOHandler->WriteLn(Users->getLISTCLIENT(ip));
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::idBankClientCommandHandlers0Command(
      TIdCommand *ASender)
{
// Command: ACKGET
	int Transaction = StrToInt(ASender->Params->Strings[0]);
	int Status = 4;
	Cmds->changeStatus(Transaction,Status);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idBankClientCommandHandlers1Command(
      TIdCommand *ASender)
{
// Command: ACKSET
	int Transaction = StrToInt(ASender->Params->Strings[0]);
	int Status = 4;
	Cmds->changeStatus(Transaction,Status);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idBankClientCommandHandlers2Command(
      TIdCommand *ASender)
{
// Command: NACKGET
	int Transaction = StrToInt(ASender->Params->Strings[0]);
	int Status = 2;
	Cmds->changeStatus(Transaction,Status);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idBankClientCommandHandlers3Command(
      TIdCommand *ASender)
{
// Command: NACKSET
	int Transaction = StrToInt(ASender->Params->Strings[0]);
	int Status = 2;
	Cmds->changeStatus(Transaction,Status);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers7Command(
      TIdCommand *ASender)
{
// Command: BUY
	//frmMain->Caption = ASender->RawLine;
	String ClientIP = ASender->Context->Connection->Socket->Binding->PeerIP;
	String StockID = ASender->Params->Strings[0];
	int Quantity = StrToInt(ASender->Params->Strings[1]);
	String BankIP = ASender->Params->Strings[2];
	Cmds->add(StockID,ClientIP,0,Quantity,BankIP,0,0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers8Command(
      TIdCommand *ASender)
{
// Command: SELL
	String ClientIP = ASender->Context->Connection->Socket->Binding->PeerIP;
	String StockID = ASender->Params->Strings[0];
	int Quantity = StrToInt(ASender->Params->Strings[1]);
	String BankIP = ASender->Params->Strings[2];
	Cmds->add(StockID,ClientIP,1,Quantity,BankIP,0,0);
}
//---------------------------------------------------------------------------
/* On each Timeslice all the Requests which has been finished will be         */
/* Retreived and coresponding BUY or SELL will be executed                    */
/* And the client will be notified by ACKSELL or ACKBUY                       */
void __fastcall TfrmMain::tmRoundTimer(TObject *Sender)
{
	Cmds->doCmds();                       /* Do Commands which are in the Queue */
	Cmds->nextCyle();                     /* Incermet Timeout in the commands   */
	String ClientIP, StockID;
	int Action, Quantity, Status;
  /* Retreive so many commands as available (Status Successfully              */
	while(Cmds->getTransaction(Action, StockID, Quantity, ClientIP, Status)) {
    if(Status == 4) {
      if(Action == 0) {                   /* If Buy?                          */
                                          /* Buy specific Stock               */
        if(!Users->buy(ClientIP,StockID,Quantity))
          Status = 6;
      }
      else                                /* Or Sell specific Stock           */
        if(!Users->sell(ClientIP,StockID,Quantity))
          Status = 6;
    }
    TList *lst = idClientServer->Contexts->LockList();
    int i;
    String ip;
    TIdContext *context;
    for(i=0;i<lst->Count;i++) {        /* Get the Context of the ClientIP     */
      context = ((TIdContext*)(lst->Items[i]));
      ip = context->Connection->Socket->Binding->PeerIP;
      if(ip == ClientIP) {             /* If found ==> Notifiy him            */
        String tmp;
        if(Status != 4)
          tmp = tmp + "N";
        if(Action == 0)
          tmp = tmp + "ACKBUY ";
        else
          tmp = tmp + "ACKSELL ";
        if(Status == 4) {
          tmp = tmp + StockID + " " + Quantity;
        }else {
          if(Status == 2)
            tmp = tmp + "MONEY" + " " +  StockID + " " + Quantity;
          if(Status == 3)
            tmp = tmp + "CONNECTION" + " " + StockID + " " + Quantity;
          if(Status == 6)
            tmp = tmp + "STOCKS" + " " + StockID + " " + Quantity;
        }
        context->Connection->IOHandler->WriteLn(tmp);
      }
    }
    idClientServer->Contexts->UnlockList();
	}
	Cmds->delOldCmds(5);         /* Delete Buy/Sell's which got timeout of 5    */
	vBuyers->doCycle();          /* Increments Timeout in all non finished cmds */

  Users->SaveToFile("users.txt");
  Stocks->SaveToFile();

	Stocks->addStocksToStringGrid(sgStocks);
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::idClientServerCommandHandlers2Command(
      TIdCommand *ASender)
{
// Command: LOGIN
  /* Retreive information for Login                                           */
	String ip   = ASender->Context->Connection->Socket->Binding->PeerIP;
	String user = ASender->Params->Strings[0];
	String pw   = ASender->Params->Strings[1];
  /* Try to Logon the client ==> If successfully notify him                   */
  /* Else close his connection                                                */
	if(Users->auth(ip,user,pw)) {
		ASender->Context->Connection->IOHandler->WriteLn("ACKLOGIN " + user);
	}else {
		ASender->Context->Connection->Socket->Binding->CloseSocket();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers0Command(
      TIdCommand *ASender)
{
// Command: CREATE (StockExchange)
  /* Retreive information for add                                             */
	String ip   = ASender->Context->Connection->Socket->Binding->PeerIP;
	String user = ASender->Params->Strings[0];
	String pw   = ASender->Params->Strings[1];
  /* Try to Add the client ==> If successfully notify him                     */
  /* Else close his connection                                                */
	if(Users->add(ip,user,pw)) {
		ASender->Context->Connection->IOHandler->WriteLn("ACKCREATE " + user + " " + pw);
    Users->addUsersToStringGrid(sgUsers);
	}else {
		ASender->Context->Connection->Socket->Binding->CloseSocket();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idClientServerCommandHandlers1Command(
      TIdCommand *ASender)
{
// Command: DELETE (StockExchange)
  /* Retreive information for delete                                          */
	String ip   = ASender->Context->Connection->Socket->Binding->PeerIP;
	String user = ASender->Params->Strings[0];
	String pw   = ASender->Params->Strings[1];
  /* Try to Delete the client ==> If successfully notify him                  */
  /* Else close his connection                                                */
  if(Users->del(ip,user,pw)) {
    ASender->Context->Connection->IOHandler->WriteLn("ACKDELETE " + user + " " + pw);
    Users->addUsersToStringGrid(sgUsers);
	}else {
		ASender->Context->Connection->Socket->Binding->CloseSocket();
	}

}
//---------------------------------------------------------------------------

void TfrmMain::warning(String s) {
	MessageDlg(s, mtWarning, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAddClick(TObject *Sender)
{
  if(frmAddStock->ShowModal() == mrOk) {
    String StockID = frmAddStock->edtStockID->Text;
    String StartPrice = frmAddStock->edtStartPrice->Text;
    String Quantity = frmAddStock->edtQuantity->Text;
    try{
      int test = StrToInt(Quantity);
      if(!Stocks->addStock(StockID,StartPrice,StartPrice,Quantity))
        warning("StockID: " + StockID + " exists allready!");
      else
        Stocks->addStocksToStringGrid(sgStocks);      
    }catch(Exception &e) {
      warning("Quantity must be number without decimals");
    }
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnRemoveClick(TObject *Sender)
{
  int selection = sgStocks->Selection.Top;
  if(selection > -1) {
    String msg = "Do you really want to delete StockID: " + sgStocks->Cells[0][selection];
    if(MessageDlg(msg, mtWarning, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0) == mrYes) {
      String StockID = sgStocks->Cells[0][selection];
      Stocks->deleteStock(StockID);
      Users->sellStock(StockID);
      Stocks->addStocksToStringGrid(sgStocks);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mmiStockOptionsClick(TObject *Sender)
{
  frmOptions->edtActions->Text = IntToStr(vBuyers->getCycle());
  frmOptions->edtLength->Text = IntToStr(tmRound->Interval / 1000) + " s";
  frmOptions->edtNumber->Text = IntToStr(vBuyers->getNumber());
  if(frmOptions->ShowModal() == mrOk) {
    int Actions = frmOptions->upActions->Position;
    int Length = frmOptions->upLength->Position * 1000;
    int Number = frmOptions->upNumber->Position;
    vBuyers->setNumber(Number);
    vBuyers->setCycle(Actions);
    tmRound->Interval = Length;
    Stocks->addStocksToStringGrid(sgStocks);
    Users->addUsersToStringGrid(sgUsers);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRemoveUserClick(TObject *Sender)
{
  int selection = sgUsers->Selection.Top;
  if(selection > -1) {
    String msg = "Do you really want to delete User: " + sgUsers->Cells[1][selection];
    if(MessageDlg(msg, mtWarning, TMsgDlgButtons() << mbYes << mbNo << mbCancel, 0) == mrYes) {
      String ip = sgUsers->Cells[0][selection];
      Users->Delete(ip);
      Users->addUsersToStringGrid(sgUsers);
      Stocks->addStocksToStringGrid(sgStocks);
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button1Click(TObject *Sender)
{
  vBuyers->sellAll();
  Users->addUsersToStringGrid(sgUsers);
  Stocks->addStocksToStringGrid(sgStocks);
}
//---------------------------------------------------------------------------

