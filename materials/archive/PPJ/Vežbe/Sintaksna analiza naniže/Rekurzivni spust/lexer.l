// Kazemo lekseru da kad stignemo do kraja ulaza ne vracamo se na pocetak
%option noyywrap

// Kazemo lekseru da koristi tokene iz "tokeni.h"
%{
    #include "tokeni.h"
%}

// Definisemo koje izraze lekser moze da prepozna
%%

[0-9]+ {return BROJ;} // Jedna ili vise cifara
"+" {return PLUS;}
"*" {return PUTA;}
"(" {return OZ;}
")" {return ZZ;}

[ \t\n] {} // Ignorise beline (ne radi nista)

//Za sve ostale karaktere vraca gresku, ona se nalazi u "yytext"
. {
    fprintf(stderr, "Leksicka greska: %s\n", yytext);
    exit(EXIT_FAILURE);
}

%%
