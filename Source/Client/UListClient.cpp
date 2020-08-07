//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UListClient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmListClient *frmListClient;
//---------------------------------------------------------------------------
__fastcall TfrmListClient::TfrmListClient(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmListClient::btnCloseClick(TObject *Sender)
{
	Hide();
}
//---------------------------------------------------------------------------
