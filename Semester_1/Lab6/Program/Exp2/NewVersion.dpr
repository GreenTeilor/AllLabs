program NewVersion;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

Const
  Week_Days: array[0..6] of String = ('Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday');
  MonthDays: array[1..12] of byte = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  Months: array[1..12] of string = ('������','�������', '����', '������', '���', '����', '����', '������', '��������', '�������', '������', '�������');

Type
  WeekDays = (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday);
var
  startDay, startMonth, startYear, finishDay, finishMonth, finishYear: integer;
  days: integer;
  counter: integer;
  startWeekDay: integer;
  currentYear, currentMonth, currentDay: integer;
  friday13WeekDay: integer;
  Friday13: integer;
begin
  startDay := 4;
  startMonth := 09;
  startYear := 1973;
  finishDay := 29;
  finishMonth := 02;
  finishYear := 2020;

  //Calculate number of days in all years before start date
  days := (startYear-1)*365;

  //Adding days in months
  for  counter := 1 to startMonth - 1 do
    inc(days, MonthDays[counter]);

  //Exclude one day if its 29 February
  if (startDay = 29) and (startMonth = 2) then
    dec(days);

  //Adding days
  inc(days, startDay);

  //Except not leap years
  for  counter := 1 to startYear do
    if (counter mod 4 = 0) and not((counter mod 100 = 0) and (counter mod 400 <> 0)) then
      inc(days);

  startWeekDay := days mod 7;

  //Set currentMonth to the original value
  currentMonth := startMonth;

  if startDay <= 13 then
    inc(days, 13-startDay)
  else
    begin
      inc(days, MonthDays[currentMonth - Days + 13]);
      inc(currentMonth);
    end;

  for currentYear := startYear to finishYear do
  begin
    if currentYear = finishYear then
      while currentMonth <= finishMonth do
      begin
        if days mod 7 = 5 then
        begin
          inc(Friday13);
          writeln(Months[currentMonth], ' ', currentYear,' ����');
        end;
        if ((currentYear mod 4 = 0) and not((currentYear mod 100 = 0) and (currentYear mod 400 <> 0))) and (currentMonth = 2) then
          inc(days);
        inc(days, MonthDays[currentMonth]);
        inc(currentMonth);
      end

    else
    begin
      while currentMonth <= 12 do
      begin
        if days mod 7 = 5 then
        begin
          inc(Friday13);
          writeln(Months[currentMonth], ' ', currentYear,' ����');
        end;
        if ((currentYear mod 4 = 0) and not((currentYear mod 100 = 0) and (currentYear mod 400 <> 0))) and (currentMonth = 2) then
          inc(days);
        inc(days,MonthDays[currentMonth]);
        inc(currentMonth);
      end;
      currentMonth := 1;
    end;

  end;

  writeln('����� ������ 13: ', Friday13);
  readln;
end.
