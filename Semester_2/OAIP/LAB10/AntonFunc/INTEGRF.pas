unit INTEGRF;

interface

// Types declaration
type
TIntegral = function(const x: real): real;
{ TIntegral - procedural type }

function Integral1(const x: real): real;
function Integral2(const x: real): real;
function Integral3(const x: real): real;

implementation

// First function
function Integral1(const x: real): real;
begin
result := sqrt(2 * x + 1.7) / (2.4 * x + sqrt(1.2 * sqr(x) + 0.6));
end;

// Second function
function Integral2(const x: real): real;
begin
result := 1 / sqrt(sqr(x) - 1);
end;

// Third function
function Integral3(const x: real): real;
begin
result := sin(0.6 * sqr(x) + 0.3) / (2.4 + cos(x + 0.5));
end;

end.
