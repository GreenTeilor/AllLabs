program Lab2;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

type
  pt = ^elem;
  elem = record
           koef: integer;
           power: integer;
           next: pt;
         end;

procedure makeList(var x: pt);
var
  i, N: integer;
  ref, temp: pt;
begin
  repeat
    write('¬ведите количество одночленов в многочлене: ');
    readln(N);
    if not(N>0) then
      writeln('ќшибка ввода');
  until N > 0;
  new(x);
  ref := x;
  for i := 1 to N do
  begin
    temp := x;
    new(x^.next);
    x := x^.next;
    write('¬ведите коэффициент ', i, ' одночлена: ');
    readln(x^.koef);
    write('¬ведите степень ', i, ' одночлена: ');
    readln(x^.power);
    if x^.koef = 0 then
    begin
      dispose(x);
      x := temp;
    end;
  end;
  x^.next :=  nil;
  x := ref;
end;

procedure printMn(x: pt);
begin
  if x^.next <> nil then
  begin
    x := x^.next;
      write(x^.koef,'x^', x^.power);
    x := x^.next;
    while x <> nil do
    begin
      write(' + ',x^.koef, 'x^', x^.power);
      x := x^.next;
    end;
  end;
end;

procedure sortMn(var x: pt);
var
  arr: array of array of integer;
  ref: pt;
  i, j, temp: integer;
begin
  ref := x;
  x := x^.next;
  i := 0;
  while x<>nil do
  begin
    inc(i);
    setLength(arr, i, 2);
    arr[i-1,0] := x^.koef;
    arr[i-1,1] := x^.power;
    x := x^.next;
  end;

  for i := 0 to length(arr) - 2 do
    for  j := 0 to length(arr) - 2 - i do
    begin
      if arr[j, 1] < arr[j + 1, 1] then
      begin
        temp := arr[j,0];
        arr[j,0] := arr[j + 1,0];
        arr[j + 1,0] := temp;
        temp := arr[j,1];
        arr[j,1] := arr[j + 1,1];
        arr[j + 1,1] := temp;
      end;
      if arr[j, 1] = arr[j + 1, 1] then
      begin
        if arr[j,0] < arr[j, 0] then
        begin
          temp := arr[j,0];
          arr[j,0] := arr[j + 1,0];
          arr[j + 1,0] := temp;
          temp := arr[j,1];
          arr[j,1] := arr[j + 1,1];
          arr[j + 1,1] := temp;
        end;
      end;
    end;

  x := ref;
  for i := 0 to length(arr) - 1 do
  begin
    x := x^.next;
    x^.koef := arr[i, 0];
    x^.power := arr[i, 1];
  end;
  x := ref;
end;

function equality(mn1, mn2: pt): boolean;
var
  i: integer;
  checker: boolean;
begin
  checker := true;
  mn1 := mn1^.next;
  mn2 := mn2^.next;
  while (mn1 <> nil) and (mn2 <> nil) and (checker) do
  begin
    if mn1^.koef <> mn2^.koef then
      checker := false;
    mn1 := mn1^.next;
    mn2 := mn2^.next;
    if ((mn1 = nil) and (mn2 <> nil)) or ((mn1 <> nil) and (mn2 = nil)) then
      checker := false;
  end;
  if ((mn1 = nil) and (mn2 <> nil)) or ((mn1 <> nil) and (mn2 = nil)) then
    checker := false;
  equality := checker;
end;

function meaning(mn: pt; x: real): real;
var
  sum: real;
begin
  sum := 0;
  mn := mn^.next;
  while mn <> nil do
  begin
    sum := sum + mn^.koef * exp(ln(x) * mn^.power);
    mn := mn^.next;
  end;
  meaning := sum;
end;

procedure add(mn1, mn2: pt; var result: pt);
var
  ref, tempMn1, tempMn2: pt;
  pow, sum: integer;
  checker: boolean;
begin
  new(result);
  if (mn1^.next <> nil) or (mn2^.next <> nil) then
  begin
  ref := result;
  if mn1^.next^.power >= mn2^.next^.power then
    pow := mn1^.next^.power
  else
    pow := mn2^.next^.power;
  tempMn1 := mn1;
  tempMn2 := mn2;
  while pow >= 0 do
  begin
    checker := false;
    mn1 := mn1^.next;
    mn2 := mn2^.next;
    sum := 0;
    while mn1 <> nil do
    begin
      if pow = mn1^.power then
      begin
        sum := sum + mn1^.koef;
        checker := true;
      end;
      mn1 := mn1^.next;
    end;
    while mn2 <> nil do
    begin
      if pow = mn2^.power then
      begin
        sum := sum + mn2^.koef;
        checker := true;
      end;
      mn2 := mn2^.next;
    end;

    if checker then
    begin
      new(result^.next);
      result := result^.next;
      result^.koef := sum;
      result^.power := pow;
    end;

    mn1 := tempMn1;
    mn2 := tempMn2;
    dec(pow);
  end;
  result^.next := nil;
  result := ref;
  end
  else
    result^.next := nil;
end;
var
  header1, header2, res: pt;
begin
  makeList(header1);
  sortMn(header1);
  printMn(header1);
  writeln;

  makeList(header2);
  sortMn(header2);
  printMn(header2);
  writeln;

  add(header1, header2, res);
  sortMn(res);
  printMn(res);
  readln;
end.
