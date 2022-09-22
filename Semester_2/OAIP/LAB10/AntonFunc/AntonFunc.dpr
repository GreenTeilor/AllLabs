program AntonFunc;
// The program that calculates integrals with procedural type, using functions

// Console app
{$APPTYPE CONSOLE}

// Modules declaration
uses
  INTEGRF;

// Consts declaration
const
min1 = 1.9;
min2 = 2;
min3 = 0.3;
max1 = 2.6;
max2 = 3.5;
max3 = 1.1;
eps1 = 1E-4;
eps2 = 1E-5;
{ min1, min2, min3 - integrals min borders
max1, max2, max3 - integrals max borders
eps1, eps2 - precisions }

// A function that evaluates integrals using left rectangles
function GetLeft(const Integral: TIntegral; const min, max, eps: real): real;
{ Integral - formal parameter, formula we evaluate
min, nax - integral borders
eps - precisions }

var
i, step: integer;
h, s, latest: real;
{ i - iterator
step - number of segments
h - segment length
temp - temp variable to store value
s - sum
latest - previous value of the integral }

begin

// Assigning varibles to the original values
step := 1;
s := 0;

repeat

// Saving sum
latest := s;
s := 0;

// Calculating segment length
h := (max - min) / step;

// Evaluating
for i := 0 to step - 1 do
s := s + Integral(min + i * h);
s := s * h;

// Incrementing step by 2
inc(step, 2);
until (abs(s - latest) < eps);

Result := s;
end;

// A function that evaluates integrals using mid rectangles
function GetMid(const Integral: TIntegral; const min, max, eps: real): real;
{ Integral - formal parameter, formula we evaluate
min, nax - integral borders
eps - precisions }

var
i, step: integer;
h, s, latest: real;
{ i - iterator
step - number of segments
h - segment length
temp - temp variable to store value
s - sum
latest - previous value of the integral }

begin

// Assigning varibles to the original values
step := 1;
s := 0;

repeat

// Saving sum
latest := s;
s := 0;

// Calculating segment length
h := (max - min) / step;

// Evaluating
for i := 0 to step - 1 do
s := s + Integral(h / 2 + min + i * h);
s := s * h;

// Incrementing step by 2
inc(step, 2);
until (abs(s - latest) < eps);

Result := s;
end;

begin

// Calculating integral for 1st epsilon and by left rectangles
writeln('Using left rectangles, EPS = 1E-4: ');
writeln('Result = ', GetLeft(Integral1, min1, max1, eps1):10:7);
writeln('Result = ', GetLeft(Integral2, min2, max2, eps1):10:7);
writeln('Result = ', GetLeft(Integral3, min3, max3, eps1):10:7);
writeln;

// Calculating integral for 2nd epsilon and by left rectangles
writeln('Using left rectangles, EPS = 1E-5: ');
writeln('Result = ', GetLeft(Integral1, min1, max1, eps2):10:7);
writeln('Result = ', GetLeft(Integral2, min2, max2, eps2):10:7);
writeln('Result = ', GetLeft(Integral3, min3, max3, eps2):10:7);
writeln;

// Calculating integral for 1st epsilon and by mid rectangles
writeln('Using mid rectangles, EPS = 1E-4: ');
writeln('Result = ', GetMid(Integral1, min1, max1, eps1):10:7);
writeln('Result = ', GetMid(Integral2, min2, max2, eps1):10:7);
writeln('Result = ', GetMid(Integral3, min3, max3, eps1):10:7);
writeln;

// Calculating integral for 2nd epsilon and by mid rectangles
writeln('Using mid rectangles, EPS = 1E-5: ');
writeln('Result = ', GetMid(Integral1, min1, max1, eps2):10:7);
writeln('Result = ', GetMid(Integral2, min2, max2, eps2):10:7);
writeln('Result = ', GetMid(Integral3, min3, max3, eps2):10:7);
readln;

end.
