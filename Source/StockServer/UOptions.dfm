object frmOptions: TfrmOptions
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Options...'
  ClientHeight = 217
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 201
    Height = 105
    Caption = 'Virtual Clients'
    TabOrder = 0
    object Label2: TLabel
      Left = 75
      Top = 32
      Width = 41
      Height = 13
      Alignment = taRightJustify
      Caption = 'Number:'
    end
    object Label3: TLabel
      Left = 41
      Top = 59
      Width = 75
      Height = 13
      Alignment = taRightJustify
      Caption = 'Actions / Cycle:'
    end
    object edtNumber: TEdit
      Left = 127
      Top = 29
      Width = 50
      Height = 21
      Enabled = False
      TabOrder = 0
      Text = '0'
    end
    object edtActions: TEdit
      Left = 127
      Top = 59
      Width = 50
      Height = 21
      Enabled = False
      TabOrder = 1
      Text = '0'
    end
    object upNumber: TUpDown
      Left = 177
      Top = 26
      Width = 17
      Height = 25
      Max = 20
      TabOrder = 2
      OnClick = upNumberClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 9
    Top = 119
    Width = 200
    Height = 58
    Caption = 'Time Slice'
    TabOrder = 1
    object Label1: TLabel
      Left = 79
      Top = 24
      Width = 40
      Height = 13
      Alignment = taRightJustify
      Caption = 'Length: '
    end
    object edtLength: TEdit
      Left = 127
      Top = 21
      Width = 50
      Height = 21
      Enabled = False
      TabOrder = 0
      Text = '2 s'
    end
  end
  object btnAdd: TButton
    Left = 8
    Top = 183
    Width = 89
    Height = 25
    Caption = 'Ok'
    ModalResult = 1
    TabOrder = 2
  end
  object btnCancel: TButton
    Left = 120
    Top = 183
    Width = 89
    Height = 25
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 3
  end
  object upActions: TUpDown
    Left = 185
    Top = 65
    Width = 17
    Height = 25
    Max = 20
    TabOrder = 4
    OnClick = upActionsClick
  end
  object upLength: TUpDown
    Left = 186
    Top = 138
    Width = 17
    Height = 25
    Min = 1
    Max = 60
    Position = 1
    TabOrder = 5
    OnClick = upLengthClick
  end
end
