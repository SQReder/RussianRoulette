object SettingsForm: TSettingsForm
  Left = 474
  Top = 116
  BorderStyle = bsDialog
  Caption = #1056#1091#1089#1089#1082#1072#1103' '#1056#1091#1083#1077#1090#1082#1072': '#1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 449
  ClientWidth = 340
  Color = clBtnFace
  TransparentColorValue = clGreen
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Padding.Left = 3
  Padding.Top = 3
  Padding.Right = 3
  Padding.Bottom = 3
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gbOptions: TGroupBox
    Left = 3
    Top = 270
    Width = 334
    Height = 142
    Align = alClient
    Caption = 'gbOptions'
    TabOrder = 4
    ExplicitHeight = 197
    object lblSoundVolume: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 18
      Width = 324
      Height = 13
      Align = alTop
      AutoSize = False
      Caption = 'lblSoundVolume'
      ExplicitLeft = 3
      ExplicitWidth = 264
    end
    object lblMusicVolume: TLabel
      Left = 5
      Top = 62
      Width = 316
      Height = 13
      AutoSize = False
      Caption = 'lblMusicVolume'
    end
    object cbFullscreen: TCheckBox
      Left = 11
      Top = 112
      Width = 161
      Height = 16
      Caption = 'cbFullscreen'
      TabOrder = 0
    end
    object cbHostModeOnOff: TCheckBox
      Left = 178
      Top = 111
      Width = 151
      Height = 17
      Caption = 'cbHostModeOnOff'
      TabOrder = 1
    end
    object cbMusicOnOff: TCheckBox
      Left = 178
      Top = 81
      Width = 138
      Height = 17
      Caption = 'cbMusicOnOff'
      TabOrder = 2
      OnClick = cbMusicOnOffClick
    end
    object cbSoundOnOff: TCheckBox
      Left = 178
      Top = 37
      Width = 138
      Height = 17
      Caption = 'cbSoundOnOff'
      TabOrder = 3
      OnClick = cbSoundOnOffClick
    end
    object cbWin7Features: TCheckBox
      Left = 11
      Top = 140
      Width = 97
      Height = 17
      Caption = 'cbWin7Features'
      TabOrder = 4
      Visible = False
    end
  end
  object gbChooseQuestionBase: TGroupBox
    Left = 3
    Top = 225
    Width = 334
    Height = 45
    Align = alTop
    Caption = 'gbChooseQuestionBase'
    TabOrder = 3
    ExplicitLeft = 6
    ExplicitWidth = 331
    object addBase: TButton
      AlignWithMargins = True
      Left = 217
      Top = 18
      Width = 112
      Height = 22
      Align = alClient
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1073#1072#1079#1091
      TabOrder = 0
      OnClick = addBaseClick
      ExplicitLeft = 214
      ExplicitTop = 17
      ExplicitWidth = 109
    end
    object cmbListOfBases: TComboBox
      AlignWithMargins = True
      Left = 5
      Top = 18
      Width = 206
      Height = 21
      Align = alLeft
      Style = csDropDownList
      TabOrder = 1
    end
  end
  object gbPlayerNames: TGroupBox
    Left = 3
    Top = 3
    Width = 334
    Height = 222
    Align = alTop
    Caption = 'gbPlayerNames'
    TabOrder = 0
    ExplicitLeft = 6
    ExplicitWidth = 331
    object edPlayer0: TLabeledEdit
      Left = 9
      Top = 36
      Width = 147
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1080#1075#1088#1086#1082#1072' 1'
      TabOrder = 0
    end
    object edPlayer1: TLabeledEdit
      Left = 9
      Top = 74
      Width = 147
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1080#1075#1088#1086#1082#1072' 2'
      TabOrder = 1
    end
    object edPlayer2: TLabeledEdit
      Left = 5
      Top = 116
      Width = 147
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1080#1075#1088#1086#1082#1072' 3'
      TabOrder = 2
    end
    object edPlayer3: TLabeledEdit
      Left = 9
      Top = 153
      Width = 147
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1080#1075#1088#1086#1082#1072' 4'
      TabOrder = 3
    end
    object edPlayer4: TLabeledEdit
      Left = 9
      Top = 188
      Width = 147
      Height = 21
      EditLabel.Width = 66
      EditLabel.Height = 13
      EditLabel.Caption = #1048#1084#1103' '#1080#1075#1088#1086#1082#1072' 5'
      TabOrder = 4
    end
    object cmbPlayerType0: TComboBox
      Left = 158
      Top = 36
      Width = 163
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 5
      Text = #1063#1077#1083#1086#1074#1077#1082
      Items.Strings = (
        #1063#1077#1083#1086#1074#1077#1082
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1083#1105#1075#1082#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1087#1088#1086#1089#1090#1086#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1088#1077#1076#1085#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1099#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1077#1081#1096#1080#1081)
    end
    object cmbPlayerType1: TComboBox
      Left = 158
      Top = 74
      Width = 163
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 6
      Text = #1063#1077#1083#1086#1074#1077#1082
      Items.Strings = (
        #1063#1077#1083#1086#1074#1077#1082
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1083#1105#1075#1082#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1087#1088#1086#1089#1090#1086#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1088#1077#1076#1085#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1099#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1077#1081#1096#1080#1081)
    end
    object cmbPlayerType2: TComboBox
      Left = 158
      Top = 116
      Width = 163
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 7
      Text = #1063#1077#1083#1086#1074#1077#1082
      Items.Strings = (
        #1063#1077#1083#1086#1074#1077#1082
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1083#1105#1075#1082#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1087#1088#1086#1089#1090#1086#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1088#1077#1076#1085#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1099#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1077#1081#1096#1080#1081)
    end
    object cmbPlayerType3: TComboBox
      Left = 158
      Top = 153
      Width = 163
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 8
      Text = #1063#1077#1083#1086#1074#1077#1082
      Items.Strings = (
        #1063#1077#1083#1086#1074#1077#1082
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1083#1105#1075#1082#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1087#1088#1086#1089#1090#1086#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1088#1077#1076#1085#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1099#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1077#1081#1096#1080#1081)
    end
    object cmbPlayerType4: TComboBox
      Left = 158
      Top = 188
      Width = 163
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 9
      Text = #1063#1077#1083#1086#1074#1077#1082
      Items.Strings = (
        #1063#1077#1083#1086#1074#1077#1082
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1083#1105#1075#1082#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1087#1088#1086#1089#1090#1086#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1088#1077#1076#1085#1080#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1099#1081
        #1050#1086#1084#1087#1100#1102#1090#1077#1088' - '#1089#1083#1086#1078#1085#1077#1081#1096#1080#1081)
    end
  end
  object pButtons: TPanel
    Left = 3
    Top = 412
    Width = 334
    Height = 34
    Align = alBottom
    BevelEdges = [beTop]
    TabOrder = 1
    ExplicitLeft = 0
    ExplicitTop = 451
    object btnCancel: TButton
      AlignWithMargins = True
      Left = 164
      Top = 4
      Width = 166
      Height = 26
      Align = alClient
      Cancel = True
      Caption = 'btnCancel'
      TabOrder = 0
      OnClick = btnCancelClick
      ExplicitTop = -8
      ExplicitWidth = 156
      ExplicitHeight = 25
    end
    object btnOK: TButton
      AlignWithMargins = True
      Left = 4
      Top = 4
      Width = 154
      Height = 26
      Align = alLeft
      Cancel = True
      Caption = 'btnOK'
      TabOrder = 1
      OnClick = btnOKClick
      ExplicitLeft = 11
      ExplicitTop = -8
      ExplicitHeight = 25
    end
  end
  object tbSoundVolume: TTrackBar
    Left = 6
    Top = 307
    Width = 169
    Height = 20
    Max = 100
    ShowSelRange = False
    TabOrder = 2
    TickStyle = tsNone
    OnChange = tbSoundVolumeChange
  end
  object tbMusicVolume: TTrackBar
    Left = 6
    Top = 351
    Width = 169
    Height = 20
    Max = 100
    ShowSelRange = False
    TabOrder = 5
    TickStyle = tsNone
    OnChange = tbMusicVolumeChange
  end
  object OpenDialog1: TOpenDialog
    Left = 296
  end
end
