#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Parent.hh"
using namespace std;
using namespace llvm;
Value *ErrorV(const char *Str)
{
  printf("Error in %s\n",Str); 
  return 0;
}

ClassChild::ClassChild(char* name, list<AstNode*> *class_members)
{
  name1=name;
  class_members1 = class_members;
}


MethodChild::MethodChild(char* name, Var_type *return_type,list<FieldChild*> *formal_params,Stmt *method_body)
        
{
  name1=name;
  return_type1 = return_type;
  formal_params1 = formal_params;
  method_body1 = method_body;
}


FieldChild::FieldChild(char *name,Var_type *type,int dimensions)
{
  name1=name;
  type1 = type;
  dimensions1=dimensions;
}


VariableChild::VariableChild(char *name,Var_type *type,int dimensions) 
{
  name1=name;
  type1 = type;
  dimensions1 = dimensions;
}

ImpExpr::ImpExpr(Expr *expr)
{
  expr1=expr;
}

void ImpExpr::print()
{
  if(expr1!=NULL)
    {
      cout << "(";
      expr1->print();
      cout << ")";
    }
}

LocationStmt::LocationStmt(AssignOperator op,Expr *lhs,Expr *rhs)
{
   op1=op;
   lhs1=lhs;
   rhs1=rhs;
}      


IfStmt::IfStmt(Expr* expr, Stmt* thenpart, Stmt* elsepart)
{
   expr1 = expr;
   thenpart1 = thenpart;
   elsepart1 = elsepart;
}



CallOutInvocation::CallOutInvocation(char *str,list <Expr *> *expr)
{
   str1=str;
   expr1=expr;
}


ForStmt::ForStmt(Expr* init, Expr* condition, Expr* update, Stmt* body){
   init1 = init;
   condition1 = condition;
   update1 = update;
   body1 = body;
}


ReturnStmt::ReturnStmt(Expr* expr){
   expr1 = expr;
}



BlockStmt::BlockStmt(list<Stmt*>* stmt_list){
   stmt_list1 = stmt_list;
}


DeclStmt::DeclStmt(Var_type* type,list<AstNode*>* var_list){
   var_list1 = var_list;
   type1=type;
}

GlobalDeclStmt::GlobalDeclStmt(Var_type* type,list<AstNode*>* var_list){
   var_list1 = var_list;
   type1=type;
}


ExprStmt::ExprStmt(Expr* expr){
   expr1 = expr;
}



BreakStmt::BreakStmt(){
   
}



ContinueStmt::ContinueStmt(){
   
}



BinaryExpr::BinaryExpr(Binary_Operator binary_operator, Expr* lhs, Expr* rhs)
{
   binary_operator1 = binary_operator;
   lhs1 = lhs;
   rhs1 = rhs;
}


AssignExpr::AssignExpr(Expr* lhs, Expr* rhs){
   lhs1 = lhs;
   rhs1 = rhs;
}




MethodInvocation::MethodInvocation(Expr* base,  list<Expr*>* args){
   base1 = base;
   args1 = args;
}



UnaryExpr::UnaryExpr(UnaryOperator unary_operator, Expr* arg){
   unary_operator1 = unary_operator;
   arg1 = arg;
}



IdExpr::IdExpr(char* id)
{
   id1 = id;
}



NullExpr::NullExpr()
{
   
}




IntegerConstant::IntegerConstant(int value){
   value1 = value;
}


HexConstant::HexConstant(char* value){
   value1 = value;
}


FloatConstant::FloatConstant(float value){
   value1 = value;
}


BooleanConstant::BooleanConstant(bool value){
   value1 = value;
}


StringConstant::StringConstant(char* value){
   value1 = value;
}



CharConstant::CharConstant(char* value)
{
   value1=value;
}


Integer_Type::Integer_Type(){
   
}






Bool_Type::Bool_Type(){
   
}






Void_Type::Void_Type(){
   
}


LocationExpr::LocationExpr(char *id,Expr *expr)
{
   id1=id;
   expr1=expr;
}




int tab=0;    

void IfStmt::print() {
  cout << "if (";
  expr()->print();
  cout << ")" << endl;
  tab++;
  thenpart()->print();
  tab--;
   for (int j=0;j<tab;j++)
  {
    printf("\t");
  }
  cout << "else" << endl;
  if (elsepart() == NULL)
  {
     for (int j=0;j<=tab;j++)
  {
    printf("\t");
  }
    cout << "empty";
  }
  else
  {
    tab++;
    elsepart()->print();
    tab--;
  }
}




// Print method for ForStmt
void ForStmt::print() {
  cout << "for (";
  init()->print();
  cout<<"="<<" ";
  //cout << ";";
  condition()->print();
  cout << ",";
  update()->print();
  cout << ")" << endl;
  tab++;
  body()->print();
  tab--;
}



// Print method for ReturnStmt
void ReturnStmt::print() {
  for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
  cout << "return ";
  expr()->print();
}



// Print method for BlockStmt
void BlockStmt::print() {
  for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
  cout << "{" << endl;
  tab++;
  list<Stmt*>::iterator i;
  for(i=stmt_list()->begin(); i != stmt_list()->end(); i++)
  {
     for (int j=0;j<tab;j++)
  {
    printf("\t");
  }
    (*i)->print();
    cout<<";"<<endl;
  }
  tab--;
  for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
  cout << "}" << endl;
}

// Print method for ExprStmt
void ExprStmt::print() {
  expr()->print();
}




void DeclStmt::print() {
  list<AstNode*>::iterator i;
  for(i=var_list()->begin(); i != var_list()->end();) {
   /* for (int j=0;j<tab;j++)
  {
    printf("\t");
  }*/
  /*  for (int j=0;j<tab;j++)
  {
    printf("\t");
  }*/
    (*i)->print();
    i++;
  //  if (i != var_list()->end())
     // cout << ", ";
  }
}


void GlobalDeclStmt::print() {
  list<AstNode*>::iterator i;
  for(i=var_list()->begin(); i != var_list()->end();) {
   /* for (int j=0;j<tab;j++)
  {
    printf("\t");
  }*/
  /*  for (int j=0;j<tab;j++)
  {
    printf("\t");
  }*/
    (*i)->print();
    i++;
  //  if (i != var_list()->end())
     // cout << ", ";
  }
}



// Print method for BreakStmt
void BreakStmt::print() {
  for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
     cout << "break";
}



// Print method for ContinueStmt
void ContinueStmt::print() {
  for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
     cout << "continue";
}



void BinaryExpr::print() 
{
  switch(binary_operator()) 
  {
  case ADD:    cout << "ADD"; break;
  case SUB:    cout << "SUB"; break;
  case MUL:    cout << "MUL"; break;
  case DIV:    cout << "DIV"; break;
  case EQ:    cout << "EQ"; break;
  case NEQ:    cout << "NEQ"; break;
  case LT:    cout << "LT"; break;
  case LEQ:    cout << "LEQ"; break;
  case GT:    cout << "GT"; break;
  case GEQ:    cout << "GEQ"; break;
  case AND:    cout << "AND"; break;
  case OR:    cout << "OR"; break;
  }
  cout << "(";
  lhs()->print();
  cout << ", ";
  rhs()->print();
  cout << ")";
}



// Print method for AssignExpr
void AssignExpr::print() {
  lhs()->print();
  cout << " = ";
  rhs()->print();
}



void ClassChild::print() {
  cout << "class Program";
  cout << "{" << endl;
  tab++;
  list<AstNode*>::iterator i;
  for(i=class_members()->begin(); i != class_members()->end(); i++) {
     for (int j=0;j<tab;j++)
  {
    printf("\t");
  }
    (*i)->print();
    cout << endl;
  }
  cout << "}" << endl;
  tab--;
}

void MethodChild::print() {
  //  cout << "method: ";
  /*for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
  */
  return_type()->print();
  cout << " ";
  printf("%s",return_name());
  cout << "( ";
  list<FieldChild*>::iterator i;
  for(i=formal_params()->begin(); i != --(formal_params()->end()); i++) {
    (*i)->print();
    cout << ",";
  }
  if((*i)!=NULL)
  {
    (*i)->print();
  }
  cout << ")" << endl;
  tab++;
  method_body()->print();
  tab--;
}

void FieldChild::print() {
  //  cout << "field: ";

  type()->print();
  cout << " ";
  printf("%s",return_name());
  if(dimensions()!=0)
  {
    cout<<"["<<dimensions1<<"]";
  }
}

void VariableChild::print() {
  //  cout << "variable: ";
 /* for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
  */
  type()->print();
  cout << " ";
  printf("%s",return_name());
  if (dimensions() > 0) {
    cout << "[dimensions = " << dimensions() << "]";
  }
  cout<<";\n";
   for (int j=0;j<tab;j++)
  {
    printf("\t");
  }
}



void AstNode::print() 
{
}

// Print method for MethodInvocation
void MethodInvocation::print() {
 /* for (int i=0;i<tab;i++)
  {
    printf("\t");
  }
  */
  base()->print();
  cout << "( ";
  list<Expr*>::iterator i;
  for(i=args()->begin(); i != args()->end();) {
    (*i)->print();
    i++;
    if (i != args()->end())
      cout << ", ";
  }
  cout << ")";
}



// Print method for UnaryExpr
void UnaryExpr::print() {
  switch(unary_operator()) {
  case NEG: cout << "NEG"; break;
  case UMINUS: cout << "UMINUS"; break;
  }
  arg()->print();
  cout << ")";
}




// Print method for IdExpr
void IdExpr::print() {
  if (id() != NULL)
    cout<<id();
  else
    cout << "UndefinedID";
}



// Print method for NullExpr
void NullExpr::print() {
  cout << "null";
}



// Print method for IntegerConstant
void IntegerConstant::print() {
  cout << value();
}

void HexConstant::print() {
  cout << value();
}



// Print method for FloatConstant
void FloatConstant::print() {
  cout << value();
}



// Print method for BooleanConstant
void BooleanConstant::print() {
  cout << value();
}



// Print method for StringConstant
void StringConstant::print() {
  cout << string_value();
}

void CharConstant::print()
{
  cout<<value();
}

// Print method for IntType
void Integer_Type::print() {
  cout << "int";
}


// Print method for BooleanType
void Bool_Type::print() {
  cout << "boolean";
}

// Print method for VoidType
void Void_Type::print() {
  cout << "void";
}


void LocationStmt::print()
{
  lhs()->print();
  switch(op()) {
  case EQUAL:    cout << "="; break;
  case PLUS_EQUAL:    cout << "+="; break;
  case MINUS_EQUAL:    cout << "-="; break;
  }
  rhs()->print();
}

void LocationExpr::print()
{
  printf("%s",id1);
//  id()->print();
  cout<<"[";
  expr()->print();
  cout<<"]";
}


void CallOutInvocation::print()
{
  cout<<"CallOut (";
    printf("%s",str1);
  //str()->print();
  cout<<" ";
  list<Expr *>::iterator i;
  for(i=expr()->begin(); i != expr()->end();) {
    (*i)->print();
    i++;
    if (i != expr()->end())
      cout << ", ";
  }
  cout<<")";
}


extern FILE *yyin;
extern int yyparse();

extern int yylineno;
extern char* yytext;

char* sourcefile;
int numerrors = 0;
AstNode *program_pointer;

int main(int argc, char* argv[])
{
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(0);
  }

  if (strcmp(argv[1], "-") == 0) {
    // take input from stdin
    yyin = stdin;
    sourcefile = (char *)malloc(strlen("stdin")+1);
    strcpy(sourcefile, "stdin");    
  } else if ((yyin = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error in opening file %s\n", argv[1]);
    exit(0);
  } else {
    sourcefile = (char *)malloc(strlen(argv[1])+1);
    strcpy(sourcefile, argv[1]);
  }


  if (yyparse() || (numerrors > 0)) {
    printf("%s contains one or more syntax errors.\n", argv[1]);
  }
  else 
  {
    (program_pointer)->print();  
    (program_pointer)->Codegen();
  }
}
