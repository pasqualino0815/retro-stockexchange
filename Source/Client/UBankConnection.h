//---------------------------------------------------------------------------

#ifndef UBankConnectionH
#define UBankConnectionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmConnectBank : public TForm
{
__published:	// IDE-managed Components
	TLabel *lblIP;
	TEdit *edtBankIP;
	TButton *btnConnect;
	TButton *btnCancel;
	TEdit *edtUsername;
	TLabel *Label1;
	TEdit *edtPassword;
	TLabel *Label2;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmConnectBank(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmConnectBank *frmConnectBank;
//---------------------------------------------------------------------------
#endif
