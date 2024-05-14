/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "1805026.y"

    //#define YYSTYPE SymbolInfo*

    #include "SymbolTable.cpp"
    #include "parameter.cpp"
    #include <bits/stdc++.h>
    #include <typeinfo>
    #define yydebug 1
    #define ERROR "ERROR"
    #define UNDECLARED "undeclared"

    using namespace std;

    int yyparse(void);
    int yylex(void);
    extern FILE *yyin;



    ofstream logfile("1805026_log.txt"), errfile("1805026_error.txt");
    SymbolTable st(7, &logfile);

    extern int linenum;
    extern int errornum;
    
    string functionReturnType = "";

    void yyerror(string s){
        logfile<<"Error at line "<<linenum<<": "<<s<<"\n"<<endl;
        errfile<<"Error at line "<<linenum<<": "<<s<<"\n"<<endl;
        errornum++;
    }

    void log(string rule, string token) {
        logfile << "Line " << linenum << ": " << rule << endl << endl << token << endl << endl;
    }
    void err(string err_msg) {
        logfile << "Error at line " << linenum << ": " << err_msg << endl << endl;
        errfile << "Error at line " << linenum << ": " << err_msg << endl << endl;
        errornum++;
    }

    vector<string> tokenize(string text, char delimiter)  {
        vector<string> tokens;
        stringstream textStream(text);
        string token;

        while(getline(textStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    vector<string> getParameterType(string parameterList) {
        vector<string> typeList;
        vector<string> pairs = tokenize(parameterList, ',');

        for (string pair: pairs) {
            typeList.push_back(tokenize(pair, ' ')[0]);
        }
        return typeList;
    }

    vector<Parameter> getParameters(string parameterList) {
        vector<Parameter> paramList;
        vector<string> pairs = tokenize(parameterList, ',');

        for (string pair: pairs) {
            vector<string> p = tokenize(pair, ' ');
            paramList.push_back(Parameter(p[1], p[0]));
        }
        return paramList;
    }

    bool checkArray(string varName) {
        if (varName.back() == ']' and (varName.find("[") != string::npos)) return true;
        return false;
    }

    pair<string, string> getArrayNameSize(string varName) {
        int L = varName.find("[");
        int R = varName.find("]");
        return {varName.substr(0, L), varName.substr(L+1, R - L - 1)};
    }

    bool isInt(string s)
    {
        string::const_iterator it = s.begin();
        while (it != s.end() && isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }


#line 164 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 306 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

#define YYUNDEFTOK  2
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   123,   123,   130,   136,   143,   148,   153,   160,   193,
     213,   236,   235,   320,   319,   390,   389,   461,   466,   471,
     476,   482,   490,   498,   505,   544,   549,   554,   561,   566,
     571,   576,   582,   589,   594,   601,   606,   611,   611,   616,
     621,   626,   631,   636,   651,   661,   665,   671,   676,   683,
     710,   745,   750,   755,   760,   788,   793,   805,   810,   816,
     821,   835,   840,   878,   883,   888,   895,   900,   933,   938,
     943,   948,   956,   966,   972,   978,   984
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOWER_THAN_ELSE", "ELSE",
  "UNRECOGNIZED", "INCOP", "DECOP", "ASSIGNOP", "NOT", "LPAREN", "RPAREN",
  "LCURL", "RCURL", "LTHIRD", "RTHIRD", "BREAK", "CASE", "CONTINUE",
  "DEFAULT", "RETURN", "SWITCH", "VOID", "CHAR", "DOUBLE", "FLOAT", "INT",
  "DO", "WHILE", "FOR", "IF", "COMMA", "SEMICOLON", "PRINTLN", "ID",
  "ERROR_ID", "CONST_FLOAT", "ERROR_FLOAT", "CONST_CHAR", "CONST_INT",
  "ADDOP", "MULOP", "RELOP", "LOGICOP", "$accept", "start", "program",
  "unit", "func_declaration", "func_definition", "$@1", "$@2", "$@3",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement", "$@4",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF (-81)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-52)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      90,   -81,   -81,   -81,    22,    90,   -81,   -81,   -81,   -81,
     -11,   -81,   -81,    11,     3,     7,    -8,    17,    30,   -81,
      40,     8,    -4,    15,    61,    55,    78,    64,   -81,    88,
      71,    90,   -81,   -81,   -81,   -81,    68,   -81,    88,    65,
     -81,   -81,    88,    74,    94,   -81,   169,   -81,   179,    29,
     -81,    29,   108,   109,   110,   -81,   114,    57,   -81,   -81,
     179,   -81,    91,   101,   -81,    88,   -81,    76,    96,     9,
      93,    46,    98,   -81,   -81,   -81,   -81,   -81,   -81,     6,
     -81,   -81,   179,   132,   112,    29,   151,    29,   111,   179,
      29,   -81,   136,   -81,   -81,   -81,   -81,   -81,   179,   -81,
     -81,   179,   179,   179,   179,   -81,   -81,   140,   151,   142,
     143,   -81,   144,   125,   149,   -81,   -81,    98,   118,   -81,
     137,    29,   137,   148,   -81,   179,   -81,   -81,   157,   168,
     -81,   -81,   137,   137,   -81,   -81
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    27,    26,    25,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    31,     0,     0,     0,     0,     0,    24,
       0,    13,     0,     0,     0,     0,    28,    15,     9,     0,
      11,     0,    21,    19,    32,    29,     0,    10,     0,     0,
      14,     8,     0,    18,     0,    16,     0,    45,     0,     0,
      23,     0,     0,     0,     0,    47,     0,    49,    69,    70,
       0,    35,     0,     0,    33,     0,    36,    66,     0,     0,
      55,    57,    59,    61,    65,    12,    17,    30,    46,    66,
      52,    64,     0,     0,     0,     0,     0,     0,     0,    74,
       0,    63,    31,    22,    34,    38,    71,    72,     0,    48,
      53,     0,     0,     0,     0,    68,    44,     0,     0,     0,
       0,    76,     0,    73,     0,    54,    56,    60,    58,    62,
       0,     0,     0,     0,    67,     0,    50,    42,     0,    40,
      43,    75,     0,     0,    39,    41
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -81,   -81,   -81,   170,   -81,   -81,   -81,   -81,   -81,   -81,
     -23,    54,   117,   -81,   -81,   -60,   -81,   -80,   -46,   -40,
     -45,    80,    79,    82,   -43,   -81,   -81,   -81
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    42,    29,    38,    22,
      40,    61,    62,    14,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   112,   113
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      79,    80,    79,    94,    17,    81,   108,    30,    20,    83,
     100,    84,    96,    97,    79,    45,    32,    91,    21,    75,
     -51,    15,    11,    13,   -51,    16,   -20,    31,   121,     1,
      82,    24,     2,     3,    18,    19,    79,    80,    48,    49,
      28,   -51,    95,    79,   111,   107,   -20,   109,    25,    33,
     114,    27,    79,   115,     9,    79,    79,    79,    79,     9,
     127,   119,   129,    57,    26,    58,    46,    89,    59,    60,
      47,    90,   134,   135,    48,    49,    34,   -37,    50,    79,
     131,   128,    96,    97,    98,    51,   102,     1,   103,    35,
       2,     3,    36,    52,    53,    54,    37,    55,    56,    57,
      39,    58,    46,    41,    59,    60,    47,    44,    76,    77,
      48,    49,     1,   -37,    93,     2,     3,    10,    85,    86,
      87,    51,    10,     1,    88,    92,     2,     3,    99,    52,
      53,    54,    23,    55,    56,    57,   101,    58,    46,   104,
      59,    60,    47,   105,   106,   110,    48,    49,    43,   -37,
      16,   120,    82,   122,   123,   124,   125,    51,   102,     1,
      48,    49,     2,     3,   126,    52,    53,    54,   132,    55,
      56,    57,   133,    58,    78,    12,    59,    60,    48,    49,
     130,   116,   118,    55,   117,    57,     0,    58,    48,    49,
      59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    57,     0,    58,     0,     0,    59,    60,
       0,     0,     0,    57,     0,    58,     0,     0,    59,    60
};

static const yytype_int16 yycheck[] =
{
      46,    46,    48,    63,     1,    48,    86,    11,     1,    49,
       1,    51,     6,     7,    60,    38,     1,    60,    11,    42,
      11,    10,     0,    34,    15,    14,    11,    31,   108,    22,
       1,    39,    25,    26,    31,    32,    82,    82,     9,    10,
      32,    32,    65,    89,    89,    85,    31,    87,    31,    34,
      90,    11,    98,    98,     0,   101,   102,   103,   104,     5,
     120,   104,   122,    34,    34,    36,     1,    10,    39,    40,
       5,    14,   132,   133,     9,    10,    15,    12,    13,   125,
     125,   121,     6,     7,     8,    20,    40,    22,    42,    34,
      25,    26,    14,    28,    29,    30,    32,    32,    33,    34,
      12,    36,     1,    32,    39,    40,     5,    39,    34,    15,
       9,    10,    22,    12,    13,    25,    26,     0,    10,    10,
      10,    20,     5,    22,    10,    34,    25,    26,    32,    28,
      29,    30,    15,    32,    33,    34,    43,    36,     1,    41,
      39,    40,     5,    11,    32,    34,     9,    10,    31,    12,
      14,    11,     1,    11,    11,    11,    31,    20,    40,    22,
       9,    10,    25,    26,    15,    28,    29,    30,    11,    32,
      33,    34,     4,    36,     5,     5,    39,    40,     9,    10,
      32,   101,   103,    32,   102,    34,    -1,    36,     9,    10,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    39,    40,
      -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    39,    40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    22,    25,    26,    45,    46,    47,    48,    49,    55,
      56,     0,    47,    34,    57,    10,    14,     1,    31,    32,
       1,    11,    53,    56,    39,    31,    34,    11,    32,    51,
      11,    31,     1,    34,    15,    34,    14,    32,    52,    12,
      54,    32,    50,    56,    39,    54,     1,     5,     9,    10,
      13,    20,    28,    29,    30,    32,    33,    34,    36,    39,
      40,    55,    56,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    54,    34,    15,     5,    62,
      64,    68,     1,    63,    63,    10,    10,    10,    10,    10,
      14,    68,    34,    13,    59,    54,     6,     7,     8,    32,
       1,    43,    40,    42,    41,    11,    32,    63,    61,    63,
      34,    64,    70,    71,    63,    64,    65,    67,    66,    68,
      11,    61,    11,    11,    11,    31,    15,    59,    63,    59,
      32,    64,    11,     4,    59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      48,    50,    49,    51,    49,    52,    49,    53,    53,    53,
      53,    53,    54,    54,    55,    56,    56,    56,    57,    57,
      57,    57,    57,    58,    58,    59,    59,    60,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    61,    61,    62,
      62,    63,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    70,    70,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     0,     7,     0,     6,     0,     7,     4,     3,     2,
       1,     2,     3,     2,     3,     1,     1,     1,     3,     4,
       6,     1,     4,     1,     2,     1,     1,     0,     2,     7,
       5,     7,     5,     5,     3,     1,     2,     1,     2,     1,
       4,     1,     2,     2,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 124 "1805026.y"
        {
            log("start : program", "");
            (yyval.syminfo) = (yyvsp[0].syminfo);
        }
#line 1596 "y.tab.c"
    break;

  case 3:
#line 131 "1805026.y"
        {
            string text = (yyvsp[-1].syminfo)->getName() + "\n" + (yyvsp[0].syminfo)->getName();
            log("program : program unit", text);
            (yyval.syminfo) = new SymbolInfo(text, "program");
        }
#line 1606 "y.tab.c"
    break;

  case 4:
#line 137 "1805026.y"
        {
            log("program : unit", (yyvsp[0].syminfo)->getName());
            (yyval.syminfo) = (yyvsp[0].syminfo);
        }
#line 1615 "y.tab.c"
    break;

  case 5:
#line 144 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("unit: var_declaration", (yyval.syminfo)->getName());
        }
#line 1624 "y.tab.c"
    break;

  case 6:
#line 149 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("unit: func_declaration", (yyval.syminfo)->getName());
        }
#line 1633 "y.tab.c"
    break;

  case 7:
#line 154 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("unit: func_defination", (yyval.syminfo)->getName());
        }
#line 1642 "y.tab.c"
    break;

  case 8:
#line 161 "1805026.y"
        {
            string returnType   = (yyvsp[-5].syminfo)->getName();
            string funcName     = (yyvsp[-4].syminfo)->getName();

            SymbolInfo* func = st.lookUp(funcName);
            if (func != nullptr) {
                err("Multiple declaration of function '" + funcName + "'");
            } else {
                vector<string>  param_type_list = getParameterType((yyvsp[-2].syminfo)->getName());
                vector<Parameter> param_list = getParameters((yyvsp[-2].syminfo)->getName());

                for (int i=0; i<param_list.size(); i++)  {
                    for (int j=i-1; j<i; j++) {
                        if (param_list[i].name == param_list[j].name) {
                            err("Multiple declaration of " + param_list[i].name);
                            break;
                        }
                    }
                }


                SymbolInfo temp("", "");
                temp.setAsFunction(funcName, returnType, param_list);
                temp.defined = false;

                st.insertSymbol(temp);
            }
            string text = (yyvsp[-5].syminfo)->getName() + " " + (yyvsp[-4].syminfo)->getName() + "(" + (yyvsp[-2].syminfo)->getName() + ");";
            (yyval.syminfo) = new SymbolInfo(text, "func_declaration");
            log("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON", text);

        }
#line 1679 "y.tab.c"
    break;

  case 9:
#line 194 "1805026.y"
        {
            string returnType   = (yyvsp[-4].syminfo)->getName();
            string funcName     = (yyvsp[-3].syminfo)->getName();
            SymbolInfo* func = st.lookUp(funcName);
            if (func != nullptr) {
                err("Multiple declaration of function '" + funcName + "'");
            }
            else {
                vector<Parameter> param_list;
                SymbolInfo temp("", "");
                temp.setAsFunction(funcName, returnType, param_list);
                temp.defined = false;

                st.insertSymbol(temp);
            }
            string text = (yyvsp[-4].syminfo)->getName() + " " + (yyvsp[-3].syminfo)->getName() + "();";
            (yyval.syminfo) = new SymbolInfo(text, "func_declaration");
            log("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", text);
        }
#line 1703 "y.tab.c"
    break;

  case 10:
#line 214 "1805026.y"
        {
            string returnType   = (yyvsp[-5].syminfo)->getName();
            string funcName     = (yyvsp[-4].syminfo)->getName();
            SymbolInfo* func = st.lookUp(funcName);
            if (func != nullptr) {
                err("Multiple declaration of function '" + funcName + "'");
            }
            else {
                vector<Parameter> param_list;
                SymbolInfo temp("", "");
                temp.setAsFunction(funcName, returnType, param_list);
                temp.defined = false;

                st.insertSymbol(temp);
            }
            string text = (yyvsp[-5].syminfo)->getName() + " " + (yyvsp[-4].syminfo)->getName() + "();";
            (yyval.syminfo) = new SymbolInfo(text, "func_declaration");
            log("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON", text);
        }
#line 1727 "y.tab.c"
    break;

  case 11:
#line 236 "1805026.y"
        {
            string returnType   = (yyvsp[-4].syminfo)->getName();
            string funcName     = (yyvsp[-3].syminfo)->getName();
            SymbolInfo* func = st.lookUp(funcName);
            vector<Parameter> pList = getParameters((yyvsp[-1].syminfo)->getName());

            if (func == nullptr) {
                SymbolInfo temp("" ,"");

                temp.setAsFunction(funcName, returnType, pList);
                temp.defined = true;
                st.insertSymbol(temp);

                st.enterScope();
                for (int i=0; i < pList.size(); i++) {
                    if (st.insert(pList[i].name, pList[i].type) == false){ 
                        err("Multiple declaration of variable '" + pList[i].name + "' in parameter");
                    }
                }
                st.printAllScopeTable();
            } else {
                if (func->isFunction) {
                    if (func->defined) {
                        err("Re-definition of function '" + funcName + "'");
                    }
                    else {
                        bool errorFound = false;
                        vector<Parameter> decPList = func->paramList;

                        if (decPList.size() != pList.size()) {
                            errorFound = true;
                            err("Total number of arguments mismatch with declaration in function " + funcName);
                        }

                        if (func->getType() != returnType) {
                            errorFound = true;
                            err("Return type mismatch with function declaration in function " + funcName);
                        }

                        if ( decPList.size() == pList.size() ) {
                            for (int i=0; i<decPList.size(); i++) {
                                if (decPList[i].type != pList[i].type) {
                                    errorFound = true;
                                    err(to_string(i+1) + "th argument mismatch in function func");
                                }
                            }
                        }

                        st.remove(funcName);

                        SymbolInfo temp("", "");
                        temp.setAsFunction(funcName, returnType, pList);
                        temp.defined = true;

                        st.insertSymbol(temp);
                        st.enterScope();
                        for (int i=0; i < pList.size(); i++) {
                            if (st.insert(pList[i].name, pList[i].type) == false){ 
                                err("Multiple declaration of variable '" + pList[i].name + "' in parameter");
                            }
                        }

                    }
                }
                else {
                    st.enterScope();
                    err("Multiple declaration of '" + funcName + "'");

                    for (int i=0; i < pList.size(); i++) {
                        if (st.insert(pList[i].name, pList[i].type) == false){ 
                            err("Multiple declaration of variable '" + pList[i].name + "' in parameter");
                        }
                    }

                }
            }
        }
#line 1809 "y.tab.c"
    break;

  case 12:
#line 314 "1805026.y"
        {
            string name = (yyvsp[-6].syminfo)->getName() + " " + (yyvsp[-5].syminfo)->getName() + "( " + (yyvsp[-3].syminfo)->getName() + ") " + (yyvsp[0].syminfo)->getName() + "\n";
            (yyval.syminfo) = new SymbolInfo(name, "func_defination");
            log("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement", name);
        }
#line 1819 "y.tab.c"
    break;

  case 13:
#line 320 "1805026.y"
        {
            string returnType   = (yyvsp[-3].syminfo)->getName();
            string funcName     = (yyvsp[-2].syminfo)->getName();
            SymbolInfo* func = st.lookUp(funcName);

            vector<Parameter> pList;

            if (func == nullptr) {
                SymbolInfo temp("" ,"");

                temp.setAsFunction(funcName, returnType, pList);
                temp.defined = true;
                st.insertSymbol(temp);

                st.enterScope();
            } else {
                if (func->isFunction) {
                    if (func->defined) {
                        err("Re-definition of function '" + funcName + "'");
                    }
                    else {
                        bool errorFound = false;
                        vector<Parameter> decPList = func->paramList;

                        if (decPList.size() != pList.size()) {
                            errorFound = true;
                            err("Total number of arguments mismatch with declaration in function " + funcName);
                        }

                        if (func->getType() != returnType) {
                            errorFound = true;
                            err("Return type mismatch with function declaration in function " + funcName);
                        }

                        if ( decPList.size() == pList.size() ) {
                            for (int i=0; i<decPList.size(); i++) {
                                if (decPList[i].type != pList[i].type) {
                                    errorFound = true;
                                    err(to_string(i+1) + "th argument mismatch in function func");
                                }
                            }
                        }

                        if (errorFound == false) {
                            st.remove(funcName);

                            SymbolInfo temp("", "");
                            temp.setAsFunction(funcName, returnType, pList);
                            temp.defined = true;

                            st.insertSymbol(temp);
                        }
                        st.enterScope();

                    }
                }
                else {
                    st.enterScope();
                    err("Multiple declaration of '" + funcName);
                }
            }
            
        }
#line 1887 "y.tab.c"
    break;

  case 14:
#line 384 "1805026.y"
        {
            string name = (yyvsp[-5].syminfo)->getName() + " " + (yyvsp[-4].syminfo)->getName() + "() " + (yyvsp[0].syminfo)->getName() + "\n";
            (yyval.syminfo) = new SymbolInfo(name, "func_defination");
            log("func_definition : type_specifier ID LPAREN RPAREN compound_statement", name);
        }
#line 1897 "y.tab.c"
    break;

  case 15:
#line 390 "1805026.y"
        {
            string returnType   = (yyvsp[-4].syminfo)->getName();
            string funcName     = (yyvsp[-3].syminfo)->getName();
            SymbolInfo* func = st.lookUp(funcName);

            vector<Parameter> pList;

            if (func == nullptr) {
                SymbolInfo temp("" ,"");

                temp.setAsFunction(funcName, returnType, pList);
                temp.defined = true;
                st.insertSymbol(temp);

                st.enterScope();
            } else {
                if (func->isFunction) {
                    if (func->defined) {
                        err("Re-definition of function '" + funcName + "'");
                    }
                    else {
                        bool errorFound = false;
                        vector<Parameter> decPList = func->paramList;

                        if (decPList.size() != pList.size()) {
                            errorFound = true;
                            err("Total number of arguments mismatch with declaration in function " + funcName);
                        }

                        if (func->getType() != returnType) {
                            errorFound = true;
                            err("Return type mismatch with function declaration in function " + funcName);
                        }

                        if ( decPList.size() == pList.size() ) {
                            for (int i=0; i<decPList.size(); i++) {
                                if (decPList[i].type != pList[i].type) {
                                    errorFound = true;
                                    err(to_string(i+1) + "th argument mismatch in function func");
                                }
                            }
                        }

                        if (errorFound == false) {
                            st.remove(funcName);

                            SymbolInfo temp("", "");
                            temp.setAsFunction(funcName, returnType, pList);
                            temp.defined = true;

                            st.insertSymbol(temp);
                        }
                        st.enterScope();

                    }
                }
                else {
                    st.enterScope();
                    err("Multiple declaration of '" + funcName);
                }
            }
            
        }
#line 1965 "y.tab.c"
    break;

  case 16:
#line 454 "1805026.y"
        {
            string name = (yyvsp[-6].syminfo)->getName() + " " + (yyvsp[-5].syminfo)->getName() + "() " + (yyvsp[0].syminfo)->getName() + "\n";
            (yyval.syminfo) = new SymbolInfo(name, "func_defination");
            log("func_definition : type_specifier ID LPAREN RPAREN compound_statement", name);
        }
#line 1975 "y.tab.c"
    break;

  case 17:
#line 462 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-3].syminfo)->getName() + "," + (yyvsp[-1].syminfo)->getName() + " " + (yyvsp[0].syminfo)->getName(), "parameter_list");
            log("parameter_list : parameter_list COMMA type_specifier ID" , (yyval.syminfo)->getName());
        }
#line 1984 "y.tab.c"
    break;

  case 18:
#line 467 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + "," + (yyvsp[0].syminfo)->getName(), "parameter_list");
            log("parameter_list : parameter_list COMMA type_specifier", (yyval.syminfo)->getName());
        }
#line 1993 "y.tab.c"
    break;

  case 19:
#line 472 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName() + " " + (yyvsp[0].syminfo)->getName(), "paramter_list");
            log("parameter_list : type_specifier ID", (yyval.syminfo)->getName());
        }
#line 2002 "y.tab.c"
    break;

  case 20:
#line 477 "1805026.y"
        {
            err("Parameter Name not given");
            (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName(), "parameter_list");
            log("parameter_list : type_specifier" , (yyval.syminfo)->getName());
        }
#line 2012 "y.tab.c"
    break;

  case 21:
#line 483 "1805026.y"
        {
            err("Parameter Name not given");
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName(), "parameter_list");
            log("parameter_list : type_specifier" , (yyval.syminfo)->getName());
        }
#line 2022 "y.tab.c"
    break;

  case 22:
#line 491 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("{\n" + (yyvsp[-1].syminfo)->getName() + "\n}", "compount_statement");
            log("compound_statement : LCURL statements RCURL" , (yyval.syminfo)->getName());

            st.printAllScopeTable();
            st.exitScope();
        }
#line 2034 "y.tab.c"
    break;

  case 23:
#line 499 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("{\n\n}", "compount_statement");
            log("compound_statement : LCURL RCURL" , (yyval.syminfo)->getName());
        }
#line 2043 "y.tab.c"
    break;

  case 24:
#line 506 "1805026.y"
        {
            string dataType = (yyvsp[-2].syminfo)->getName();
            string varNames = (yyvsp[-1].syminfo)->getName();

            if (dataType == "void") {
                err("Void type variables not allowed");
            }
            else {
                vector<string> var_name_list = tokenize(varNames, ',');
                SymbolInfo temp("", "");
                for (string vName: var_name_list) {

                    if (checkArray(vName)) {
                        pair<string, string> nameSize = getArrayNameSize(vName);
                        if (isInt(nameSize.second) == false) {
                            err("Non integer size for array provided");
                            continue;
                        }
                        int arraySize = stoi(nameSize.second);
                        temp.setAsArray(nameSize.first, dataType, arraySize);
                    }
                    else {
                        temp = SymbolInfo(vName, dataType);
                    }


                    if (!st.insertSymbol(temp)) {
                        err("Multiple Declaration of variable '" + temp.getName() + "'");
                    }
                    // cout << st.lookUp(temp.getName())->getType() << endl;
                }

                (yyval.syminfo) = new SymbolInfo(dataType + " " + varNames + ";", " var_declaration");
                log("var_declaration : type_specifier declaration_list SEMICOLON", (yyval.syminfo)->getName());
            }
        }
#line 2084 "y.tab.c"
    break;

  case 25:
#line 545 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("int" , "int");
            log("type_specifier : INT", (yyval.syminfo)->getName());
        }
#line 2093 "y.tab.c"
    break;

  case 26:
#line 550 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("float" , "float");
            log("type_specifier : FLOAT", (yyval.syminfo)->getName());
        }
#line 2102 "y.tab.c"
    break;

  case 27:
#line 555 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("void" , "void");
            log("type_specifier : VOID", (yyval.syminfo)->getName());
        }
#line 2111 "y.tab.c"
    break;

  case 28:
#line 562 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + "," + (yyvsp[0].syminfo)->getName(), "declaration_list");
            log("declaration_list : declaration_list COMMA ID", (yyval.syminfo)->getName());
        }
#line 2120 "y.tab.c"
    break;

  case 29:
#line 567 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-3].syminfo)->getName() + "," + (yyvsp[0].syminfo)->getName(), "declaration_list");
            log("declaration_list : declaration_list COMMA ID", (yyval.syminfo)->getName());
        }
#line 2129 "y.tab.c"
    break;

  case 30:
#line 572 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-5].syminfo)->getName() + "," + (yyvsp[-3].syminfo)->getName() + "[" + (yyvsp[-1].syminfo)->getName() + "]", "declaration_list");
            log("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD", (yyval.syminfo)->getName());
        }
#line 2138 "y.tab.c"
    break;

  case 31:
#line 577 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName() , "declaration_list");
            log("declaration_list : ID", (yyval.syminfo)->getName());
        }
#line 2147 "y.tab.c"
    break;

  case 32:
#line 583 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-3].syminfo)->getName() + "[" + (yyvsp[-1].syminfo)->getName() + "]", "declaration_list");
            log("declaration_list : ID LTHIRD CONST_INT RTHIRD", (yyval.syminfo)->getName());
        }
#line 2156 "y.tab.c"
    break;

  case 33:
#line 590 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName(), "statements");
            log("statements : statement", (yyval.syminfo)->getName());
        }
#line 2165 "y.tab.c"
    break;

  case 34:
#line 595 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName() + "\n" + (yyvsp[0].syminfo)->getName(), "statements");
            log("statements : statements statement", (yyval.syminfo)->getName());
        }
#line 2174 "y.tab.c"
    break;

  case 35:
#line 602 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName(), "statement");
            log("statement : var_declaration", (yyval.syminfo)->getName());
        }
#line 2183 "y.tab.c"
    break;

  case 36:
#line 607 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName(), "statement");
            log("statement : expression_statement", (yyval.syminfo)->getName());
        }
#line 2192 "y.tab.c"
    break;

  case 37:
#line 611 "1805026.y"
          { st.enterScope(); }
#line 2198 "y.tab.c"
    break;

  case 38:
#line 612 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName(), "statement");
            log("statement : compound_statement", (yyval.syminfo)->getName());
        }
#line 2207 "y.tab.c"
    break;

  case 39:
#line 617 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("for (" + (yyvsp[-4].syminfo)->getName() + (yyvsp[-3].syminfo)->getName() + (yyvsp[-2].syminfo)->getName() + ")" + (yyvsp[0].syminfo)->getName(),	"statement");
			log("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement", (yyval.syminfo)->getName());
        }
#line 2216 "y.tab.c"
    break;

  case 40:
#line 622 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("if(" + (yyvsp[-2].syminfo)->getName() + ")" + (yyvsp[0].syminfo)->getName(), "statement");
			log("statement : IF LPAREN expression RPAREN statement", (yyval.syminfo)->getName());
        }
#line 2225 "y.tab.c"
    break;

  case 41:
#line 627 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("if(" + (yyvsp[-4].syminfo)->getName() + ")" + (yyvsp[-2].syminfo)->getName() + "else" + (yyvsp[0].syminfo)->getName(),	"statement");
            log("statement : IF LPAREN expression RPAREN statement ELSE statement", (yyval.syminfo)->getName());
        }
#line 2234 "y.tab.c"
    break;

  case 42:
#line 632 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("while(" + (yyvsp[-2].syminfo)->getName() + ")" + (yyvsp[0].syminfo)->getName(),	"statement");
            log("statement : WHILE LPAREN expression RPAREN statement", (yyval.syminfo)->getName());
        }
#line 2243 "y.tab.c"
    break;

  case 43:
#line 637 "1805026.y"
        {
            string varName = (yyvsp[-2].syminfo)->getName();
            SymbolInfo* sym_var = st.lookUp(varName);

            if (sym_var) {
                if (sym_var->isVar == false) {
                    err("Not a variable : " + varName);
                }
            } else {
                err("Undeclared variable " + varName);
            }
            (yyval.syminfo) = new SymbolInfo("printf(" + varName + ");", "statement");
            log("statement : PRINTLN LPAREN ID RPAREN SEMICOLON", (yyval.syminfo)->getName());
        }
#line 2262 "y.tab.c"
    break;

  case 44:
#line 651 "1805026.y"
                                      {

            if (functionReturnType == "void") {
                err("Void Function cannot have return statement");
                functionReturnType = "";
            }

            (yyval.syminfo) = new SymbolInfo("return " + (yyvsp[-1].syminfo)->getName() + ";", "statement");
            log("statement: RETURN expression SEMICOLON", (yyval.syminfo)->getName());
        }
#line 2277 "y.tab.c"
    break;

  case 45:
#line 661 "1805026.y"
                       {
            (yyval.syminfo) = new SymbolInfo("", "");
            err("Unrecognized Character");
        }
#line 2286 "y.tab.c"
    break;

  case 46:
#line 665 "1805026.y"
                             {
            (yyval.syminfo) = new SymbolInfo("", "");
            err("Unrecognized Character");
        }
#line 2295 "y.tab.c"
    break;

  case 47:
#line 672 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo(";", "expression_statement");
            log("expression_statement : SEMICOLON", (yyval.syminfo)->getName());
        }
#line 2304 "y.tab.c"
    break;

  case 48:
#line 677 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName() + ";", "expression_statement");
            log("expression_statement : expression SEMICOLON", (yyval.syminfo)->getName());
        }
#line 2313 "y.tab.c"
    break;

  case 49:
#line 684 "1805026.y"
        {
            string varName = (yyvsp[0].syminfo)->getName();
            SymbolInfo* var_symbol = st.lookUp(varName);

            if (var_symbol) {
                if (var_symbol->isArray) {
                    SymbolInfo* temp = new SymbolInfo("", "");
                    temp->setAsArray(var_symbol->getName(), "array", var_symbol->size);
                    (yyval.syminfo) = temp;
                }
                else if (var_symbol->isFunction)  {
                    SymbolInfo* temp = new SymbolInfo("", "");
                    temp->setAsFunction(var_symbol->getName(), ERROR, vector<Parameter>());
                    (yyval.syminfo) = temp;
                }
                else {
                    (yyval.syminfo) = new SymbolInfo(var_symbol->getName(), var_symbol->getType());
                }
            }
            else {
                err("Undeclared variable " + varName);
                (yyval.syminfo) = new SymbolInfo((yyvsp[0].syminfo)->getName(), ERROR);
            }

            log("variable : ID", (yyval.syminfo)->getName());
        }
#line 2344 "y.tab.c"
    break;

  case 50:
#line 711 "1805026.y"
        {
            string varName = (yyvsp[-3].syminfo)->getName();
            SymbolInfo* var_symbol = st.lookUp(varName);
            string text = (yyvsp[-3].syminfo)->getName() + "[" + (yyvsp[-1].syminfo)->getName() + "]";

            if (var_symbol) {
                if (var_symbol->isArray) {
                    if ((yyvsp[-1].syminfo)->getType() != "int") {
                        err("Expression inside third brackets not an integer");
                    }
                    (yyval.syminfo) = new SymbolInfo(text, var_symbol->getType());
                }
                else if (var_symbol->isFunction)  {
                    SymbolInfo* temp = new SymbolInfo("", "");
                    temp->setAsFunction(var_symbol->getName(), ERROR, vector<Parameter>());
                    (yyval.syminfo) = temp;
                }
                else {
                    err(varName+ " is not a array");
                    if ((yyvsp[-1].syminfo)->getType() != "int") {
                        err("Expression inside third brackets not an integer");
                    }
                    SymbolInfo* temp = new SymbolInfo(text, ERROR);
                    (yyval.syminfo) = temp;
                }
            }
            else {
                err("Undeclared variable " + varName);
                (yyval.syminfo) = new SymbolInfo(text , ERROR);
            }
            log("variable : ID LTHIRD expression RTHIRD", (yyval.syminfo)->getName());
        }
#line 2381 "y.tab.c"
    break;

  case 51:
#line 746 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("expression : logic_expression", (yyval.syminfo)->getName());
        }
#line 2390 "y.tab.c"
    break;

  case 52:
#line 751 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("expression : logic_expression", (yyval.syminfo)->getName());
        }
#line 2399 "y.tab.c"
    break;

  case 53:
#line 756 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[-1].syminfo);
            log("expression : logic_expression", (yyval.syminfo)->getName());
        }
#line 2408 "y.tab.c"
    break;

  case 54:
#line 761 "1805026.y"
        {
            if ((yyvsp[0].syminfo)->getType() == "void" or (yyvsp[-2].syminfo)->getType() == "void") {
                err("Void function used in expression");
            }
            else if ((yyvsp[-2].syminfo)->getType() != (yyvsp[0].syminfo)->getType()) {
                if ((yyvsp[-2].syminfo)->getType() == ERROR or (yyvsp[0].syminfo)->getType() == ERROR) {
                    if ((yyvsp[-2].syminfo)->isArray) {
                        err("Type Mismatch, " + (yyvsp[-2].syminfo)->getName() + " is an array");
                    }
                    else if ((yyvsp[0].syminfo)->isArray) {
                        err("Type Mismatch, " + (yyvsp[0].syminfo)->getName() + " is an array");
                    } else {

                    }
                }
                else if ((yyvsp[-2].syminfo)->getType() == "float" and (yyvsp[0].syminfo)->getType() == "int"){

                }
                else {
                    err("Type Mismatch ");
                }
            }
            (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + "=" + (yyvsp[0].syminfo)->getName(), "expression");
            log("expression : variable ASSIGNOP logic_expression", (yyval.syminfo)->getName());
        }
#line 2438 "y.tab.c"
    break;

  case 55:
#line 789 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("logic_expression : rel_expression", (yyval.syminfo)->getName());
        }
#line 2447 "y.tab.c"
    break;

  case 56:
#line 794 "1805026.y"
        {
            if ((yyvsp[-2].syminfo)->getType() == "int" and (yyvsp[0].syminfo)->getType() == "int") {
                (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + (yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(),	"int");
            } else {
                err("Both operands must be int type. Given " + (yyvsp[-2].syminfo)->getType() + " : " + (yyvsp[0].syminfo)->getType());
                (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + (yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(),	ERROR);
            }
            log("logic_expression : rel_expression LOGICOP rel_expression", (yyval.syminfo)->getName());
        }
#line 2461 "y.tab.c"
    break;

  case 57:
#line 806 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
			log("rel_expression : simple_expression", (yyval.syminfo)->getName());
        }
#line 2470 "y.tab.c"
    break;

  case 58:
#line 811 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + (yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(), "int");
            log("rel_expression : simple_expresssion RELOP simple_expression" , (yyval.syminfo)->getName());
        }
#line 2479 "y.tab.c"
    break;

  case 59:
#line 817 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
			log("simple_expression : term", (yyval.syminfo)->getName());
        }
#line 2488 "y.tab.c"
    break;

  case 60:
#line 822 "1805026.y"
        {
            if ((yyvsp[-2].syminfo)->getType() == "void" or (yyvsp[0].syminfo)->getType() == "void") {
                err("void function used in expression");
            }
            if ((yyvsp[-2].syminfo)->getType() == "float" or (yyvsp[0].syminfo)->getType() == "float") {
                (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + (yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(), "float");
            } else {
                (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + (yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(), "int");
            }
            log("simple_expression : simple_expression ADDOP term", (yyval.syminfo)->getName());
        }
#line 2504 "y.tab.c"
    break;

  case 61:
#line 836 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
			log("term : unary_expression", (yyval.syminfo)->getName());
        }
#line 2513 "y.tab.c"
    break;

  case 62:
#line 841 "1805026.y"
        {
            string retType = UNDECLARED;
            string ops = (yyvsp[-1].syminfo)->getName();

            if ((yyvsp[-2].syminfo)->getType() == "void" or (yyvsp[0].syminfo)->getType() == "void") {
                err("void function used in expression");
            }

            if (ops == "%") {
                retType = "int";
                if ((yyvsp[-2].syminfo)->getType() != "int" or (yyvsp[0].syminfo)->getType() != "int") {
                    err("Non-integer operand on modulus operator");
                    retType = ERROR;
                }
                else if ((yyvsp[0].syminfo)->getName() == "0"){
                    err("Modulus by zero");
                    retType = ERROR;
                }
            }
            else if (ops == "/") {
                if ((yyvsp[0].syminfo)->getName() == "0"){
                    err("Division by zero");
                    retType = ERROR;
                }
                else if ((yyvsp[-2].syminfo)->getType() == "float" or (yyvsp[0].syminfo)->getType() == "float") retType = "float";
                else retType = "int";
            }
            else if (ops == "*") {
                if ((yyvsp[-2].syminfo)->getType() == "float" or (yyvsp[0].syminfo)->getType() == "float") retType = "float";
                else retType = "int";
            }

            (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + (yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(), retType);
			log("term : term MULOP unary_expression", (yyval.syminfo)->getName());
        }
#line 2553 "y.tab.c"
    break;

  case 63:
#line 879 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName() + (yyvsp[0].syminfo)->getName(), (yyvsp[0].syminfo)->getType());
			log("unary_expression : ADDOP unary_expression", (yyval.syminfo)->getName());
        }
#line 2562 "y.tab.c"
    break;

  case 64:
#line 884 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("!" + (yyvsp[0].syminfo)->getName(), (yyvsp[0].syminfo)->getType());
			log("unary_expression : NOT unary_expression", (yyval.syminfo)->getName());
        }
#line 2571 "y.tab.c"
    break;

  case 65:
#line 889 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("unary_expression : factor", (yyval.syminfo)->getName());
        }
#line 2580 "y.tab.c"
    break;

  case 66:
#line 896 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("factor : variable", (yyval.syminfo)->getName());
        }
#line 2589 "y.tab.c"
    break;

  case 67:
#line 901 "1805026.y"
        {
            string retType = ERROR;
            SymbolInfo* func = st.lookUp((yyvsp[-3].syminfo)->getName());

            if (func) {
                if (func->isFunction) {
                    retType = func->getType();
                    vector<string> argNames = tokenize((yyvsp[-1].syminfo)->getName(), ',') , argTypes = tokenize((yyvsp[-1].syminfo)->getType(), ',');

                    vector<Parameter> pList = func->paramList;
                    
                    if (pList.size() != argNames.size()) {
                        err("Inconsistent number of arguments in function call " + func->getName());
                    }
                    else {
                        for (int i=0; i<argTypes.size(); i++) {
                            if (argTypes[i] != pList[i].type) {
                                err(to_string(i+1) + " th argument has inconsistent type in function '" + (yyvsp[-3].syminfo)->getName() + "'\nType : " + argTypes[i] + " inplace of " + pList[i].type + " " + pList[i].name);
                            }
                        }
                    }

                } else {
                    err("Multiple declaration of '" + (yyvsp[-3].syminfo)->getName() + "'");
                }
            } else {
                err("Undeclared function call '" + (yyvsp[-3].syminfo)->getName() + "' ");
            }

            (yyval.syminfo) = new SymbolInfo((yyvsp[-3].syminfo)->getName() + "(" + (yyvsp[-1].syminfo)->getName() + ")",	retType);
			log("factor : ID LPAREN argument_list RPAREN", (yyval.syminfo)->getName());
        }
#line 2626 "y.tab.c"
    break;

  case 68:
#line 934 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("(" + (yyvsp[-1].syminfo)->getName() + ")",	(yyvsp[-1].syminfo)->getType() );
			log("factor : LPAREN expression RPAREN", (yyval.syminfo)->getName());
        }
#line 2635 "y.tab.c"
    break;

  case 69:
#line 939 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo(yylval.syminfo->getName(), "float");
			log("factor : CONST_FLOAT", (yyval.syminfo)->getName());
        }
#line 2644 "y.tab.c"
    break;

  case 70:
#line 944 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo(yylval.syminfo->getName(), "int");
			log("factor : CONST_INT", (yyval.syminfo)->getName());
        }
#line 2653 "y.tab.c"
    break;

  case 71:
#line 949 "1805026.y"
        {
            if ((yyvsp[-1].syminfo)->getType() == "void") {
                err("Void function cannot be incremented");
            }
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName() + "++", (yyvsp[-1].syminfo)->getType());
			log("factor : variable INCOP", (yyval.syminfo)->getName());
        }
#line 2665 "y.tab.c"
    break;

  case 72:
#line 957 "1805026.y"
        {
            if ((yyvsp[-1].syminfo)->getType() == "void") {
                err("Void function cannot be decremented");
            }
            (yyval.syminfo) = new SymbolInfo((yyvsp[-1].syminfo)->getName() + "--", (yyvsp[-1].syminfo)->getType());
			log("factor : variable DECOP", (yyval.syminfo)->getName());
        }
#line 2677 "y.tab.c"
    break;

  case 73:
#line 967 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("argument_list : arguments", (yyval.syminfo)->getName());
        }
#line 2686 "y.tab.c"
    break;

  case 74:
#line 972 "1805026.y"
        {
            (yyval.syminfo) = new SymbolInfo("", "void");
            log("argument_list : " , (yyval.syminfo)->getName());
        }
#line 2695 "y.tab.c"
    break;

  case 75:
#line 979 "1805026.y"
        {
            // cout << "Adding " << $3->getType() << " " << $3->getName() << endl;
            (yyval.syminfo) = new SymbolInfo((yyvsp[-2].syminfo)->getName() + "," + (yyvsp[0].syminfo)->getName(), (yyvsp[-2].syminfo)->getType() + "," + (yyvsp[0].syminfo)->getType());
            log("arguments : arguments COMMA logic_expression", (yyval.syminfo)->getName());
        }
#line 2705 "y.tab.c"
    break;

  case 76:
#line 985 "1805026.y"
        {
            (yyval.syminfo) = (yyvsp[0].syminfo);
            log("arguments : logic_expression", (yyval.syminfo)->getName());
        }
#line 2714 "y.tab.c"
    break;


#line 2718 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 992 "1805026.y"


int main( int argc, char** argv)
{
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
    FILE *fin = fopen(argv[1], "r");

	if(fin == nullptr) {
        cout << "File Not Found" << endl;
        return 0;
	}    

    yyin=fin;
	yyparse();

    st.printAllScopeTable();

    logfile << "Total Line Count : " << linenum << endl;
    logfile << "Total Error Count : " << errornum << endl;


    fclose(yyin);
    logfile.close();
    errfile.close();

    return 0;
}
