program lab1;
//Console app
{$APPTYPE CONSOLE}

{$R *.res}
//Modules declaration
uses
  System.SysUtils;

//Variables declaration
var
  x,sum,f: Real;
  n: Integer;
{ n - counter
  x - argument of function
  sum - value of sum
  f - value of function }
begin
//Assignment x to the original value
  x:=0.6;
//Cycle entry condition
  while x<=1.1  do
  begin
  //Assignment sum to the original value
    sum := 0;
    //Cycle entry condition
    for n := 1 to 15 do
    begin
    //Values of the sum
      sum:=sum + (exp(ln(x)*(2*n-1))+(1/7))/sqrt(exp(x/n)+exp(ln(x)*((n-1)/n)));
      //Values of the function
      if n>=10 then
      begin
        f:=arctan(x) - sum;
        //Output values
        writeln('x=',x:0:2,' n=',n,' f(x,n)=',f:9:5);
      end;
    end;
  writeln;
  //Increment x
  x:=x + 0.1;
  end;
  //Final operations
  writeln('PRESS ENTER TO EXIT THE PROGRAM');
  readln;
end.
