program lab2edit;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;
var Num, NumCopy1, NumCopy2, NumCopy3, NumCopy4 , Divider, Sumdigit1, SumEachDigit1, SumEachDigit2, DividerCopy, MultipliersSum1, MultipliersSum2, N1, N: Integer;
    SqrtNum, SqrtNumCopy: real;
    flag1, flag2, flag3: boolean;

begin
  Try
  writeln('������� ����� ������ �����-����� ����� �� ���� ��������:');
  readln(N);
  N1 := 0;
  Num := 4;
  while N1 < N do
  begin
    flag1 := false;
    flag2 := false;
    flag3 := false;
//This part of code finds sum of all digits of simple  multipliers
    NumCopy2 := Num;
    NumCopy3 := Num;
    NumCopy4 := Num;
    NumCopy1 := Num;
    Divider := 2; {������ �������� 2}
    MultipliersSum1 := 0;
    while Num > 1 do
    begin {���� ����� �� 1}
      if Num mod Divider = 0 then
      begin {���� ����� ������� �� ��������� ��������}
        DividerCopy := Divider;
        Sumdigit1 := 0;
        while DividerCopy <> 0 do
        begin
          Sumdigit1 := Sumdigit1 + (DividerCopy mod 10);
          DividerCopy := DividerCopy div 10;
        end;
        MultipliersSum1 := MultipliersSum1 + Sumdigit1;
        Num := Num div Divider; {����� �����}
      end
      else
      Divider := Divider + 1; {����������� ��������}
    end; {while}
    writeln('����� ���� ������� ���������� ��������� �����:',MultipliersSum1);




//This part of code finds sum of all digits of number
    SumEachDigit1 := 0;
    while NumCopy1<>0 do
    begin
      SumEachDigit1 := SumEachDigit1 + (NumCopy1 mod 10);
      NumCopy1 := NumCopy1 div 10;
    end;
    writeln('����� ���� ���� ��������� �����:',SumEachDigit1);




//This part of code compares value of Sum_Common and Sum2
    if (SumEachDigit1 = MultipliersSum1) and (Divider <> NumCopy2) then
    begin
      writeln('���� ����� - ����� �����!!!');
      flag1 := true;
    end
    else
    writeln('���, ���� ����� - �� ����� �����');



//This part of code checks if sum of all numbers of original number is Smyth number too
    NumCopy1 := SumEachDigit1;
    NumCopy2 := SumEachDigit1;
    Divider := 2; {������ �������� 2}
    MultipliersSum2 := 0;
    while SumEachDigit1 > 1 do
    begin {���� ����� �� 1}
      if SumEachDigit1 mod Divider = 0 then
      begin {���� ����� ������� �� ��������� ��������}
        DividerCopy := Divider;
        Sumdigit1 := 0;
        while DividerCopy<>0 do
        begin
          Sumdigit1 := Sumdigit1 + (DividerCopy mod 10);
          DividerCopy := DividerCopy div 10;
        end;
        MultipliersSum2 := MultipliersSum2 + Sumdigit1;
        SumEachDigit1 := SumEachDigit1 div Divider; {����� �����}
      end
      else
      Divider := Divider + 1; {����������� ��������}
    end; {while}
    writeln('����� ���� ������� ���������� �����, ����������� ������ ���� ��������� �����:',MultipliersSum2);
//This part of code finds sum of all digits of sum of all digits of original number
    SumEachDigit2 := 0;
    while NumCopy1<>0 do
    begin
      SumEachDigit2 := SumEachDigit2 + (NumCopy1 mod 10);
      NumCopy1 := NumCopy1 div 10;
    end;
    writeln('����� ���� �����, ����������� ������ ���� ��������� �����:',SumEachDigit2);




//This part of code checks if sum of all digits of original number is Smyth number
    if (SumEachDigit2 = MultipliersSum2) and (Divider <> NumCopy2) then
    begin
      writeln('���� ����� - ����� ����� �����!!!');
      flag2 := true;
    end
    else
    writeln('���, ���� ����� - �� ����� ����� �����');


//This part of code checks if original number is a full square
    SqrtNum := sqrt(NumCopy3);
    SqrtNumCopy := SqrtNum;
    if SqrtNum = trunc(SqrtNum) then
    begin
      NumCopy3 := trunc(SqrtNum);
      Divider := 2; {������ �������� 2}
      while SqrtNum > 1 do
      begin {���� ����� �� 1}
        if trunc(SqrtNum) mod Divider = 0 then {���� ����� ������� �� ��������� ��������}
        SqrtNum := trunc(SqrtNum) div Divider {����� �����}
        else
        Divider := Divider + 1; {����������� ��������}
      end; {while}
    end;
   if SqrtNumCopy = Divider then
    begin
      writeln('���� ����� - ������ �������!');
      flag3 := true;
    end
    else
    writeln ('���� ����� - �� ������ �������');
    if (flag1 = true) and (flag2 = true) and (flag3 = true) then
    N1 := N1 + 1;
    NumCopy4  := NumCopy4 + 1;
    Num := NumCopy4;
  end;
  writeln('���� �����:',Num - 1);

Except
  writeln('������ �����');
End;
//Final operations
  ReadLn;
end.
