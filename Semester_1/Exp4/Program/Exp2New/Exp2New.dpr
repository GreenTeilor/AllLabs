program Exp2New;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

var
  Num1Str, Num2Str: String;
  Checker: boolean;
  I, BigLength, Temp, NewSize, K: integer;
  Num1: array of integer;
  Num2: array of integer;
  SumNum: array of integer;

//Start the program
begin

  //Input 1-st number
  repeat
    Checker := true;
    write('Пожалуйста, введите первое число: ');
    readln(Num1Str);
    if length(Num1Str) = 0 then
      Checker := false;
    i := 1;
    for i := 1 to length(Num1Str) do
      if (ord(Num1Str[i]) < 48) or (ord(Num1Str[i]) > 58) then
        Checker := false;
    if not(Checker) then
      writeln('Ошибка ввода!');
  until Checker;

  writeln('-':35);

  //Input 2-nd number
  repeat
    Checker := true;
    write('Пожалуйста, введите второе число: ');
    readln(Num2Str);
    if length(Num2Str) = 0 then
      Checker := false;
    i := 1;
    for i := 1 to length(Num2Str) do
      if (ord(Num2Str[i]) < 48) or (ord(Num2Str[i]) > 58) then
        Checker := false;
    if not(Checker) then
      writeln('Ошибка ввода!');
  until Checker;

  if length(Num1Str) > length(Num2Str) then
    BigLength := length(Num1Str)
  else
    BigLength := length(Num2Str);

  //Set lengths of arrays
  setlength(Num1, BigLength);
  setlength(Num2, BigLength);
  setlength(SumNum, BigLength);

  //In order to place number 1 at the end of array num1
  for i :=  0 to length(Num1Str) - 1 do
    Num1[BigLength - length(Num1Str) + i] := StrToInt(Num1Str[i + 1]);

  //In order to place number 2 at the end of array num2
  for i :=  0 to length(Num2Str) - 1 do
    Num2[BigLength - length(Num2Str) + i] := StrToInt(Num2Str[i + 1]);

  //1-st Number - 2-nd number
  for i := BigLength - 1 downto 0 do
  begin

    //If value from 1-st number bigger than value from 2-nd number
    if Num1[i] >= Num2[i]  then
    SumNum[i] := Num1[i] - Num2[i]

    //If we need to take 1 from the next rank
    else
    begin
      SumNum[i] := Num1[i] + 10 - Num2[i];
      Num1[i-1] := Num1[i-1] - 1;
    end;
  end;

  writeln('=':35);

  //Remove 0 before SumNumbers
  i:=0;
  NewSize := BigLength;
  while SumNum[i] = 0 do
  begin
    for k := 0 to BigLength - 1 do
    SumNum[k] := Sumnum[k+1];
    NewSize := NewSize - 1;
  end;

  //To make space in front of SumNum
  write('':34);

  //Output SumNumbers
  for i := 0 to NewSize - 1 do
  write(SumNum[i]);

  //Final operations
  readln;

end.
