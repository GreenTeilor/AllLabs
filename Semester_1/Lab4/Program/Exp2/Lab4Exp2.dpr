program Lab4Exp2;
//Program supplement the array

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Constants declaration
Const
  N = 10;

//Arrays
Type
  Mas = array[1..N,1..N] of real;

//Variables declaration
Var
  i, j: integer;
  Y: Mas;
{ Mas - array
  i - counter for raws
  j - counter for columns }



//Start the program
begin

  //Creating first raw
  Randomize;
  i := 1;
  for j := 1 to N do
  Y[i,j] := random(10000)/100;

  //Creating first column
  j := 1;
  for i := 2 to N do
  Y[i,j] := random(10000)/100;

  //Output original array
  writeln('�������� ������');
  for i := 1 to N do
  begin
    for j := 1 to N do
    write(Y[i,j]:6:2);
    writeln;
    writeln;
  end;

  //Supplement the array
  for i:=2 to N do
  for j:=2 to N do
  Y[i,j]:=Y[i-1,j-1];

  //Output supplemented array
  writeln('��������������� ������');
  for i := 1 to N do
  begin
    for j := 1 to N do
    write(Y[i,j]:6:2);
    writeln;
    writeln;
  end;

  //Fianl operations
  readln;

end.

