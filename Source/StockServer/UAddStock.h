//---------------------------------------------------------------------------

#ifndef UAddStockH
#define UAddStockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmAddStock : public TForm
{
__published:	// IDE-managed Components
  TButton *btnAdd;
  TButton *btnCancel;
  TLabel *Label1;
  TLabel *Label2;
  TEdit *edtStockID;
  TEdit *edtStartPrice;
  TLabel *Label3;
  TEdit *edtQuantity;
  void __fastcall btnAddClick(TObject *Sender);
private:	// User declarations
  bool CheckNumber(String s);
  void warning(String s);
public:		// User declarations
	__fastcall TfrmAddStock(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAddStock *frmAddStock;
//---------------------------------------------------------------------------
#endif
