Program Lab3Exp3;
//Program exclude repeating elements

//Console app
{$APPTYPE CONSOLE}

//Modules declaration
Uses
  System.SysUtils;

//Constants declaration
Const
  N = 10;

//Variables declaration
Var
  B:array[1..N] of real = (1.1,6,-3.2,1.1,9,6,7,-3.2,9,1.1);
  i, j, k, Size: integer;
  { B - array
    i - counter 1
    j - counter 2
    k - counter 3
    Size - current size of array }

//Start the program
Begin

  //Output original array
  writeln('�������� ������');
  for i:=1 to N do
  write(B[i]:6:2);

   //Remember the original size of array
  Size:=N;

  //Set i to the original value
  i:=Size+1;

  //Entering the cycle
  while i>=N-Size+1 do
  begin

    //Decrement i
    dec(i);

    //Make j equals to i
    j:=i;

    //Entering the cycle
    while j>=N-Size+2 do
    begin

      //Increment of j
      dec(j);

      //If repeated element was found
      if B[i]=B[j] then
      begin
        for k:=j downto 2 do

        //Move elements to the left
        B[k]:=B[k-1];

        //Decrease size of array
        dec(Size);

        //If number repeated more than once
        j := i;

      end;
    end;
  end;
  writeln;

  //Output new array
  writeln('��������������� ������');
  for i:=N-Size+1 to N do
  write(B[i]:6:2);

  //Final operations
  readln;

End.
