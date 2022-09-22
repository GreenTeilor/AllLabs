program Lab4Exp4;
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

//Variables declaration
Var
  i, j: integer;
  Y: array[1..N,1..N] of real = ((1,2,3,4,5,6,7,8,9,10),
                                 (0.5,0,0,0,0,0,0,0,0,0),
                                 (-3.4,0,0,0,0,0,0,0,0,0),
                                 (2,0,0,0,0,0,0,0,0,0),
                                 (2.3,0,0,0,0,0,0,0,0,0),
                                 (6,0,0,0,0,0,0,0,0,0),
                                 (1,0,0,0,0,0,0,0,0,0),
                                 (-2.5,0,0,0,0,0,0,0,0,0),
                                 (10,0,0,0,0,0,0,0,0,0),
                                 (2.8,0,0,0,0,0,0,0,0,0));
{ Y - array
  i - counter for raws
  j - counter for columns }



//Start the program
begin

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
  Y[i,j]:=Y[i-1,j-1];

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

