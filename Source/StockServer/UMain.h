//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "UUsers.h"
#include "UStocks.h"
#include "UCommandQueue.h"
#include "UVirtualBuyers.h"
#include "UAddStock.h"
#include "UOptions.h"
#include <Grids.hpp>
#include "IdCmdTCPClient.hpp"
#include "IdCmdTCPServer.hpp"
#include "IdCustomTCPServer.hpp"
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>


//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *mmMain;
	TMenuItem *mmFile;
	TMenuItem *mmiQuit;
	TMenuItem *Options1;
	TMenuItem *mmiStockOptions;
	TGroupBox *grpStocks;
	TIdCmdTCPServer *idClientServer;
	TIdCmdTCPClient *idBankClient;
	TStringGrid *sgStocks;
	TPanel *pnlListen;
	TButton *btnListen;
	TTimer *tmRound;
  TButton *btnRemove;
  TButton *btnAdd;
  TGroupBox *GroupBox1;
  TStringGrid *sgUsers;
  TButton *btnRemoveUser;
  TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnListenClick(TObject *Sender);
	void __fastcall idClientServerCommandHandlers3Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers4Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers5Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers6Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers0Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers1Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers2Command(TIdCommand *ASender);
	void __fastcall idBankClientCommandHandlers3Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers7Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers8Command(TIdCommand *ASender);
	void __fastcall tmRoundTimer(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall idClientServerCommandHandlers2Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers0Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers1Command(TIdCommand *ASender);
  void __fastcall btnAddClick(TObject *Sender);
  void __fastcall btnRemoveClick(TObject *Sender);
  void __fastcall mmiStockOptionsClick(TObject *Sender);
  void __fastcall btnRemoveUserClick(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	TStocks *Stocks;
	TUsers *Users;
	TCommandQueue *Cmds;
	TVirtualBuyers *vBuyers;
  void warning(String s);
public:		// User declarations
	__fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
