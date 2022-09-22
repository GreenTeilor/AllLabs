unit INTEGRP;

interface

// Types declaration
type
TIntegral = procedure(const x: real; out res: real);
{ TIntegral - procedural type }

procedure Integral1(const x: real; out res: real);
procedure Integral2(const x: real; out res: real);
procedure Integral3(const x: real; out res: real);

implementation

// First function
procedure Integral1(const x: real; out res: real);
begin
res := sqrt(2 * x + 1.7) / (2.4 * x + sqrt(1.2 * sqr(x) + 0.6));
end;

// Second function
procedure Integral2(const x: real; out res: real);
begin
res := 1 / sqrt(sqr(x) - 1);
end;

// Third function
procedure Integral3(const x: real; out res: real);
begin
res := sin(0.6 * sqr(x) + 0.3) / (2.4 + cos(x + 0.5));
end;

end.
