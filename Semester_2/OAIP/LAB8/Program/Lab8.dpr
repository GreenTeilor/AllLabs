program Lab8;
//Program build Pascal triangle

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Procedure build Pascal triangle of n size
procedure BuildTriangle(const n: integer);
var
  pscTrg: array[1..15] of integer;
  i, j, k: integer;
  F: textFile;
{ pscTrg - store each raw of Pascal triangle
  i - counter 1
  j - counter 2
  k - counter 3
  F - text file }
begin
  AssignFile(F, 'pscTrg.txt');
  Rewrite(F);

  //Initialize first value of triangle
  pscTrg[1] := 1;

  //Output 1..n raw of triangle
  for i := 1 to n do
  begin

    //Calculate values of raw
    for j := 2 to i do
    begin
      pscTrg[j] := 0;
      for k := j downto 2 do
        pscTrg[k] := pscTrg[k-1] + pscTrg[k];
    end;

   //Output raw
   for k := 1 to i do
     write(F, pscTrg[k]:6);

   //Next raw
   writeln(F);

  end;
  CloseFile(F);
end;

//Variables declaration
var
  n, error: integer;
  nStr: string;
{ n - size of Pascal triangle
  error - <> 0 if input is invalid
  nStr - string represention of n }
begin
  //Input n with mistake checker
  repeat
    write('������� ������ ������������ �������: ');
    readln(nstr);
    Val(nStr,n,error);
    if (error <> 0) or not ((n >= 1) and (n <= 15)) then
      writeln('������ �����!');
  until (error = 0) and ((n >= 1) and (n <= 15));

  //Build triangle
  BuildTriangle(n);

  //Final operations
  readln;
end.
