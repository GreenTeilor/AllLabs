program Exp1;
//Program calculates number of Head, Usual monks and pupils

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Variables declaration
var
   Heads, Monks, Pies: integer;
   Usuals, Pupils, Heads_Consuming, Usuals_Consuming, Pupils_Consuming: double;
   Solution_Existance: boolean;
   MonksStr, PiesStr, Heads_ConsumingStr, Usuals_ConsumingStr, Pupils_ConsumingStr: String;
   {Monks - number of monks
   Heads - number of head monks
   Usuals - number of usual monks
   Pupils - number of pupils
   Heads_Consuming - consuming of head monks
   Usuals_Consuming - consuming of usual monks
   Pupils_Consuming - consuming of pupils
   Solution_Existance - check if solution exists
   MonksStr - mistakes checker for Monks
   PiesStr - mistakes checker for Pies
   Heads_ConsumingStr - mistakes checker for Heads_Consuming
   Usuals_ConsumingStr - mistakes checker for Usuals_Consuming
   Pupils_ConsumingStr - mistakes checker for Pupils_Consuming}

begin
//Repeating the cycle
  while (True) do
  begin
//Set Solution_Existance to the original value
    Solution_Existance := false;

//Input Pies, Monks, Heads_Consuming, Usuals_Consuming, Pupils_Consuming
    writeln('������� ����� �������');
    readln(PiesStr);
    writeln('������� ����� �������');
    readln(MonksStr);
    writeln('�������, ������� ������� ����������� ������� ������(���� �� �����, �� ������� ����� �������� �������)');
    readln(Heads_ConsumingStr);
    writeln('�������, ������� ������� ����������� ������� ������(���� �� �����, �� ������� ����� �������� �������)');
    readln(Usuals_ConsumingStr);
    writeln('�������, ������� ������� ����������� �������(���� �� �����, �� ������� ����� �������� �������)');
    readln(Pupils_ConsumingStr);
//Input mistakes checker
    if (TryStrToInt(MonksStr,Monks) = true) and (TryStrToInt(PiesStr,Pies) = true) and (TryStrToFloat(Heads_ConsumingStr,Heads_Consuming) = true) and (TryStrToFloat(Usuals_ConsumingStr,Usuals_Consuming) = true) and (TryStrToFloat(Pupils_ConsumingStr,Pupils_Consuming) = true) then
    begin

//Cycle entry condition
      if (Pupils_Consuming > 0) and (Heads_Consuming > Usuals_Consuming) and (Usuals_Consuming > Pupils_Consuming) and (Monks > 0) and (Pies > 0) then
      begin

//Calculating number of monks of each type
        for Heads := 0 to trunc(Pies/Heads_Consuming) do
        begin
//Common formula
          Usuals := (Pies + Heads*(Pupils_Consuming - Heads_Consuming) - Monks* Pupils_Consuming)/(Usuals_Consuming - Pupils_Consuming);

//If exists at least one appropriate number of usual monks
          if (Usuals = trunc(Usuals)) and (Usuals >= 0) then
          begin

//Finding number of pupils
            Pupils := Monks - Heads - Usuals;

//Check if number of pupils is positive
            if Pupils >= 0 then
            begin

//Set Solution_Existance to true
              Solution_Existance := true;

//Output number of monks of each type
              writeln('����� ������� �������:', Heads:2,' ����� ������� �������:', Usuals:2:0,' ����� ��������:', Pupils:2:0);

            end;
          end;
        end;

//Check if solution exists
        if Solution_Existance = false  then
        writeln('������� �� ����������');
      end

//If inputted values are incorrect in terms of our task
      else
      begin
        writeln('��������� ����, ����������� �� ����� ��� ���������� �� ��������� ������:');;
        writeln('1)��� ������ ������ ����! ����������� �� ����� ���� ������ ���� ��� ����� ���� �� � ������ �� ����� �������');
        writeln('2)������� ������ ������ ���� ������ ������� ������� � ��������, ������� ������ ������ ���� ������ ��������');
      end;
    end

//If user inputted letters instead of numbers or numbers are too big
    else
    begin
      writeln('��������� ����, ����������� �� ����� �� ��������� ������:');
      writeln('1)� �����-���� ���� ������� �� �����, � ����� ��� ���� �������');
      writeln('2)��������� ����� ������� �������');
      writeln('3)�� �� ����� ������ � ���� �� �����');
      writeln('4)���������� ������� ��� ������� ���� �� ����������� ������')
    end;

    writeln;
  end;

//Final operations
  readln;

end.
