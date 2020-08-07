//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UAddStock.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAddStock *frmAddStock;
//---------------------------------------------------------------------------
__fastcall TfrmAddStock::TfrmAddStock(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddStock::btnAddClick(TObject *Sender)
{
  if(edtStockID->Text != "") {
    if(edtStartPrice->Text != "") {
      if(edtQuantity->Text != "") {
        if(CheckNumber(edtStartPrice->Text)) {
          if(CheckNumber(edtQuantity->Text)) {
            frmAddStock->ModalResult = mrOk;
          }else warning("Quantity > 0!");
        }else warning("StartPrice > 0!");
      }else warning("Fill in Quantity");
    }else warning("Fill in StartPrice");
  }else warning("Fill in StockID");
}
//---------------------------------------------------------------------------
bool TfrmAddStock::CheckNumber(String s) {
  float number;
  try {
    number = StrToFloat(s);
    if(number > 0)
      return true;
  } catch (EConvertError &e) {
    return false;
  }
  return false;
}
//---------------------------------------------------------------------------
void TfrmAddStock::warning(String s) {
	MessageDlg(s, mtWarning, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

