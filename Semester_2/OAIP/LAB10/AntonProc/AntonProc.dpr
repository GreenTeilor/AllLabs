program AntonProc;
// The program that calculates integrals with procedural type, using procedures

// Console app
{$APPTYPE CONSOLE}

// Modules declaration
uses
  INTEGRP;

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

// A procedure that evaluates integrals using left rectangles
procedure GetLeft(const Integral: TIntegral; const min, max, eps: real);
{ Integral - formal parameter, formula we evaluate
min, nax - formal parameters, integral borders
eps - formal parameter, precisions }

// Vars declaration
var
i, step: integer;
h, s, latest, temp: real;
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
for i := 0 to step - 1 do
begin

// Evaluating the function
Integral(min + i * h, temp);
s := s + temp;
end;
s := s * h;

// Incrementing step by 2
inc(step, 2);
until (abs(s - latest) < eps);

// Outputting result
writeln('Result = ', s:10:7);
end;

// A procedure that evaluates integrals using left rectangles
procedure GetMid(const Integral: TIntegral; const min, max, eps: real);
{ Integral - formal parameter, formula we evaluate
min, nax - formal parameters, integral borders
eps - formal parameter, precisions }

// Vars declaration
var
i, step: integer;
h, s, latest, temp: real;
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
for i := 0 to step - 1 do
begin

// Evaluating the function
Integral(h / 2 + min + i * h, temp);
s := s + temp;
end;
s := s * h;

// Incrementing step by 2
inc(step, 2);
until (abs(s - latest) < eps);

// Outputting result
writeln('Result = ', s:10:7);
end;

begin

// Calculating integral for 1st epsilon and by left rectangles
writeln('Using left rectangles, EPS = 1E-4: ');
GetLeft(Integral1, min1, max1, eps1);
GetLeft(Integral2, min2, max2, eps1);
GetLeft(Integral3, min3, max3, eps1);
writeln;

// Calculating integral for 2nd epsilon and by left rectangles
writeln('Using left rectangles, EPS = 1E-5: ');
GetLeft(Integral1, min1, max1, eps2);
GetLeft(Integral2, min2, max2, eps2);
GetLeft(Integral3, min3, max3, eps2);
writeln;

// Calculating integral for 1st epsilon and by mid rectangles
writeln('Using mid rectangles, EPS = 1E-4: ');
GetMid(Integral1, min1, max1, eps1);
GetMid(Integral2, min2, max2, eps1);
GetMid(Integral3, min3, max3, eps1);
writeln;

// Calculating integral for 2nd epsilon and by mid rectangles
writeln('Using mid rectangles, EPS = 1E-5: ');
GetMid(Integral1, min1, max1, eps2);
GetMid(Integral2, min2, max2, eps2);
GetMid(Integral3, min3, max3, eps2);
readln;

end.
