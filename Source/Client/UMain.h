//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
#include "IdCmdTCPClient.hpp"
#include <Classes.hpp>
#include <Controls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "UBankConnection.h"
#include "UListClient.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *mmMain;
	TMenuItem *mmFile;
	TMenuItem *mmiConnectBank;
	TMenuItem *mmiConnectStockExchange;
	TMenuItem *mmiQuit;
	TIdCmdTCPClient *idBankClient;
	TPanel *pnlMain;
	TStatusBar *StatusBar;
	TPanel *pnlStockExchange;
	TMenuItem *mmiDisconnectStockExchange;
	TTimer *tmUpdateAmounts;
	TEdit *edtMsg;
	TMenuItem *mmiCreateBankAccount;
	TMenuItem *mmiCreateStockAccount;
	TMenuItem *mmBank;
	TMenuItem *mmStockExchange;
	TMenuItem *mmiDeleteStockAccount;
	TMenuItem *mmiDeleteBankAccount;
	TMenuItem *N1;
	TMenuItem *N2;
	TIdCmdTCPClient *idStockClient;
	TPanel *pnlBanks;
	TPanel *pnlBankLabel;
	TLabel *lblBanks;
	TPageControl *pcBanks;
	TStringGrid *sgStocks;
	TStringGrid *sgMyStocks;
	TLabel *Label1;
	TLabel *lblStockExchange;
	TLabel *Label2;
	TButton *btnBuy;
	TButton *btnSell;
	TLabel *Label3;
	TStringGrid *sgClients;
	TButton *Button3;
	TButton *btnRefreshOwnStocks;
	TButton *btnRefreshStocks;
	TButton *btnRefreshClients;
  TPanel *pnlStockConnection;
	void __fastcall mmiQuitClick(TObject *Sender);
	void __fastcall mmiConnectBankClick(TObject *Sender);
	void __fastcall idBankClientCommandHandlers0Command(TIdCommand *ASender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall tmUpdateAmountsTimer(TObject *Sender);
	void __fastcall idBankClientCommandHandlers2Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers1Command(TIdCommand *ASender);


	void __fastcall btnDisconnectClick(TObject *Sender);
	void __fastcall btnAddAmounts(TObject *Sender);

	void __fastcall idStockClientStatus(TObject *ASender, const TIdStatus AStatus,
          const AnsiString AStatusText);
	void __fastcall idBankClientCommandHandlers3Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers4Command(TIdCommand *ASender);
	void __fastcall mmiCreateBankAccountClick(TObject *Sender);
	void __fastcall idBankClientCommandHandlers5Command(TIdCommand *ASender);
	void __fastcall mmiDeleteBankAccountClick(TObject *Sender);
	void __fastcall idBankClientCommandHandlers7Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers6Command(TIdCommand *ASender);
	void __fastcall idBankClientStatus(TObject *ASender, const TIdStatus AStatus,
          const AnsiString AStatusText);
	void __fastcall mmiDisconnectStockExchangeClick(TObject *Sender);
	void __fastcall mmiConnectStockExchangeClick(TObject *Sender);
	void __fastcall mmiCreateStockAccountClick(TObject *Sender);
	void __fastcall mmiDeleteStockAccountClick(TObject *Sender);
	void __fastcall btnRefreshStocksClick(TObject *Sender);
	void __fastcall idStockClientCommandHandlers6Command(TIdCommand *ASender);
	void __fastcall idStockClientCommandHandlers7Command(TIdCommand *ASender);
	void __fastcall btnRefreshOwnStocksClick(TObject *Sender);
	void __fastcall idStockClientCommandHandlers8Command(TIdCommand *ASender);
	void __fastcall btnRefreshClientsClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall idStockClientCommandHandlers9Command(TIdCommand *ASender);
	void __fastcall btnBuyClick(TObject *Sender);
	void __fastcall btnSellClick(TObject *Sender);
  void __fastcall idStockClientCommandHandlers10Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers11Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers2Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers3Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers5Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers4Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers1Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers0Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers12Command(TIdCommand *ASender);
  void __fastcall idStockClientCommandHandlers13Command(TIdCommand *ASender);
private:	// User declarations
	bool createTabSheet(bool Create);
	bool isUniqueBankIP(String ip);
	void setMessage(String msg, bool good);
	TIdCmdTCPClient *clients[10];
	String formatString(String a, String b, int l);
	int getBankSheetIndex(String ip);
	void warning(String s);
public:		// User declarations
				__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
