//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmOptions *frmOptions;
//---------------------------------------------------------------------------
__fastcall TfrmOptions::TfrmOptions(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool TfrmOptions::CheckNumber(String s) {
  int number;
  try {
    number = StrToInt(s);
    if(number >= 0)
      return true;
  } catch (EConvertError &e) {
    return false;
  }
  return false;
}
//---------------------------------------------------------------------------
void TfrmOptions::warning(String s) {
	MessageDlg(s, mtWarning, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------
void __fastcall TfrmOptions::upNumberClick(TObject *Sender, TUDBtnType Button)
{
  edtNumber->Text = IntToStr(upNumber->Position);
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::upActionsClick(TObject *Sender, TUDBtnType Button)
{
  edtActions->Text = IntToStr(upActions->Position);
}
//---------------------------------------------------------------------------

void __fastcall TfrmOptions::upLengthClick(TObject *Sender, TUDBtnType Button)
{
  edtLength->Text = IntToStr(upLength->Position) + " s";
}
//---------------------------------------------------------------------------

