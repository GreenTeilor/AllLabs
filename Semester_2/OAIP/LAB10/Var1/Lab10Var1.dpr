program Lab10Var1;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

type
  TIntegral = function(const x: real): real;

const
  Min1: real = 0.8;
  Max1: real = 1.8;
  Min2: real = 0.4;
  Max2: real = 1.0;
  Min3: real = 1.0;
  Max3: real = 2.0;
  Min4: real = 0.2;
  Max4: real = 1.0;
  Eps1: real = 1E-4;
  Eps2: real = 1E-5;

//Return value of under-integral function in x point (integral 1)
function Integral1(const x: real): real;
begin
  Integral1 := sqrt(0.8*sqr(x) + 1)/(x + sqrt(1.5*sqr(x) + 2));
end;

//Return value of under-integral function in x point (integral 2)
function Integral2(const x: real): real;
begin
  Integral2 := sin(x + 1.4)/(0.8 + cos(2*sqr(x) + 0.5));
end;

//Return value of under-integral function in x point (integral 3)
function Integral3(const x: real): real;
begin
  Integral3 := 1/sqrt(2*sqr(x) + 1.3);
end;

//Return value of under-integral function in x point (integral 4)
function Integral4(const x: real): real;
begin
  Integral4 := (sin(sqr(x))/cos(sqr(x)))/(sqr(x) + 1);
end;

//Right rectangle method
function GetRight(Integral: TIntegral; const Min, Max, Eps: real): real;
var
  i, n: integer;
  h, sum, last, dif: real;
begin
  sum := 0;
  n := 1;

  dif := eps + 1;
  while (abs(dif) > Eps) and (n <= 1000) do
  begin
    last := sum;
    sum := 0;
    h := (max - min) / n;
    for i := 1 to n do
      sum := sum  + Integral(min + i*h);
    sum := sum*h;
    dif := sum - last;
    n := n + 5;
  end;
  if n <= 1000 then
    GetRight := sum
  else
    GetRight := 1000000000;
end;

//Trapeze method
function GetTrapeze(Integral: TIntegral; const Min, Max, Eps: real): real;
var
  i, n: integer;
  h, sum, last, dif: real;
begin
  sum := 0;
  n := 1;

  dif := eps + 1;
  while (abs(dif) > Eps) and (n <= 1000) do
  begin
    last := sum;
    sum := 0;
    h := (max - min)/n;
    for i := 1 to n - 1 do
      sum := sum  + Integral(min + i*h);
    sum := sum + Integral(min)/2;
    sum := sum + Integral(min + n*h)/2;
    sum := sum*h;
    dif := sum - last;
    n := n + 5;
  end;

  if n <= 1000 then
    GetTrapeze := sum
  else
    GetTrapeze := 1000000000;
end;

procedure OutputResult(const x: real);
begin
  if x = 1000000000 then
    writeln('Неопределенный интеграл!')
  else
    writeln(x:6:6);
end;

begin
  //Calculate value of first integral with 1E-4, 1E-5
  writeln('Первый интеграл');
  writeln('Метод правых прямоугольников');
  write('С точностью 1Е-4: ');
  OutputResult(GetRight(Integral1, Min1, Max1, Eps1));
  write('C точностью 1Е-5: ');
  OutputResult(GetRight(Integral1, Min1, Max1, Eps2));
  writeln('Метод трапеций');
  write('С точностью 1Е-4: ');
  OutputResult(GetTrapeze(Integral1, Min1, Max1, Eps1));
  write('С точностью 1Е-5: ');
  OutputResult(GetTrapeze(Integral1, Min1, Max1, Eps2));

  //Spaces
  writeln;
  writeln;

  //Calculate value of second integral with 1E-4, 1E-5
  writeln('Второй интеграл');
  writeln('Метод правых прямоугольников');
  write('С точностью 1Е-4: ');
  OutputResult(GetRight(Integral2, Min2, Max2, Eps1));
  write('C точностью 1Е-5: ');
  OutputResult(GetRight(Integral2, Min2, Max2, Eps2));
  writeln('Метод трапеций');
  write('С точностью 1Е-4: ');
  OutputResult(GetTrapeze(Integral2, Min2, Max2, Eps1));
  write('С точностью 1Е-5: ');
  OutputResult(GetTrapeze(Integral2, Min2, Max2, Eps2));

  //Spaces
  writeln;
  writeln;

  //Calculate value of second integral with 1E-4, 1E-5
  writeln('Третий интеграл');
  writeln('Метод правых прямоугольников');
  write('С точностью 1Е-4: ');
  OutputResult(GetRight(Integral3, Min3, Max3, Eps1));
  write('C точностью 1Е-5: ');
  OutputResult(GetRight(Integral3, Min3, Max3, Eps2));
  writeln('Метод трапеций');
  write('С точностью 1Е-4: ');
  OutputResult(GetTrapeze(Integral3, Min3, Max3, Eps1));
  write('С точностью 1Е-5: ');
  OutputResult(GetTrapeze(Integral3, Min3, Max3, Eps2));

  //Spaces
  writeln;
  writeln;

  //Calculate value of second integral with 1E-4, 1E-5
  writeln('Четвертый интеграл');
  writeln('Метод правых прямоугольников');
  write('С точностью 1Е-4: ');
  OutputResult(GetRight(Integral4, Min4, Max4, Eps1));
  write('C точностью 1Е-5: ');
  OutputResult(GetRight(Integral4, Min4, Max4, Eps2));
  writeln('Метод трапеций');
  write('С точностью 1Е-4: ');
  OutputResult(GetTrapeze(Integral4, Min4, Max4, Eps1));
  write('С точностью 1Е-5: ');
  OutputResult(GetTrapeze(Integral4, Min4, Max4, Eps2));

  //Final operations
  readln;
end.
