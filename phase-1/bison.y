%{
#include <cstdio>
#include <iostream>
#include <stdarg.h>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
int line_num = 1;
int err_count = 0;
extern const char *yytext;
char *filename;
%}

%locations
%error-verbose


%union {
	int ival;
	float fval;
	char *sval;
	char *cmtval;
	char *errval;
	char *strval;
	char chrval;
}

%token <ival> INT_CONST
%token <strval> STRING_CONST
%token <sval> ID
%token <cmtval> COMMENT
%token <errval> SYN_ERR
%token <chrval> CHAR_CONST



%token INT
%token IF
%token ELSE
%token FOR
%token RETURN
%token BREAK
%token CONTINUE
%token NULL_TOKEN
%token TRUE
%token FALSE

%token CLASS
%token CALLOUT
%token OPEN_BRACE
%token CLOSE_BRACE
%token SEMI_COLON
%token BOOLEAN
%token COMMA
%token DOT
%token OPEN_PARANTHESIS
%token CLOSE_PARANTHESIS
%token OPEN_SQR_BRACKET
%token CLOSE_SQR_BRACKET
%token VOID
%token MODULUS
%token PLUS
%token PLUS_PLUS
%token MINUS
%token MINUS_MINUS
%token MULTIPLY
%token DIVIDE
%token NOT_EQUAL
%token NOT
%token OR
%token AND
%token EQUAL_EQUAL
%token EQUAL
%token PLUS_EQUAL
%token MINUS_EQUAL
%token LESS_EQUAL
%token LESS
%token GREATER_EQUAL
%token GREATER
%token EOF_TOKEN
%token PROGRAM

%right EQUAL
%left OR
%left AND
%left EQUAL_EQUAL NOT_EQUAL
%nonassoc LESS GREATER LESS_EQUAL GREATER_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right NOT UMINUS UPLUS


%%
program: CLASS PROGRAM OPEN_BRACE CLASS_DECLARATION CLOSE_BRACE
		 ;
		

CLASS_DECLARATION		: CLASS_DECL
						| CLASS_DECLARATION CLASS_DECL


CLASS_DECL              : FIELD_DECLARATION
						| METHOD_DECLARATION
						;

FIELD_DECLARATION		:  TYPE VARIABLES SEMI_COLON
						;
		


METHOD_DECLARATION: TYPE ID OPEN_PARANTHESIS formals_list CLOSE_PARANTHESIS BLOCK
		| VOID ID OPEN_PARANTHESIS formals_list CLOSE_PARANTHESIS BLOCK
		;



VARIABLES: 	VARIABLE
		| VARIABLES COMMA VARIABLE
		;


VARIABLE: ID ARR
	    ;


ARR  : 
	 | INT_ARR
	 ;


INT_ARR: OPEN_SQR_BRACKET INT_CONST CLOSE_SQR_BRACKET
	;	




formals_list : 
		| formals
		;



formals	: TYPE ID 
	| TYPE ID COMMA formals
	;



TYPE_VOID: INT
		| BOOLEAN
	    | VOID
	    ;


BLOCK: OPEN_BRACE VAR_DECLARATION STATEMENTS CLOSE_BRACE
	;


VAR_DECLARATION: 
		| VAR_DECLARATION VAR_DECL
		;


STATEMENTS: 
		| STATEMENTS STATEMENT
		;
	

VAR_DECL: TYPE ID_PLUS SEMI_COLON
		;


ID_PLUS: ID
	| ID_PLUS COMMA ID
	;
		

TYPE: INT
	| BOOLEAN
	;


STATEMENT: LOCATION ASSIGN_OP EXPR SEMI_COLON
		| METHOD_CALL SEMI_COLON
		| IF OPEN_PARANTHESIS EXPR CLOSE_PARANTHESIS BLOCK ELSE_BLK
		| FOR ID EQUAL EXPR COMMA EXPR BLOCK
		| RETURN EX_PR SEMI_COLON
		| BREAK SEMI_COLON
		| CONTINUE SEMI_COLON
		| BLOCK
		;		
	

ELSE_BLK: 
	| ELSE_BLOCK
	;


ELSE_BLOCK: ELSE BLOCK
		;


EX_PR: 
	| EXPR
	;


ASSIGN_OP : EQUAL
		| PLUS_EQUAL
		| MINUS_EQUAL
		;


METHOD_CALL: METHOD_NAME OPEN_PARANTHESIS arguments_mult CLOSE_PARANTHESIS
		| CALLOUT OPEN_PARANTHESIS STRING_CONST CALL_OUT_ARGS CLOSE_PARANTHESIS
		;


arguments_mult: 
		| EXPRS_COMMA
		;


EXPRS_COMMA:  EXPR
		| EXPRS_COMMA COMMA EXPR
		;


CALL_OUT_ARGS: 
		| CALL_OUT_LIST
		;


CALL_OUT_LIST: COMMA CALL_OUT
		;

	
CALL_OUT: CALLOUT_ARG COMMA CALL_OUT
		| CALLOUT_ARG
		;


CALLOUT_ARG: EXPR
	| STRING_CONST
	;


METHOD_NAME: ID
	;


LOCATION: ID
	| ID OPEN_SQR_BRACKET EXPR CLOSE_SQR_BRACKET
	;


EXPR: LOCATION
	| METHOD_CALL
	| LITERAL
	| EXPR BIN_OP EXPR
	| MINUS EXPR
	| NOT EXPR
	| OPEN_PARANTHESIS EXPR CLOSE_PARANTHESIS
	;



BIN_OP: ARITH_OP
	| REL_OP
	| EQ_OP
	| COND_OP
	;


ARITH_OP: PLUS
		| MINUS
		| MULTIPLY
		| DIVIDE
		| MODULUS

REL_OP: GREATER
	  | LESS
	  | GREATER_EQUAL
	  | LESS_EQUAL

EQ_OP: EQUAL_EQUAL
	 | NOT_EQUAL

COND_OP: AND
	   | OR


LITERAL: INT_CONST
	| CHAR_CONST
	| BOOL
	| STRING_CONST
	;

BOOL	: TRUE
	| FALSE




%%

int line_no = 0;

int main(int argc, char *argv[]) {
	// open a file handle to a particular file:

	if(argc<2)
	{
		cout<<"Correct usage : ./decafch <input-file-name>\n";
		return -1;
	}

		

	FILE *myfile = fopen(argv[1], "r");
	filename = argv[1];
	// make sure it is valid:
	if (!myfile) {
		cout << "Could not open .decaf file!" << endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

	if(err_count>0)
		cout<<"decaf : Error ["<<err_count<<"]"<<endl;
	else
		cout<<"decaf : "<<filename<<" successfully parsed"<<endl;

	
}
void
yyerror(const char *s)
{
	
	
	if(yylloc.first_line)
	{
		if(yylloc.first_column == yylloc.last_column)
			cout<<filename<<":"<<yylloc.first_line<<": "<<s<<endl;
		else
			cout<<filename<<":"<<yylloc.first_line<<"."<<yylloc.first_column<<"-"<<yylloc.last_line<<"."<<yylloc.last_column<<": "<<s<<endl;
		err_count++;
	}
}