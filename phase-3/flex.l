%{
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#include "Parent.hh"
#include "bison.tab.hpp"

%}
%option noyywrap
X "x"|"X"
HEX_NUM [0-9a-fA-F]+
ID [a-zA-Z][a-zA-Z0-9]*
DIGIT [0-9]*
HEX_DIGIT ({DIGIT}|[a-fA-F])+
HEX_CONST 0x{HEX_NUM}
%%


if 			{return IF;}
else 		{return ELSE;}
for 		{return FOR;}
return 		{return RETURN;}
break		{return BREAK;}
continue	{return CONTINUE;}
true		{return TRUE;}
false 		{return FALSE;}
callout 	{return CALLOUT;}
class 		{return CLASS;}
Program 	{return PROGRAM;}
%			{return TOK_MODULUS;}
,			{return COMMA;}
\.			{return DOT;}
\+\+	    {return TOK_PLUS_PLUS;}
\+			{return TOK_PLUS;}
--			{return TOK_MINUS_MINUS;}
-			{return TOK_MINUS;}
\*			{return TOK_MULTIPLY;}
\/			{return TOK_DIVIDE;}
!=			{return TOK_NOT_EQUAL;}
!			{return TOK_NOT;}
\|\|	    {return TOK_OR;}
&&			{return TOK_AND;}
==			{return TOK_EQUAL_EQUAL;}
=			{return TOK_EQUAL;}
\+=			{return TOK_PLUS_EQUAL;}
\-=			{return TOK_MINUS_EQUAL;}
\<=			{return TOK_LESS_EQUAL;}
\<			{return TOK_LESS;}
>=			{return TOK_GREATER_EQUAL;}
>			{return TOK_GREATER;}

0x([0-9 a-f A-F]+) 		{
	yylval.string_val = strdup(yytext);
				return HEX_CONST;
			}

;			{return SEMI_COLON;}
boolean		{return BOOLEAN;}
int			{return INT;}
void 		{return VOID;}
\(			{return OPEN_PARANTHESIS;}
\)			{return CLOSE_PARANTHESIS;}
\{			{return OPEN_BRACE;}
\}			{return CLOSE_BRACE;}
\[			{return OPEN_SQR_BRACKET;}
\]			{return CLOSE_SQR_BRACKET;}
[ \t]	          	;
[\n]		{ ;}

[0-9]+      {yylval.ival = atoi(yytext); return INT_CONST;}
\/\/.*$     {;}


\"(\\.|[^\\"])*\" { yylval.string_val = strdup(yytext); return STRING_CONST;}

 \'(\\.|[^\\'])*\' { yylval.char_val = strdup(yytext); return CHAR_CONST;}


{ID}        { yylval.string_val = strdup(yytext); return ID;}
.			{
				printf("ERROR\n");
				return SYN_ERR;
			}

%%



