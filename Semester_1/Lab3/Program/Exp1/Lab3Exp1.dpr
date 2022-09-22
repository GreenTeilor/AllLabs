Program Lab3Exp1;
//Program exclude repeating elements

//Console app
{$APPTYPE CONSOLE}

//Modules declaration
Uses
  System.SysUtils;

//Constants declaration
Const
  N = 10;

//Types declaration
Type
  Mas = array[1..N] of real;
  MasStr = array [1..N] of String;

//Variables declaration
Var B:Mas;
    BStr:MasStr;
    i, j, k, Size, Error: integer;
    Rep: boolean;
  { B - array
    BStr - Mistakes checker
    i - counter for compare 1
    j - counter for compare 2
    k - counter fot moving elements of array
    Size - current size of array
    Error - variable which is <> 0 if user made a mistake and 0 if not }

//Start the program
Begin
  //Set Error to the original value
  Error := 1;

  //Inputting array elements
  for i:=1 to N do
  begin

    //Protection from mistakes
    repeat
      write('B[',i,'] = ');
      readln(BStr[i]);
      val(BStr[i], B[i], Error);

      //If mistake happened warn about it
      if Error <> 0 then
      writeln('Пожалуйста, введите вещественное число');

    //If Error = 1 repeat the cycle
    until Error = 0;

  end;

  //Output original array
  writeln('Исходный массив');
  for i:=1 to N do
  write(B[i]:6:2);

  //Remember the original size of array
  Size:=N;

  //Set i to the original value
  i:=Size+1;

  //Set Rep to the original value
  Rep := false;

  //Entering the cycle
  while i>=2 do
  begin

    //In order to avoid double decrement
    if Rep = false then
      dec(i);  (*Decrement i*)

    //Set Rep to false
    Rep := false;

    //Make j equals to i
    j:=i;

    //Entering the cycle
    while j>=2 do
    begin

      //Increment of j
      dec(j);

      //If repeated element was found
      if B[i]=B[j] then
      begin
        for k:=j to Size - 1 do

        //Move elements to the left
        B[k]:=B[k+1];

        //Decrease size of array
        dec(Size);

        //Position of checking element has changed
        dec(i);

        //In order to avoid double decrement of i
        Rep := true;

        //If number repeated more than once
        j := i;

      end;
    end;
  end;
  writeln;

  //Output new array
  writeln('Преобразованный массив');
  for i:=1 to Size do
  write(B[i]:6:2);

  //Final operations
  readln;

End.
