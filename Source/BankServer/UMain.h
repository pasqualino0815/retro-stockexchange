//---------------------------------------------------------------------------

#ifndef UMainH
#define UMainH
#include "IdCmdTCPServer.hpp"
#include "IdCustomTCPServer.hpp"
#include <Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPServer.hpp>
#include "UUsers.cpp"
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

class TfrmMain : public TForm
{
__published:	// IDE-managed Components
	TIdCmdTCPServer *idClientServer;
	TTimer *tmAmounts;
	TPanel *pnlListen;
	TPanel *pnlLog;
	TMemo *memLog;
	TButton *btnListen;
	TListBox *lbClients;
	TCheckBox *chkActiveUsers;
	TIdCmdTCPServer *idStockServer;
  TEdit *edtSalary;
  TLabel *Label1;
  TLabel *Label2;
  TEdit *edtTimer;
  TUpDown *upTimer;
  TUpDown *upSalary;
	void __fastcall idClientServerCommandHandlers0Command(TIdCommand *ASender);
	void __fastcall idClientServerConnect(TIdContext *AContext);
	void __fastcall idClientServerDisconnect(TIdContext *AContext);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall idClientServerCommandHandlers1Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers3Command(TIdCommand *ASender);
	void __fastcall idClientServerCommandHandlers2Command(TIdCommand *ASender);
	void __fastcall tmAmountsTimer(TObject *Sender);
	void __fastcall btnListenClick(TObject *Sender);
	void __fastcall idClientServerCommandHandlers5Command(TIdCommand *ASender);
	void __fastcall chkActiveUsersClick(TObject *Sender);
	void __fastcall idStockServerCommandHandlers0Command(TIdCommand *ASender);
	void __fastcall idStockServerCommandHandlers1Command(TIdCommand *ASender);
  void __fastcall upTimerClick(TObject *Sender, TUDBtnType Button);
  void __fastcall upSalaryClick(TObject *Sender, TUDBtnType Button);
private:	// User declarations
	String getTime();
	void addLog(String log);
	TUsers users;
public:		// User declarations
        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
