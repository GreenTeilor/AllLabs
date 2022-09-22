program Exp2;
//Program calculates residual of 2 numbers

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Constants declaration
const
  N = 50;

//Arrays
type
  Mas1 = array[1..N] of integer;
  Mas2 = array[1..N] of integer;
  Mas3 = array[1..N] of integer;

//Variables declaration
var
  Num1: Mas1;
  Num2: Mas2;
  Result: Mas3;
  i, NewSize, k: integer;
{ Num1 - array with the first number
  Num2 - array with the first number
  Result - array with the residual of numbers
  i - counter for input, output, calculations
  NewSize - number of outputted array elements after removing 0
  k - counter, which moves to the left arrays, which contain 0 before the number }

//Start the program
Begin
  //Create numbers
  Randomize;
  for i := 1 to N do
  begin

    //Create 2-nd number which is always < 1 -st number
    if i = 1 then
    begin
      Num2[i] := random(9);
      Num1[i] := Num2[i] + 1;
    end
    else
    begin
      Num1[i] := random(10);
      Num2[i] := random(10);
    end;
  end;

  //Output 1-st number
  for i := 1 to N do
  begin
  write(Num1[i]);
  end;
  writeln;
  writeln('-');

  //1-st Number - 2-nd number
  for i := N downto 1 do
  begin

    //If value from 1-st number bigger than value from 2-nd number
    if Num1[i] >= Num2[i]  then
    Result[i] := Num1[i] - Num2[i]

    //If we need to take 1 from the next rank
    else
    begin
      Result[i] := Num1[i] + 10 - Num2[i];
      Num1[i-1] := Num1[i-1] - 1;
    end;
  end;

  ////Remove 0 before Num2
  i:=1;
  NewSize := N;
  while Num2[i] = 0 do
  begin
    for k := 1 to N - 1 do
    Num2[k] := Num2[k+1];
    NewSize := NewSize - 1;
  end;

  //Output 2-nd number
  for i := 1 to NewSize do
  begin
  write(Num2[i]);
  end;
  writeln;
  writeln('=');

  //Remove 0 before Result
  i:=1;
  NewSize := N;
  while Result[i] = 0 do
  begin
    for k := 1 to N - 1 do
    Result[k] := Result[k+1];
    NewSize := NewSize - 1;
  end;

  //Output result
  for i := 1 to NewSize do
  write(Result[i]);
  readln;
End.
