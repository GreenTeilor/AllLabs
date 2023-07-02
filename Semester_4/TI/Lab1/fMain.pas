unit fMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls;

type
  TfmMain = class(TForm)
    odOpenFile: TOpenDialog;
    sdSaveFile: TSaveDialog;
    memInput: TMemo;
    memOutput: TMemo;
    btOpen: TButton;
    btSave: TButton;
    Label1: TLabel;
    cbСipher: TComboBox;
    editKeyWord: TEdit;
    btEncrypt: TButton;
    btDecrypt: TButton;
    lbDecryptionStatus: TLabel;
    lbEncryptionStatus: TLabel;
    lbCipherStatus: TLabel;
    procedure btOpenClick(Sender: TObject);
    procedure btSaveClick(Sender: TObject);
    procedure btEncryptClick(Sender: TObject);
    procedure btDecryptClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  fmMain: TfmMain;

implementation

{$R *.dfm}

//Returns true if letter belongs to the russian alphabet, false otherwise
function isRussianLetter(const letterCode: integer): boolean;
begin
  if ((letterCode >= ord(widechar('А')))
    and (letterCode <= ord(widechar('Я'))))
    or ((letterCode >= ord(widechar('а')))
    and (letterCode <= ord(widechar('я'))))
    or (letterCode = ord(widechar('ё'))) or (letterCode = ord(widechar('Ё'))) then
      Result := true
  else
      Result := false;
end;

//Fetches original text from memo, deletes not russian letters
function fetchM(const memInput: TMemo): String;
var
  i, j, letterCode: integer;
begin
  for i := 0 to memInput.Lines.Count-1 do
    for j := 1 to Length(memInput.Lines[i]) do
    begin
      letterCode := ord(memInput.Lines[i][j]);
      if isRussianLetter(letterCode) then
        Result := Result + AnsiUpperCase(chr(letterCode));
    end;
end;

//Fetches key from edit, deletes not russian letters and repeated russian letters
function fetchKey(const keyInput: TEdit): String;
var
  buf, s: String;
  i: integer;
begin
  s := AnsiUpperCase(keyInput.Text);
  i := 1;
  while i <= Length(s) do
    if not(isRussianLetter(ord(s[i]))) then
      delete(s, i, 1)
    else
      inc(i);

  //Code if you need to delete repeated letters
  {
  while length(s)<>0 do
  begin
    buf:=buf+s[1];
    delete(s,1,1);
    while pos(buf[length(buf)],s) <> 0 do
      delete(s,pos(buf[length(buf)],s),1);
  end;
  Result := buf;
  }

  Result := s;
end;

//Open text file
procedure TfmMain.btOpenClick(Sender: TObject);
var
  str: String;
begin
  if odOpenFile.Execute then
    memInput.Lines.LoadFromFile(odOpenFile.FileName, TEncoding.UTF8);
end;

//Save text file
procedure TfmMain.btSaveClick(Sender: TObject);
begin
  if sdSaveFile.Execute then
    if Pos('.txt', sdSaveFile.FileName) > 0 then
      memOutput.Lines.SaveToFile(sdSaveFile.FileName, TEncoding.UTF8)
    else
      memOutput.Lines.SaveToFile(sdSaveFile.FileName + '.txt', TEncoding.UTF8);
end;

//Return alphabet index of upcase russian letter
function indexOf(rusLetter: widechar): integer;
begin
  if (rusLetter >= 'А') and (rusLetter <= 'Е') then
    Result := ord(rusLetter) - ord(widechar('А'))
  else if (rusLetter >= 'Ж') then
    Result := ord(rusLetter) - ord(widechar('А')) + 1
  else
    Result := 6;
end;

//Return upcase russian letter with index counting from 0
function letterOf(index: integer): widechar;
begin
  if (index <= 5) then
    Result := widechar(chr(ord(widechar('А')) + index))
  else if (index >= 7) then
    Result := widechar(chr(ord(widechar('А')) + index - 1))
  else
    Result := widechar('Ё');
end;

//Show error if there is no russian letters in plaintext or key
procedure showError(lbError: TLabel; text: String);
begin
  lbError.Font.Color := clRed;
  lbError.Caption := text;
  lbError.Visible := true;
end;

procedure showSucces(lbSucces: TLabel; text: String);
begin
  lbSucces.Font.Color := clGreen;
  lbSucces.Caption := text;
  lbSucces.Visible := true;
end;

//Encrypt or decrypt string using Vishener algorithm
function Vishener(MorS, key: String; encrypt: boolean): String;
var
  i: integer;
begin
  Result := '';
  if encrypt then
    for i := 1 to Length(MorS) do
      Result := Result + letterOf((indexOf(MorS[i]) + indexOf(key[i])) mod 33)
  else
    for i := 1 to Length(MorS) do
    begin
      Result := Result + letterOf((indexOf(MorS[i]) - indexOf(key[i]) + 33) mod 33);
      key := key + Result[i];
    end;
end;

//Encrypt or decrypt string using Transposition algorithm
function Transposition(const MorS, key: String; const encrypt: boolean): String;
var
  letter: widechar;
  i, j, k, modulo, currentLetter, keyLength, rows, columns: integer;
  table: array of array of widechar;
begin
  Result := '';
  keyLength := Length(key);
  if encrypt then
    for i := 0 to 32 do
    begin
      letter := letterOf(i);
      for j := 1 to keyLength do
        if key[j] = letter then
        begin
          modulo := 0;
          while modulo*keyLength + j <= length(MorS) do
          begin
            Result := Result + MorS[modulo*keyLength + j];
            inc(modulo);
          end;
        end;
    end
  else
  begin
    modulo := length(MorS) mod keyLength;
    rows := Length(MorS) div Length(key);
    if modulo <> 0 then
      inc(rows);
    columns := keyLength;
    SetLength(table, rows, columns);

    for i := 0 to rows - 1 do
      for j := 0 to columns - 1 do
        table[i][j] := widechar(' ');

    currentLetter := 1;
    for i := 0 to 32 do
    begin
      letter := letterOf(i);
      for j := 1 to keyLength do
        if key[j] = letter then
          if (modulo = 0) or (j <= modulo) then
            for k := 0 to rows - 1 do
            begin
              table[k][j - 1] := MorS[currentLetter];
              inc(currentLetter);
            end
          else
            for k := 0 to rows - 2 do
            begin
              table[k][j - 1] := MorS[currentLetter];
              inc(currentLetter);
            end;
    end;

    for i := 0 to rows - 1 do
      for j := 0 to columns - 1 do
        Result := Result + table[i][j];
  end;
end;

//Encrypt message
procedure TfmMain.btEncryptClick(Sender: TObject);
var
  str, key: String;
begin
  lbCipherStatus.Visible := false;
  lbDecryptionStatus.Visible := false;
  lbEncryptionStatus.Visible := false;
  memOutput.Text := '';
  str := fetchM(memInput);
  key := fetchKey(editKeyWord);
  if cbСipher.ItemIndex = -1 then
    showError(lbCipherStatus, 'Выберите метод шифрования!');
  if (key = '') or (str = '') then
    showError(lbEncryptionStatus, 'В введенном тексте и/или ключе отсутствуют какие-либо русские символы!')
  else
    if cbСipher.ItemIndex <> -1 then
    begin
      if cbСipher.ItemIndex = 1 then
        memOutput.Text := Vishener(str, key + str, true)
      else if cbСipher.ItemIndex = 0 then
        memOutput.Text := Transposition(str, key, true);
      showSucces(lbEncryptionStatus, 'Выполнено!');
    end;
end;

//Decrypt message
procedure TfmMain.btDecryptClick(Sender: TObject);
var
  str, key: String;
begin
  lbCipherStatus.Visible := false;
  lbDecryptionStatus.Visible := false;
  lbEncryptionStatus.Visible := false;
  memOutput.Text := '';
  str := fetchM(memInput);
  key := fetchKey(editKeyWord);
  if cbСipher.ItemIndex = -1 then
    showError(lbCipherStatus, 'Выберите метод шифрования!');
  if (key = '') or (str = '') then
    showError(lbDecryptionStatus, 'В введенном тексте и/или ключе отсутствуют какие-либо русские символы!')
  else
    if cbСipher.ItemIndex <> -1 then
    begin
      if cbСipher.ItemIndex = 1 then
        memOutput.Text := Vishener(str, key, false)
      else if cbСipher.ItemIndex = 0 then
        memOutput.Text := Transposition(str, key, false);
      showSucces(lbDecryptionStatus, 'Выполнено!');
    end;
end;

end.
