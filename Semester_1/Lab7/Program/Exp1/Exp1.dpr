Program Exp1;
//Program removes odd elements

//Console app
{$APPTYPE CONSOLE}

{$R *.res}

//Modules declaration
Uses
  System.SysUtils;

//Variables declaration
Var
  Str, LastWord: string;
  Word, Letter, WordCopy, Temp: string;
  I, J: integer;
  Checker: boolean;
{ Str - original string
  LastWord - the last word
  Word - current checking word
  Letter - 1-st, 2-nd, etc. letter of Word
  WordCopy - copy of Word
  Temp - variable, which contains palindrom of LastWord
  I - counter 1
  J - counter 2
  Checker - variable, which is used to find mistakes and to delete words with
            repeating letters }

//Start the program
Begin

  //Mistakes checker
  repeat

    //Set checker to the original value
    Checker := true;
    //Input String
    write('������� ���� ������: ');
    readln(Str);

    //Check condition of only english letters, allowing input spaces and �ommas
    if length(Str) <> 0 then
    begin
      for I := 1 to length(Str) - 1 do
      begin
        if ((ord(Str[I]) < 96) or (ord(Str[I]) > 125)) and (Str[I] <> ' ') and (Str[I] <> ',') then
          Checker := false;
      end;
    end

    //If nothing was inputted
    else
      Str := ' ';(*In order to make insufficient input*)

    //If mistake was found
    if (Str = '') or ((pos(' ',Str) = 0) and (pos(',',Str) = 0)) or (Checker = false) or (Str[length(Str)] <> '.') then
      writeln('������ �����');

  //If input is sufficient
  until (Checker = true) and (Str[length(Str)] = '.') and (Str <> '') and ((pos(' ',Str) <> 0) or (pos(',',Str) <> 0));

  //Set Temp to the original value
  Temp := '';

  //Set i to the original value
  I := length(Str) - 1;

  //Find palindrom of the last word
  while (Str[I] <> ',') and (Str[I] <> ' ') do
  begin
    Temp := Temp + copy(Str,I,1);
    dec(I);
  end;

  //Set LastWord to the original value
  LastWord := '';

  //Write palindrom of the last word in reverse order
  for I := 1 to length(Temp) do
    LastWord := Temp[I] + LastWord;

  //Output original string and last word
  writeln('�������� ������: ', Str);
  writeln('��������� �����: ', LastWord);
  write('��������������� ������: ');

  //Set I to the original value
  I := 1;

  //While Str[i] not equals '.'
  while Str[I] <> '.' do
  begin

    //If new word was found
    if (Str[I] <> ' ') and (Str[I] <> ',') then
    begin

      //Set checker to the original value
      Checker := true;

      //Set Word to the original value
      Word := '';

      //Find Word
      while (Str[I] <> ' ') and (Str[I] <> ',') and (I < Length(Str)) do
      begin
        Word := Word + Str[I];
        inc(I);
      end;

      //Set WordCopy to the original value
      WordCopy := Word;

      //Check if there are repeated letters in Word
      for J := 1 to length(Word) do
      begin

        //Copy 1-st, 2-nd, ... letter of the word
        Letter := Copy(Word,J,1);

        //Delete this letter
        delete(WordCopy,1,1);

        //Check if the same letter was found
        if pos(Letter,WordCopy) <> 0 then
          Checker := false;
      end;

      //If found word is not equals to last word and there is no repeated lettters
      if (Word <> LastWord) and (Checker = true) then
        write(Word,' ');
    end

    //If we met space or comma
    else
      inc(I);

  end;

  //Final operations
  readln;
End.
