object SettingsForm: TSettingsForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1056#1091#1089#1089#1082#1072#1103' '#1056#1091#1083#1077#1090#1082#1072': '#1053#1072#1089#1090#1088#1086#1081#1082#1080
  ClientHeight = 470
  ClientWidth = 339
  Color = clBtnFace
  TransparentColorValue = clGreen
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object gbOptions: TGroupBox
    Left = 8
    Top = 288
    Width = 328
    Height = 137
    Caption = 'gbOptions'
    TabOrder = 12
    object lblSoundVolume: TLabel
      Left = 9
      Top = 18
      Width = 264
      Height = 13
      AutoSize = False
      Caption = 'lblSoundVolume'
    end
    object lblMusicVolume: TLabel
      Left = 9
      Top = 57
      Width = 264
      Height = 13
      AutoSize = False
      Caption = 'lblMusicVolume'
    end
  end
  object gbChooseQuestionBase: TGroupBox
    Left = 8
    Top = 236
    Width = 328
    Height = 45
    Caption = 'gbChooseQuestionBase'
    TabOrder = 11
    object addBase: TButton
      Left = 217
      Top = 17
      Width = 107
      Height = 21
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1073#1072#1079#1091
      TabOrder = 0
      OnClick = addBaseClick
    end
  end
  object btnCancel: TButton
    Left = 180
    Top = 440
    Width = 156
    Height = 25
    Cancel = True
    Caption = 'btnCancel'
    TabOrder = 0
    OnClick = btnCancelClick
  end
  object cbSoundOnOff: TCheckBox
    Left = 183
    Top = 325
    Width = 138
    Height = 17
    Caption = 'cbSoundOnOff'
    TabOrder = 1
    OnClick = cbSoundOnOffClick
  end
  object gbPlayerNames: TGroupBox
    Left = 8
    Top = 8
    Width = 328
    Height = 222
    Caption = 'gbPlayerNames'
    TabOrder = 2
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
      Left = 9
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
    object FileListBox1: TFileListBox
      Left = 141
      Top = -2
      Width = 145
      Height = 19
      ItemHeight = 13
      TabOrder = 10
      Visible = False
    end
  end
  object btnOK: TButton
    Left = 8
    Top = 440
    Width = 154
    Height = 25
    Cancel = True
    Caption = 'btnOK'
    TabOrder = 3
    OnClick = btnOKClick
  end
  object Panel1: TPanel
    Left = 8
    Top = 431
    Width = 327
    Height = 3
    BevelOuter = bvLowered
    TabOrder = 4
  end
  object cbFullscreen: TCheckBox
    Left = 17
    Top = 400
    Width = 161
    Height = 16
    Caption = 'cbFullscreen'
    TabOrder = 5
  end
  object cbWin7Features: TCheckBox
    Left = 120
    Top = 494
    Width = 97
    Height = 17
    Caption = 'cbWin7Features'
    TabOrder = 6
    Visible = False
  end
  object cmbListOfBases: TComboBox
    Left = 17
    Top = 253
    Width = 206
    Height = 21
    Style = csDropDownList
    TabOrder = 7
  end
  object cbMusicOnOff: TCheckBox
    Left = 183
    Top = 366
    Width = 138
    Height = 17
    Caption = 'cbMusicOnOff'
    TabOrder = 8
    OnClick = cbMusicOnOffClick
  end
  object cbHostModeOnOff: TCheckBox
    Left = 180
    Top = 399
    Width = 151
    Height = 17
    Caption = 'cbHostModeOnOff'
    TabOrder = 9
  end
  object tbSoundVolume: TTrackBar
    Left = 8
    Top = 323
    Width = 169
    Height = 19
    Max = 100
    ShowSelRange = False
    TabOrder = 10
    TickStyle = tsNone
    OnChange = tbSoundVolumeChange
  end
  object tbMusicVolume: TTrackBar
    Left = 8
    Top = 364
    Width = 169
    Height = 19
    Max = 100
    ShowSelRange = False
    TabOrder = 13
    TickStyle = tsNone
    OnChange = tbMusicVolumeChange
  end
  object OpenDialog1: TOpenDialog
    Left = 312
  end
end
