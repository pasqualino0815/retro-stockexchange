//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdCmdTCPClient"
#pragma link "IdCmdTCPClient"
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TfrmMain::createTabSheet(bool Create) {
  if(frmConnectBank->edtBankIP->Text != "" && frmConnectBank->edtPassword->Text != "" && frmConnectBank->edtUsername->Text != "") {
    int p = pcBanks->PageCount;
    if(! isUniqueBankIP(frmConnectBank->edtBankIP->Text))
      return false;
    clients[p] = new TIdCmdTCPClient(*idBankClient);
    clients[p]->Host = frmConnectBank->edtBankIP->Text;
    clients[p]->Port = 12345;
    clients[p]->Connect();
    if(clients[p]->Connected()) {
      if(Create)
        clients[p]->IOHandler->WriteLn("CREATE " + frmConnectBank->edtUsername->Text + " " + frmConnectBank->edtPassword->Text);
      TTabSheet *sheet = new TTabSheet(pcBanks);
      TButton *button = new TButton(sheet);
      TButton *btnGetAllAmounts = new TButton(sheet);
      TLabel *lblAmount = new TLabel(sheet);
      TStringGrid *sgAmounts = new TStringGrid(sheet);

      sheet->Caption = frmConnectBank->edtBankIP->Text;
      sheet->PageControl = pcBanks;

      button->Name    = "btnDisconnect";
      button->Caption = "Close";
      button->OnClick = btnDisconnectClick;
      button->Tag     = p;
      button->Left    = sheet->Width - button->Width - 5;
      button->Top     = 5;

      btnGetAllAmounts->Name    = "btnGetAllAmounts";
      btnGetAllAmounts->Caption = "Get All Amounts";
      btnGetAllAmounts->OnClick = btnAddAmounts;
      btnGetAllAmounts->Tag     = p;
      btnGetAllAmounts->Left    = 5;
      btnGetAllAmounts->Width   = sheet->Width - 10;
      btnGetAllAmounts->Top     = 50;

      sgAmounts->Name   = "sgAmounts";
      sgAmounts->Font->Size = 10;
      sgAmounts->Top    = 90;
      sgAmounts->Left   = 5;
      sgAmounts->Width = sheet->Width - 10;
      sgAmounts->Height = sheet->Height - 5 - sgAmounts->Top;
      sgAmounts->ColCount = 2;
      sgAmounts->RowCount = 2;
      sgAmounts->FixedCols = 0;
      sgAmounts->DefaultRowHeight = 18;
      sgAmounts->DefaultColWidth = (sheet->Width - 10) / 2 - 2;
      sgAmounts->Cells[0][0] = "Name";
      sgAmounts->Cells[1][0] = "Amount";
      sgAmounts->ScrollBars = ssVertical;

      lblAmount->Name        = "lblAmount";
      lblAmount->AutoSize    = false;
      lblAmount->Caption     = "Amount: ?";
      lblAmount->Font->Style << fsBold;
      lblAmount->Left        = 5;
      lblAmount->Top         = 5;
      lblAmount->Font->Size  = 11;
      lblAmount->Font->Style << fsBold;
      lblAmount->Width       = sheet->Width - 10;
      lblAmount->Height      = 30;

      button           ->Parent = sheet;
      lblAmount        ->Parent = sheet;
      sgAmounts        ->Parent = sheet;
      btnGetAllAmounts ->Parent = sheet;

      pcBanks->ActivePageIndex = pcBanks->PageCount - 1;

      clients[p]->IOHandler->WriteLn("LOGIN " + frmConnectBank->edtUsername->Text + " " +frmConnectBank->edtPassword->Text);
      return true;
    }
    clients[p]->Free();
    return false;
  }else {
    warning("IP, username and password must be filled in!");
    return false;
  }
}
//---------------------------------------------------------------------------
void TfrmMain::warning(String s) {
	MessageDlg(s, mtWarning, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------
bool TfrmMain::isUniqueBankIP(String ip) {
	int i;
	for(i=0;i<pcBanks->PageCount;i++) {
		if(pcBanks->Pages[i]->Caption == ip)
			return false;
	}
	return true;
}
//---------------------------------------------------------------------------
int TfrmMain::getBankSheetIndex(String ip) {
	int i,p=-1;
	for(i=0;i<pcBanks->PageCount;i++)
		if(pcBanks->Pages[i]->Caption == ip)
			p=i;
	return p;
}
//---------------------------------------------------------------------------
String TfrmMain::formatString(String a, String b, int l) {
	String t;
	int i;
	t = a;
	for(i=t.Length();i<l-b.Length();i++)
		t = t + " ";
	return t + b;
}
//---------------------------------------------------------------------------
void TfrmMain::setMessage(String msg, bool good) {
	Sleep((unsigned int)500);
	if(good)
		edtMsg->Color = clGreen;
	else
		edtMsg->Color = clRed;
	edtMsg->Text = msg;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmiQuitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmiConnectBankClick(TObject *Sender)
{
	frmConnectBank->btnConnect->Caption = "Connect";
	frmConnectBank->Caption = "Connect to Bank...";
	if(frmConnectBank->ShowModal() == mrOk) {
    if(frmConnectBank->edtBankIP->Text != "" && frmConnectBank->edtPassword->Text != "" && frmConnectBank->edtUsername->Text != "") {
      if(pcBanks->PageCount < 10)
        if(!createTabSheet(false))
          setMessage("ERROR: BankIP Exists // ERROR: Connecting",false);
    }else {
      warning("IP, username and password must be filled in!");
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmiDeleteBankAccountClick(TObject *Sender)
{
// Command: DELETE
	if(pcBanks->PageCount > 0) {
		frmConnectBank->btnConnect->Caption = "Delete";
		frmConnectBank->Caption = "Delete Bank Account...";
		if(frmConnectBank->ShowModal() == mrOk) {
			int p = getBankSheetIndex(frmConnectBank->edtBankIP->Text);
			if(p > -1) {
				String s = "DELETE ";
				s = s + frmConnectBank->edtUsername->Text + " ";
				s = s + frmConnectBank->edtPassword->Text;
				clients[p]->IOHandler->WriteLn(s);
			}else
				warning("Server did not match current connection!");
		}
	}else {
		warning("Not Connected!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmiCreateBankAccountClick(TObject *Sender)
{
	frmConnectBank->btnConnect->Caption = "Create";
	frmConnectBank->Caption = "Create Bank Account...";
	if(frmConnectBank->ShowModal() == mrOk)
		if(pcBanks->PageCount < 10)
			if(!createTabSheet(true))
				setMessage("ERROR: BankIP Exists // ERROR: Connecting",false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnDisconnectClick(TObject *Sender) {
	TButton *pButton = dynamic_cast<TButton*>(Sender);
	int index = pButton->Tag;
	int i = index;
	clients[i]->Disconnect();
	for(i=pButton->Tag;i<pcBanks->PageCount-1;i++) {
		clients[i] = clients[i+1];
		pButton = dynamic_cast<TButton*>(pcBanks->Pages[i+1]->FindComponent("btnDisconnect"));
		pButton->Tag = pButton->Tag - 1;
	}
	pcBanks->Pages[index]->Free();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnAddAmounts(TObject *Sender) {
	TButton *pButton = dynamic_cast<TButton*>(Sender);
	clients[pButton->Tag]->IOHandler->WriteLn("GETALLAMOUNTS");
}
//---------------------------------------------------------------------------
// Disconnect all available Client Connections
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
	int i;
	for(i=0;i<pcBanks->PageCount;i++) {
		clients[i]->Disconnect();
	}
}
//---------------------------------------------------------------------------
// Send GETAMOUNT to the respective server to get the current amount on the
// Bank account
void __fastcall TfrmMain::tmUpdateAmountsTimer(TObject *Sender)
{
	if(pcBanks->PageCount > 0) {
		int i;
		for(i=0;i<pcBanks->PageCount;i++) {
			if(pcBanks->Pages[i]->Tag == 1 && clients[i]->Connected())
				clients[i]->IOHandler->WriteLn("GETAMOUNT");
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idStockClientStatus(TObject *ASender,
      const TIdStatus AStatus, const AnsiString AStatusText)
{
	if(idStockClient->Connected() == false)
	StatusBar->Panels->Items[0]->Text = "Not Connected";
	else
	StatusBar->Panels->Items[0]->Text = "Connected";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idBankClientCommandHandlers0Command(
			TIdCommand *ASender)
{
// Command: AMOUNT
	int i,p=-1;
	for(i=0;i<pcBanks->PageCount;i++) {
		if(pcBanks->Pages[i]->Caption == ASender->Context->Connection->Socket->Host)
			p=i;
	}
	if(p > -1) {
		TLabel *pLabel = dynamic_cast<TLabel*>(pcBanks->Pages[p]->Components[2]);
		pLabel->Caption = "Amount: " + ASender->Params->Strings[0] + " €";
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers7Command(
      TIdCommand *ASender)
{
// Conmmand: ACKDELETE
	setMessage("Succesfully Deleted Account", true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers6Command(
      TIdCommand *ASender)
{
// Conmmand: NACKDELETE
	setMessage("Account Delete Failed", false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers5Command(
			TIdCommand *ASender)
{
// Command: ALLAMOUNTS
	int i,p=-1,j=1;
	for(i=0;i<pcBanks->PageCount;i++) {
		if(pcBanks->Pages[i]->Caption == ASender->Context->Connection->Socket->Host)
			p=i;
	}
	if(p > -1) {
		TStringGrid *sgAmounts = dynamic_cast<TStringGrid*>(pcBanks->Pages[p]->FindComponent("sgAmounts"));
		sgAmounts->RowCount = ASender->Params->Count / 2 + 1;
		for(i=0;i<ASender->Params->Count;i=i+2) {
			sgAmounts->Cells[0][j] = ASender->Params->Strings[i];
			sgAmounts->Cells[1][j] = ASender->Params->Strings[i+1] + " €";
			j++;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::idBankClientStatus(TObject *ASender,
			const TIdStatus AStatus, const AnsiString AStatusText)
{
	if(AStatus == hsDisconnected) {
		String classname = ASender->ClassName();
		if(classname == "TIdIOHandlerStack") {
			TIdIOHandlerStack *stack = dynamic_cast<TIdIOHandlerStack*>(ASender);
			warning("Disconnected on bank: " + stack->Host);
			int p = getBankSheetIndex(stack->Host);
			TButton *btnDisconnect = dynamic_cast<TButton*>(pcBanks->Pages[p]->FindComponent("btnDisconnect"));
			dynamic_cast<TLabel*>(pcBanks->Pages[p]->FindComponent("lblAmount"))->Caption = "DISCONNECTED";
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mmiDisconnectStockExchangeClick(TObject *Sender)
{
	idStockClient->Disconnect();
	StatusBar->Panels->Items[0]->Text = "Not Connected";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mmiConnectStockExchangeClick(TObject *Sender)
{
	frmConnectBank->btnConnect->Caption = "Connect";
	frmConnectBank->Caption = "Connect to StockExchange...";
	if(frmConnectBank->ShowModal() == mrOk) {
		idStockClient->Port = 12000;
    if(frmConnectBank->edtBankIP->Text != "" && frmConnectBank->edtPassword->Text != "" && frmConnectBank->edtUsername->Text != "") {
      idStockClient->Host = frmConnectBank->edtBankIP->Text;
      idStockClient->Connect();
      idStockClient->IOHandler->WriteLn("LOGIN " + frmConnectBank->edtUsername->Text + " " + frmConnectBank->edtPassword->Text);
    }else {
      warning("IP, username and password must be filled in!");
    }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mmiCreateStockAccountClick(TObject *Sender)
{
	frmConnectBank->btnConnect->Caption = "Create";
	frmConnectBank->Caption = "Create Account on StockExchange...";
	if(frmConnectBank->ShowModal() == mrOk) {
    if(frmConnectBank->edtBankIP->Text != "" && frmConnectBank->edtPassword->Text != "" && frmConnectBank->edtUsername->Text != "") {
      idStockClient->Port = 12000;
      idStockClient->Host = frmConnectBank->edtBankIP->Text;
      idStockClient->Connect();
      idStockClient->IOHandler->WriteLn("CREATE " + frmConnectBank->edtUsername->Text + " " + frmConnectBank->edtPassword->Text);
      Sleep((unsigned int)200);
      idStockClient->IOHandler->WriteLn("LOGIN " + frmConnectBank->edtUsername->Text + " " + frmConnectBank->edtPassword->Text);
    }else {
      warning("IP, username and password must be filled in!");
    }
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::mmiDeleteStockAccountClick(TObject *Sender)
{
	frmConnectBank->btnConnect->Caption = "Delete";
	frmConnectBank->Caption = "Delete Account on StockExchange...";
	if(idStockClient->Connected()) {
	 	if(frmConnectBank->ShowModal() == mrOk) {
      String s = "DELETE ";
      s = s + frmConnectBank->edtUsername->Text + " ";
      s = s + frmConnectBank->edtPassword->Text;
      idStockClient->IOHandler->WriteLn(s);
		}
	}else {
		setMessage("ERROR: Not Connected to Stock Exchange Server",false);
  }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRefreshStocksClick(TObject *Sender)
{
	if(idStockClient->Connected())
		idStockClient->IOHandler->WriteLn("LIST");
	else
		ShowMessage("Not Connected to Stock Exchange!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers6Command(
      TIdCommand *ASender)
{
// StockCommand: LIST
	int i,j=1;
	sgStocks->Cells[0][0] = "StockID";
	sgStocks->Cells[1][0] = "Old Price";
	sgStocks->Cells[2][0] = "Actual";
	sgStocks->Cells[3][0] = "Quantity";

	sgStocks->RowCount = ASender->Params->Count / 4 + 1;
	if(sgStocks->RowCount == 1) {
		sgStocks->RowCount = 2;
    sgStocks->Cells[0][1] = "";
    sgStocks->Cells[1][1] = "";
    sgStocks->Cells[2][1] = "";
    sgStocks->Cells[3][1] = "";
    sgStocks->Cells[4][1] = "";
		sgStocks->FixedRows = 1;
	}
	for(i=0;i<ASender->Params->Count;i=i+4) {
		sgStocks->Cells[0][j] = ASender->Params->Strings[i];
		sgStocks->Cells[1][j] = ASender->Params->Strings[i+1] + " €";
		sgStocks->Cells[2][j] = ASender->Params->Strings[i+2] + " €";
		sgStocks->Cells[3][j] = ASender->Params->Strings[i+3];
		j++;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers7Command(
      TIdCommand *ASender)
{
// StockCommand: LISTME
	int i,j=1, qua;
	float marge;
	sgMyStocks->Cells[0][0] = "StockID";
	sgMyStocks->Cells[1][0] = "Old Price";
	sgMyStocks->Cells[2][0] = "Actual";
	sgMyStocks->Cells[3][0] = "Quantity";
	sgMyStocks->Cells[4][0] = "Marge";
	sgMyStocks->RowCount = ASender->Params->Count / 4 + 1;
	if(sgMyStocks->RowCount == 1) {
		sgMyStocks->RowCount = 2;
    sgMyStocks->Cells[0][1] = "";
    sgMyStocks->Cells[1][1] = "";
    sgMyStocks->Cells[2][1] = "";
    sgMyStocks->Cells[3][1] = "";
    sgMyStocks->Cells[4][1] = "";
		sgMyStocks->FixedRows = 1;
	}
	for(i=0;i<ASender->Params->Count;i=i+4) {
		qua = StrToInt(ASender->Params->Strings[i+3]);
		marge = (StrToFloat(ASender->Params->Strings[i+2]) * qua) - (StrToFloat(ASender->Params->Strings[i+1]) * qua);
		sgMyStocks->Cells[0][j] = ASender->Params->Strings[i];
		sgMyStocks->Cells[1][j] = ASender->Params->Strings[i+1] + " €";
		sgMyStocks->Cells[2][j] = ASender->Params->Strings[i+2] + " €";
		sgMyStocks->Cells[3][j] = ASender->Params->Strings[i+3];
		sgMyStocks->Cells[4][j] = FormatFloat("0.00",marge) + " €";
		j++;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRefreshOwnStocksClick(TObject *Sender)
{
	if(idStockClient->Connected())
		idStockClient->IOHandler->WriteLn("LISTME");
	else
		ShowMessage("Not Connected to Stock Exchange!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers8Command(
      TIdCommand *ASender)
{
// StockCommand: LISTCLIENTS
	int i,j=1;
	sgClients->Cells[0][0] = "IP";
	sgClients->Cells[1][0] = "User Name";
	sgClients->RowCount = ASender->Params->Count / 2 + 1;
	if(sgClients->RowCount == 1) {
		sgClients->RowCount = 2;
    sgClients->Cells[0][1] = "";
    sgClients->Cells[1][1] = "";
		sgClients->FixedRows = 1;
	}
	for(i=0;i<ASender->Params->Count;i=i+2) {
		sgClients->Cells[0][j] = ASender->Params->Strings[i];
		sgClients->Cells[1][j] = ASender->Params->Strings[i+1];
		j++;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnRefreshClientsClick(TObject *Sender)
{
	if(idStockClient->Connected())
		idStockClient->IOHandler->WriteLn("LISTCLIENTS");
	else
		ShowMessage("Not Connected to Stock Exchange!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Button3Click(TObject *Sender)
{
	String ip = sgClients->Cells[0][sgClients->Selection.Top];
	if(ip != "") {
		idStockClient->IOHandler->WriteLn("LISTCLIENT " + ip);
		frmListClient->Caption = "Stocks of Client " + ip;
		frmListClient->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers9Command(
      TIdCommand *ASender)
{
// StockCommand: LISTCLIENT
	int i,j=1;
  float total = 0;
  float q,a;
	frmListClient->sgClientStocks->Cells[0][0] = "StockID";
	frmListClient->sgClientStocks->Cells[1][0] = "Old Price";
	frmListClient->sgClientStocks->Cells[2][0] = "Actual";
	frmListClient->sgClientStocks->Cells[3][0] = "Quantity";
	frmListClient->sgClientStocks->RowCount = ASender->Params->Count / 4 + 1;
	if(frmListClient->sgClientStocks->RowCount == 1) {
		frmListClient->sgClientStocks->RowCount = 2;
    frmListClient->sgClientStocks->Cells[0][1] = "";
    frmListClient->sgClientStocks->Cells[1][1] = "";
    frmListClient->sgClientStocks->Cells[2][1] = "";
    frmListClient->sgClientStocks->Cells[3][1] = "";
    frmListClient->sgClientStocks->Cells[4][1] = "";
		frmListClient->sgClientStocks->FixedRows = 1;
	}
	if(ASender->Params->Count > 1) {
		for(i=0;i<ASender->Params->Count;i=i+4) {
			frmListClient->sgClientStocks->Cells[0][j] = ASender->Params->Strings[i];
			frmListClient->sgClientStocks->Cells[1][j] = ASender->Params->Strings[i+1] + " €";
			frmListClient->sgClientStocks->Cells[2][j] = ASender->Params->Strings[i+2] + " €";
      a = StrToFloat(ASender->Params->Strings[i+2]);
			frmListClient->sgClientStocks->Cells[3][j] = ASender->Params->Strings[i+3];
      q = StrToInt(ASender->Params->Strings[i+3]);
      total = total + a * q;
			j++;
		}
    frmListClient->lblTotal->Caption = "Total: " + FormatFloat("0.00",total) + " €";
	}else frmListClient->lblTotal->Caption = "Total: 0 €";
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnBuyClick(TObject *Sender)
{
	String StockID  = sgStocks->Cells[0][sgStocks->Selection.Top];
	if(StockID != "") {
		if(pcBanks->PageCount > 0) {
			String BankIP = pcBanks->ActivePage->Caption;
			String Quantity = InputBox("Please Enter Quantity","Quantity", "0");
			int q = StrToInt(Quantity);
      if(q != 0) {
        if(q <= StrToInt(sgStocks->Cells[3][sgStocks->Selection.Top]) && q > 0) {
          String tmp = StockID + " " + Quantity + " " + BankIP;
          idStockClient->IOHandler->WriteLn("BUY " + tmp);
        }else
          ShowMessage("Please Enter Quantity > 0 and Quantity <= Available Quantity!");
      }
		}else
			ShowMessage("Please Connect to a Bank!");
	}else
		ShowMessage("Please Select a Stock!");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSellClick(TObject *Sender)
{
	String StockID  = sgMyStocks->Cells[0][sgMyStocks->Selection.Top];
	if(StockID != "") {
		if(pcBanks->PageCount > 0) {
			String BankIP = pcBanks->ActivePage->Caption;
			String Quantity = InputBox("Please Enter Quantity","Quantity", "0");
			int q = StrToInt(Quantity);
      if(q != 0) {
        if(q <= StrToInt(sgMyStocks->Cells[3][sgMyStocks->Selection.Top]) && q > 0) {
          String tmp = StockID + " " + Quantity + " " + BankIP;
          idStockClient->IOHandler->WriteLn("SELL " + tmp);
        }else
          ShowMessage("Please Enter Quantity > 0 and Quantity <= Available Quantity!");
      }
		}else
			ShowMessage("Please Connect to a Bank!");
	}else
		ShowMessage("Please Select a Stock!");
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::idStockClientCommandHandlers10Command(
      TIdCommand *ASender)
{
// StockCommand: ACKBUY
  String msg = "Successfully bought StockID: " + ASender->Params->Strings[0] + " * " +  ASender->Params->Strings[1];
  btnRefreshOwnStocksClick(0);
  setMessage(msg,true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers11Command(
      TIdCommand *ASender)
{
// StockCommand: SELL
  String msg = "Successfully sold StockID: " + ASender->Params->Strings[0] + " * " +  ASender->Params->Strings[1];
  btnRefreshOwnStocksClick(0);
  setMessage(msg,true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers2Command(
      TIdCommand *ASender)
{
// StockCommand: ACKCREATE
  String msg = "Successfully Created Account on StockExchange: Username = " + ASender->Params->Strings[0] + " Password = " +  ASender->Params->Strings[1];
  setMessage(msg,true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers3Command(
      TIdCommand *ASender)
{
// StockCommand: NACKCREATE
  String msg = "Error Creating Account on StockExchange: Username = " + ASender->Params->Strings[0] + " Password = " +  ASender->Params->Strings[1];
  setMessage(msg,false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers5Command(
      TIdCommand *ASender)
{
// StockCommand: ACKDELETE
  String msg = "Successfully Deleted Account on StockExchange: Username = " + ASender->Params->Strings[0] + " Password = " +  ASender->Params->Strings[1];
  setMessage(msg,true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers4Command(
      TIdCommand *ASender)
{
// StockCommand: NACKDELETE
  String msg = "Error Deleting Account on StockExchange: Username = " + ASender->Params->Strings[0] + " Password = " +  ASender->Params->Strings[1];
  idStockClient->Disconnect(true);  
  setMessage(msg,false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers1Command(
      TIdCommand *ASender)
{
// StockCommand: ACKLOGIN
  String msg = "Successfully Logged On Account on StockExchange: Username = " + ASender->Params->Strings[0];
  setMessage(msg,true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers0Command(
      TIdCommand *ASender)
{
// StockCommand: NACKLOGIN
  String msg = "Error Login Account on StockExchange: Username = " + ASender->Params->Strings[0];
  setMessage(msg,false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers3Command(
      TIdCommand *ASender)
{
// BankCommand: ACKCREATE
  String msg = "Successfully Created Account on Bank(" + ASender->Context->Connection->Socket->Host + "): Username = " + ASender->Params->Strings[0] + " Password = " +  ASender->Params->Strings[1];
  setMessage(msg,true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers4Command(
      TIdCommand *ASender)
{
  String msg = "Error Creating Account on Bank(" + ASender->Context->Connection->Socket->Host + "): Username = " + ASender->Params->Strings[0] + " Password = " +  ASender->Params->Strings[1];
  setMessage(msg,false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers2Command(
			TIdCommand *ASender)
{
// BankCommand: ACKLOGIN
	pcBanks->Pages[pcBanks->PageCount-1]->Tag = 1;
	setMessage("Login Successfully on Bank",true);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idBankClientCommandHandlers1Command(
			TIdCommand *ASender)
{
// BankCommand: NACKLOGIN
	setMessage("Login failed",false);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::idStockClientCommandHandlers12Command(
      TIdCommand *ASender)
{
// StockCommand: NACKBUY
  String msg = "Error Buying " + ASender->Params->Strings[1] + " * " + ASender->Params->Strings[2] + " Reason: ";
  if(ASender->Params->Strings[0] == "MONEY")
    setMessage(msg + "Not enough money",false);
  if(ASender->Params->Strings[0] == "CONNECTION")
    setMessage(msg + "Connecting to Bank",false);
  if(ASender->Params->Strings[0] == "STOCKS")
    setMessage(msg + "Not enough Stocks",false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::idStockClientCommandHandlers13Command(
      TIdCommand *ASender)
{
// StockCommand: NACKSELL
  String msg = "Error Selling " + ASender->Params->Strings[1] + " * " + ASender->Params->Strings[2] + " Reason: ";
  if(ASender->Params->Strings[0] == "MONEY")
    setMessage(msg + "Not enough money",false);
  if(ASender->Params->Strings[0] == "CONNECTION")
    setMessage(msg + "Connecting to Bank",false);
  if(ASender->Params->Strings[0] == "STOCKS")
    setMessage(msg + "Not enough Stocks",false);
}
//---------------------------------------------------------------------------

