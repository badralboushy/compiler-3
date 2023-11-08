#include "ast.h"


Node::Node(int line, int column)
{
	this->line = line;
	this->column = column;
	this->father = NULL;
}



Class_decl::Class_decl(int line ,int column ,string accmod,  Id* id, Smallc_program* smallc_program  ) : Node(line, column)
{
		this->id = id;
		this->smallc_program = smallc_program;
		this->accmod = accmod;
		id->father = this;
		smallc_program->father = this;
}

Smallc_program::Smallc_program(int line, int column) :Node(line, column) 
{

}

Func_program::Func_program(int line, int column, Smallc_program* s, Func* f) : Smallc_program(line, column) {
	this->smallc_program = s;
	this->func = f;
	if (func != NULL)this->func->father = this;
	if (this->smallc_program != NULL)	this->smallc_program = this;
}

Var_program::Var_program(int line, int column, Smallc_program* s, Var_decl* v) : Smallc_program(line, column) {
	this->smallc_program = s;
	this->var_decl = v;
	if (var_decl != NULL) this->var_decl->father = this;
	if (this->smallc_program != NULL)	this->smallc_program = this;
}



Func::Func(int line, int column) :Node(line, column ) 
{
	
}
Array_func::Array_func(int line, int column, int type, Id* id, Param_decl_list* p, Compound_stmt* c) : Func(line, column) {
	this->type = type;
	this->id = id;
	this->param_decl_list = p;
	this->compound_stmt = c;

	id->father = this;
	if (param_decl_list != NULL)
		param_decl_list->father = this;

	if (compound_stmt != NULL)
		compound_stmt->father = this;
}

Normal_func::Normal_func(int line, int column, int type, Id* id, Param_decl_list* p, Compound_stmt* c) : Func(line, column) {
	this->type = type;
	this->id = id;
	this->param_decl_list = p;
	this->compound_stmt = c;

	id->father = this;
	if (param_decl_list != NULL)
		param_decl_list->father = this;

	if (compound_stmt != NULL)
		compound_stmt->father = this;
}
Param_decl::Param_decl(int line, int column) :Node(line, column) {
	
}
Normal_param_decl::Normal_param_decl(int line, int column, int type, Id* id) : Param_decl(line, column) {
	this->type = type;
	this->id = id;
	if (id != NULL) id->father = this;
}
Array_param_decl::Array_param_decl(int line, int column, int type, Id* id) : Param_decl(line, column) {
	this->type = type;
	this->id = id;
	if (id != NULL) id->father = this;
}
Param_decl_list::Param_decl_list(int line , int column):Node(line,column)
{
	this->list = new vector<Param_decl*>(); 

}
void Param_decl_list::add_param(Param_decl* p) {
	this->list->push_back(p); 
	p->father = this; 

}
Param_decl_list::Param_decl_list(int line, int column, Param_decl* p) : Node(line, column)
{	
	this->list = new vector <Param_decl*>();				// not sure;


	this->list->push_back(p); 

}

Compound_stmt::Compound_stmt(int line, int column, Compound_stmts* c) : Node(line, column) {
	this->compound_stmts = c;
	this->compound_stmts->father = this;
}
Compound_stmts::Compound_stmts(int line, int column) : Node(line, column) {
	this->stmt_list = new vector <Stmt*>(); 
	this->var_decl_list = new vector <Var_decl*>();

}

void Compound_stmts::add_stmt(Stmt* s) {
	this->stmt_list->push_back(s);
}
void Compound_stmts::add_var(Var_decl* v)
{
	this->var_decl_list->push_back(v);
}


Var_decl::Var_decl(int line, int column, int type, Var_decl_list* v) : Node(line, column) {
	this->type = type;
	this->var_decl_list = v;
	this->var_decl_list->father = this;

}

Var_decl_list::Var_decl_list(int line, int column) :Node(line, column)
{
	this->list = new vector<Variable_id*>();

}
void Var_decl_list::add_var(Variable_id* v) {
	this->list->push_back(v);
	v->father = this;

}
Var_decl_list::Var_decl_list(int line, int column, Variable_id* v) : Node(line, column)
{

	this->list->push_back(v);

}
Variable_id::Variable_id(int line, int column) : Node(line, column) {
	
}

Id::Id(int line, int column, string s) : Variable_id(line, column)
{
	this->value = s;

}
Variable_assignment::Variable_assignment(int line, int column, Id* id, Expr* expr) : Variable_id(line, column) {
	this->id = id;
	this->expr = expr;
	if (id != NULL) this->id->father = this;
	if (expr != NULL) this->expr->father = this;
}

Array_variable_assignment::Array_variable_assignment(int line, int column, Id* id, Primary_list* p ) :Variable_id(line, column) {
	this->id = id;
	this->primary_list = p;
	if (id != NULL) this->id->father = this;
	if (p != NULL) this->primary_list->father = this;
}

Array_variable_id::Array_variable_id(int line, int column, Id* i) : Variable_id(line, column)
{
	this->id = i; 
	this->id->father= this; 
}
Stmt::Stmt(int line, int column) : Node(line, column)
{

};



If_cond_stmt::If_cond_stmt(int line, int column, Expr* expr, Stmt* ifs) : Cond_stmt(line, column) {
	this->expr = expr;
	this->ifstmt = ifs;
	this->expr->father = this;
	this->ifstmt->father = this;
}

Else_cond_stmt::Else_cond_stmt(int line, int column, Expr* expr, Stmt* ifs, Stmt* els) : Cond_stmt(line, column)
{
	this->expr = expr;
	this->ifstmt = ifs;
	this->elsestmt = els;
	this->expr->father = this;
	this->ifstmt->father = this;
	this->elsestmt->father = this;
}

While_stmt::While_stmt(int line, int column, Expr* e , Stmt* s):Stmt(line,column)
{
	this->expr = e; 
	this->stmt = s; 	
	this->expr->father = this; 
	this->stmt->father = this; 
}

AssigStmt::AssigStmt(int line, int column, Id* id, Expr* expr ) : Stmt(line, column)
{
	this->id = id; 
	this->expr = expr; 
	this->id->father = this; 
	this->expr->father = this; 
}


Expr::Expr(int line, int column) : Node(line, column)
{

}


TripleCondition::TripleCondition(int line, int column, Expr* e1, Expr* e2, Expr* e3) : Expr(line, column) {
	this->expr1 = e1;
	this->expr2 = e2;
	this->expr3 = e3;
	this->expr1->father = this;
	this->expr2->father = this;
	this->expr3->father = this;
}

Operator_expr::Operator_expr(int line, int column, Operator* o, Expr* left, Expr* right) : Expr(line, column) {
	this->op = o;
	this->expr_left = left;
	this->expr_right = right;
	this->expr_left->father = this;
	this->expr_right->father = this;
	this->op->father = this; 
}

Not_expr::Not_expr(int line, int column, Expr* e) : Expr(line, column) {
	this->expr = e;
	this->expr->father = this;

}

Parentheses_expr::Parentheses_expr(int line, int column, Expr* e) : Expr(line, column) {
	this->expr = e;
	this->expr->father = this;

}

Minus_expr::Minus_expr(int line, int column, Expr* e) : Expr(line, column) {
	this->expr = e;
	this->expr->father = this;

}

Func_call_expr::Func_call_expr(int line, int column, Id* id, Expr_list* e) : Expr(line, column) {
	this->id = id;
	this->list = e;
	this->id->father = this;
	this->list->father = this;
}

Array_expr::Array_expr(int line, int column, Id* id, Expr* e) : Expr(line, column) {
	this->id = id;
	this->expr = e;
	this->id->father = this;
	this->expr->father = this;
}

Expr_list::Expr_list(int line, int column) :Node(line, column)
{
	this->list = new vector<Expr*>();

}
void Expr_list::add_expr(Expr* e) {
	this->list->push_back(e);
	e->father = this;

}
Expr_list::Expr_list(int line, int column, Expr* e) : Node(line, column)
{

	this->list->push_back(e);

}

Primary_list::Primary_list(int line, int column) :Node(line, column)
{
	this->list = new vector<Primary*>();

}
void Primary_list::add_primary(Primary* p) {
	this->list->push_back(p);
	p->father = this;

}
Primary_list::Primary_list(int line, int column, Primary* p) : Node(line, column)
{

	this->list->push_back(p);

}


/////// badr 6/6
Class_decl_program::Class_decl_program(int line, int column, Smallc_program* sm, Class_decl* cl) :Smallc_program(line, column)
{
	this->smallc_program = sm; 
	this->class_decl = cl; 
	smallc_program->father = this; 
	class_decl->father = this; 

}

Constructor::Constructor(int line, int column, Id* i, Param_decl_list* pd, Compound_stmt* cs) : Node(line,column)
{
	this->id = id; 
	this->param_decl_list = pd; 
	this->compound_stmt = cs; 
	param_decl_list->father = this;
	compound_stmt->father = this; 

}

Exp_primary::Exp_primary(int line, int column ,Primary* primary):Expr(line, column )
{
	this->primary = primary; 
	this->primary->father = this; 
}

Exp_triplecondition::Exp_triplecondition(int line, int coloumn, TripleCondition* t) : Expr(line,column)
{
	this->triple_condition = t; 
	this->triple_condition->father = this; 
}



Operator::Operator(int line, int column, int op):Node(line,column)
{
	this->op_code = op; 
}

Primary::Primary(int line , int column):Node(line,column)
{
}

Primary_null::Primary_null(int line, int column, Node* n) : Primary(line,column)
{
	this->varnull = n; 
}

Primary_true::Primary_true(int line, int column, bool b) : Primary(line,column)
{
	this->vartrue = b; 
}

Primary_false::Primary_false(int line, int column, bool f):Primary(line,column)
{
	this->varfalse = f; 
}

Primary_id::Primary_id(int line, int column, string name) : Primary ( line ,column)
{
	this->value = name; 
}

Primary_char::Primary_char(int line, int column, char c) : Primary ( line ,column)
{
	this->value = c; 
}

Primary_float::Primary_float(int line, int column, float f):Primary (line,column)
{
	this->value = f; 
}

Primary_num::Primary_num(int line, int column, int n) : Primary ( line ,column )
{
	this->value = n;
}

Stmt_expr::Stmt_expr(int line, int column, Expr* e): Stmt(line,column)
{
	this->expr = e; 
}

Stmt_assignstmt::Stmt_assignstmt(int line, int column, AssigStmt* a) : Stmt(line,column)
{
	this->assignment = a; 
}

Stmt_while::Stmt_while(int line, int column ,While_stmt* wstmt) : Stmt(line,column)
{
	this->while_stmt = wstmt; 
}

Stmt_compound::Stmt_compound(int line, int column, Compound_stmt* cs):Stmt(line,column)
{
	this->compound_stmt = cs; 
}

Stmt_cond::Stmt_cond(int line, int column, Cond_stmt* cs):Stmt(line,column)
{
	this->cond_stmt = cs;
}

Cond_stmt::Cond_stmt(int line, int column) : Node(line,column)
{
}
