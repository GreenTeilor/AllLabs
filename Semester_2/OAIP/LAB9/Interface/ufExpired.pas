unit ufExpired;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls;

type
  TFormExpired = class(TForm)
    dtpExpireDate: TDateTimePicker;
    btConfirm: TButton;
    btClose: TButton;
    lbExpired: TLabel;
    procedure btCloseClick(Sender: TObject);
    procedure btConfirmClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FormExpired: TFormExpired;

implementation
uses
  unExpired, ufMain;
{$R *.dfm}

procedure TFormExpired.btCloseClick(Sender: TObject);
begin
  FormExpired.Close;
end;

procedure TFormExpired.btConfirmClick(Sender: TObject);
begin
  PrintExpired(head, tail, FormMain.lvList);
end;

end.
