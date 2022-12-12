%{ 

%} 

%% 

(<!--(.)+-->) {fprintf(yyout, "");} 

.       { fprintf(yyout, "%s", yytext); }
%% 

int yywrap(){} 

int main(){ 
  
FILE* in, out;
yyin = fopen("file.txt", "r");
yyout = fopen("Output.txt", "w"); 

yylex(); 

fclose(yyin);
fclose(yyout); 

return 0; 
} 