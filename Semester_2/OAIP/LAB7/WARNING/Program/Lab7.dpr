program Lab7;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

type
  ��� = (����, ������, ���, ����, ������, ����, ������, ����, ���, �����, ���);
  ����� = set of ���;
  ������ = Array[���] of �����;

function Everywhere(group: ������): boolean;
var
  stateArr: array[���] of boolean;
  i, j: integer;
  isPresent: boolean;
begin
  for i := 1 to 11 do
    stateArr[���(i-1)] := true;
  for i := 1 to 11 do
    for j := 1 to 11 do
      if not ((���(j-1) in group[���(i-1)])) and (���(j-1) <> ���(i-1)) then
        stateArr[���(j-1)] := false;
  isPresent := false;
  i := 1;
  while (i <= 11) and not (isPresent) do
  begin
    if stateArr[���(i-1)] then
      isPresent := true;
    inc(i);
  end;
  Everywhere := isPresent;
end;

var
  group: ������;
begin
  group[����] := [������, ���, ���];
  group[������] := [���, ������];
  group[���] := [������, ������, ���];
  group[����] := [������, ������, ���];
  group[������] := [������];
  group[����] := [������, ������, ���];
  group[������] := [������, ���, ������];
  group[����] := [������, ������, ���];
  group[���] := [������, ���, ������];
  group[�����] := [������, ������, ���, ���];
  group[���] := [������, ���, ������];
  if Everywhere(group) then
    writeln('���� �������, ������� ��� � ������ � ���� ���������!')
  else
    writeln('��� ��������, ������� ��� � ������ � ���� ���������!');
  readln;
end.
