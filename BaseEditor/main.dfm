object MainForm: TMainForm
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
  PixelsPerInch = 96
  TextHeight = 13
  object pTop: TPanel
    Left = 0
    Top = 0
    Width = 614
    Height = 57
    Align = alTop
    TabOrder = 0
    ExplicitWidth = 663
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
      ExplicitLeft = 624
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
      ExplicitLeft = 2
      ExplicitTop = -1
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
      ExplicitTop = 6
      ExplicitWidth = 529
    end
    object SpinButton1: TSpinButton
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
      ExplicitLeft = 65
      ExplicitTop = 2
    end
  end
  object pAnswers: TPanel
    Left = 0
    Top = 57
    Width = 289
    Height = 347
    Align = alLeft
    Caption = 'pAnswers'
    TabOrder = 1
    ExplicitHeight = 404
    object lstAnswers: TCheckListBox
      AlignWithMargins = True
      Left = 4
      Top = 36
      Width = 281
      Height = 307
      Margins.Top = 0
      OnClickCheck = lstAnswersClickCheck
      Align = alClient
      ItemHeight = 13
      Items.Strings = (
        'Etiam convallis ipsum luctus neque amet'
        'Pellentesque habitant morbi turpis duis')
      TabOrder = 0
      OnDblClick = lstAnswersDblClick
      ExplicitTop = 31
      ExplicitWidth = 305
      ExplicitHeight = 344
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
      Caption = 'pAddAnswer'
      TabOrder = 1
      ExplicitLeft = 0
      ExplicitTop = 57
      ExplicitWidth = 663
      object btnAddAnswer: TButton
        AlignWithMargins = True
        Left = 258
        Top = 4
        Width = 25
        Height = 24
        Margins.Left = 0
        Align = alRight
        Caption = 'v'
        TabOrder = 0
        OnClick = btnAddAnswerClick
        ExplicitLeft = 634
      end
      object edAnswer: TEdit
        AlignWithMargins = True
        Left = 4
        Top = 4
        Width = 254
        Height = 24
        Margins.Right = 0
        Align = alClient
        MaxLength = 40
        TabOrder = 1
        Text = 'Integer vulputate, lacus vel massa nunc.'
        OnKeyDown = edAnswerKeyDown
        ExplicitWidth = 630
        ExplicitHeight = 21
      end
    end
  end
  object pQuestions: TPanel
    Left = 289
    Top = 57
    Width = 325
    Height = 347
    Align = alClient
    Caption = 'pQuestions'
    TabOrder = 2
    ExplicitLeft = 313
    ExplicitWidth = 350
    ExplicitHeight = 404
    object lstQuestions: TListBox
      AlignWithMargins = True
      Left = 4
      Top = 31
      Width = 317
      Height = 312
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      ExplicitLeft = 6
      ExplicitTop = 54
      ExplicitWidth = 282
      ExplicitHeight = 268
    end
    object edSearch: TEdit
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 317
      Height = 21
      Align = alTop
      TabOrder = 1
      Text = 'edSearch'
      ExplicitLeft = 2
      ExplicitTop = 2
      ExplicitWidth = 121
    end
  end
end
