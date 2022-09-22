program Lab4;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

type
  elem1 = ^list1;
  elem2 = ^list2;

  list1 = record
    phoneNumber: string;
    next: elem1;
    prev: elem1;
  end;

  list2 = record
    phoneNumber: string;
    next: elem2;
  end;

//Check validity of inputted phone number
function isValidInput(phoneNumber: string): boolean;
var
  isValidCharacters, isValidLength: boolean;
  i: integer;
begin
  isValidCharacters := true;
  isValidLength := true;
  i := 1;

  //Check validity of all characters in string(only digits allowed)
  while (i <= length(phoneNumber)) and (isValidCharacters) do
  begin
    if not(charInSet(phoneNumber[i], ['0'..'9'])) then
      isValidCharacters := false;
    inc(i);
  end;

  //Check validity of string length(only 7 or 3 allowed)
  isValidLength :=  (length(trim(phoneNumber)) = 7) or (length(trim(phoneNumber)) = 3);

  //Return true if both conditions are fullfilled
  isValidInput := isValidCharacters and isValidLength;
end;

//Create list
procedure makeList(var first, last: elem1);
const
  N: integer = 6;
var
  i: integer;
  temp, ref: elem1;
begin
  new(first);
  first^.prev := nil;
  ref := first;
  for i := 1 to N do
  begin
    repeat
      write('Введите ', i, ' номер: ');
      readln(first^.phoneNumber);
      if not(isValidInput(first^.phoneNumber)) then
        writeln('INVALID INPUT!');
    until isValidInput(first^.phoneNumber);
    if i <> N then
    begin
      new(first^.next);
      temp := first;
      first := first^.next;
      first^.prev := temp;
    end
    else
      first^.next := nil;
  end;
  last := first;
  first := ref;
end;

procedure printList(first, last: elem1);
begin
  while last <> nil do
  begin
    writeln(last^.phoneNumber);
    last := last^.prev;
  end;
end;

procedure createNewList(first, last: elem1; var newFirst: elem2);
var
  ref: elem2;
begin
  new(newFirst);
  ref := newFirst;
  while last <> nil do
  begin
    if length(last^.phoneNumber) = 3 then
    begin
      new(newFirst^.next);
      newFirst := newFirst^.next;
      newFirst^.phoneNumber := last^.phoneNumber;
    end;
    last := last^.prev;
  end;
  newFirst^.next := nil;
  newFirst := ref;
end;

procedure sortNewList(var newFirst: elem2);
var
  mas: array of string;
  i, j: integer;
  temp: string;
  ref: elem2;
begin
  ref := newFirst;
  newFirst := newFirst^.next;
  i := 0;
  while newFirst <> nil do
  begin
    setLength(mas, length(mas) + 1);
    mas[i] := newFirst^.phoneNumber;
    newFirst := newFirst^.next;
    inc(i);
  end;
  newFirst := ref;
  for i := 0 to length(mas) - 2 do
    for j := 0 to length(mas) - 2 - i do
      if mas[j] > mas[j+1] then
      begin
        temp := mas[j];
        mas[j] := mas[j+1];
        mas[j+1] := temp;
      end;
  newFirst := newFirst^.next;
  i := 0;
  while newFirst <> nil do
  begin
    newFirst^.phoneNumber := mas[i];
    newFirst := newFirst^.next;
    inc(i);
  end;
  newFirst := ref;
end;

procedure printNewList(newFirst: elem2);
begin
  newFirst := newFirst^.next;
  while newFirst <> nil do
  begin
    writeln(newFirst^.phoneNumber);
    newFirst := newFirst^.next;
  end;
end;

var
  head, tail: elem1;
  newHead: elem2;
begin
  makeList(head, tail);
  writeln;
  writeln('Все номера: ');
  printList(head, tail);
  createNewList(head, tail, newHead);
  sortNewList(newHead);
  writeln;
  writeln('Отсортированный список номеров спцеслужб: ');
  printNewList(newHead);
  readln;
end.
