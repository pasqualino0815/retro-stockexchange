object frmMain: TfrmMain
  Left = 192
  Top = 114
  Caption = 'Client'
  ClientHeight = 600
  ClientWidth = 739
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = mmMain
  OldCreateOrder = False
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object pnlMain: TPanel
    Left = 0
    Top = 21
    Width = 739
    Height = 579
    Margins.Left = 0
    Margins.Top = 0
    Margins.Right = 0
    Margins.Bottom = 0
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    object pnlStockExchange: TPanel
      Left = 321
      Top = 0
      Width = 418
      Height = 579
      Align = alClient
      TabOrder = 0
      object lblStockExchange: TLabel
        Left = 16
        Top = 46
        Width = 63
        Height = 20
        Caption = 'Stocks:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label2: TLabel
        Left = 16
        Top = 190
        Width = 109
        Height = 20
        Caption = 'Own Stocks:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label3: TLabel
        Left = 16
        Top = 327
        Width = 105
        Height = 20
        Caption = 'Client Stats:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object StatusBar: TStatusBar
        Left = 1
        Top = 559
        Width = 416
        Height = 19
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        Panels = <
          item
            Text = 'Not Connected'
            Width = 50
          end>
        UseSystemFont = False
      end
      object sgStocks: TStringGrid
        Left = 16
        Top = 72
        Width = 320
        Height = 105
        ColCount = 4
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        ScrollBars = ssVertical
        TabOrder = 1
        ColWidths = (
          64
          87
          78
          81)
      end
      object sgMyStocks: TStringGrid
        Left = 16
        Top = 216
        Width = 320
        Height = 105
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        ScrollBars = ssVertical
        TabOrder = 2
        ColWidths = (
          64
          73
          59
          50
          64)
      end
      object btnBuy: TButton
        Left = 342
        Top = 103
        Width = 59
        Height = 25
        Caption = 'Buy'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        OnClick = btnBuyClick
      end
      object btnSell: TButton
        Left = 342
        Top = 245
        Width = 59
        Height = 25
        Caption = 'Sell'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 4
        OnClick = btnSellClick
      end
      object sgClients: TStringGrid
        Left = 16
        Top = 353
        Width = 320
        Height = 112
        ColCount = 2
        DefaultRowHeight = 18
        FixedCols = 0
        RowCount = 2
        ScrollBars = ssVertical
        TabOrder = 5
        ColWidths = (
          147
          166)
      end
      object Button3: TButton
        Left = 342
        Top = 384
        Width = 59
        Height = 25
        Caption = 'Show'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        OnClick = Button3Click
      end
      object btnRefreshOwnStocks: TButton
        Left = 342
        Top = 214
        Width = 59
        Height = 25
        Caption = 'Refresh'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        OnClick = btnRefreshOwnStocksClick
      end
      object btnRefreshStocks: TButton
        Left = 342
        Top = 72
        Width = 59
        Height = 25
        Caption = 'Refresh'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 8
        OnClick = btnRefreshStocksClick
      end
      object btnRefreshClients: TButton
        Left = 342
        Top = 353
        Width = 59
        Height = 25
        Caption = 'Refresh'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 9
        OnClick = btnRefreshClientsClick
      end
      object pnlStockConnection: TPanel
        Left = 1
        Top = 1
        Width = 416
        Height = 34
        Align = alTop
        TabOrder = 10
        object Label1: TLabel
          Left = 5
          Top = 5
          Width = 151
          Height = 24
          Caption = 'Stock Exchange'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'MS Reference Sans Serif'
          Font.Style = []
          ParentFont = False
        end
      end
    end
    object pnlBanks: TPanel
      Left = 0
      Top = 0
      Width = 321
      Height = 579
      Align = alLeft
      Caption = 'pnlBanks'
      TabOrder = 1
      object pnlBankLabel: TPanel
        Left = 1
        Top = 1
        Width = 319
        Height = 34
        Align = alTop
        TabOrder = 0
        object lblBanks: TLabel
          Left = 8
          Top = 5
          Width = 57
          Height = 24
          Caption = 'Banks'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'MS Reference Sans Serif'
          Font.Style = []
          ParentFont = False
        end
      end
      object pcBanks: TPageControl
        Left = 1
        Top = 35
        Width = 319
        Height = 543
        Align = alClient
        TabOrder = 1
      end
    end
  end
  object edtMsg: TEdit
    Left = 0
    Top = 0
    Width = 739
    Height = 21
    Align = alTop
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindow
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object mmMain: TMainMenu
    Left = 192
    Top = 32
    object mmFile: TMenuItem
      Caption = '&File'
      object mmiQuit: TMenuItem
        Caption = '&Quit'
        OnClick = mmiQuitClick
      end
    end
    object mmBank: TMenuItem
      Caption = '&Bank'
      object mmiConnectBank: TMenuItem
        Caption = '&Connect...'
        OnClick = mmiConnectBankClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object mmiCreateBankAccount: TMenuItem
        Caption = 'Create &Account...'
        OnClick = mmiCreateBankAccountClick
      end
      object mmiDeleteBankAccount: TMenuItem
        Caption = 'Delete Account...'
        OnClick = mmiDeleteBankAccountClick
      end
    end
    object mmStockExchange: TMenuItem
      Caption = '&StockExchange'
      object mmiConnectStockExchange: TMenuItem
        Caption = '&Connect...'
        OnClick = mmiConnectStockExchangeClick
      end
      object mmiDisconnectStockExchange: TMenuItem
        Caption = '&Disconnect'
        OnClick = mmiDisconnectStockExchangeClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object mmiCreateStockAccount: TMenuItem
        Caption = 'Create &Account...'
        OnClick = mmiCreateStockAccountClick
      end
      object mmiDeleteStockAccount: TMenuItem
        Caption = '&Delete Account...'
        OnClick = mmiDeleteStockAccountClick
      end
    end
  end
  object idBankClient: TIdCmdTCPClient
    OnStatus = idBankClientStatus
    ConnectTimeout = 0
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    CommandHandlers = <
      item
        CmdDelimiter = ' '
        Command = 'AMOUNT'
        Disconnect = False
        Name = 'idCmdAMOUNT'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers0Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKLOGIN'
        Disconnect = False
        Name = 'idCmdNACKLOGIN'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers1Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKLOGIN'
        Disconnect = False
        Name = 'idCmdACKLOGIN'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers2Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKCREATE'
        Disconnect = False
        Name = 'idCmdACKCREATE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers3Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKCREATE'
        Disconnect = False
        Name = 'idCmdNACKCREATE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers4Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ALLAMOUNTS'
        Disconnect = False
        Name = 'idCmdALLAMOUNTS'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers5Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKDELETE'
        Disconnect = False
        Name = 'idCmdNACKDELETE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers6Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKDELETE'
        Disconnect = False
        Name = 'idCmdACKDELETE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idBankClientCommandHandlers7Command
      end>
    ExceptionReply.Code = '500'
    ExceptionReply.Text.Strings = (
      'Unknown Internal Error')
    Left = 224
    Top = 32
  end
  object tmUpdateAmounts: TTimer
    Interval = 2000
    OnTimer = tmUpdateAmountsTimer
    Left = 160
    Top = 32
  end
  object idStockClient: TIdCmdTCPClient
    OnStatus = idStockClientStatus
    ConnectTimeout = 0
    IPVersion = Id_IPv4
    Port = 0
    ReadTimeout = -1
    CommandHandlers = <
      item
        CmdDelimiter = ' '
        Command = 'NACKLOGIN'
        Disconnect = False
        Name = 'idCmdNACKLOGIN'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers0Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKLOGIN'
        Disconnect = False
        Name = 'idCmdACKLOGIN'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers1Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKCREATE'
        Disconnect = False
        Name = 'idCmdACKCREATE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers2Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKCREATE'
        Disconnect = False
        Name = 'idCmdNACKCREATE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers3Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKDELETE'
        Disconnect = False
        Name = 'idCmdNACKDELETE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers4Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKDELETE'
        Disconnect = False
        Name = 'idCmdACKDELETE'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers5Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LIST'
        Disconnect = False
        Name = 'idCmdLIST'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers6Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LISTME'
        Disconnect = False
        Name = 'idCmdLISTME'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers7Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LISTCLIENTS'
        Disconnect = False
        Name = 'idCmdLISTCLIENTS'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers8Command
      end
      item
        CmdDelimiter = ' '
        Command = 'LISTCLIENT'
        Disconnect = False
        Name = 'idCmdLISTCLIENT'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers9Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKBUY'
        Disconnect = False
        Name = 'TIdCommandHandler10'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers10Command
      end
      item
        CmdDelimiter = ' '
        Command = 'ACKSELL'
        Disconnect = False
        Name = 'TIdCommandHandler11'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers11Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKBUY'
        Disconnect = False
        Name = 'idCmdNACKBUY'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers12Command
      end
      item
        CmdDelimiter = ' '
        Command = 'NACKSELL'
        Disconnect = False
        Name = 'idCmdNACKSELL'
        NormalReply.Code = '200'
        ParamDelimiter = ' '
        Tag = 0
        OnCommand = idStockClientCommandHandlers13Command
      end>
    ExceptionReply.Code = '500'
    ExceptionReply.Text.Strings = (
      'Unknown Internal Error')
    Left = 440
    Top = 32
  end
end
