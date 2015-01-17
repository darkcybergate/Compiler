%{
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "bison.tab.h"  // to get the token types that we return

//#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = line_num; \
  //  yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
   // yycolumn += yyleng;


%}

X "x"|"X"
HEX_NUM [0-9a-fA-F]+

%%


if 			{return IF;}
else 			{return ELSE;}
for 			{return FOR;}
return 			{return RETURN;}
break			{return BREAK;}
continue		{return CONTINUE;}

true			{return TRUE;}
false 			{return FALSE;}
callout 		{return CALLOUT;}

class 			{return CLASS;}


Program 	{return PROGRAM;}
%			{return MODULUS;}
,			{return COMMA;}
\.			{return DOT;}

\+\+			{return PLUS_PLUS;}
\+			{return PLUS;}
--			{return MINUS_MINUS;}
-			{return MINUS;}
\*			{return MULTIPLY;}
\/			{return DIVIDE;}
!=			{return NOT_EQUAL;}
!			{return NOT;}
\|\|			{return OR;}
&&			{return AND;}
==			{return EQUAL_EQUAL;}
=			{return EQUAL;}
\+=			{return PLUS_EQUAL;}
\-=			{return MINUS_EQUAL;}
\<=			{return LESS_EQUAL;}
\<			{return LESS;}
>=			{return GREATER_EQUAL;}
>			{return GREATER;}

0{X}{HEX_NUM} 		{
			//	yylval.ival = (int)strtod(yytext, NULL);
				return INT_CONST;
			}


;			{return SEMI_COLON;}
boolean			{return BOOLEAN;}
int			    {return INT;}

\'.\'       		{return CHAR_CONST;}
void 			{return VOID;}
\(			{return OPEN_PARANTHESIS;}
\)			{return CLOSE_PARANTHESIS;}
\{			{return OPEN_BRACE;}
\}			{return CLOSE_BRACE;}
\[			{return OPEN_SQR_BRACKET;}
\]			{return CLOSE_SQR_BRACKET;}
[ \t]	          	;
[\n]			{ ;}

[0-9]+            	{ 
					//	yylval.ival = atoi(yytext); 
						return INT_CONST; 
					}

\/\/.*$      		{
				
				
				;
			}


\"(\\.|[^\\"])*\"	{ //yylval.sval = strdup(yytext); 
						return STRING_CONST; 
					}


[a-zA-Z][a-zA-Z0-9_]*   {
				//yylval.sval = strdup(yytext);
				return ID;
			}


.			{
				printf("ERROR\n");
				//yylval.errval = strdup(yytext); 
				//cout<<"SYN_ERROR : "<<yytext<<endl;
				return SYN_ERR;
			}

%%

