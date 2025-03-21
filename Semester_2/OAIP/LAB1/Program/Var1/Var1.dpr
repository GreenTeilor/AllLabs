program Var1;
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

//Procedure calculates sum of matrices
procedure addMatrix(X, Y: mas; var temp1: mas);
var
  i, j: integer;
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
      temp1[i,j] := X[i,j] + Y[i,j];
end;

//Procedure calculates difference of matrices
procedure subMatrix(X, Y: mas; var temp2: mas);
var
  i, j: integer;
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
      temp2[i,j] := X[i,j] - Y[i,j];
end;

//Procedure calculates result of multiplication of matrix and number
procedure multNum(num: integer; X: mas; var temp3: mas);
var
  i, j: integer;
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
      temp3[i,j] := X[i,j] * num;
end;

//Procedure calculates result of multiplication of matrices
procedure multMatrix(X, Y: mas; var temp4: mas);
var
  i, j, k: integer;
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
        temp4[i,j] := temp4[i,j] + X[i,k] * Y[k,j];
    end;
end;

//Output matrix
procedure outputMatrix(X: mas);
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
      write(X[i,j]:6);
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
  writeln('������� A: ');
  outputMatrix(A);

  //Output matrix B
  writeln('������� B: ');
  outputMatrix(B);

  //Calculate result of operations
  subMatrix(A, B, res1); { A - B }
  multNum(2, res1, res2); { 2*(A - B)}
  multMatrix(A, A, res3); { A*A }
  addMatrix(res3, B, res4); { A*A + B }
  multMatrix(res2, res4, finalRes); { 2*(A - B)*(A*A + B) }

  //Output result of calculations
  writeln('��������� ����������: ');
  outputMatrix(finalRes);

  //Final operations
  readln;

end.
