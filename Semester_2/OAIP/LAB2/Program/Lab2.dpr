﻿program Lab2;
//Program compare sorts

//Consnole app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Array type
type
  mas =  array of integer;

//Fills array with random integer numbers in range [1..length(arr1)]
procedure RandomArr(var arr1: mas);
var
  i: integer;
{ arr1 - array
  i - counter }
begin
  for i := 0 to length(arr1) - 1 do
    arr1[i] := random(length(arr1))  + 1;
end;

//Fills array with integer numbers from 1 to N
//where N - number of array elements
procedure StraightArr(var arr2: mas);
var
  i: integer;
{ arr2 - array
  i - counter }
begin
  for i := 0 to length(arr2) - 1 do
    arr2[i] := i + 1;
end;

//Fills array with integer numbers from N to 1
//where N - number of array elements
procedure RevArr(var arr3: mas);
var
  i: integer;
begin
  for i := 0 to length(arr3) - 1 do
    arr3[i] := length(arr3) - i;
end;

//Swap elements
procedure Swap(var a,b: integer);
var
  temp: integer;
{ a - 1-st number
  b - 2-nd number
  temp - auxiliary variable}
begin
  temp := a;
  a := b;
  b := temp;
end;

//Calculate number of swaps in shaker sort
function ShakerSortSwapsExp(const arr4: mas): integer;
var
  i, count: integer;
  leftBorder, rightBorder: integer;
  arr: mas;
{ arr4 - array
  i - counter
  count - number of swaps
  leftBorder - left border in sort
  rightBorder - rightBorder in sort }
begin
  //Copy elements of Arr4 to Arr
  setLength(arr, length(arr4));
  for i := 0 to length(arr4) - 1 do
    arr[i] := arr4[i];

  //Set borders
  leftBorder := 0;
  rightBorder := length(arr) - 1;

  //Initialize count
  count := 0;

  //Shaker Sort
  while rightBorder > leftBorder do
  begin

    //From left to right
    for i := leftBorder to rightBorder - 1 do
      if arr[i] > arr[i+1] then
      begin
        swap(arr[i], arr[i+1]);
        inc(count);
      end;

    //From right to left
    for i := rightBorder downto leftBorder + 1 do
      if arr[i] < arr[i-1] then
      begin
        swap(arr[i], arr[i-1]);
        inc(count);
      end;

    //Move borders
    inc(leftBorder);
    dec(rightBorder);
  end;

  //Return number of swaps
  ShakerSortSwapsExp := count;
end;

//Calculate theoretical number of swaps in shaker sort
function ShakerSortSwapsTheory(const N: integer; const arrayType: integer): integer;
begin
  if arrayType = 1 then
    ShakerSortSwapsTheory := trunc(3*(N*N - N)/12);
  if arrayType = 2 then
    ShakerSortSwapsTheory := 0;
  if arrayType = 3 then
    ShakerSortSwapsTheory := trunc(3*(N*N - N)/6);
end;

//Calculate number of swaps in insert barrier sort
function InsertBarSortSwapsExp(const arr5: mas): integer;
var
  i, j, count: integer;
  arr: mas;
{ arr5 - array
  i - counter 1
  j - counter 2
  count - number of swaps}
begin
   //Copy elements of Arr5 to Arr reserving free space for barrier
   setLength(arr, length(arr5) + 1);
   for i := 1 to length(arr) - 1 do
     arr[i] := arr5[i - 1];

   //Initialize count
   count := 0;

   //Barrier sort
   for  i:= 2  to  length(arr) - 1  do
       if  arr[i-1] > arr[i]  then
       begin
          arr[0]:= arr[i];
          j:= i-1;
          while arr[j]>arr[0]  do
          begin
             arr[j+1]:= arr[j];
             inc(count);
             j:= j-1;
          end;
          arr[j+1]:= arr[0];
          inc(count);
       end;

   //Return number of swaps
   InsertBarSortSwapsExp := count;
end;

//Calculate theoretical number of swaps in insert barrier sort
function InsertBarSortSwapsTheory(const N: integer; const arrayType: integer): integer;
begin
  if arrayType = 1 then
    InsertBarSortSwapsTheory := trunc((N*N + 9*N - 10)/4);
  if arrayType = 2 then
    InsertBarSortSwapsTheory := 0;
  if arrayType = 3 then
    InsertBarSortSwapsTheory := trunc((N*N + 3*N - 4)/2);
end;

//Prints result of theoretical and practical swaps in both sorts
procedure PrintExperiment(const N: integer);
var
  i, j: integer;
  arr6: mas;
  arrResults: array[1..3, 1..4] of integer;
{ i - counter 1
  j - counter 2
  arr6 - experimental array to calculate swaps
  arrResults -  array which contains results }
begin
  setLength(arr6, N);
  for i := 1 to 3 do
  begin
     if i = 1 then
       RandomArr(arr6);
     if i = 2 then
       StraightArr(arr6);
     if i = 3 then
       RevArr(arr6);
    for j := 1 to 4 do
    begin
      if j = 1 then
        arrResults[i,j] := ShakerSortSwapsExp(arr6);
      if j = 2 then
        arrResults[i,j] := InsertBarSortSwapsExp(arr6);
      if j = 3 then
        arrResults[i,j] := ShakerSortSwapsTheory(N,i);
      if j = 4 then
        arrResults[i,j] := InsertBarSortSwapsTheory(N,i);
    end;
  end;



  //Print results
  for i := 1 to 3 do
  begin
    if i = 1 then
      write('|',N:11, '            |       случайный  |');
    if i = 2 then
      write('|',N:11, '            |   сортированный  |');
    if i = 3 then
      write('|',N:11, '            |    перевернутый  |');

    //Print values of arrResults
    for j := 1 to 4 do
    begin
      if j = 1 then
        write(arrResults[i,j]:12,'       |');
      if j = 2 then
        write(arrResults[i,j]:17,'           |');
      if j = 3 then
        write(arrResults[i,j]:11,'       |');
      if j = 4 then
        write(arrResults[i,j]:17,'           |');
    end;
    writeln;
    writeln('|_______________________|__________________|___________________|____________________________|__________________|____________________________|');
  end;

end;

//Print results for all sizes of arrays
procedure PrintResults;
begin
  writeln(' _______________________ __________________ ___________________ ____________________________ __________________ ____________________________');
  writeln('| Размерность массива   |    Тип массива   |   Шейкер(эксп.)   |  Вставка с барьером(эксп.) |   Шейкер(теор.)  |  Вставка с барьером(теор.) |');
  writeln('|_______________________|__________________|___________________|____________________________|__________________|____________________________|');
  PrintExperiment(100);
  PrintExperiment(250);
  PrintExperiment(500);
  PrintExperiment(1000);
  PrintExperiment(2000);
  PrintExperiment(3000);
end;

//Start the program
begin
  randomize;

  //Print table
  PrintResults;

  //Final operations
  readln;
end.
