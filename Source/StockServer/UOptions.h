//---------------------------------------------------------------------------

#ifndef UOptionsH
#define UOptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmOptions : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *GroupBox1;
  TGroupBox *GroupBox2;
  TButton *btnAdd;
  TButton *btnCancel;
  TLabel *Label1;
  TEdit *edtNumber;
  TLabel *Label2;
  TLabel *Label3;
  TEdit *edtActions;
  TEdit *edtLength;
  TUpDown *upNumber;
  TUpDown *upActions;
  TUpDown *upLength;
  void __fastcall upNumberClick(TObject *Sender, TUDBtnType Button);
  void __fastcall upActionsClick(TObject *Sender, TUDBtnType Button);
  void __fastcall upLengthClick(TObject *Sender, TUDBtnType Button);
private:	// User declarations
  bool CheckNumber(String s);
  void warning(String s);
public:		// User declarations
  __fastcall TfrmOptions(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
#endif
