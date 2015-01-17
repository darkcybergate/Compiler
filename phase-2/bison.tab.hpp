/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_BISON_TAB_HPP_INCLUDED
# define YY_YY_BISON_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_CONST = 258,
    STRING_CONST = 259,
    COMMENT = 260,
    SYN_ERR = 261,
    CHAR_CONST = 262,
    ID = 263,
    INT = 264,
    IF = 265,
    ELSE = 266,
    FOR = 267,
    RETURN = 268,
    BREAK = 269,
    CONTINUE = 270,
    NULL_TOKEN = 271,
    TRUE = 272,
    FALSE = 273,
    HEX_CONST = 274,
    CLASS = 275,
    CALLOUT = 276,
    OPEN_BRACE = 277,
    CLOSE_BRACE = 278,
    SEMI_COLON = 279,
    BOOLEAN = 280,
    COMMA = 281,
    DOT = 282,
    OPEN_PARANTHESIS = 283,
    CLOSE_PARANTHESIS = 284,
    OPEN_SQR_BRACKET = 285,
    CLOSE_SQR_BRACKET = 286,
    VOID = 287,
    TOK_MODULUS = 288,
    TOK_PLUS = 289,
    TOK_PLUS_PLUS = 290,
    TOK_MINUS = 291,
    TOK_MINUS_MINUS = 292,
    TOK_MULTIPLY = 293,
    TOK_DIVIDE = 294,
    TOK_NOT_EQUAL = 295,
    TOK_NOT = 296,
    TOK_OR = 297,
    TOK_AND = 298,
    TOK_EQUAL_EQUAL = 299,
    TOK_EQUAL = 300,
    TOK_PLUS_EQUAL = 301,
    TOK_MINUS_EQUAL = 302,
    TOK_LESS_EQUAL = 303,
    TOK_LESS = 304,
    TOK_GREATER_EQUAL = 305,
    TOK_GREATER = 306,
    EOF_TOKEN = 307,
    PROGRAM = 308,
    TOK_UMINUS = 309,
    TOK_UPLUS = 310
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 42 "bison.ypp" /* yacc.c:1909  */

	int ival;
	float fval;
	char *sval;
	char *cmtval;
	char *errval;
	char *strval;
#line 51 "bison.ypp" /* yacc.c:1909  */

	char* string_val;
	int int_val;
	float float_val;
	char *char_val;
	bool bool_val;
	bool bool_arr_2[2];
	AssignOperator  a_op;
	Type * type;
	AstNode* par;
	list<AstNode*>* par_list;
	Expr *expr;
	list<Expr*> *expr_list;
	Stmt *stmt;
	list<Stmt*> *stmt_list;
	VariableChild* var_par;
	list<MethodChild*>* ME;
	struct mh
	{
		bool bool_arr_2[2];
		char *name;
		Type *type;
	} mhead;
	struct vinfo
	{
		char *name;
		int dim;
	}varinfo;

#line 148 "bison.tab.hpp" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_BISON_TAB_HPP_INCLUDED  */
