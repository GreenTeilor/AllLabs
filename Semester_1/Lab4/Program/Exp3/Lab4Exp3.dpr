program Lab4Exp3;
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
  MasRaw: array[1..N] of real = (1,2,3,4,5,6,7,8,9,10);
  MasCol: array[1..N] of real = (1,0.5,-3.4,2,2.3,6,1,-2.5,10,2.8);

//Variables declaration
Var
  Y: array[1..N,1..N] of real;
  i, j: integer;
{ MasRaw - 1-st raw elements
  MasCol - 1-st column elements
  Y - array
  i - counter for raws
  j - counter for columns }



//Start the program
begin

  //Filling the 1-st raw
  i := 1;
  for j := 1 to N do
  Y[i,j] := MasRaw[j];

  //Filling the 1-st column
  j := 1;
  for i := 1 to N do
  Y[i,j] := MasCol[i];

  //Output original array
  writeln('Исходный массив');
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
  Y[i,j] := Y[i-1,j-1];

  //Output supplemented array
  writeln('Преобразованный массив');
  for i := 1 to N do
  begin
    for j := 1 to N do
    write(Y[i,j]:6:2);
    writeln;
    writeln;
  end;

  //Final operations
  readln;

end.
