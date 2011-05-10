object f: Tf
  Left = 0
  Top = 0
  Caption = 'Roulette Base Editor'
  ClientHeight = 404
  ClientWidth = 614
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object pTop: TPanel
    Left = 0
    Top = 0
    Width = 614
    Height = 57
    Align = alTop
    TabOrder = 0
    object btnAddQuestionToBase: TButton
      AlignWithMargins = True
      Left = 575
      Top = 4
      Width = 35
      Height = 49
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
      Width = 501
      Height = 49
      Margins.Right = 0
      TabStop = False
      Align = alClient
      Lines.Strings = (
        
          'Fusce facilisis, risus in venenatis commodo, purus magna ornare ' +
          'metus, a aliquam mi elit eget purus. '
        
          'Etiam porttitor viverra mi et fringilla. Aenean tincidunt lacus ' +
          'quis dui laoreet in convallis leo molestie. '
        'Cras faucibus odio id urna adipiscing id amet')
      TabOrder = 2
      WantReturns = False
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
    Height = 289
    Align = alLeft
    TabOrder = 1
    object lstAnswers: TCheckListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 281
      Height = 249
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
      object edAnswer: TEdit
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 254
        Height = 24
        Margins.Right = 0
        Align = alClient
        MaxLength = 40
        TabOrder = 0
        Text = 'Integer vulputate, lacus vel massa nunc.'
        OnKeyDown = edAnswerKeyDown
        ExplicitHeight = 21
      end
      object btnAddAnswer: TButton
        AlignWithMargins = True
        Left = 258
        Top = 4
        Width = 25
        Height = 24
        Margins.Left = 0
        Align = alRight
        Caption = 'v'
        TabOrder = 1
        OnClick = btnAddAnswerClick
      end
    end
  end
  object pQuestions: TPanel
    Left = 289
    Top = 57
    Width = 325
    Height = 289
    Align = alClient
    TabOrder = 2
    object lstQuestions: TListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 317
      Height = 249
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnDblClick = lstQuestionsDblClick
      ExplicitTop = 31
      ExplicitHeight = 254
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 323
      Height = 32
      Align = alTop
      TabOrder = 1
      object edSearch: TEdit
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 276
        Height = 24
        Margins.Right = 0
        Align = alClient
        TabOrder = 0
        Text = 'edSearch'
        OnChange = edSearchChange
        ExplicitWidth = 261
      end
      object btnClearSearchField: TButton
        AlignWithMargins = True
        Left = 280
        Top = 4
        Width = 39
        Height = 24
        Margins.Left = 0
        Align = alRight
        Caption = 'Clear'
        TabOrder = 1
        OnClick = btnClearSearchFieldClick
      end
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 385
    Width = 614
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
    Top = 349
    Width = 608
    Height = 33
    Align = alBottom
    TabOrder = 4
  end
end
