program Lab7;
// A program that determines if this text is a
// valid formula

// Console app
{$APPTYPE CONSOLE}

// Modules declaration
uses
  System.SysUtils;

// A function which verifies text
function IsValid(const str: string): boolean;

// Types declaration
type
  TNums = set of '1' .. '9';
  TSigns = set of '*' .. '-';
  TLetters = set of 'a' .. 'g';
  TCondition = (error, none, formula, formulaPlus,
  sign, name, int);

// Const declaration
const
  signs: TSigns = ['*', '+', '-'];
  nums: TNums = ['1', '2', '3', '4', '5', '6', '7',
  '8', '9'];
  letters: TLetters = ['a', 'b', 'c', 'd', 'e',
  'f', 'g'];

// Vars declaration
var
  i: integer;
  condition: TCondition;

begin

  // Setting variables to the original values
  IsValid := false;
  condition := none;
  i := 1;

  // Start of the cycle A1, checking every element
  // and changing condition type
  while (str[i] <> '.') and (condition <> error) do
  begin
    case condition of

      // To start determining
      none:
        begin
          if str[i] in letters then
            condition := name
          else if str[i] in nums then
            condition := int
          else
            condition := error
        end;

      // If the condition only contains numbers
      int:
        begin
          if str[i] in nums then
            condition := int
          else if str[i] in signs then
            condition := formulaPlus
          else
            condition := error
        end;

      // If the condition is a name
      name:
        begin
          if (str[i] in letters) or (str[i] in nums) then

          else
            if str[i] in signs then
              condition := formulaPlus
            else
              condition := error
        end;

        // If the condition is a formula with something
     formulaPlus:
        begin
          if str[i] in letters then
            condition := formula
          else
            if str[i] in nums then
              condition := formula
            else
              condition := error;
        end;

        // If the condition is a finished formula
     formula:
        begin
          if (str[i] in letters) or (str[i] in nums) then
            condition := formula
          else
            if str[i] in signs then
              condition := formulaPlus
            else
              condition := error
        end
    end;
    // Finish of the cycle A1

    inc(i);
  end;

  // The condition is a formula if it only contains
  //numbers or its a name
  if (condition = name) or (condition = int) or (condition = formula) then
    IsValid := true;

end;

// Variables declaration
var
  inputStr: string;
  isCorrect: boolean;
  { inputStr - string the program verifies
    isCorrect - is inputted expression correct}

begin
  //Input string
  write('Input condition: ');
  readln(inputStr);

  //Check string
  isCorrect := IsValid(inputStr);

  // Outputting the result of the verification
  write('Is correct: ');
  writeln(isCorrect);

  //Final operations
  readln;

end.


