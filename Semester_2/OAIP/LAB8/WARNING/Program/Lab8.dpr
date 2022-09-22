program Lab8;
//Program move reversed strings from textFile F to textFile G

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Return reversed string str
function RevString(const str: string): string;
var
  i: integer;
  revStr: string;
{ i - counter
  revStr - reversed string }
begin
  revStr := '';
  for i := 1 to length(str) do
    revStr := revStr + str[length(str) - i + 1];
  RevString := revStr;
end;

//Variables declaration
var
  F, G: textFile;
  str: string;
{ F - file to read
  G - file to write
  str - string readed from F }

begin
  //Assign files
  AssignFile(F, 'F.txt');
  AssignFile(G, 'G.txt');

  //Open F to read
  Reset(F);

  //Open G to write
  Rewrite(G);

  //Move reversed strings from F to G
  while not Eof(F) do
  begin
    Readln(F, str);
    Writeln(G, RevString(str));
  end;

  //Close files
  CloseFile(F);
  CloseFile(G);
end.
