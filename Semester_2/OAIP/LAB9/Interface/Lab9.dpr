program Lab9;

uses
  Vcl.Forms,
  ufMain in 'ufMain.pas' {FormMain},
  ufAdd in 'ufAdd.pas' {FormAdd},
  unTypes in 'unTypes.pas',
  unListFunc in 'unListFunc.pas',
  unDeleteFunc in 'unDeleteFunc.pas',
  ufEdit in 'ufEdit.pas' {FormEdit},
  unEditFunc in 'unEditFunc.pas',
  ufExpired in 'ufExpired.pas' {FormExpired},
  unExpired in 'unExpired.pas',
  unByGroup in 'unByGroup.pas',
  ufSearch in 'ufSearch.pas' {FormSearch},
  unSearchFunc in 'unSearchFunc.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TFormMain, FormMain);
  Application.CreateForm(TFormAdd, FormAdd);
  Application.CreateForm(TFormEdit, FormEdit);
  Application.CreateForm(TFormExpired, FormExpired);
  Application.CreateForm(TFormSearch, FormSearch);
  Application.Run;
end.
