%{
	#include <iostream>
	#include "parser.h" 
	using std::cout ; 
	using std::endl ;
	int yyerror1(const char *s1) ;
	int line = 1 ; 
	int column=1 ; 
	int getLine() ; 
	int getColumn () ; 
%}
%option noyywrap

escape_sequence		"'"\\n"'"|"'"\\\\"'"|"'"\\a"'"|"'"\\r"'"

%%
[ \t]								{column +=yyleng ; }
[\n]								{column=0 ; line++ ; }
"if"								{column+= 2 ;return IF;}
"else"								{column += 4 ; return ELSE ; }
"break"								{column += yyleng ; return BREAK; }
"continue"							{column += yyleng ;return CONTINUE; }
"while"								{column += yyleng ;return WHILE; }
"return"							{column += yyleng ;return RETURN; }

"int"								{column += yyleng ; return INT;  }
"char"								{column += yyleng ;return CHAR ;  }
"float"								{column += yyleng ;return FLOAT;  }
"string"							{column += yyleng ;return STRING;  }
"bool"								{column += yyleng ;return BOOL ;  }
0|([1-9][0-9]*)						{column += yyleng ;return INTNUM;  }
(0|([1-9][0-9]*))("."[0-9]+)?		{column += yyleng ;return FLOATNUM ;  } 
		
"'"."'"|{escape_sequence}			{column += yyleng ;return CHARCONST ; }
\".*\"								{column += yyleng ;return STRINGCONST ;  }
"false"								{column += yyleng ;return FALSE; }
"true"								{column += yyleng ;return TRUE; }
"null"								{column += yyleng ;return NUL ;  }
[_a-zA-Z][_0-9a-zA-Z]*				{column += yyleng ;return ID ;  }
", "								{column += yyleng ; return SPACECOM;}
"=="								{column += yyleng ; return IS_EQUAL;}

[-=\+\*,<>\/ "?":!;(){}]|"&&"|"||"	{column += yyleng ;return *yytext ;}
.									{column+= yyleng ; yyerror1("lexical error");}
%%

int getLine () 
{
return line ; 
}

int getColumn () 
{
	return column ; 
}

int yyerror1 ( const char* s1 ) 
{
	cout << s1 << " line : "<<line << " column : " << column << endl;
return 1 ; 
}