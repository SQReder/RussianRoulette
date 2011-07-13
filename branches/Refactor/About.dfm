object AboutForm: TAboutForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 473
  ClientWidth = 378
  Color = clBlack
  DoubleBuffered = True
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWhite
  Font.Height = -32
  Font.Name = 'FrizQuadrataCTT'
  Font.Style = []
  GlassFrame.SheetOfGlass = True
  KeyPreview = True
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 38
  object lblProjTitle: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 372
    Height = 41
    Align = alTop
    Alignment = taCenter
    AutoSize = False
    Caption = #171#1056#1091#1089#1089#1082#1072#1103' '#1088#1091#1083#1077#1090#1082#1072#187
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWhite
    Font.Height = -32
    Font.Name = 'FrizQuadrataCTT'
    Font.Style = []
    Font.Quality = fqAntialiased
    ParentFont = False
    WordWrap = True
    ExplicitLeft = -2
    ExplicitTop = 8
    ExplicitWidth = 351
  end
  object lblLicence: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 422
    Width = 372
    Height = 16
    Margins.Top = 0
    Margins.Bottom = 0
    Align = alBottom
    Alignment = taRightJustify
    Caption = #1051#1080#1094#1077#1085#1079#1080#1103' GNU GPLv3 ('#1082#1083#1080#1082#1085#1080#1090#1077', '#1095#1090#1086#1073#1099' '#1087#1088#1086#1095#1077#1089#1090#1100')'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clSilver
    Font.Height = -13
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    OnClick = lblLicenceClick
    ExplicitLeft = 24
    ExplicitWidth = 340
  end
  object Label22: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 454
    Width = 372
    Height = 16
    Margins.Top = 0
    Align = alBottom
    Alignment = taRightJustify
    Caption = #1057#1072#1081#1090' '#1080#1075#1088#1099': http://rusrul.ru'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clSilver
    Font.Height = -13
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    ExplicitLeft = 185
    ExplicitWidth = 179
  end
  object Label1: TLabel
    AlignWithMargins = True
    Left = 3
    Top = 438
    Width = 372
    Height = 16
    Margins.Top = 0
    Margins.Bottom = 0
    Align = alBottom
    Alignment = taRightJustify
    Caption = 'Copyright '#169' 2010-2011 QWERule Studios'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clSilver
    Font.Height = -13
    Font.Name = 'Verdana'
    Font.Style = []
    ParentFont = False
    ExplicitLeft = 90
    ExplicitWidth = 274
  end
end
