program Lab1;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

const
    N = 3;

type elem = ^list;
list = record
         lastName: string;
         number: string;
         next: elem;
end;

function isValidNumber(number: string): boolean;
var
  numberInt: integer;
begin
  if (tryStrToInt(trim(number), numberInt)) and (length(trim(number)) = 7) then
    isValidNumber := true
  else
    isValidNumber := false;
end;

procedure makeList(var x: elem);
var
  i: integer;
  ref: elem;
begin
  new(x);
  ref := x;
  for i := 1 to N do
  begin
    new(x^.next);
    x := x^.next;
    write('������� ������� ', i, ' ������������: ');
    readln(x^.lastName);
    repeat
      write('������� ����� �������� ', i, ' ������������: ');
      readln(x^.number);
      if not(isValidNumber(x^.number)) then
        writeln('������ �����!');
    until isValidNumber(x^.number);
  end;
  x^.next := nil;
  x := ref;
end;

procedure sortList(x: elem);
var arr: array of array of string;
    i, j: integer;
    temp: string;
    ref: elem;
begin
  ref := x;
  x := x^.next;
  i := 0;
  while x<>nil do
  begin
    inc(i);
    setLength(arr, i, 2);
    arr[i-1,0] := x^.lastName;
    arr[i-1,1] := x^.number;
    x := x^.next;
  end;
  for i := 0 to length(arr) - 2 do
    for j := 0 to length(arr) - i - 2 do
      if AnsiLowerCase(arr[j, 0]) > AnsiLowerCase(arr[j + 1, 0]) then
      begin
        temp := arr[j, 0];
        arr[j, 0] := arr[j+1, 0];
        arr[j+1, 0] := temp;
        temp := arr[j, 1];
        arr[j, 1] := arr[j+1, 1];
        arr[j+1, 1] := temp;
      end;
  x := ref;
  for i := 0 to length(arr) - 1 do
  begin
    x := x^.next;
    x^.lastName := arr[i, 0];
    x^.number := arr[i, 1];
  end;
end;

procedure searchNumber(x: elem; phoneNumber: string);
var
  i: integer;
  flag: boolean;
begin
  x := x^.next;
  flag := false;
  while x <> nil do
  begin
    if trim(x^.number) = trim(phoneNumber) then
    begin
      writeln(trim(x^.lastName),' ', trim(x^.number));
      if not(flag) then
        flag := true;
    end;
    x := x^.next;
  end;
  if not(flag) then
    writeln('������������� � ����� ������� ���!');
end;

procedure searchLastName(x: elem; lastName: string);
var
  i: integer;
  flag1, flag2: boolean;
begin
  x := x^.next;
  flag1 := false;
  flag2 := false;
  while (x <> nil) and not(flag2) do
  begin
    if trim(ansiLowerCase(x^.lastName)) = trim(ansiLowerCase(lastName)) then
    begin
      flag1 := true;
      while (x <> nil) and (trim(ansiLowerCase(x^.lastName)) = trim(ansiLowerCase(lastName))) do
      begin
        writeln(trim(x^.lastName),' ', trim(x^.number));
        x := x^.next;
      end;
      flag2 := true;
    end;
    if not(flag2) then
      x := x^.next;
  end;
  if not(flag1) then
    writeln('������������� � ����� �������� ���!');
end;

procedure printList(x: elem);
begin
  x := x^.next;
  while x <> nil do
  begin
    writeln(trim(x^.lastName),' ', trim(x^.number));
    x := x^.next;
  end;
end;


var
  header: elem;
  num, lastName: string;
begin
  makeList(header);
  sortList(header);
  writeln;
  writeln('������ ���� ���������:');
  printList(header);
  writeln;
  write('������� ������� �����: ');
  readln(num);
  writeln('������������ � ������� ', num, ':');
  searchNumber(header, num);
  writeln;
  write('������� ������� �������: ');
  readln(lastName);
  writeln('������������ � �������� ', lastName, ':');
  searchLastName(header, lastName);
  readln;
end.
