program Var1;
//Program calculates mathematical expression

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils,
  Functions in 'Functions.pas';

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
  res1 := subMatrix(A, B); { A - B }
  res2 := multNum(2, res1); { 2*(A - B)}
  res3 := multMatrix(A, A); { A*A }
  res4 := addMatrix(res3, B); { A*A + B }
  finalRes := multMatrix(res2, res4); { 2*(A - B)*(A*A + B) }

  //Output result of calculations
  writeln('��������� ����������: ');
  outputMatrix(finalRes);

  //Final operations
  readln;

end.
