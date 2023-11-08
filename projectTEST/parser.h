/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INT = 259,
     FLOAT = 260,
     CHAR = 261,
     STRING = 262,
     BOOL = 263,
     RETURN = 264,
     BREAK = 265,
     CONTINUE = 266,
     WHILE = 267,
     IF = 268,
     ELSE = 269,
     ACCMOD = 270,
     INTNUM = 271,
     FLOATNUM = 272,
     CHARCONST = 273,
     STRINGCONST = 274,
     TRUE = 275,
     FALSE = 276,
     NUL = 277,
     IS_EQUAL = 278,
     SPACECOM = 279,
     CLASS = 280,
     IF_PREC = 281,
     OP = 282
   };
#endif
/* Tokens.  */
#define ID 258
#define INT 259
#define FLOAT 260
#define CHAR 261
#define STRING 262
#define BOOL 263
#define RETURN 264
#define BREAK 265
#define CONTINUE 266
#define WHILE 267
#define IF 268
#define ELSE 269
#define ACCMOD 270
#define INTNUM 271
#define FLOATNUM 272
#define CHARCONST 273
#define STRINGCONST 274
#define TRUE 275
#define FALSE 276
#define NUL 277
#define IS_EQUAL 278
#define SPACECOM 279
#define CLASS 280
#define IF_PREC 281
#define OP 282




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



