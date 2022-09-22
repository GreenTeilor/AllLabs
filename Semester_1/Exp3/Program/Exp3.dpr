program Exp3;
//Program calculates best number of diskets, boxes, and bigboxes

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Constants declaration
Const
  Disket_Price = 11.5;
  Box_Price = 114.5;
  BigBox_Price = 1255;
  Disket = 1;
  Box = Disket*12;
  BigBox = Box*12;

//Variables declaration
var
  N, Error, BigBoxes, Boxes, Profit1, Profit2, Bonus: integer;
  NStr: String;
  Price: real;
{ N - number of diskets
  Error - variable, which is 1 if user made a mistake
  and 0 if not
  NStr - mistakes checker
  BigBoxes - number of big boxes
  Boxes - number of boxes
  Profit1 - maximum number of diskets when you get more
  value bying boxes instead of big boxes
  Profit2 - maximum number of diskets when you get more
  value bying diskets instead of boxes
  Bonus - number of bonus diskets
  Price - price }
begin
  //Repeat the cycle
  while (True) do
  begin
    //Set Error to the original value
    Error := 1;

    //Set BigBoxes to the original value
    BigBoxes := 0;

    //Set Boxes to the original value
    Boxes := 0;

    //Set Bonus to the original value
    Bonus := 0;

    //Set price to the original value
    Price := 0;

    //Set Profit1 to the original value
    Profit1 := trunc(Box/Disket);

    //Set Profit2 to the original value
    Profit2 := trunc(BigBox/Box);

    //Mistakes checker
    repeat
      write('Пожалуйста, введите число дискет: ');
      readln(NStr);
      val(NStr, N, Error);

      //If mistake happened warn about it
      if (Error <> 0) or (N <= 0) then
      writeln('Введенное количество дискет должно быть натуральным числом');

    //If Error = 1 or N <= 0 repeat the cycle
    until
      (Error = 0) and (N > 0);

    //Find value of Profit1
    while BigBox_Price < Profit1*Box_Price do
    Profit1 := Profit1 - 1;
    Profit1 := Profit1 * trunc(Box/Disket);

    //Find value of Profit2
    while Box_Price < Profit2*Disket_Price do
    Profit2 := Profit2 - 1;

    //If you have more value bying big box instead of boxes
    if N mod BigBox > Profit1 then
    BigBoxes := N div BigBox + 1

    //If you have more value bying boxes instead of big box
    else
    BigBoxes := N div BigBox;

    //N diskets left
    N := N - BigBoxes*BigBox;

    //If we bought boxes instead of big box then we have diskets to buy left
    if N > 0 then
    begin

      //If you have more value bying  box instead of diskets
      if N mod Box > Profit2 then
      Boxes := N div Box + 1

      //If you have more value bying diskets instead of box
      else
      Boxes := N div Box;

      //N diskets left
      N := N - Boxes*Box;
    end;

    ///If we bought diskets instead of box then we have diskets bought and no bonuses
    if N > 0 then
    begin
      Price := BigBoxes*BigBox_Price + Boxes*Box_Price + N*Disket_Price;
      Bonus := 0;
    end

    //If we bought box instead of diskets then we dont have diskets bought but, probably, bonuses
    else
    begin
      Price := BigBoxes*BigBox_Price + Boxes*Box_Price;
      Bonus := abs(N);
      N := 0;
    end;

    //Output all values
    writeln('Советуем вам купить:');
    writeln(BigBoxes,' ящиков');
    writeln(Boxes,' коробок');
    writeln(N,' дискет');
    writeln('Лучшая цена: ', Price:0:1);
    writeln('Количество бонусных дискет:', Bonus);
    writeln;
  end;
end.
