object f: Tf
  Left = 0
  Top = 0
  Caption = 'Russian Roulette Base Editor v0.0.0.0.0.0(.0)'
  ClientHeight = 371
  ClientWidth = 618
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
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pTop: TPanel
    Left = 0
    Top = 0
    Width = 618
    Height = 57
    Align = alTop
    TabOrder = 0
    object btnAddQuestionToBase: TButton
      AlignWithMargins = True
      Left = 579
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
    object edRound: TEdit
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 49
      Height = 49
      Margins.Right = 0
      Align = alLeft
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -35
      Font.Name = 'Tahoma'
      Font.Style = []
      MaxLength = 1
      NumbersOnly = True
      ParentFont = False
      TabOrder = 1
      Text = '0'
      OnChange = edRoundChange
    end
    object mQuestion: TMemo
      AlignWithMargins = True
      Left = 74
      Top = 4
      Width = 505
      Height = 49
      Margins.Right = 0
      Align = alClient
      Lines.Strings = (
        'Some question')
      MaxLength = 255
      TabOrder = 2
      WantReturns = False
      OnEnter = FieldEnter
      OnExit = FieldExit
    end
    object SpinRound: TSpinButton
      AlignWithMargins = True
      Left = 53
      Top = 4
      Width = 15
      Height = 49
      Margins.Left = 0
      Align = alLeft
      DownGlyph.Data = {
        0E010000424D0E01000000000000360000002800000009000000060000000100
        200000000000D800000000000000000000000000000000000000008080000080
        8000008080000080800000808000008080000080800000808000008080000080
        8000008080000080800000808000000000000080800000808000008080000080
        8000008080000080800000808000000000000000000000000000008080000080
        8000008080000080800000808000000000000000000000000000000000000000
        0000008080000080800000808000000000000000000000000000000000000000
        0000000000000000000000808000008080000080800000808000008080000080
        800000808000008080000080800000808000}
      TabOrder = 3
      UpGlyph.Data = {
        0E010000424D0E01000000000000360000002800000009000000060000000100
        200000000000D800000000000000000000000000000000000000008080000080
        8000008080000080800000808000008080000080800000808000008080000080
        8000000000000000000000000000000000000000000000000000000000000080
        8000008080000080800000000000000000000000000000000000000000000080
        8000008080000080800000808000008080000000000000000000000000000080
        8000008080000080800000808000008080000080800000808000000000000080
        8000008080000080800000808000008080000080800000808000008080000080
        800000808000008080000080800000808000}
      OnDownClick = SpinRoundDownClick
      OnUpClick = SpinRoundUpClick
    end
  end
  object pAnswers: TPanel
    Left = 0
    Top = 57
    Width = 289
    Height = 256
    Align = alLeft
    TabOrder = 1
    object lstAnswers: TCheckListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 281
      Height = 216
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
    Width = 329
    Height = 256
    Align = alClient
    TabOrder = 2
    object lstQuestions: TListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 321
      Height = 216
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnDblClick = lstQuestionsDblClick
      OnKeyDown = lstQuestionsKeyDown
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 327
      Height = 32
      Align = alTop
      TabOrder = 1
      object btnClearSearchField: TButton
        AlignWithMargins = True
        Left = 284
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
        Width = 277
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
    Top = 352
    Width = 618
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
    Top = 316
    Width = 612
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
    Caption = 'Button1'
    TabOrder = 5
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
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 488
    Top = 8
  end
  object dlgSave: TSaveDialog
    Left = 440
    Top = 8
  end
end
