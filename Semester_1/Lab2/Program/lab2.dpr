program lab2;
//Program finds Smyth number with special conditions

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils;

//Variables declaration
var Num, NumDigitCopy1, NumDigitCopy2, NumCopy3, NumCopy4 , Divider, Sumdigit, SumEachDigit1, SumEachDigit2, DividerCopy, MultipliersSum1, MultipliersSum2, N1, N, Error: Integer;
    SqrtNum, SqrtNumCopy: real;
    Flag1, Flag2, Flag3, Checker: boolean;
    NStr: String;
  { Num - potential Smyth number with special conditions
    NumDigitCopy1 - Num and then SumEachDigit1 copy
    NumDigitCopy2 - Num and then SumEachDigit2 copy
    NumCopy3 - Num copy
    NumCopy4 - Num copy
    Divider - divider in all cases to find all simple multipliers of certain number
    SumDigit - auxiliary variable which contains sum of digits of multiplier after each division
    SumEachDigit1 - sum of digits of original number
    SumEachDigit2 - sum of digits of sum of digits of original number
    DividerCopy - Divider copy
    MultipliersSum1 - sum of all digits of simple multipliers of original number
    MultipliersSum2 - sum of all digits of simple multipliers of sum of digits of original number
    N1 - cycle counter
    N - number of Smyth number with special conditions
    NStr - mistakes checker
    Error - variable, which is 1 if user made a mistake and 0 if not
    SqrtNum - square root from Num
    SqrtNumCopy - SqrtNum copy
    Flag1 - Smyth number checker
    Flag2 - Super-Smyth number checker
    Flag3 - Full square checker
    Checker - false if user made a mistake true if not }

//Start the program
Begin

  //Repeating the cycle
  while(True) do
  begin

    //Protection from mistakes
    Checker := false;
    while Checker = false  do
    begin
      writeln('������� ����� ������ �����-����� ����� �� ���� ��������:');
      readln(NStr);
      val(NStr,N,Error);
      if (Error = 0) and (N > 0) then
      Checker := true
      else
      writeln('������ �����');
    end;

    //Set N1, Num to the original value
    N1 := 0;
    Num := 4;

    //Entering the cycle
    while N1 < N do
    begin

      //Check if square from Num is integer
      if sqrt(Num) = trunc(sqrt(Num)) then
      begin

        //Set Flag1, Flag2, Flag3 to the original value
        flag1 := false;
        flag2 := false;
        flag3 := false;

        //Copying Num
        NumDigitCopy1 := Num;
        NumDigitCopy2 := Num;
        NumCopy3 := Num;
        NumCopy4 := Num;

        //This part of code finds all simple multimpliers of Num
        Divider := 2;{First divider is 2}
        MultipliersSum1 := 0;
        while Num > 1 do{While Num is not 1}
        begin
          if Num mod Divider = 0 then
          begin {If Num divides by Divider}
            DividerCopy := Divider;
            Sumdigit := 0;

            //Find sum of all digits of simple multipliers
            while DividerCopy <> 0 do
            begin
              Sumdigit := Sumdigit + (DividerCopy mod 10);
              DividerCopy := DividerCopy div 10;
            end;
            MultipliersSum1 := MultipliersSum1 + Sumdigit;

            Num := Num div Divider;
          end
          else{If Num not divides by Divider}
          Divider := Divider + 1;
        end;

        //This part of code finds sum of all digits of original number
        SumEachDigit1 := 0;
        while NumDigitCopy1<>0 do
        begin
          SumEachDigit1 := SumEachDigit1 + (NumDigitCopy1 mod 10);
          NumDigitCopy1 := NumDigitCopy1 div 10;
        end;

        //This part of code checks if Num is a Smyth number
        if (SumEachDigit1 = MultipliersSum1) and (Divider <> NumDigitCopy2) then
        Flag1 := true;

        //This part of code finds all simple multipliers of sum of all digits of original number
        NumDigitCopy1 := SumEachDigit1;
        NumDigitCopy2 := SumEachDigit1;
        Divider := 2;{First divider is 2}
        MultipliersSum2 := 0;
        while SumEachDigit1 > 1 do
        begin {While SumEachDigit is not 1}
          if SumEachDigit1 mod Divider = 0 then
          begin{If SumEachDigit divides by Divider}
            DividerCopy := Divider;
            Sumdigit := 0;

            //Find sum of all digits of simple multipliers
            while DividerCopy<>0 do
            begin
              Sumdigit := Sumdigit + (DividerCopy mod 10);
              DividerCopy := DividerCopy div 10;
            end;
            MultipliersSum2 := MultipliersSum2 + Sumdigit;

            SumEachDigit1 := SumEachDigit1 div Divider;
          end
          else{If SumEachDigit not divides by Divider}
          Divider := Divider + 1;
        end;

        //This part of code finds sum of all digits of sum of all digits of original number
        SumEachDigit2 := 0;
        while NumDigitCopy1<>0 do
        begin
          SumEachDigit2 := SumEachDigit2 + (NumDigitCopy1 mod 10);
          NumDigitCopy1 := NumDigitCopy1 div 10;
        end;

        //This part of code checks if Num is a Super-Smyth number
        if (SumEachDigit2 = MultipliersSum2) and (Divider <> NumDigitCopy2) then
        Flag2 := true;

        //This part of code finds all simple multipliers of square root from Num
        SqrtNum := sqrt(NumCopy3);{Find square root from Num}
        SqrtNumCopy := SqrtNum;{Memorize square root from Num}
        Divider := 2;{First divider is 2}
        while SqrtNum > 1 do
        begin{While SqrtNum is not 1}
          if trunc(SqrtNum) mod Divider = 0 then{If SqrtNum divides by Divider}
          SqrtNum := trunc(SqrtNum) div Divider
          else{If SqrtNum not divides by divider}
          Divider := Divider + 1;
        end;

        //This part of code checks if Num is a full square
        if SqrtNumCopy = Divider then
        Flag3 := true;

        //If Num satisfies all 3 conditions
        if (flag1 = true) and (flag2 = true) and (flag3 = true) then
        N1 := N1 + 1;

        //Increment Num
        if N1 <> N then
        NumCopy4  := NumCopy4 + 1;
        Num := NumCopy4;

      end

      //If square root from Num is not integer
      else
      Num := Num + 1;
    end;

    //Output Smyth number with special conditions
    writeln('���� �����:',Num);

    //Final operations
    writeln;
  end;
End.
