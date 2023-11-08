%{
#include<iostream>
using std::cout; 
using std::endl; 
extern int yylex() ; 
extern int getLine() ; 
extern int getColumn(); 
int yyerror(const char* s1) ;
extern int yydebug;

%}

%token ID INT FLOAT CHAR STRING BOOL RETURN BREAK CONTINUE WHILE IF ELSE
%token INTNUM FLOATNUM CHARCONST STRINGCONST TRUE FALSE NUL IS_EQUAL SPACECOM
%nonassoc IF_PREC
%nonassoc ELSE
%nonassoc ID
%nonassoc '<' '>' '&&' '||' IS_EQUAL
%right '!'
%right '=' 
%left '+' '-'
%left '*' '/' 

%right '('
%left  ')'
%nonassoc OP
%right ':'
%left '?' 

%%
smallc_program: 
				|smallc_program func 
				|smallc_program var_decl
; 
func: type_specifier ID '(' param_decl_list ')' compound_stmt
;
type_specifier: INT
				|FLOAT
				|CHAR
				|STRING
				|BOOL
;

param_decl_list:
				|param_decl
				|param_decl_list ',' param_decl 
;
param_decl:		type_specifier ID

compound_stmt:'{'compound_stmts '}'
;
compound_stmts:  
				|compound_stmts var_decl
				|compound_stmts stmt
;
var_decl: type_specifier var_decl_list ';'
;
var_decl_list:	variable_id
				|var_decl_list ',' variable_id
; 
variable_id:	ID
				|ID '=' expr
;
stmt: compound_stmt
		|cond_stmt
		|while_stmt
		|BREAK ';'
		|assignstmt ';'
		|CONTINUE ';' 
		|RETURN expr ';'
;
cond_stmt:	IF '(' expr ')' stmt	%prec IF_PREC 
			|IF '(' expr ')' stmt ELSE stmt
;
while_stmt: WHILE '(' expr ')' stmt 
;
assignstmt: ID '=' expr
;
triplecondition: expr '?' expr ':' expr 
expr: primary 
	|expr operator expr		%prec OP
	|'!' expr 
	| '(' expr ')' 
	|triplecondition
	|'-' expr
	|ID '(' expr_list ')'
;
expr_list: 
			|expr
			|expr_list SPACECOM expr
;

operator: '+'
		|'-'
		|'*'
		|'/'
		|'<'
		|'>'
		|'||'
		|IS_EQUAL
		|'&&'
;
primary:INTNUM
		|FLOATNUM
		|CHARCONST
		|STRINGCONST
		|ID
		|TRUE
		|FALSE
		|NUL
;

	
%%


int yyerror(const char *s1)
{
	cout << "Syntax Error : " << "line : "<< getLine()  << " column : " << getColumn() << endl;
	return 1;
}

int main() 
{
yydebug=1;
yyparse() ; 
cout<< "parsing done !!!"<< endl; 
	return 0 ; 

}