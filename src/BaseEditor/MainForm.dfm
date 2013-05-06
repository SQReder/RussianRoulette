object F: TF
  AlignWithMargins = True
  Left = 0
  Top = 0
  Caption = 'Base editor'
  ClientHeight = 386
  ClientWidth = 615
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = menuMain
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter2: TSplitter
    Left = 0
    Top = 336
    Width = 615
    Height = 6
    Cursor = crVSplit
    Align = alBottom
    AutoSnap = False
    ResizeStyle = rsUpdate
    ExplicitTop = 502
    ExplicitWidth = 512
  end
  object PanelContent: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 0
    Width = 609
    Height = 336
    Margins.Top = 0
    Margins.Bottom = 0
    Align = alClient
    AutoSize = True
    BevelOuter = bvNone
    Constraints.MinHeight = 300
    Ctl3D = True
    ParentColor = True
    ParentCtl3D = False
    TabOrder = 0
    ExplicitTop = 30
    ExplicitHeight = 300
    object Splitter1: TSplitter
      Left = 200
      Top = 0
      Width = 6
      Height = 336
      AutoSnap = False
      MinSize = 200
      ResizeStyle = rsUpdate
      ExplicitLeft = 216
      ExplicitTop = -3
      ExplicitHeight = 345
    end
    object PanelEditor: TPanel
      Left = 206
      Top = 0
      Width = 403
      Height = 336
      Align = alClient
      BevelOuter = bvNone
      Caption = 'PanelEditor'
      Constraints.MinWidth = 200
      ParentColor = True
      TabOrder = 0
      ExplicitTop = 3
      object Label2: TLabel
        AlignWithMargins = True
        Left = 3
        Top = 49
        Width = 397
        Height = 13
        Align = alTop
        Caption = 'Question'
        ExplicitTop = 3
        ExplicitWidth = 43
      end
      object Label1: TLabel
        AlignWithMargins = True
        Left = 3
        Top = 114
        Width = 397
        Height = 13
        Align = alTop
        Caption = 'Answers'
        ExplicitTop = 49
        ExplicitWidth = 41
      end
      object Label5: TLabel
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 397
        Height = 13
        Align = alTop
        Caption = 'Round'
        ExplicitLeft = 6
      end
      object mQuestion: TMemo
        AlignWithMargins = True
        Left = 3
        Top = 68
        Width = 397
        Height = 40
        Align = alTop
        TabOrder = 0
      end
      object mAnswers: TMemo
        AlignWithMargins = True
        Left = 3
        Top = 133
        Width = 397
        Height = 200
        Align = alClient
        TabOrder = 1
        ExplicitLeft = 6
        ExplicitTop = 114
        ExplicitHeight = 189
      end
      object cbRound: TComboBox
        AlignWithMargins = True
        Left = 3
        Top = 22
        Width = 397
        Height = 21
        Align = alTop
        Style = csDropDownList
        ItemIndex = 4
        TabOrder = 2
        Text = 'Final'
        Items.Strings = (
          '1'
          '2'
          '3'
          '4'
          'Final')
        ExplicitLeft = 6
      end
    end
    object PanelQuestions: TPanel
      Left = 0
      Top = 0
      Width = 200
      Height = 336
      Align = alLeft
      BevelOuter = bvNone
      Caption = 'PanelQuestions'
      Constraints.MinWidth = 200
      ParentColor = True
      TabOrder = 1
      ExplicitHeight = 467
      object Label3: TLabel
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 194
        Height = 13
        Align = alTop
        Caption = 'Filter'
        ExplicitWidth = 24
      end
      object Label4: TLabel
        AlignWithMargins = True
        Left = 3
        Top = 49
        Width = 194
        Height = 13
        Align = alTop
        Caption = 'Questions'
        ExplicitWidth = 48
      end
      object edQuestionFilter: TEdit
        AlignWithMargins = True
        Left = 3
        Top = 22
        Width = 194
        Height = 21
        Align = alTop
        TabOrder = 0
      end
      object ListBox1: TListBox
        AlignWithMargins = True
        Left = 3
        Top = 65
        Width = 194
        Height = 268
        Margins.Top = 0
        Align = alClient
        ItemHeight = 13
        TabOrder = 1
        ExplicitHeight = 399
      end
    end
  end
  object PanelBottom: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 342
    Width = 609
    Height = 41
    Margins.Top = 0
    Align = alBottom
    BevelOuter = bvNone
    Ctl3D = True
    ParentColor = True
    ParentCtl3D = False
    TabOrder = 1
    ExplicitTop = 503
    ExplicitWidth = 506
    object lstLog: TListBox
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 603
      Height = 35
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      ExplicitWidth = 500
    end
  end
  object menuMain: TMainMenu
    Left = 160
    object mFile: TMenuItem
      Caption = '&File'
      object mExit: TMenuItem
        Caption = 'E&xit'
      end
    end
  end
end
