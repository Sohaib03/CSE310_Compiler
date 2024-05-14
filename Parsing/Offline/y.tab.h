/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    LOWER_THAN_ELSE = 258,
    ELSE = 259,
    UNRECOGNIZED = 260,
    INCOP = 261,
    DECOP = 262,
    ASSIGNOP = 263,
    NOT = 264,
    LPAREN = 265,
    RPAREN = 266,
    LCURL = 267,
    RCURL = 268,
    LTHIRD = 269,
    RTHIRD = 270,
    BREAK = 271,
    CASE = 272,
    CONTINUE = 273,
    DEFAULT = 274,
    RETURN = 275,
    SWITCH = 276,
    VOID = 277,
    CHAR = 278,
    DOUBLE = 279,
    FLOAT = 280,
    INT = 281,
    DO = 282,
    WHILE = 283,
    FOR = 284,
    IF = 285,
    COMMA = 286,
    SEMICOLON = 287,
    PRINTLN = 288,
    ID = 289,
    ERROR_ID = 290,
    CONST_FLOAT = 291,
    ERROR_FLOAT = 292,
    CONST_CHAR = 293,
    CONST_INT = 294,
    ADDOP = 295,
    MULOP = 296,
    RELOP = 297,
    LOGICOP = 298
  };
#endif
/* Tokens.  */
#define LOWER_THAN_ELSE 258
#define ELSE 259
#define UNRECOGNIZED 260
#define INCOP 261
#define DECOP 262
#define ASSIGNOP 263
#define NOT 264
#define LPAREN 265
#define RPAREN 266
#define LCURL 267
#define RCURL 268
#define LTHIRD 269
#define RTHIRD 270
#define BREAK 271
#define CASE 272
#define CONTINUE 273
#define DEFAULT 274
#define RETURN 275
#define SWITCH 276
#define VOID 277
#define CHAR 278
#define DOUBLE 279
#define FLOAT 280
#define INT 281
#define DO 282
#define WHILE 283
#define FOR 284
#define IF 285
#define COMMA 286
#define SEMICOLON 287
#define PRINTLN 288
#define ID 289
#define ERROR_ID 290
#define CONST_FLOAT 291
#define ERROR_FLOAT 292
#define CONST_CHAR 293
#define CONST_INT 294
#define ADDOP 295
#define MULOP 296
#define RELOP 297
#define LOGICOP 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 99 "1805026.y"

	SymbolInfo* syminfo;

#line 147 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
