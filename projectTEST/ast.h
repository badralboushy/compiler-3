#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std; 






class Node; 
class Class_decl;
class Id; 
class Smallc_program;
class Param_decl_list;
class Compound_stmt; 
class Compound_stmts;
class Var_decl; 
class Var_decl_list; 
class Variable_id; 
class Stmt; 
class Cond_stmt; 
class While_stmt; 
class AssigStmt; 
class TripleCondition;
class Expr; 
class Expr_list; 
class Operator; 
class Primary_list;
class Primary; 
class Func; 
class Operator;


class Node
{
public:
	int line;
	int column;
	Node* father;
	Node(int, int);
};

class Class_decl : public Node {
public:
	string accmod; 
	Id* id; 
	Smallc_program* smallc_program; 
	Class_decl(int, int,string, Id*, Smallc_program*);



};




class Smallc_program : public Node  //not sure 
{
public:	
	Smallc_program(int, int); 
};

class Func_program : public Smallc_program {
public:

	Smallc_program* smallc_program;
	Func* func;
	Func_program(int, int, Smallc_program*, Func*);
};

class Var_program : public Smallc_program {
	public:
	Smallc_program* smallc_program;
	Var_decl* var_decl;
	Var_program(int, int, Smallc_program* ,Var_decl* );
};
class Func : public Node 
{
public:
	Func(int, int); 
};
class Array_func : public Func {
public:
	int type;
	Id* id;
	Param_decl_list* param_decl_list;
	Compound_stmt* compound_stmt;
	Array_func(int, int ,int, Id*, Param_decl_list*, Compound_stmt*);

};

class Normal_func : public Func {
public:
	int type;
	Id* id;
	Param_decl_list* param_decl_list;
	Compound_stmt* compound_stmt;
	Normal_func(int ,int ,int, Id*, Param_decl_list*, Compound_stmt*);

};
/// <summary> 
// badr 6/6
class Class_decl_program :public Smallc_program
{
	Smallc_program* smallc_program; 
	Class_decl* class_decl; 
	Class_decl_program(int, int, Smallc_program*, Class_decl*);
};

class Constructor :public Node
{
public :
	Id* id; 
	Param_decl_list* param_decl_list; 
	Compound_stmt* compound_stmt; 
	Constructor(int, int, Id*, Param_decl_list*, Compound_stmt*);
};
/// </summaryp
class Param_decl : public Node { 
public :

	Param_decl(int, int); 

};
class Normal_param_decl : public Param_decl {
public:
	int type;
	Id* id;
	Normal_param_decl(int, int, int, Id*);

};
class Array_param_decl : public Param_decl { 
public:
	int type;
	Id* id;
	Array_param_decl(int, int, int, Id*);

};

class Param_decl_list:public Node  {
public:
	vector<Param_decl* > *list; 
	Param_decl_list(int , int ); 
	Param_decl_list(int, int, Param_decl*); 
	void add_param(Param_decl*); 
};

class Compound_stmt : public Node {
public:
	Compound_stmts* compound_stmts;
	Compound_stmt(int, int, Compound_stmts*);
};
//class Compound_stmts : public Node {//not sure
//public:
//	Compound_stmts* compound_stmts;
//	Var_decl* var_decl;
//	Stmt* stmt;
//	Compound_stmts(int, int, Compound_stmts*, Var_decl*);
//}; 
/// <badr>
class Compound_stmts : public Node
{
public:
	
	vector <Stmt*> *stmt_list;
	vector < Var_decl*> *var_decl_list; 
	Compound_stmts(int, int);
	void add_var(Var_decl*);
	void add_stmt(Stmt*);

};


/// </badr>

class Var_decl : public Node {
public:
	int type;
	Var_decl_list* var_decl_list;
	Var_decl(int, int, int, Var_decl_list*);

};
class Var_decl_list :public Node {
public:
	vector<Variable_id* >* list;
	Var_decl_list(int, int);
	Var_decl_list(int, int, Variable_id*);
	void add_var(Variable_id*);
};

class Variable_id : public Node {
public:

	Variable_id(int, int);

};
class Id : public Variable_id
{
public:

	string value;
	Id(int, int, string);

};
class Variable_assignment : public Variable_id {
	Id* id;
	Expr* expr;
	Variable_assignment(int, int, Id*, Expr*);
};

class Array_variable_assignment : public Variable_id {
public:
	Id* id;
	Primary_list* primary_list;
	Array_variable_assignment(int, int, Id*, Primary_list*);
};

class Array_variable_id: public Variable_id {
	Id* id; 
	Array_variable_id(int, int, Id*);
};

// 2/6/2021.

class Stmt : public Node
{
public:

	Stmt(int, int); 
};

class Stmt_cond : public Stmt 
{
public:
	Cond_stmt* cond_stmt; 
	Stmt_cond(int, int , Cond_stmt*);

};
class Stmt_compound: public Stmt
{
public:
	Compound_stmt* compound_stmt;
	Stmt_compound(int, int , Compound_stmt*);

};

class Stmt_while : public Stmt
{
public:
	While_stmt* while_stmt ;
	Stmt_while(int, int , While_stmt* );

};

class Stmt_assignstmt : public Stmt
{
public:
	AssigStmt* assignment;
	Stmt_assignstmt(int, int, AssigStmt*);

};
class Stmt_expr : public Stmt
{
public:
	Expr* expr; 
	Stmt_expr(int, int, Expr*);
};


class Cond_stmt :public Node {
public :
	Cond_stmt(int, int);
};

class If_cond_stmt : public Cond_stmt {
public:
	Expr* expr;
	Stmt* ifstmt;
	If_cond_stmt(int, int, Expr*, Stmt*);
};

class Else_cond_stmt : public Cond_stmt 
{
public:

	Expr* expr;
	Stmt* ifstmt;
	Stmt* elsestmt;
	Else_cond_stmt(int, int, Expr*, Stmt*, Stmt*);

};

class While_stmt : public Stmt
{
public:

	Expr* expr; 
	Stmt* stmt; 
	While_stmt(int, int, Expr*, Stmt*); 

};

class AssigStmt :public Stmt
{
public:

	Id* id; 
	Expr* expr; 
	AssigStmt(int, int, Id*, Expr*); 
};

class Expr : public Node 
{
public:
	Expr(int, int); 
};

//class Primary : public Expr
//{
//public:	
//	int intNum; 
//	double floatNum; 
//	char charConst; 
//	string stringConst; 
//	Id* id;
//	bool booltrue; 
//	bool boolfalse; 
//	Node* nullValue;  
//
//
//	Primary(int, int, int, double, char, string, Id*, bool, bool, Node*);
//
//};
class Primary : public Node
{
public:
	Primary(int, int); 

};
class Primary_num : public Primary
{
public:
	int value; 
	Primary_num(int, int, int);

};
class Primary_float :public Primary
{
public :
	double value; 
	Primary_float(int, int, float); 
};

class Primary_char :public Primary
{
public :

	char value; 
	Primary_char(int, int, char);
};
class Primary_string : public Primary
{
	string value; 
	Primary_string(int, int, string);
};
class Primary_id : public Primary
{
public:
	string value; 
	Primary_id( int , int ,string);
};
class Primary_false : public Primary
{
public:
	bool varfalse; 
	Primary_false(int, int, bool);

};
class Primary_true : public Primary
{
public:
	bool vartrue; 
	Primary_true(int, int, bool); 


};
class Primary_null : public Primary
{
public:
	Node* varnull;
	Primary_null(int, int, Node*);

};
class Exp_primary : public Expr
{
public :
	Primary* primary; 
	Exp_primary( int , int ,Primary* primary);
};

class TripleCondition : public Expr {
public :

	Expr* expr1;
	Expr* expr2;
	Expr* expr3;
	TripleCondition(int, int, Expr*, Expr*, Expr*);

};
class Exp_triplecondition : public Expr
{
public :

	TripleCondition* triple_condition; 
	Exp_triplecondition(int, int, TripleCondition*); 

};

class Operator_expr : public Expr {
public:
	Expr* expr_left;
	Expr* expr_right;
	Operator* op;
	Operator_expr(int, int, Operator*, Expr*, Expr*);
};

class Operator :public Node {
public:

	int op_code;
	Operator(int, int, int);

}; 

class Not_expr : public Expr {
public:
	Expr* expr;
	Not_expr(int, int, Expr*);
};

class  Parentheses_expr : public Expr {
public:
	Expr* expr;
	Parentheses_expr(int, int, Expr*);
};

class Minus_expr : public Expr {
public:

	Expr* expr;
	Minus_expr(int, int, Expr*);
};

class Func_call_expr : public Expr {
public:

	Id* id;
	Expr_list* list;
	Func_call_expr(int, int, Id*, Expr_list*);
};

class Array_expr : public Expr {
public:
	Id* id;
	Expr* expr;
	Array_expr(int, int, Id*, Expr*);

};

class Expr_list : public Node {
public:
	vector<Expr* >* list;
	Expr_list(int, int);
	Expr_list(int, int, Expr*);
	void add_expr(Expr*);
};

class Primary_list : public Node {
public:
	vector<Primary* >* list;
	Primary_list(int, int);
	Primary_list(int, int, Primary*);
	void add_primary(Primary*);
};