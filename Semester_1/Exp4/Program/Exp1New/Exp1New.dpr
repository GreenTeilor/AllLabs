program Exp1New;
//Program pluses 2 numbers

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
Uses
  System.SysUtils;

//Variables declaration
Var
  Num1Str, Num2Str: String;
  Checker: boolean;
  I, BigLength, Temp, NewSize, K: integer;
  Num1: array of integer;
  Num2: array of integer;
  SumNum: array of integer;
{ Num1Str - Num1 in String
  Num2Str - Num2 in String
  Checker - mistakes checker
  I - counter for arrays
  BigLength - length of biggest inputted number
  Temp - auxilliary variable used to move 1 to the next rank if necessary
  NewSize - size of final number after removing 0 in the front
  K - counter to output result
  Num1 - 1-st number
  Num2 - 2-nd number
  SumNum - calculations result }

//Start the program
Begin

  //Input 1-st number
  repeat
    Checker := true;
    write('����������, ������� ������ �����: ');
    readln(Num1Str);
    if length(Num1Str) = 0 then
      Checker := false;
    i := 1;
    for i := 1 to length(Num1Str) do
      if (ord(Num1Str[i]) < 48) or (ord(Num1Str[i]) > 58) then
        Checker := false;
    if not(Checker) then
      writeln('������ �����!');
  until Checker;

  writeln('+':35);

  //Input 2-nd number
  repeat
    Checker := true;
    write('����������, ������� ������ �����: ');
    readln(Num2Str);
    if length(Num2Str) = 0 then
      Checker := false;
    i := 1;
    for i := 1 to length(Num2Str) do
      if (ord(Num2Str[i]) < 48) or (ord(Num2Str[i]) > 58) then
        Checker := false;
    if not(Checker) then
      writeln('������ �����!');
  until Checker;

  //Find out which variable is bigger
  if length(Num1Str) > length(Num2Str) then
    BigLength := length(Num1Str)
  else
    BigLength := length(Num2Str);

  //Set lengths of arrays
  setlength(Num1, BigLength);
  setlength(Num2, BigLength);
  setlength(SumNum, BigLength + 1);

  //In order to place number 1 at the end of array num1
  for i :=  0 to length(Num1Str) - 1 do
    Num1[BigLength - length(Num1Str) + i] := StrToInt(Num1Str[i + 1]);

  //In order to place number 2 at the end of array num2
  for i :=  0 to length(Num2Str) - 1 do
    Num2[BigLength - length(Num2Str) + i] := StrToInt(Num2Str[i + 1]);

  //Calculate the sum

  for i := BigLength - 1 downto 0 do
  begin

    //Pluses two columns
    SumNum[i+1] := (SumNum[i+1] + (Num1[i] + Num2[i]) mod 10) mod 10 ;

    //To stay within arrays border
    if i < BigLength - 1 then

      //Find value of Temp
      Temp := Temp + Num1[i+1] + Num2[i + 1];

    //If we need to move 1 to the next rank then Temp = 1
    if Temp >= 10 then
      Temp := 1

    //If we dont need to move 1 to the next rank then Temp = 0
    else
      Temp := 0;

    //If we need to move 1 to the next rank
    if Num1[i] + Num2[i] + Temp >= 10 then
      SumNum[i] := 1;
  end;

  writeln('=':35);

  //Remove 0 before SumNumbers
  i:=0;
  NewSize := BigLength + 1;
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

End.
