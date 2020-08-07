object frmAddStock: TfrmAddStock
  Left = 0
  Top = 0
  Caption = 'Add Stock...'
  ClientHeight = 154
  ClientWidth = 223
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 9
    Top = 24
    Width = 70
    Height = 21
    Alignment = taRightJustify
    Caption = 'Stock ID: '
  end
  object Label2: TLabel
    Left = 6
    Top = 51
    Width = 70
    Height = 13
    Alignment = taRightJustify
    Caption = 'Start Price:'
  end
  object Label3: TLabel
    Left = 9
    Top = 78
    Width = 70
    Height = 13
    Alignment = taRightJustify
    Caption = 'Quantity: '
  end
  object btnAdd: TButton
    Left = 8
    Top = 113
    Width = 89
    Height = 25
    Caption = '&Add'
    Default = True
    TabOrder = 0
    OnClick = btnAddClick
  end
  object btnCancel: TButton
    Left = 120
    Top = 113
    Width = 85
    Height = 25
    Caption = '&Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object edtStockID: TEdit
    Left = 84
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object edtStartPrice: TEdit
    Left = 84
    Top = 51
    Width = 121
    Height = 21
    TabOrder = 3
  end
  object edtQuantity: TEdit
    Left = 84
    Top = 78
    Width = 121
    Height = 21
    TabOrder = 4
  end
end
