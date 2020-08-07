object frmListClient: TfrmListClient
  Left = 0
  Top = 0
  Caption = 'Stocks of Client '
  ClientHeight = 152
  ClientWidth = 331
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblTotal: TLabel
    Left = 143
    Top = 119
    Width = 185
    Height = 19
    AutoSize = False
    Caption = 'Total:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object sgClientStocks: TStringGrid
    Left = 8
    Top = 8
    Width = 320
    Height = 105
    ColCount = 4
    DefaultRowHeight = 18
    FixedCols = 0
    RowCount = 2
    ScrollBars = ssVertical
    TabOrder = 0
    ColWidths = (
      64
      87
      78
      81)
  end
  object btnClose: TButton
    Left = 8
    Top = 119
    Width = 113
    Height = 25
    Caption = 'Close'
    Default = True
    TabOrder = 1
    OnClick = btnCloseClick
  end
end
