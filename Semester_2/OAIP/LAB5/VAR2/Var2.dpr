program Var2;
//Program calculates mathematical expression

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Types declaration
type
  mas = array[1..3,1..3] of integer;

//Constants declaration
const
  A:mas = ((5,1,7),
           (-10,-2,1),
           (0,1,2));
  B:mas = ((2,4,1),
           (3,1,0),
           (7,2,1));
  Num: integer = 2;

//Function calculates sum of matrices
function addMatrix(const X, Y): mas;
var
  i, j: integer;
  temp1: mas;
{ X - matrix 1
  Y - matrix 2
  temp1 - result
  i - counter 1
  j - counter 2 }
begin
  //Filling temp1 with 0
  for i := 1 to 3 do
    for j := 1 to 3 do
      temp1[i,j] := 0;

  //Calculating sum of matrices
  for i := 1 to 3 do
    for j := 1 to 3 do
      temp1[i,j] := mas(X)[i,j] + mas(Y)[i,j];

  //Return sum of matrices
  addMatrix := temp1;
end;

//Procedure calculates difference of matrices
function subMatrix(const X, Y): mas;
var
  i, j: integer;
  temp2: mas;
{ X - matrix 1
  Y - matrix 2
  temp2 - result
  i - counter 1
  j - counter 2 }
begin
  //Filling temp2 with 0
  for i := 1 to 3 do
    for j := 1 to 3 do
      temp2[i,j] := 0;

  //Calculating difference of matrices
  for i := 1 to 3 do
    for j := 1 to 3 do
      temp2[i,j] := mas(X)[i,j] - mas(Y)[i,j];

  //Return difference of matrices
  subMatrix := temp2;
end;

//Procedure calculates result of multiplication of matrix and number
function multNum(const num, X): mas;
var
  i, j: integer;
  temp3: mas;
{ X - matrix 1
  Y - matrix 2
  temp3 - result
  i - counter 1
  j - counter 2 }
begin
  //Filling temp1 with 0
  for i := 1 to 3 do
    for j := 1 to 3 do
      temp3[i,j] := 0;

  //Calculate result of multiplication
  for i := 1 to 3 do
    for j := 1 to 3 do
      temp3[i,j] := mas(X)[i,j] * integer(num);

  //Return result of multiplication of num and matrix
  multNum := temp3;
end;

//Procedure calculates result of multiplication of matrices
function multMatrix(const X, Y): mas;
var
  i, j, k: integer;
  temp4: mas;
{ X - matrix 1
  Y - matrix 2
  temp4 - result
  i - counter 1
  j - counter 2
  k - counter 3 }
begin
  //Calculate result of multiplication
  for i := 1 to 3 do
    for j := 1 to 3 do
    begin
      temp4[i,j] := 0;
      for k := 1 to 3 do
        temp4[i,j] := temp4[i,j] + mas(X)[i,k] * mas(Y)[k,j];
    end;

  //Return result of multiplication of matrices
  multMatrix := temp4;
end;

//Output matrix
procedure outputMatrix(const X);
var
  i, j: integer;
{ X - matrix
  i - counter
  j - counter }
begin
  //Output matrix
  for i := 1 to 3 do
  begin
    for j := 1 to 3 do
      write(mas(X)[i,j]:6);
    writeln;
    writeln;
  end;
end;

//Variables declaration
var
  res1, res2, res3, res4, finalRes: mas;
{ res1 - 1-st part of calculations
  res2 - 2-nd part of calculations
  res3 - 3-rd part of calculations
  res4 - 4-th part of calculations
  finalRes - final result of calculations }

//Start the program
begin

  //Output matrix A
  writeln('Матрица A: ');
  outputMatrix(A);

  //Output matrix B
  writeln('Матрица B: ');
  outputMatrix(B);

  //Calculate result of operations
  res1 := subMatrix(A, B); { A - B }
  res2 := multNum(Num, res1); { 2*(A - B)}
  res3 := multMatrix(A, A); { A*A }
  res4 := addMatrix(res3, B); { A*A + B }
  finalRes := multMatrix(res2, res4); { 2*(A - B)*(A*A + B) }

  //Output result of calculations
  writeln('Результат вычислений: ');
  outputMatrix(finalRes);

  //Final operations
  readln;

end.
