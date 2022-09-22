Program Dates;
//Program calculates how many Friday 13-th were in certain period of time

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
Uses
  System.SysUtils;

//Types declaration
Type
  Month = (Январь, Февраль, Март, Апрель, Май, Июнь, Июль, Август, Сентябрь, Октябрь, Ноябрь, Декабрь);
  Week_Day = (Суббота, Воскресенье, Понедельник, Вторник, Среда, Четверг, Пятница);
  Day = 1..31;
{ Month - months type
  Week_Day - days of week type
  Day - days type }

//Constants declaration
Const
  NotLeapDays:array[Month] of Byte = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  LeapDays:array[Month] of Byte = (31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
  MonthArr: array[Month] of String = ('Январь', 'Февраль', 'Март', 'Апрель', 'Май', 'Июнь', 'Июль', 'Август', 'Сентябрь', 'Октябрь', 'Ноябрь', 'Декабрь');
{ NotLeapDays - days in months of not leap year
  LeapDays - days in months of leap year
  MonthArr - contains strings of months in order to output them if necessary }

//Variables declaration
Var
  currentWeekDay: Week_Day;
  currentMonth: Month;
  currentDay: Day;
  error: integer;
  startDay, startMonth, startYear, finishDay, finishMonth, finishYear, currentYear: integer;
  wd, startMonthTransformed, startYearTransformed, j, k: integer;
  Friday13: integer;
  startDayStr, startMonthStr, startYearStr, finishDayStr, finishMonthStr, finishYearStr: String;
  checker, leapYear: boolean;
{ currentWeekDay - current day of week in cycle
  currentMonth - current month in cycle
  currentDay - current date in cycle
  error - variable which is <> 0 if user made input mistake and 1 otherwise
  startDay - start day
  startMonth - start month
  startYear - start year
  finishDay - finish day
  finishMonth - finish month
  finishYear - finish year
  currentYear - current year in cycle
  wd - index of week day of the start day, 0 - saturday, 1 - sunday, etc.
  startMonthTransformed - transformed month in order to use it in Zellers formula
  startYearTransformed - transformed year in order to use it in Zellers formula
  j - part of the formula which calculates index of current day of week
  k - part of the formula which calculates index of current day of week
  Friday13 - contains number of fridays 13-th in inputted period
  startDayStr - mistakes checker for startDay
  startMonthStr - mistakes checker for startMonth
  startYearStr - mistakes checker for startYear
  finishDayStr - mistakes checker for finishDay
  finishMonthStr - mistakes checker for finishMonth
  finishYearStr - mistakes checker for finishYear
  checker - variable which is used to prevent mistakes because of leap years
  leapYear - true if year is leap, false otherwise }

//Start the program
Begin
  //Input start day
  repeat
    write('Пожалуйста, введите начальный день: ');
    readln(startDayStr);
    val(startDayStr, startDay, error);
    if (error <> 0) or ((startDay < 1) or (startDay > 31)) then
      writeln('Ошибка ввода');
  until (error = 0) and (startDay >= 1) and (startDay <= 31);

  //Input start month
  repeat
    write('Пожалуйста, введите начальный месяц: ');
    readln(startMonthStr);
    val(startMonthStr, startMonth, error);
    if (startDay > 29) and (startMonth = 2) then
      checker := false
    else
      checker := true;
    if (error <> 0) or ((startMonth < 1) or (startMonth > 12)) or (checker = false) then
      writeln('Ошибка ввода');
  until (error = 0) and (startMonth >= 1) and (startMonth <= 12) and (checker = true);

  //Input start Year
  repeat
    write('Пожалуйста, введите начальный год: ');
    readln(startYearStr);
    val(startYearStr, startYear, error);
    if (startYear mod 4 = 0) and not((startYear mod 100 = 0) and (startYear mod 400 <> 0)) then
      leapYear := true
    else
      leapYear := false;
    if (leapYear = false) and (startMonth = 2) and (startDay > 28) then
      checker := false
    else
      checker := true;
    if (error <> 0) or (startYear < 1) or (checker = false) then
      writeln('Ошибка ввода');
  until (error = 0) and (startYear >= 1) and (checker = true);

  //Input finish day
  repeat
    write('Пожалуйста, введите конечный день: ');
    readln(finishDayStr);
    val(finishDayStr, finishDay, error);
    if (error <> 0) or ((finishDay < 1) or (finishDay > 31)) then
      writeln('Ошибка ввода');
  until (error = 0) and (finishDay >= 1) and (finishDay <= 31);

  //Input finish month
  repeat
    write('Пожалуйста, введите конечный месяц: ');
    readln(finishMonthStr);
    val(finishMonthStr, finishMonth, error);
    if (finishDay > 29) and (finishMonth = 2) then
      checker := false
    else
      checker := true;
    if (error <> 0) or ((finishMonth < 1) or (finishMonth > 12)) or (checker = false) then
      writeln('Ошибка ввода');
  until (error = 0) and (finishMonth >= 1) and (finishMonth <= 12) and (checker = true);

  //Input finish year
  repeat
    write('Пожалуйста, введите конечный год: ');
    readln(finishYearStr);
    val(finishYearStr, finishYear, error);
    if (finishYear mod 4 = 0) and not((startYear mod 100 = 0) and (startYear mod 400 <> 0)) then
      leapYear := true
    else
      leapYear := false;
    if (leapYear = false) and (finishMonth = 2) and (finishDay > 28) then
      checker := false
    else
      checker := true;
    if (error <> 0) or (finishYear < 1) or (checker = false) or ((finishYear < startYear) or ((finishMonth < startMonth) and (finishYear <= startYear)) or ((finishDay <= startDay) and (finishMonth <= startMonth) and (finishYear <= startYear))) then
      writeln('Ошибка ввода');
  until (error = 0) and (finishYear >= 1) and (checker = true) and ((finishYear > startYear) or ((finishMonth > startMonth) and (finishYear >= startYear)) or ((finishDay > startDay) and (finishMonth >= startMonth) and (finishYear >= startYear)));

  //Space between input and output
  writeln;

  //Transform start month and start year in order to insert them into
  //Zellers formula
  if startMonth < 3 then
  begin
    startMonthTransformed := startMonth + 12;
    startYearTransformed := startYear - 1;
  end
  else
  begin
    startMonthTransformed := startMonth;
    startYearTransformed := startYear;
  end;

  //Find 1-st part of Zellers formula
  j := startYearTransformed div 100;

  //Find 2-nd part Zellers formula
  k := startYearTransformed mod 100;

  //Insert all components to Zellers formula and get index of week day of
  //start date as a result
  wd := (startDay + (13*(startMonthTransformed + 1) div 5) + k + (k div 4) + (j div 4) - 2*j) mod 7;

  //Set currentWeekDay to the original value
  currentWeekDay := Week_Day(wd);

  //Set currentMonth to the original value
  currentMonth :=  Month(startMonth - 1);

  //Set currentDay to the original value
  currentDay := Day(startDay);

  //Set currentYear to the original value
  currentYear := startYear;

  //Calculations
  while (currentYear <= finishYear) do
  begin

    //Leap year check
    if (currentYear mod 4 = 0) and not((currentYear mod 100 = 0) and (currentYear mod 400 <> 0)) then
      leapYear := true
    else
      leapYear := false;

    //If current year equals to finish year
    if currentYear = finishYear then
    begin

      //While current month less or equals to finishmonth
      while currentMonth <= Month(finishMonth - 1) do
      begin

        //If current month equals to finish month
        if currentMonth = Month(finishMonth - 1) then
        begin

          //While current day less or equals to finish day
          while currentDay <= Day(finishDay) do
          begin

            //If we met friday 13-th
            if (currentDay = 13) and (currentWeekDay = Пятница) then
            begin
              inc(Friday13);
              writeln(MonthArr[currentMonth],' ', currentYear, ' года');
            end;

            //Increment current day
            currentDay := succ(currentDay);

            //Increment current day of week
            if currentWeekDay = пятница then
              currentWeekDay := Week_Day(0)
            else
              currentWeekDay := succ(currentWeekDay);

          end;

          //Set current day to the first day of next month
          currentDay := Day(1);

        end

        //If current month doesn't equals to finish month
        else
        begin

          //If year is not leap
          if leapYear = false then
          begin

            //While current day less or equals to number of days
            //in current month of not leap year
            while currentDay <= Day(NotLeapDays[currentMonth]) do
            begin

              //If we met friday 13-th
              if (currentDay = 13) and (currentWeekDay = Пятница) then
              begin
                inc(Friday13);
                writeln(MonthArr[currentMonth],' ', currentYear, ' года');
              end;

              //Increment current day
              currentDay := succ(currentDay);

              //Increment current day of week
              if currentWeekDay = пятница then
                currentWeekDay := Week_Day(0)
              else
                currentWeekDay := succ(currentWeekDay);

            end;
          end

          //If year is leap
          else
          begin

            //While current day less or equals to number of days
            //in current month of leap year
            while currentDay <= Day(LeapDays[currentMonth]) do
            begin

              //If we met friday 13-th
              if (currentDay = 13) and (currentWeekDay = Пятница) then
              begin
                inc(Friday13);
                writeln(MonthArr[currentMonth],' ', currentYear, ' года');
              end;

              //Increment current day
              currentDay := succ(currentDay);

              //Increment current day of week
              if currentWeekDay = пятница then
                currentWeekDay := Week_Day(0)
              else
                currentWeekDay := succ(currentWeekDay);

            end;
          end;

          //Set current day to the first day of next month
          currentDay := Day(1);

        end;

        //Increment current month
        currentMonth := succ(currentMonth);
      end;

      //When current year is over
      currentMonth := Month(0);

    end

    //If current year doesn't equals to finish year
    else
    begin

      //While current month less of equals to december
      while currentMonth <= Month(11) do
      begin

        //If year is not leap
        if leapYear = false then
        begin

          //While current day less or equals to number of days
          //in current month of not leap year
          while currentDay <= Day(NotLeapDays[currentMonth]) do
          begin

            //If we met friday 13-th
            if (currentDay = 13) and (currentWeekDay = Пятница) then
            begin
              inc(Friday13);
              writeln(MonthArr[currentMonth],' ', currentYear, ' года');
            end;

            //Increment current day
            currentDay := succ(currentDay);

            //Increment current day of week
            if currentWeekDay = пятница then
              currentWeekDay := Week_Day(0)
            else
              currentWeekDay := succ(currentWeekDay);

          end;

          //Set current day to the first day of next month
          currentDay := Day(1);

        end

        //If year is leap
        else
        begin

          //While current day less or equals to number of days
          //in current month of leap year
          while currentDay <= Day(LeapDays[currentMonth]) do
          begin

            //If we met friday 13-th
            if (currentDay = 13) and (currentWeekDay = Пятница) then
            begin
              inc(Friday13);
              writeln(MonthArr[currentMonth],' ', currentYear, ' года');
            end;

            //Increment current day
            currentDay := succ(currentDay);

            //Increment current day of week
            if currentWeekDay = пятница then
              currentWeekDay := Week_Day(0)
            else
              currentWeekDay := succ(currentWeekDay);

          end;

          //Set current day to the first day of next month
          currentDay := Day(1);

        end;

        //Increment current month
        currentMonth := succ(currentMonth);

      end;

      //When current year is over
      currentMonth := Month(0);

    end;

    //Increment current year
    inc(currentYear);

  end;


  //Output number of fridays 13-th
  write('Число пятниц 13: ');
  writeln(Friday13);

  //Final operations
  readln;

End.

