Program Lab3Exp2;
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
  Mas = array[1..N] of integer;

//Variables declaration
Var B: Mas;
    i, j, k, Size: integer;
  { B - array
    i - counter for compare 1
    j - counter for compare 2
    k - counter for moving
    Size - current size of array }

//Start the program
Begin

  //In order to create new random numbers
  Randomize;

  //Generate random elements of array
  for i := 1 to N do
  B[i]:=Random(10);

  //Output original array
  writeln('Исходный массив');
  for i:=1 to N do
  write(B[i]:4);

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
  writeln('Преобразованный массив');
  for i:=N-Size+1 to N do
  write(B[i]:4);

  //Final operations
  readln;

End.
