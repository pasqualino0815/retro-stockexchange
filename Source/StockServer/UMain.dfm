object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'Stock Exchange Server'
  ClientHeight = 363
  ClientWidth = 509
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = mmMain
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object grpStocks: TGroupBox
    Left = 8
    Top = 80
    Width = 265
    Height = 252
    Caption = 'Stocks'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object sgStocks: TStringGrid
      Left = 2
      Top = 18
      Width = 261
      Height = 232
      Align = alClient
      ColCount = 4
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
      ColWidths = (
        60
        65
        56
        71)
    end
  end
  object pnlListen: TPanel
    Left = 0
    Top = 0
    Width = 509
    Height = 41
    Align = alTop
    TabOrder = 1
    object btnListen: TButton
      Left = 8
      Top = 9
      Width = 106
      Height = 25
      Caption = 'Start Listening'
      TabOrder = 0
      OnClick = btnListenClick
    end
  end
  object btnRemove: TButton
    Left = 84
    Top = 47
    Width = 64
    Height = 25
    Caption = 'Remove'
    TabOrder = 2
    OnClick = btnRemoveClick
  end
  object btnAdd: TButton
    Left = 8
    Top = 47
    Width = 70
    Height = 25
    Caption = 'Add'
    TabOrder = 3
    OnClick = btnAddClick
  end
  object GroupBox1: TGroupBox
    Left = 295
    Top = 83
    Width = 202
    Height = 252
    Caption = 'Users'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    object sgUsers: TStringGrid
      Left = 2
      Top = 18
      Width = 198
      Height = 232
      Align = alClient
      ColCount = 2
      DefaultRowHeight = 18
      FixedCols = 0
      RowCount = 2
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
      ColWidths = (
        84
        106)
    end
  end
  object btnRemoveUser: TButton
    Left = 422
    Top = 47
    Width = 75
    Height = 25
    Caption = 'Remove'
    TabOrder = 5
    OnClick = btnRemoveUserClick
  end
  object Button1: TButton
    Left = 154
    Top = 47
    Width = 119
    Height = 25
    Caption = 'Virtual Player (Sell ALL)'
    TabOrder = 6
    OnClick = Button1Click
  end
  object mmMain: TMainMenu
    Left = 184
    Top = 112
    object mmFile: TMenuItem
      Caption = '&File'
      object mmiQuit: TMenuItem
        Caption = '&Quit'
      end
    end
    object Options1: TMenuItem
      Caption = '&Options'
      object mmiStockOptions: TMenuItem
        Caption = '&Stocks...'
        OnClick = mmiStockOptionsClick
      end
    end
  end
  object idClientServer: TIdCmdTCPServer
    Bindings = <>
    DefaultPort = 0
    CommandHandlers = <
      item
        CmdDelimiter = ' '
        Command = 'CREATE'
        Disconnect = False
        Name = 'idCmdCREATE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers0Command
      end
      item
        CmdDelimiter = ' '
        Command = 'DELETE'
        Disconnect = False
        Name = 'idCmdDelte'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers1Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LOGIN'
        Disconnect = False
        Name = 'idCmdLogin'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers2Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LIST'
        Disconnect = False
        Name = 'idCmdLIST'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers3Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LISTME'
        Disconnect = False
        Name = 'idCmdLISTME'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers4Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LISTCLIENTS'
        Disconnect = False
        Name = 'idCmdLISTCLIENTS'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers5Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LISTCLIENT'
        Disconnect = False
        Name = 'idCmdLISTCLIENT'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers6Command
      end
      item
        CmdDelimiter = ' '
        Command = 'BUY'
        Disconnect = False
        Name = 'idCmdBUY'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers7Command
      end
      item
        CmdDelimiter = ' '
        Command = 'SELL'
        Disconnect = False
        Name = 'idCmdSELL'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers8Command
      end>
    ExceptionReply.Code = '500'
    ExceptionReply.Text.Strings = (
      'Unknown Internal Error')
    Greeting.Code = '200'
    Greeting.Text.Strings = (
      'Welcome')
    HelpReply.Code = '100'
    HelpReply.Text.Strings = (
      'Help follows')
    MaxConnectionReply.Code = '300'
    MaxConnectionReply.Text.Strings = (
      'Too many connections. Try again later.')
    ReplyTexts = <>
    ReplyUnknownCommand.Code = '400'
    ReplyUnknownCommand.Text.Strings = (
      'Unknown Command')
    Left = 96
    Top = 88
  end
  object idBankClient: TIdCmdTCPClient
    ConnectTimeout = 0
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    CommandHandlers = <
      item
        CmdDelimiter = ' '
        Command = 'ACKGET'
        Disconnect = False
        Name = 'idCmdACKGET'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers0Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKSET'
        Disconnect = False
        Name = 'idCmdACKSET'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers1Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKGET'
        Disconnect = False
        Name = 'idCmdNACKGET'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers2Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKSET'
        Disconnect = False
        Name = 'idCmdNACKSET'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers3Command
      end>
    ExceptionReply.Code = '500'
    ExceptionReply.Text.Strings = (
      'Unknown Internal Error')
    Left = 128
    Top = 96
  end
  object tmRound: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = tmRoundTimer
    Left = 120
    Top = 112
  end
end
