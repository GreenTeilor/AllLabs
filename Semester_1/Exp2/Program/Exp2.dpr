program Exp2;
//The program calculates number of green and red bacteries after certain amount of tacts

//Console app
{$APPTYPE CONSOLE}

//Modules declaration
uses
  System.SysUtils;

var
  Red_Bacteries, Red_Bacteries_Before, Green_Bacteries, K, K1: integer;
  Red_BacteriesStr, K1Str: string;
  Checker : boolean;
  { Red_Bacteries -  current number of red bacteries
   Green_Bacteries -  current number of green bacteries
   Red_Bacteries_Before - number of red bacteries before the current division
   K - counter
   K1 - number of tacts
   Red_BacteriesStr - users mistakes checker for bacteries
   K1Str - users mistakes checker for tacts }

Begin
  //Entering the enclosed cycle
  while (true) do
  begin

    //Input number of bacteries and tacts
    writeln('Введите количество красных бактерий: ');
    readln(Red_BacteriesStr);
    writeln('Введите количество тактов');
    readln(K1Str);

    //Condition to start the calculations
    if (TryStrToInt(Red_BacteriesStr, Red_Bacteries) = true) and (TryStrToInt(K1Str, K1) = true) and (Red_Bacteries >=0) and (K1 >=0)   then
    begin
      //Set Green_Bacteries to the original value
      Green_Bacteries := 0;

      //Set Checker to the original value
      Checker := false;

      //Set K to the original value
      K := 1;

      //Check if something happens or not
      if (K1 = 0) or (Red_Bacteries = 0) then
      writeln('Ничего не происходит!')
      else
      begin
        writeln('Красных бактерий:                         Зеленых бактерий:                       Всего бактерий:            Тактов:');
        writeln(' __________________________________________________________________________________________________________________________________');
        //Entering the cycle
        while (Red_Bacteries >= 0) and (Green_Bacteries >= 0) and  (Red_Bacteries + Green_Bacteries >= 0) and (K <= K1) do
        begin

          //Assignment number of red bacteries before the current division to the original value
          Red_Bacteries_Before := Red_Bacteries;

          //Number of red bacteries after division
          Red_Bacteries := Green_Bacteries;

          //Number of green bacteries after division
          Green_Bacteries := Green_Bacteries + Red_Bacteries_Before;

          //Condition to output values
          if (Red_Bacteries >= 0) and (Green_Bacteries >= 0) and  (Red_Bacteries + Green_Bacteries >= 0) then
          begin
            //Output number of red, green bacteries and number of tacts
            writeln('|  Количество красных бактерий:',Red_Bacteries:10,'| Количество зеленых бактерий:',Green_Bacteries:10,'| Всего бактерий:',Red_Bacteries + Green_Bacteries:10,'| Количество тактов:',K:2,' |');
            writeln('|________________________________________|_______________________________________|__________________________|______________________|');
            //Increment K
            K := K + 1;
          end

          //If further calculations are impossible
          else
          begin
            writeln('Произошло переполнение, к сожалению, дальнейшие расчеты невозможны');
            Checker := true;
          end;
        end;

        //Output number of red, green bacteries, their sum and number of tacts if overflow happened
        if Checker = true then
        writeln('В итоге имеем: ',Red_Bacteries_Before,' красных бактерий, ',Red_Bacteries,' зеленых бактерий, ',Red_Bacteries + Red_Bacteries_Before,' всего бактерий, ', K-1, ' такта/тактов')

        //Output number of red, green bacteries, their sum and number of tacts
        else
        writeln('В итоге имеем: ',Red_Bacteries,' красных бактерий, ',Green_Bacteries,' зеленых бактерий, ',Red_Bacteries + Green_Bacteries,' всего бактерий, ', K-1, ' такта/тактов');
      end;
    end

    //If user inputted letters instead of numbers or numbers are too big
    else
    begin
      writeln('Произошла ошибка по одной из следующих причин:');
      writeln('1)Введенные вами числа слишком большие');
      writeln('2)Вы ввели не положительные целые числа');
    end;

    //Final operations
    writeln;

  end;
End.
