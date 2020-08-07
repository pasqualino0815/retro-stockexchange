//---------------------------------------------------------------------------

#ifndef UListClientH
#define UListClientH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmListClient : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *sgClientStocks;
	TButton *btnClose;
  TLabel *lblTotal;
	void __fastcall btnCloseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmListClient(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmListClient *frmListClient;
//---------------------------------------------------------------------------
#endif
