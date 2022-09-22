object FormSearch: TFormSearch
  Left = 0
  Top = 0
  Caption = 'FormSearch'
  ClientHeight = 299
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lbByGroup: TLabel
    Left = 24
    Top = 29
    Width = 87
    Height = 13
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1075#1088#1091#1087#1087#1077':'
  end
  object lbByReceiveDate: TLabel
    Left = 24
    Top = 88
    Width = 134
    Height = 13
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1076#1072#1090#1077' '#1087#1086#1083#1091#1095#1077#1085#1080#1103':'
  end
  object lbByReturnDate: TLabel
    Left = 24
    Top = 141
    Width = 139
    Height = 13
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1076#1072#1090#1077' '#1080#1089#1087#1086#1083#1085#1077#1085#1080#1103':'
  end
  object lbGroupSearchWarning: TLabel
    Left = 276
    Top = 51
    Width = 145
    Height = 13
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1075#1088#1091#1087#1087#1091' '#1076#1083#1103' '#1087#1086#1080#1089#1082#1072'!'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object dtpReceiveDateSearch: TDateTimePicker
    Left = 24
    Top = 107
    Width = 186
    Height = 21
    Date = 44689.000000000000000000
    Time = 0.913764131946663800
    TabOrder = 0
  end
  object dtpReturnDateSearch: TDateTimePicker
    Left = 24
    Top = 160
    Width = 186
    Height = 21
    Date = 44689.000000000000000000
    Time = 0.913764131946663800
    TabOrder = 1
  end
  object cbGroupSearch: TComboBox
    Left = 24
    Top = 48
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 2
    TextHint = #1043#1088#1091#1087#1087#1072'...'
    Items.Strings = (
      #1058#1077#1083#1077#1074#1080#1079#1086#1088
      #1058#1077#1083#1077#1092#1086#1085
      #1050#1086#1084#1087#1100#1102#1090#1077#1088
      #1053#1086#1091#1090#1073#1091#1082)
  end
  object btClose: TButton
    Left = 24
    Top = 248
    Width = 81
    Height = 33
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 3
    OnClick = btCloseClick
  end
  object btByReturnDate: TButton
    Left = 232
    Top = 156
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 4
    OnClick = btByReturnDateClick
  end
  object btByReceiveDate: TButton
    Left = 232
    Top = 107
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 5
    OnClick = btByReceiveDateClick
  end
  object btByGroup: TButton
    Left = 192
    Top = 46
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 6
    OnClick = btByGroupClick
  end
end
