object fmMain: TfmMain
  Left = 0
  Top = 0
  Caption = 'App'
  ClientHeight = 561
  ClientWidth = 984
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 368
    Top = 16
    Width = 228
    Height = 35
    Caption = #1044#1086#1073#1088#1086' '#1087#1086#1078#1072#1083#1086#1074#1072#1090#1100'!'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Sylfaen'
    Font.Style = []
    ParentFont = False
  end
  object lbDecryptionStatus: TLabel
    Left = 551
    Top = 517
    Width = 91
    Height = 13
    Caption = 'lbDecryptionStatus'
    Visible = False
  end
  object lbEncryptionStatus: TLabel
    Left = 464
    Top = 517
    Width = 90
    Height = 13
    Caption = 'lbEncryptionStatus'
    Visible = False
  end
  object lbCipherStatus: TLabel
    Left = 32
    Top = 517
    Width = 70
    Height = 13
    Caption = 'lbCipherStatus'
    Visible = False
  end
  object memInput: TMemo
    Left = 32
    Top = 120
    Width = 449
    Height = 345
    TabOrder = 0
  end
  object memOutput: TMemo
    Left = 504
    Top = 120
    Width = 449
    Height = 345
    Lines.Strings = (
      '')
    TabOrder = 1
  end
  object btOpen: TButton
    Left = 32
    Top = 80
    Width = 81
    Height = 34
    Caption = #1054#1090#1082#1088#1099#1090#1100
    TabOrder = 2
    OnClick = btOpenClick
  end
  object btSave: TButton
    Left = 504
    Top = 80
    Width = 89
    Height = 34
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 3
    OnClick = btSaveClick
  end
  object cbСipher: TComboBox
    Left = 32
    Top = 488
    Width = 137
    Height = 21
    Hint = #1052#1077#1090#1086#1076' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
    Style = csDropDownList
    ParentShowHint = False
    ShowHint = False
    TabOrder = 4
    TextHint = #1052#1077#1090#1086#1076' '#1096#1080#1092#1088#1086#1074#1072#1085#1080#1103
    Items.Strings = (
      #1057#1090#1086#1083#1073#1094#1086#1074#1099#1081' '#1084#1077#1090#1086#1076
      #1040#1083#1075#1086#1088#1080#1090#1084' '#1042#1080#1078#1077#1085#1077#1088#1072)
  end
  object editKeyWord: TEdit
    Left = 208
    Top = 488
    Width = 225
    Height = 21
    TabOrder = 5
    TextHint = #1050#1083#1102#1095#1077#1074#1086#1077' '#1089#1083#1086#1074#1086'...'
  end
  object btEncrypt: TButton
    Left = 464
    Top = 486
    Width = 81
    Height = 25
    Caption = #1047#1072#1096#1080#1092#1088#1086#1074#1072#1090#1100
    TabOrder = 6
    OnClick = btEncryptClick
  end
  object btDecrypt: TButton
    Left = 551
    Top = 486
    Width = 81
    Height = 25
    Caption = #1044#1077#1096#1080#1092#1088#1086#1074#1072#1090#1100
    TabOrder = 7
    OnClick = btDecryptClick
  end
  object odOpenFile: TOpenDialog
    DefaultExt = '*.txt'
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099'|*.txt'
    Left = 712
    Top = 16
  end
  object sdSaveFile: TSaveDialog
    Filter = #1058#1077#1082#1089#1090#1086#1074#1099#1077' '#1092#1072#1081#1083#1099'|*.txt'
    Left = 792
    Top = 16
  end
end
