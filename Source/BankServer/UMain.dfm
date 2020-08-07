object frmMain: TfrmMain
  Left = 367
  Top = 217
  Caption = 'Bank Server'
  ClientHeight = 252
  ClientWidth = 669
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object pnlListen: TPanel
    Left = 0
    Top = 0
    Width = 669
    Height = 38
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 288
      Top = 12
      Width = 32
      Height = 13
      Caption = 'Salary:'
    end
    object Label2: TLabel
      Left = 416
      Top = 12
      Width = 29
      Height = 13
      Caption = 'Timer:'
    end
    object btnListen: TButton
      Left = 7
      Top = 7
      Width = 99
      Height = 25
      Caption = 'Start Listening'
      TabOrder = 0
      OnClick = btnListenClick
    end
    object chkActiveUsers: TCheckBox
      Left = 123
      Top = 11
      Width = 134
      Height = 17
      Caption = 'Show Inactive Users'
      TabOrder = 1
      OnClick = chkActiveUsersClick
    end
    object edtSalary: TEdit
      Left = 326
      Top = 9
      Width = 51
      Height = 21
      Enabled = False
      TabOrder = 2
      Text = '100 '#8364
    end
    object edtTimer: TEdit
      Left = 451
      Top = 9
      Width = 30
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = '10 s'
    end
    object upTimer: TUpDown
      Left = 480
      Top = 7
      Width = 17
      Height = 25
      Min = 1
      Max = 200
      Position = 10
      TabOrder = 4
      OnClick = upTimerClick
    end
    object upSalary: TUpDown
      Left = 376
      Top = 7
      Width = 17
      Height = 25
      Min = 50
      Max = 1000
      Increment = 50
      Position = 100
      TabOrder = 5
      OnClick = upSalaryClick
    end
  end
  object pnlLog: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 41
    Width = 663
    Height = 208
    Align = alClient
    TabOrder = 1
    object memLog: TMemo
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 345
      Height = 200
      Hint = 'Server Log'
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ReadOnly = True
      ScrollBars = ssVertical
      ShowHint = True
      TabOrder = 0
    end
    object lbClients: TListBox
      Left = 352
      Top = 1
      Width = 310
      Height = 206
      Align = alRight
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ItemHeight = 14
      ParentFont = False
      TabOrder = 1
    end
  end
  object idClientServer: TIdCmdTCPServer
    Bindings = <>
    DefaultPort = 12345
    OnConnect = idClientServerConnect
    OnDisconnect = idClientServerDisconnect
    CommandHandlers = <
      item
        CmdDelimiter = ' '
        Command = 'CREATE'
        Description.Strings = (
          'create '
          'Creates a user account')
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
        Name = 'idCmdDELETE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers1Command
      end
      item
        CmdDelimiter = ' '
        Command = 'GETAMOUNT'
        Disconnect = False
        Name = 'idCmdGETAMOUNT'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers2Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LOGIN'
        Disconnect = False
        Name = 'idCmdLOGIN'
        NormalReply.Code = '200'
        NormalReply.Text.Strings = (
          'AMOUNT 1000')
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers3Command
      end
      item
        CmdDelimiter = ' '
        Command = 'MOVE'
        Disconnect = False
        Name = 'idCmdMOVE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
      end
      item
        CmdDelimiter = ' '
        Command = 'GETALLAMOUNTS'
        Disconnect = False
        Name = 'idCmdGETALLAMOUNTS'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idClientServerCommandHandlers5Command
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
    Left = 64
    Top = 56
  end
  object tmAmounts: TTimer
    Enabled = False
    Interval = 10000
    OnTimer = tmAmountsTimer
    Left = 96
    Top = 56
  end
  object idStockServer: TIdCmdTCPServer
    Bindings = <>
    DefaultPort = 12222
    ReuseSocket = rsFalse
    CommandHandlers = <
      item
        CmdDelimiter = ' '
        Command = 'GET'
        Disconnect = False
        Name = 'idCmdGET'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockServerCommandHandlers0Command
      end
      item
        CmdDelimiter = ' '
        Command = 'SET'
        Disconnect = False
        Name = 'idCmdSET'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockServerCommandHandlers1Command
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
    Left = 128
    Top = 56
  end
end
