Program Lab8;
//Program sort the array

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
Uses
  System.SysUtils;

//Constants declaration
Const
  N = 8;
  M = 9;

//Types declaration
Type
  Mas = array[1..N,1..M] of integer;

//Variables declaration
Var
  X:Mas;
  i, j, k, Temp: integer;
{ X - array
  i - counter for raws
  j - counter for columns
  k - counter to sort arrays
  Temp - auxillary variable which is used to swap elements }

//Start the program
Begin

  //Create new random numbers
  Randomize;

  //Fill the array with random elements
  for i := 1 to N do
    for j := 1 to M do
      X[i,j] := random(100) + 1;

  //Output original array
  writeln('�������� ������:');
  for i := 1 to N do
    begin
      for j := 1 to M do
        write(X[i,j]:3,' ');
      writeln;
      writeln;
    end;
  writeln;

  //Sort elements in raws of array in growth order
  for i := 1 to N do(*To sort each raw step by step*)
    for j := 1 to M - 1 do(*Reffering to each element of current raw*)
      for k := 1 to M - j do(*Bubble sort*)
      begin

        //If next element bigger than previous one
        if X[i,k] > X[i,k+1] then

        //Swap elements
        begin
          Temp := X[i,k+1];
          X[i,k+1] := X[i,k];
          X[i,k] := Temp;
        end;

      end;

  //Sort raws in decrease order
  for i := 1 to N do(*Reffering to each raw of array*)
    for k := 1 to N - i do(*Bubble sort*)
    begin

      //Biggest elements of each raw are in 9-th column, because of previous sort,
      //sort, therefore, in order to compare biggest elements of each raw we
      //need to compare all elements from 9-th column
      if X[k,M] > X[k+1,M] then
      begin

        //Swap all elements from both raws
        for j := 1 to M do
        begin
          Temp := X[k+1,j];
          X[k+1,j] := X[k,j];
          X[k,j] := Temp;
        end;

      end;
    end;

  //Output transformed array
  writeln('��������������� ������:');
  for i := 1 to N do
    begin
      for j := 1 to M do
        write(X[i,j]:3,' ');
      writeln;
      writeln;
    end;

  //Final operations
  readln;
End.
