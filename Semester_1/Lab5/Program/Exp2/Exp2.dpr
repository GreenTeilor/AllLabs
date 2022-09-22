program Exp2;
//Program calculates iterative cycle

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Constants declaration
Const
  Eps1 = 0.00001;
  Eps2 = 0.000001;

//Variables declaration
var
  X, Y, El, T1: real;
  T2, T3, F: integer;
  Flag: boolean;
  { X - argument of function
    Y - function
    El - current value of function
    T1 - numerator of function
    T2 -  1-st part of denominator of function
    T3 -  2-st part of denominator of function
    F - auxiliary variable which helps to calculate factorial
    Flag - true when Delta <= Eps1 false until }

//Start the program
Begin

  //Assign X to the original value
  X := 0.1;

  //Entering the cycle
  while X <= 0.9 do
  begin
    //Assign y to the original value
    Y := sqr(x)/6;

    //Assign T1 to the original value
    T1 := exp(ln(x)*3);

    //Assign T2 to the original value
    T2 := 2;

    //Assign T3 to the original value
    T3 := 24;

    //Assign F to the original value
    F := 5;

    //Assign Flag to the original value
    Flag := false;

    //Assign El to the original value
    El := Eps1 + 1;

    //Entering the cycle
    while El >= Eps2 do
    begin

      //Calculate El
      El := T1/(T2*T3);

      //Calculate value of function
      Y := Y + T1/(T2*T3);

      //Calculate numerator of function
      T1 := T1*x;

      //Calculate the 1-st part of denominator of function
      T2 := T2 + 1;

      //Calculate the 2-st part of denominator of function
      T3 := T3*F;

      //Calculate F
      F := F + 1;

      //If the first accuracy was reached
      if (El < Eps1) and (Flag = false) then
      begin

        //In order to output just once
        Flag := true;

        //Output X, Eps1, Y
        writeln('x = ',x:6:1);
        writeln('Eps1 = ',Eps1:6:5);
        writeln('Y = ',Y:12:10);

      end;

    end;

    //Output Eps2, Y
    writeln('Eps2 = ',Eps2:8:6);
    writeln('Y = ',Y:12:10);
    writeln;

    //Increment X
    X := X + 0.1;

  end;

  //Final operations
  readln;

End.
