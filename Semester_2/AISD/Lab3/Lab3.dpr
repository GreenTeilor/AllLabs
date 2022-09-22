program Lab3;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

type
  elem = ^list;
  list = record
    number: integer;
    next: elem;
  end;
  mas = array of integer;

procedure MakeList(var x: elem; const n: integer);
var
  i: integer;
  ref: elem;
begin
  new(x);
  ref := x;
  for i := 1 to n do
  begin
    x^.number := i;
    new(x^.next);
    if x^.number <> n then
      x := x^.next;
  end;
  x^.next := ref;
  x := ref;
end;

procedure Delete(var x: elem; const k: integer; var deletedChildren: mas);
var
  i: integer;
  ref, temp: elem;
begin
  ref := x;
  SetLength(deletedChildren, 0);
  while x^.next <> x do
  begin
    for i := 1 to k - 1 do
    begin
      if i = k - 1 then
        temp := x;
      x := x^.next;
    end;
    SetLength(deletedChildren, length(deletedChildren) + 1);
    deletedChildren[length(deletedChildren) - 1] := x^.number;
    temp^.next := x^.next;
    dispose(x);
    x := temp^.next;
  end;
end;

procedure PrintDeleted(const deletedChildren: mas);
var
  i: integer;
begin
  for i := 0 to length(deletedChildren) - 1 do
    write(deletedChildren[i]:4);
end;

procedure PrintTable(const k: integer);
var
  i: integer;
  first: elem;
  deletedChildren: mas;
begin
  writeln('_____________________________________________________________________');
  write('|Количество детей | ');
  write('Номер удаляемого ребенка | ');
  writeln('Остался ребенок номер|');
  writeln('|_________________|__________________________|______________________|');
  for i := 1 to 64 do
  begin
    MakeList(first, i);
    Delete(first, k, deletedChildren);
    write('|',i:10,'       |');
    write(k:15,'           |');
    writeln(first^.number:12,'          |');
    writeln('|_________________|__________________________|______________________|')
  end;

end;

const
  N: integer = 50;
  k: integer = 45;
var
  first: elem;
  deletedChildren: mas;
begin
  MakeList(first, N);
  Delete(first, k, deletedChildren);
  writeln('Удаленные дети:');
  PrintDeleted(deletedChildren);
  writeln;
  PrintTable(k);
  readln;
end.
