program Lab5;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

type
  TStake = record
      top: integer;
      elem: array[1..1000] of string;
  end;

const
  N: integer = 1000;

//Make empty stake
procedure MakeNull(var stake: TStake);
var
  i: integer;
begin
  stake.top := N + 1;
  for i := 1 to N do
    stake.elem[i] := '';
end;

//Return element from top of the stake
function Top(stake: TStake): string;
begin
  Top := stake.elem[stake.top];
end;

//Pop value from top of the stake to valuePop
procedure Pop(var stake: TStake; var valuePop: string);
begin
  valuePop := stake.elem[stake.top];
  stake.elem[stake.top] := '';
  inc(stake.top);
end;

//Push valuePush to the top of stake
procedure Push(var stake: TStake; valuePush: string);
begin
  dec(stake.top);
  stake.elem[stake.top] := valuePush;
end;

//Return true if stake emty, false otherwise
function IsEmpty(stake: TStake): boolean;
var
  i: integer;
  checker: boolean;
begin
  checker := true;
  i := 1;
  while (i <= N) and (checker) do
  begin
    if stake.elem[i] <> '' then
      checker := false;
    inc(i);
  end;
  IsEmpty := checker;
end;

//Return relative priority of element
function RelPriority(character: char): integer;
begin
  case UpCase(character) of
    '+', '-': RelPriority := 1;
    '*', '/': RelPriority := 3;
    '^'     : RelPriority := 6;
    'A'..'Z': RelPriority := 7;
    '('     : RelPriority := 9;
    ')'     : RelPriority := 0;
    else
      RelPriority := -1;
  end;
end;

//Return stake priority of element
function StakePriority(character: char): integer;
begin
  case UpCase(character) of
    '+', '-': StakePriority := 2;
    '*', '/': StakePriority := 4;
    '^'     : StakePriority := 5;
    'A'..'Z': StakePriority := 8;
    '('     : StakePriority := 0;
    ')'     : StakePriority := -1;
    else
      StakePriority := -1;
  end;
end;

//Return true if expression doesn't contain any characters, except operations, operands, spaces
function IsValidExpression(expression: string): boolean;
var
  i: integer;
  checker: boolean;
begin
  checker := true;
  i := 1;
  if length(expression) = 0 then
    checker := false;
  while (i <= length(expression)) and (checker) do
  begin
    if not CharInSet(UpCase(expression[i]), ['A'..'Z', '+','-','*','/','^','(',')',' ']) then
      checker := false;
    inc(i);
  end;
  IsValidExpression := checker;
end;

//Input expression with check
procedure InputExpression(var expression: string);
begin
  repeat
    write('������� ���������: ');
    readln(expression);
    if not IsValidExpression(expression) then
      writeln('������������ �������, ��������� ����!');
  until IsValidExpression(expression);
end;

//Delete spaces in string
procedure DeleteSpaces(var expression: string);
var
  i: integer;
begin
  i := 1;
  while i <= length(expression) do
  begin
    if expression[i] = ' 'then
      delete(expression, i, 1);
    inc(i);
  end;
end;

var
  stake: TStake;
  expression: string;
  temp: string;
  revPolExpr: string;
  i, rank: integer;
begin
  //Input expression and reform it, make empty stake
  InputExpression(expression);
  DeleteSpaces(expression);
  expression := AnsiLowerCase(expression);
  MakeNull(stake);

  //Reverse poland expression
  for i := 1 to length(expression) do
  begin
    if (IsEmpty(stake)) or (RelPriority(expression[i]) > StakePriority(Top(stake)[1])) then
      push(stake, expression[i])
    else
    begin
      if expression[i] = ')' then
      begin
        while Top(stake) <> '(' do
        begin
          Pop(stake, temp);
          revPolExpr := revPolExpr + temp;
        end;
        Pop(stake, temp);
      end
      else
      begin
        while (not isEmpty(stake)) and (RelPriority(expression[i]) < StakePriority(Top(stake)[1])) do
        begin
          Pop(stake, temp);
          revPolExpr := revPolExpr + temp;
        end;
        Push(stake, expression[i]);
      end;
    end;
  end;

  //Pop all whats left in stake
  while not isEmpty(stake) do
  begin
    Pop(stake, temp);
    revPolExpr :=  revPolExpr + temp;
  end;

  //Calculate rank
  rank := 0;
  for i := 1 to length(revPolExpr) do
    if CharInSet(revPolExpr[i], ['a'..'z']) then
      inc(rank)
    else
      dec(rank);

  //Output Results
  writeln;
  write('�������� �������� ������: ');
  writeln(revPolExpr);
  write('���� ������������� ���������: ');
  writeln(rank);

  readln;
end.
