%{
			#include<iostream>
			#include "ast.h"
			using std::cout; 
			using std::endl; 
			extern int yylex() ; 
			extern int getLine() ; 
			extern int getColumn(); 
			int yyerror(const char* s1) ;
			extern int yydebug;
			bool flage = false ;
			Class_decl* root ; 

%}

%union{
	Class_decl*			tclass_decl;
	Smallc_program*		tsmallc_program;
	Func*				tfunc; 
	Var_decl*			tvar_decl; 
	Constructor*		tconstructor ;











}

%type <tclass_decl>	class_decl
%type <tsmallc_program>	smallc_program 
%type <tfunc> func
%type <tvar_decl> var_decl
%type <tconstructor> constructor




%token ID INT FLOAT CHAR STRING BOOL RETURN BREAK CONTINUE WHILE IF ELSE ACCMOD
%token INTNUM FLOATNUM CHARCONST STRINGCONST TRUE FALSE NUL IS_EQUAL SPACECOM CLASS
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

class_decl: ACCMOD CLASS ID '{'smallc_program'}'
					{
						$$ = new Class_decl(getLine(),getColumn(), $1 , $3, $5);
						root = $$ 

					
					}
			|CLASS ID '{' smallc_program '}'
					{
					$$ = new Class_decl(getLine(), getColumn(),"private" ,$2, $4) ; 
					class_decl = $$ ; 
					}
;

smallc_program: 
					{
					// i don't know what to do here ......................
					}
				|smallc_program func 
					{
					$$ = new Func_program(getLine(),getColumn(),$1 ,$2);
					}

				|smallc_program var_decl
					{
					$$ = new Var_program(getLine(),getColumn(),$1,$2); 
					
					}
				|smallc_program class_decl
					{
						$$ = new Class_decl_program(getLine(),getColumn(),$1,$2);
					}
				|smallc_program constructor
					{
					$$ = new Constructor (getLine() , getColumn() , $1, $2);
					}

; 


constructor: ID '(' param_decl_list ')' compound_stmt
					{
					$$ = new Constructor (getLine(),getColumn(),$1 , $3, $5);
					}
			
;


func: type_specifier ID '(' param_decl_list ')' compound_stmt
			{
			$$ = new Normal_func(getLine(),getColumn(),$1,$2,$4,$6);
			}
	|type_specifier '['']' ID '(' param_decl_list ')' compound_stmt
			{
			$$ = new Array_func(getLine(),getColumn(), $1, $4 ,$6 , $8);
			}
;
type_specifier: INT
					{
						$$ = 1 ; 
					}
				|FLOAT
					{
						$$ = 2 ; 
					}
				|CHAR
					{
						$$ = 3 ; 

					}
				|STRING
					{
						$$ = 4 ; 
					}
				|BOOL
					{
						$$ = 5 ; 
					}
;

param_decl_list:
			{
				$$ = new Param_decl_list(getLine(),getColumn());
			}
				|param_decl
			{
				$$ = new Param_decl_list(getLine(),getColumn(),$1);
			}
				|param_decl_list ',' param_decl 
			{
				$1->add_param($3);
				$$ = $1 ; 
			
			}
;
param_decl:		type_specifier ID
			{
				$$ = new Normal_param_decl(getLine(),getColumn(),$1,$2);
			}
				|type_specifier ID '['']' 
			{
				$$ = new Array_param_decl(getLine(),getColumn(),$1,$2);
			}
;

compound_stmt:'{' compound_stmts '}'
					{
						$$ = new Compound_stmt(getLine(),getColumn(),$2);
					}
;
compound_stmts:  
					{
						$$ = new Compound_stmts(getLine(),getColumn());
					}
				|compound_stmts var_decl
					{
						if ( $1 == NULL) $1 = new Compound_stmts(getLine(),getColumn());
						$1->add_var($2);
						$$ = $1 ; 
					}
				|compound_stmts stmt
					{
						if ($1 == NULL) new Compound_stmts(getLine(),getColumn());
						$1->add_stmt($2);
						$$ = $1 ; 
					}
;
var_decl: type_specifier var_decl_list ';'	
					{
						$$ = new Var_decl(getLine(),getColumn(),$1,$2);
					}
;
var_decl_list:	variable_id	
					{
						$$ = new Var_decl_list(getLine(),getColumn(), $1);
					}
				|var_decl_list ',' variable_id
					{
						$1->add_var(getLine(),getColumn(),$3);
						$$ = $1 ; 
					}
; 
variable_id:	ID
					{
						$$  = new Id (getLine(),getColumn(),$1) ; 
					}
				|ID '=' expr
					{
						$$ = new Variable_assignment(getLine(),getColumn(),$1,$3);
					}
				|ID '['']' '=' '{' primary_list '}'
					{
						$$ = new Array_variable_assignment(getLine(),getColumn(),$1,$6);
					}
				|ID '['']'
					{
						$$ = new Array_variable_id(getLine(),getColumn(),$1);
					}
; 




stmt: compound_stmt
					{
						$$ = new Stmt_compound(getLine(),getcolumn(),$1);
					
					}
		|cond_stmt
					{
						$$ = new Stmt_cond(getLine(),getcolumn(),$1);
					}
		|while_stmt
					{
						$$ = new Stmt_while(getLine(),getcolumn(),$1);

					}
		|BREAK ';'
		|assignstmt ';'
					{
						$$ = new Stmt_assignment(getLine(),getColumn(),$1);
					}

		
		|CONTINUE ';' 
		|RETURN expr ';'
					{
						$$ = new stmt_expr(getLine(),getColumn(),$1);
					}

;

cond_stmt:	IF '(' expr ')' stmt	%prec IF_PREC 
					{
					$$ = new If_cond_stmt(getLine(),getColumn(),$3,$5);

					}
			|IF '(' expr ')' stmt ELSE stmt
					{
					$$ = new Else_cond_stmt(getLine(),getColumn(),$3,$5,$7); 
					}
;
while_stmt: WHILE '(' expr ')' stmt 
					{
					$$ = new While_stmt(getLine(),getColumn(),$3,$5) ; 
					}
;
assignstmt: ID '=' expr
					{
					$$ = new AssigStmt(getLine(),getColumn(),$1,$3);
					}
;
triplecondition: expr '?' expr ':' expr 
					{
						$$ = new TripleCondition(getLine(),getColumn(),$1,$3,$5);
					}
;
expr: primary
					{
						$$ = new Exp_primary($1);
					}
	|expr operator expr		%prec OP
					{
						$$ = new Operator_expr(getLine(),getColumn(),$2,$1,$3);
					}
	|'!' expr 
					{
						$$ = new Not_expr(getLine(),getColumn(),$2);
					}
	| '(' expr ')'
					{
						$$ = new Parentheses_expr(getLine(),getColumn(),$2);
					}
	|triplecondition
					{
					$$ = new Exp_triplecondition(getLine(),getColumn(),$1);
					}
	|'-' expr
					{
						$$ = new Minus_expr(getLine(),getColumn(),$2);
					}
	|ID '(' expr_list ')'
					{
					$$ = new Func_call_expr(getLine(),getColumn(),$1,$3);	
					}
	|ID '['expr ']' 
					{
					$$ = new Array_expr(getLine(),getColumn(),$1,$3);
					
					}
;
expr_list: 
					{
					$$ = new Expr_list(getLine(),getColumn());
					}
			|expr
					{
					$$ = new Expr_list(getLine(),getColumn(),$1);
					}
			|expr_list SPACECOM expr
					{
					$1-> add_expr($3);
					$$ = $1 ; 
					}
;

operator: '+'
				{
					$$ = new Operator(getLine(), getColumn(),1);
				}
		|'-'
				{
					$$ = new Operator(getLine(), getColumn(),2);
				}
		|'*'
				{
					$$ = new Operator(getLine(), getColumn(),3);
				}
		|'/'
				{
					$$ = new Operator(getLine(), getColumn(),4);
				}
		|'<'
				{
					$$ = new Operator(getLine(), getColumn(),5);
				}
		|'>'
				{
					$$ = new Operator(getLine(), getColumn(),6);
				}
		|'||'
				{
					$$ = new Operator(getLine(), getColumn(),7);
				}
		|IS_EQUAL
				{
					$$ = new Operator(getLine(), getColumn(),8);
				}
		|'&&'
				{
					$$ = new Operator(getLine(), getColumn(),9);
				}
;
primary:INTNUM
				{
					$$ = new Primary_num($1) ; 
				}
		|FLOATNUM
				{
					$$ = new Primary_float($1);
				}
		|CHARCONST
				{
					$$ = new Primary_char($1) ; 
				}
		|STRINGCONST
				{
					$$ = new Primary_string($1) ;
				}
		|ID
				{
					$$ = new Primary_id($1); 
				}
		|TRUE
				{
					$$ = new Primary_true($1);
				}
		|FALSE
				{
					$$ = new Primary_false($1);
				}
		|NUL
				{
					$$ = new Primary_null($1) ; 
				}
;
primary_list: primary_list ',' primary
				{
					$1->add_primary($3);
					$$ = $1 ; 
				}
				| primary
				{
					$$ = new Primary_list(getLine(),getColumn(),$1);
				}
;
	
%%


int yyerror(const char *s1)
{
	flage = true ;
	cout << "Syntax Error : " << "line : "<< getLine()  << " column : " << getColumn() << endl;
	return 1;
}

int main() 
{
flage = false ; 
yydebug=1;
yyparse() ; 
if ( flage== false ) cout<< "parsing done !!!"<< endl; 
	return 0 ; 

}