program Lab11;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

function isReal(str: string; psn: integer; pntMet, EMet: boolean): boolean;
begin
  if (pos('.', str) = 0) and (pos('E', str) = 0) then
    isReal := false
  else
    if not (CharInSet(str[1], ['0'..'9','+','-']) and not CharInSet(str[length(str)], ['E','.','-','+'])) then
      isReal := false
    else
    if psn < length(str) then
      case str[psn] of
      '0'..'9':
        begin
          if (str[psn+1] = '-') or (str[psn+1] = '+') then
            isReal := false
          else
            isReal := isReal(str, psn+1, pntMet, EMet);
        end;
      '+', '-':
        begin
          if not CharInSet(str[psn+1], ['0'..'9']) then
            isReal := false
          else
            isReal := isReal(str, psn+1, pntMet, EMet);
        end;
      '.':
        begin
          if not (CharInSet(str[psn+1], ['0'..'9']) and not pntMet)  then
            isReal := false
          else
          begin
            pntMet := true;
            isReal := isReal(str, psn+1, pntMet, EMet);
          end;
        end;
      'E':
        begin
          if not (CharInSet(str[psn+1], ['0'..'9']) or CharInSet(str[psn+1], ['+','-'])) or (Emet) then
            isReal := false
          else
          begin
            EMet := true;
            isReal := isReal(str, psn+1, pntMet, EMet);
          end;
        end;
      end
    else
      isReal := true;
end;
var
  str: string;
begin
  write('¬ведите строку: ');
  readln(str);
  if isReal(str, 1, false, false) then
    writeln('TRUE')
  else
    writeln('FALSE');
  readln;
end.
