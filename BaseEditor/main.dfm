object f: Tf
  Left = 0
  Top = 0
  Caption = 'Russian Roulette Base Editor v0.0.0.0.0.0(.0)'
  ClientHeight = 472
  ClientWidth = 777
  Color = clBtnFace
  Constraints.MinHeight = 300
  Constraints.MinWidth = 600
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pTop: TPanel
    Left = 0
    Top = 0
    Width = 777
    Height = 57
    Align = alTop
    TabOrder = 0
    object btnAddQuestionToBase: TButton
      AlignWithMargins = True
      Left = 738
      Top = 4
      Width = 35
      Height = 49
      Hint = 'Add question to base'
      Margins.Left = 0
      Align = alRight
      Caption = 'v'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = btnAddQuestionToBaseClick
    end
    object mQuestion: TMemo
      AlignWithMargins = True
      Left = 63
      Top = 4
      Width = 675
      Height = 49
      Margins.Right = 0
      Align = alClient
      Lines.Strings = (
        'Some question')
      MaxLength = 255
      TabOrder = 1
      WantReturns = False
      OnEnter = FieldEnter
      OnExit = FieldExit
    end
    object edRound: TComboBox
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 53
      Height = 48
      Align = alLeft
      AutoCloseUp = True
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -33
      Font.Name = 'Tahoma'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      Sorted = True
      TabOrder = 2
      Text = '1'
      OnChange = edRoundChange
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        'Final')
      ExplicitTop = 7
    end
  end
  object pAnswers: TPanel
    Left = 0
    Top = 57
    Width = 289
    Height = 357
    Align = alLeft
    TabOrder = 1
    object lstAnswers: TCheckListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 281
      Height = 317
      Margins.Top = 0
      OnClickCheck = lstAnswersClickCheck
      Align = alClient
      ItemHeight = 13
      Items.Strings = (
        'Etiam convallis ipsum luctus neque amet'
        'Pellentesque habitant morbi turpis duis')
      TabOrder = 0
      OnDblClick = lstAnswersDblClick
    end
    object pAddAnswer: TPanel
      AlignWithMargins = True
      Left = 1
      Top = 1
      Width = 287
      Height = 32
      Margins.Left = 0
      Margins.Top = 0
      Margins.Right = 0
      Align = alTop
      TabOrder = 1
      object btnAddAnswer: TButton
        AlignWithMargins = True
        Left = 258
        Top = 4
        Width = 25
        Height = 24
        Hint = 'Add answer to question'
        Margins.Left = 0
        Align = alRight
        Caption = 'v'
        TabOrder = 0
        OnClick = btnAddAnswerClick
      end
      object mAnswer: TMemo
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 251
        Height = 24
        Align = alClient
        Lines.Strings = (
          'mAnswer')
        TabOrder = 1
        WantReturns = False
        OnEnter = FieldEnter
        OnExit = FieldExit
        OnKeyDown = mAnswerKeyDown
      end
    end
  end
  object pQuestions: TPanel
    Left = 289
    Top = 57
    Width = 488
    Height = 357
    Align = alClient
    TabOrder = 2
    object lstQuestions: TListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 480
      Height = 317
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnDblClick = lstQuestionsDblClick
      OnKeyDown = lstQuestionsKeyDown
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 486
      Height = 32
      Align = alTop
      TabOrder = 1
      object btnClearSearchField: TButton
        AlignWithMargins = True
        Left = 443
        Top = 4
        Width = 39
        Height = 24
        Margins.Left = 0
        Align = alRight
        Caption = 'Clear'
        TabOrder = 0
        OnClick = btnClearSearchFieldClick
      end
      object mSearch: TMemo
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 436
        Height = 24
        Align = alClient
        Lines.Strings = (
          'mSearch')
        TabOrder = 1
        WantReturns = False
        OnChange = edSearchChange
        OnEnter = FieldEnter
        OnExit = FieldExit
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 453
    Width = 777
    Height = 19
    BiDiMode = bdLeftToRight
    Panels = <
      item
        Text = 'StatusMessage'
        Width = 50
      end>
    ParentBiDiMode = False
  end
  object mComment: TMemo
    AlignWithMargins = True
    Left = 3
    Top = 417
    Width = 771
    Height = 33
    Align = alBottom
    MaxLength = 255
    TabOrder = 4
    WantReturns = False
    OnEnter = FieldEnter
    OnExit = FieldExit
  end
  object Button1: TButton
    Left = 8
    Top = 285
    Width = 75
    Height = 25
    Caption = 'TestButton'
    TabOrder = 5
    Visible = False
    OnClick = Button1Click
  end
  object MainMenu: TMainMenu
    Left = 544
    Top = 8
    object mmFile: TMenuItem
      Caption = 'File'
      object mmNewBase: TMenuItem
        Caption = 'New'
        ShortCut = 16462
        OnClick = mmNewBaseClick
      end
      object mmOpenBase: TMenuItem
        Caption = 'Open...'
        ShortCut = 16463
        OnClick = mmOpenBaseClick
      end
      object mmSaveBase: TMenuItem
        Caption = 'Save...'
        ShortCut = 16467
        OnClick = mmSaveBaseClick
      end
      object mmSaveBaseAs: TMenuItem
        Caption = 'Save as...'
        OnClick = mmSaveBaseAsClick
      end
      object mSetPass: TMenuItem
        Caption = 'Set password...'
        OnClick = mSetPassClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object mImportBase: TMenuItem
        Caption = 'Import old base...'
        OnClick = mImportBaseClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object mmExit: TMenuItem
        Caption = 'Exit'
        ShortCut = 16471
        OnClick = mmExitClick
      end
    end
    object mmAbout: TMenuItem
      Caption = 'About...'
      ShortCut = 112
    end
  end
  object dlgOpen: TOpenDialog
    Filter = 'Russian Roulette Base|*.rrb'
    InitialDir = '.'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 488
    Top = 8
  end
  object dlgSave: TSaveDialog
    Filter = 'Russian Roulette Base|*.rrb'
    InitialDir = '.'
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 440
    Top = 8
  end
end
