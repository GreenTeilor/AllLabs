program Lab9;
//Program give information about repaired appliances

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
uses
  System.SysUtils,
  unByGroup in '..\Interface\unByGroup.pas';

//Types declaration
type
  //Group of appliance
  TGroup = (TV, phone, computer, laptop);

  //Brand of appliance
  TBrand = (Samsung, Apple, Huawei, LG, HP);

  //Date type
  TDate = record
    day, month, year: integer;
  end;

  //Type with information about appliance
  TAppliance = record
    group: TGroup;
    brand: TBrand;
    receiveDate: TDate;
    returnDate: TDate;
    isReady: boolean;
  end;

//Get group of appliance
function GetGroup(group: integer): TGroup;
begin
  GetGroup := TGroup(group - 1);
end;

//Ouput group of appliance
function OutputGroup(group: TGroup): string;
begin
  case group of
    TV: OutputGroup := 'телевизор';
    phone: OutputGroup := 'телефон';
    computer: OutputGroup := 'компьютер';
    laptop: OutputGroup := 'ноутбук';
    else
      OutputGroup := 'новый тип';
  end;
end;

//Get group of appliance
function GetBrand(brand: integer): TBrand;
begin
  GetBrand := TBrand(brand - 1);
end;

//Output brand of appliance
function OutputBrand(brand: TBrand): string;
begin
  case brand of
    Samsung: OutputBrand := 'samsung';
    Apple: OutputBrand := 'apple';
    Huawei: OutputBrand := 'huawei';
    LG: OutputBrand := 'LG';
    HP: OutputBrand := 'HP'
    else
      OutputBrand := 'новая марка';
  end;
end;

//Get date
procedure GetDate(var date: TDate);
begin
  write('Введите день: ');
  readln(date.day);
  write('Введите месяц: ');
  readln(date.month);
  write('Введите год: ');
  readln(date.year);
end;

//Output date
function OutputDate(date: TDate): string;
begin
  write(date.day, '.', date.month, '.', date.year);
end;

//Return condition by index
function GetCondition(isReadyIndex: integer): boolean;
begin
  if isReadyIndex = 1 then
    GetCondition := false
  else
    GetCondition := true;
end;

//Output condition depending on value of isReady
function OutputCondition(isReady: boolean): string;
begin
  if isReady then
    OutputCondition := 'Готов'
  else
    OutputCondition := 'Не готов';
end;

procedure GetApplianceInfo(var appliance: TAppliance);
var
  groupIndex: integer;
  brandIndex: integer;
  isReadyIndex: integer;
  receiveDate: TDate;
  returnDate: TDate;
begin
  //Input information about new appliance
  writeln('Введите вид техники: 1 - телевизор   2 - телефон   3 - компьютер   4 - ноутбук');
  readln(groupIndex);
  appliance.group := GetGroup(groupIndex);
  writeln('Введите марку техники: 1 - samsung   2 - apple   3 - huawei   4 - LG   5 - HP');
  readln(brandIndex);
  appliance.brand := GetBrand(brandIndex);
  writeln('Введите дату приемки: ');
  GetDate(appliance.receiveDate);
  writeln('Введите дату исполнения заказа: ');
  GetDate(appliance.returnDate);
  writeln('Введите состояние готовности: 1 - не готов   2 - готов');
  readln(isReadyIndex);
  appliance.isReady := GetCondition(isReadyIndex);
end;

//Input information about new appliance
procedure AddAppliance(appliance: TAppliance);
var
  dataBase: file of TAppliance;
begin

  //Create file if it doesnt exist
  if not FileExists('dataBase.dt') then
  begin
    AssignFile(dataBase, 'dataBase.dt');
    Rewrite(dataBase);
    CloseFile(dataBase);
  end;

  //Move info about new appliance to file
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  Seek(dataBase, FileSize(dataBase));
  Write(dataBase, appliance);
  CloseFile(dataBase);
end;

//Print info about 1 appliance
procedure PrintApplianceInfo(appliance: TAppliance);
begin
  write('Группа: ');
  writeln(OutputGroup(appliance.group));
  write('Марка: ');
  writeln(OutputBrand(appliance.brand));
  write('Дата получения: ');
  writeln(OutputDate(appliance.receiveDate));
  write('Дата исполнения: ');
  writeln(OutputDate(appliance.returnDate));
  write('Готовность: ');
  writeln(OutputCondition(appliance.isReady));
end;

//Forward declaration
function isLater(date1, date2: TDate): boolean; forward;

//Sort group of appliances by date
procedure SortAppliancesInGroup(var group: array of TAppliance);
var
  i, j: integer;
  temp: TAppliance;
begin
  for i := 0 to length(group) - 2 do
    for j := 0 to length(group) - i - 2 do
      if isLater(group[j].returnDate, group[j+1].returnDate) then
      begin
        temp := group[j];
        group[j] := group[j+1];
        group[j+1] := temp;
      end;
end;

//Print information about all appliances
procedure PrintConditions;
var
  dataBase: file of TAppliance;
  TVGroup, phoneGroup, computerGroup, laptopGroup: array of TAppliance;
  appliance: TAppliance;
  i: integer;
begin
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  SetLength(TVGroup, 0);
  SetLength(phoneGroup, 0);
  SetLength(computerGroup, 0);
  SetLength(laptopGroup, 0);
  while not Eof(dataBase) do
  begin
    read(dataBase, appliance);
    case appliance.group of
    TV:
      begin
        Setlength(TVGroup, length(TVGroup) + 1);
        TVGroup[length(TVGroup) - 1] := appliance;
      end;
    phone:
      begin
        Setlength(phoneGroup, length(phoneGroup) + 1);
        phoneGroup[length(phoneGroup) - 1] := appliance;
      end;
    computer:
      begin
        Setlength(computerGroup, length(computerGroup) + 1);
        computerGroup[length(computerGroup) - 1] := appliance;
      end;
    laptop:
      begin
        Setlength(laptopGroup, length(laptopGroup) + 1);
        laptopGroup[length(laptopGroup) - 1] := appliance;
      end;
    end;
  end;
  SortAppliancesInGroup(TVGroup);
  SortAppliancesInGroup(phoneGroup);
  SortAppliancesInGroup(computerGroup);
  SortAppliancesInGroup(laptopGroup);
  writeln('Телевизоры:');
  for i := 0 to length(TVGroup) - 1 do
  begin
    writeln(i + 1, ')');
    PrintApplianceInfo(TVGroup[i]);
  end;
  writeln;
  writeln;
  writeln('Телефоны:');
  for i := 0 to length(phoneGroup) - 1 do
  begin
    writeln(i + 1, ')');
    PrintApplianceInfo(phoneGroup[i]);
  end;
  writeln;
  writeln;
  writeln('Компьютеры:');
  for i := 0 to length(computerGroup) - 1 do
  begin
    writeln(i + 1, ')');
    PrintApplianceInfo(computerGroup[i]);
  end;
  writeln;
  writeln;
  writeln('Ноутбуки:');
  for i := 0 to length(laptopGroup) - 1 do
  begin
    writeln(i + 1, ')');
    PrintApplianceInfo(laptopGroup[i]);
  end;
  writeln;
  writeln;
  CloseFile(dataBase);
end;

//Return true if date1 later than date2
function isLater(date1, date2: TDate): boolean;
begin
  if (date1.year > date2.year) or ((date1.year >= date2.year) and (date1.month > date2.month)) or ((date1.year >= date2.year) and (date1.month >= date2.month) and (date1.day > date2.day)) then
    isLater := true
  else
    isLater := false;
end;

//Print expired orders
procedure PrintExpired(curDate: TDate);
var
  dataBase: file of TAppliance;
  appliance: TAppliance;
begin
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  while not Eof(dataBase) do
  begin
    read(dataBase, appliance);
    if isLater(curDate, appliance.returnDate) and (not appliance.isReady) then
    begin
      PrintApplianceInfo(appliance);
      writeln;
    end;

  end;
  CloseFile(dataBase);
end;

//Compare 2 dates, return true if equal
function areEqualDates(date1, date2: TDate): boolean;
begin
  if (date1.day = date2.day) and (date1.month = date2.month) and (date1.year = date2.year) then
    areEqualDates := true
  else
    areEqualDates := false;
end;

//Search appliance by group, receive Date and return Date, then print
//critPar:  1 - Search by group  2 - Search by receiveDate  3 - Search by returnDate
procedure SearchAppliance;
var
  dataBase: file of TAppliance;
  appliance: TAppliance;
  curAppliance: TAppliance;
  count2, count: integer;
  isFound: boolean;
begin
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  writeln('1 - Вид техники   2 - Дата получения   3 - Дата исполнения заказа');
  write('Выберите параметр, по которому хотите искать устройство: ');
  readln(count2);
  writeln;
  isFound := false;
  case count2 of
  1:
    begin
      writeln('Введите вид техники: 1 - телевизор   2 - телефон   3 - компьютер   4 - ноутбук');
      readln(count);
      appliance.group := GetGroup(count);
    end;
  2:
    begin
      writeln('Введите дату получения: ');
      GetDate(appliance.receiveDate);
    end;
  3:
    begin
      writeln('Введите дату исполнения заказа: ');
      GetDate(appliance.returnDate);
    end;
  end;

  while not Eof(dataBase) do
  begin
    read(dataBase, curAppliance);
    case count2 of
    1:
      begin
        if curAppliance.group = appliance.group  then
        begin
          PrintApplianceInfo(curAppliance);
          isFound := true;
          writeln;
        end;
      end;
    2:
      begin
        if  areEqualDates(curAppliance.receiveDate, appliance.receiveDate) then
        begin
          PrintApplianceInfo(curAppliance);
          isFound := true;
          writeln;
        end;
      end;
    3:
      begin
        if  areEqualDates(curAppliance.returnDate, appliance.returnDate) then
        begin
          PrintApplianceInfo(curAppliance);
          isFound := true;
          writeln;
        end;
      end;
    end;
  end;
  if not isFound then
    writeln('Ничего не найдено!');
  CloseFile(dataBase);
end;

//Print all appliances
procedure PrintFile;
var
  appliance: Tappliance;
  dataBase: file of TAppliance;
  i: integer;
begin
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  i := 1;
  while not Eof(dataBase) do
  begin
    read(dataBase, appliance);
    writeln(i,')');
    PrintApplianceInfo(appliance);
    writeln;
    inc(i);
  end;
  CloseFile(dataBase);
end;

//Delete appliance
procedure DeleteAppliance(index: integer);
var
  i: integer;
  dataBase: file of TAppliance;
  appliance: TAppliance;
begin
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  seek(dataBase, index - 1);
  for i := index - 1 to FileSize(dataBase) - 2 do
  begin
    Seek(dataBase, i + 1);
    Read(dataBase, appliance);
    Seek(dataBase, i);
    Write(dataBase, appliance);
  end;
  Seek(dataBase, FileSize(dataBase) - 1);
  Truncate(dataBase);
  CloseFile(dataBase);
end;

//Edit appliance
procedure EditAppliance(index: integer);
var
  i, count: integer;
  dataBase: file of TAppliance;
  appliance: TAppliance;
begin
  AssignFile(dataBase, 'dataBase.dt');
  Reset(dataBase);
  Seek(dataBase, index - 1);
  Read(dataBase, appliance);
  Seek(dataBase, index - 1);
  writeln('1 - Вид техники   2 - Марка техники   3 - Дата приемки   4 - Дата исполнения заказа   5 - Состояние готовности');
  writeln('Введите параметр, который вы желаете отредактировать:');
  readln(i);
  case i of
  1:
    begin
      writeln('Введите вид техники: 1 - телевизор   2 - телефон   3 - компьютер   4 - ноутбук');
      readln(count);
      appliance.group := GetGroup(count);
    end;
  2:
    begin
      writeln('Введите марку техники: 1 - samsung   2 - apple   3 - huawei   4 - LG   5 - HP');
      readln(count);
      appliance.brand := GetBrand(count);
    end;
  3:
    begin
      writeln('Введите дату приемки: ');
      GetDate(appliance.receiveDate);
    end;
  4:
    begin
      writeln('Введите дату исполнения заказа: ');
      GetDate(appliance.returnDate);
    end;
  5:
    begin
      writeln('Введите состояние готовности: 1 - не готов   2 - готов');
      readln(count);
      appliance.isReady := GetCondition(count);
    end;
  end;
  Write(dataBase, appliance);
end;

var
  keepOn, option: integer;
  firstTime: boolean;
  appliance: TAppliance;
  date: TDate;
begin
  firstTime := true;
  writeln('Добро пожаловать в радиоателье!');
  repeat
    if not firstTime then
    begin
      writeln('Хотите ли вы продолжить работу с радиоателье?   1 - Да   0 - Нет');
      readln(keepOn);
    end
    else
      keepOn := 1;
    if keepOn = 1 then
    begin
      writeln('1 - Добавить устройство   2 - Удалить устройство   3 - Редактировать информацию об устройстве   4 - Информация о заказах, не выполненных в срок   5 - Поиск изделия   6 - Состояние готовности по группам');
      write('Выберите желаемое действие: ');
      readln(option);
      case option of
      1:
        begin
          GetApplianceInfo(appliance);
          AddAppliance(appliance);
        end;
      2:
        begin
          PrintFile;
          write('Введите номер устройства, которое вы желаете удалить: ');
          readln(option);
          DeleteAppliance(option);
        end;
      3:
        begin
          PrintFile;
          write('Введите номер устройства, которое вы желаете редактировать: ');
          readln(option);
          EditAppliance(option);
        end;
      4:
        begin
          writeln('Введите сегодняшнюю дату');
          GetDate(date);
          PrintExpired(date);
        end;
      5:
        begin
          SearchAppliance;
        end;
      6:
        begin
          PrintConditions;
        end;
      end;
    end;
    firstTime := false;
  until keepOn = 0;
  readln;
end.
