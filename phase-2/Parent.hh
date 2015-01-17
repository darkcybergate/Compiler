#include <iostream>
#include <list>
#include <cstring>
#include <cstdio>
#include <ext/hash_map>

using namespace std;

class AstNode
{
public:
  virtual void print();
};

struct eqstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};


class ClassChild:public AstNode 
{
public:
  ClassChild(const char*name, list<AstNode*> *class_members);

public:
  virtual list<AstNode*> *class_members()
  {
    return class_members1;
  }
  virtual void set_class_members(list<AstNode*> *class_members)
  {
    class_members1 = class_members;
  }
  virtual void add_class_member(AstNode* new_member)
  {
    class_members1->push_back(new_member);
  }
  virtual void print();


  list<AstNode*> *class_members1;
  const char *name1;
};


class Stmt;  
class Type;       

class MethodChild:public AstNode{
public:
  MethodChild(const char*name, Type *return_type, list<AstNode*> *formal_params,Stmt *method_body);
public:
  virtual Type *return_type()
  {
    return return_type1;
  }
  virtual list <AstNode*> *formal_params()
  {
    return formal_params1;
  }
  virtual Stmt *method_body()
  {
    return method_body1;
  }
  virtual const char * return_name()
  {
    return name1;
  }
  virtual void set_return_type(Type *return_type)
  {
    return_type1=return_type;
  }
  virtual void set_formal_params(list<AstNode*> *formal_params)
  {
    formal_params1=formal_params;
  }
  virtual void set_method_body(Stmt *method_body)
  {
    method_body1=method_body;
  }
  virtual void print();


  const char *name1;
  Type *return_type1;
  list<AstNode*> *formal_params1;
  Stmt* method_body1;
};

class FieldChild:public AstNode{
public:
  FieldChild(const char *name,Type* type,int dimensions);


public:
  virtual Type *type()
  {
    return type1;
  }
  virtual const char * return_name()
  {
    return name1;
  }
  virtual void print();
  virtual int dimensions()
  {
    return dimensions1;
  }


  const char *name1;
  Type *type1;
  int dimensions1;
};

  
class VariableChild:public AstNode
{
public:
  VariableChild(const char*name, Type* type, int dimensions);

public:
  virtual Type *type()
  {
    return type1;
  }
  virtual const char * return_name()
  {
    return name1;
  }
  virtual int dimensions()
  {
    return dimensions1;
  }
  virtual void set_type(Type *t)
  {
    type1=t;
  }
  virtual void print();


  const char *name1;
  Type *type1;
  int dimensions1;
};


class Stmt {

public:  
  Stmt() {}
  virtual void print() = 0;
};

class Expr{
public:
  Expr() {};
  virtual void print() = 0;
};


typedef enum {
  ADD, SUB, MUL, DIV, EQ, NEQ, LT, LEQ, GT, GEQ, AND, OR , MOD
} BinaryOperator;

typedef enum {
  NEG, UMINUS
} UnaryOperator;


typedef enum {EQUAL,PLUS_EQUAL,MINUS_EQUAL} AssignOperator;

class LiteralExpr:public Expr{
public:
  LiteralExpr() {};
  virtual void print() = 0;
};


class Type {
public:
  Type() {};
  virtual void print() = 0;
};

class StringConstant:public LiteralExpr{
   public:
     StringConstant(char* value);

   public:
     virtual char* value()
     {
      return value1;
     }
   
     void print();  
   
     char* value1;

};

class CharConstant:public LiteralExpr
{
public:
  CharConstant(char* value);
public:
  virtual char* value()
  {
    return value1;
  }
  void print();

  char* value1;
};

class IdExpr:public Expr{
   public:
     IdExpr(char* id);
   public:
     virtual char* id()
     {
      return id1;
     }
     void print();  
   
     char* id1;

};


class LocationExpr:public Expr
{
public:
  LocationExpr(Expr *id,Expr *expr);
public:
  virtual Expr *id()
  {
    return id1;
  }
  virtual Expr *expr()
  {
    return expr1;
  }
  void print();

  Expr *id1;
  Expr *expr1;

};

class LocationStmt:public Stmt
{
  public:
    LocationStmt(AssignOperator op,Expr *lhs,Expr *rhs);
  public:
    virtual AssignOperator op()
    {
      return op1;
    }
    virtual Expr *lhs()
    {
      return lhs1;
    }
    virtual Expr *rhs()
    {
      return rhs1;
    }

    void print();
  
    AssignOperator op1;
    Expr *lhs1;
    Expr *rhs1;
};

class IfStmt:public Stmt
{
   public:
     IfStmt(Expr* expr,Stmt* thenpart,Stmt* elsepart);
   public:
     virtual Expr* expr()
     {
      return expr1;
     }
     virtual Stmt* thenpart()
     {
      return thenpart1;
     }
     virtual Stmt* elsepart()
     {
      return elsepart1;
     }
               
     void print(); 
   
     Expr* expr1;
     Stmt* thenpart1;
     Stmt* elsepart1;

};

class CallOutInvocation:public LiteralExpr
{
public:
  CallOutInvocation(StringConstant* str,list <Expr *>* expr);
public:
  virtual StringConstant* str()
  {
    return str1;
  }
  virtual list <Expr *>* expr()
  {
    return expr1;
  }

  void print();

  StringConstant *str1;
  list <Expr *> *expr1;
};




class ForStmt:public Stmt{
   public:
     ForStmt(Expr* init, Expr* condition, Expr* update, Stmt* body);

   public:
     virtual Expr* init()
     {
      return init1;
     }
     virtual Stmt* body()
     {
      return body1;
     }
     virtual Expr* update()
     {
      return update1;
     }
     virtual Expr* condition()
     {
      return condition1;
     }

                    
     void print();  
   
     Expr* init1;
     Stmt* body1;
     Expr* update1;
     Expr* condition1;

};

class ReturnStmt:public Stmt
{
   public:
     ReturnStmt(Expr* expr);

   public:
     virtual Expr* expr()
     {
      return expr1;
     }
     
     void print();  
   
     Expr* expr1;

};

class BlockStmt:public Stmt{
   public:
     BlockStmt(list<Stmt*>* stmt_list);
   public:
     virtual list<Stmt*>* stmt_list()
     {
      return stmt_list1;
     }
     
     void print();  
   
     list<Stmt*>* stmt_list1;

};

class DeclStmt:public Stmt
{
   public:
     DeclStmt(list<AstNode*>* var_list);
   public:
     virtual list<AstNode*>* var_list()
     {
      return var_list1;
     }
     void print();  
   
     list<AstNode*>* var_list1;

};

class ExprStmt:public Stmt{
   public:
     ExprStmt(Expr* expr);

   public:
     virtual Expr* expr()
     {
      return expr1;
     }
     
     void print();  
   
     Expr* expr1;

};

class BreakStmt:public Stmt{
   public:
     BreakStmt();

   public:
     
     void print();  
   
     

};

class ContinueStmt:public Stmt{
   public:
     ContinueStmt();

   public:
     
     void print();  
   
     

};


class BinaryExpr:public Expr{
   public:
     BinaryExpr(BinaryOperator binary_operator,Expr* lhs,Expr* rhs);


   public:
     virtual BinaryOperator binary_operator()
     {
      return binary_operator1;
     }
     virtual Expr* lhs()
     {
      return lhs1;
     }
     virtual Expr* rhs()
     {
      return rhs1;
     }
               
     void print();  
   
     BinaryOperator binary_operator1;
     Expr* lhs1;
     Expr* rhs1;

};

class AssignExpr:public Expr
{
   public:
     AssignExpr(Expr* lhs,Expr* rhs);

   public:
     virtual Expr* lhs()
     {
      return lhs1;
     }
     virtual Expr* rhs()
     {
      return rhs1;
     }
          
     void print();
   
     Expr* lhs1;
     Expr* rhs1;

};




class MethodInvocation:public Expr{
   public:
     MethodInvocation(Expr* base,list<Expr*>* args);

   public:
     virtual Expr* base()
     {
      return base1;
     }
     virtual list<Expr*>* args()
     {
      return args1;
     }
               
     void print();  
   
     Expr* base1;
     list<Expr*>* args1;

};

class UnaryExpr:public Expr{
   public:
     UnaryExpr(UnaryOperator unary_operator,Expr* arg);


   public:
     virtual UnaryOperator unary_operator()
     {
      return unary_operator1;
     }
     virtual Expr* arg()
     {
      return arg1;
     }

          
     void print();  
   
     UnaryOperator unary_operator1;
     Expr* arg1;

};



class NullExpr:public LiteralExpr{
   public:
     NullExpr();
   public:
     void print();  
   
     

};

class IntegerConstant:public LiteralExpr{
   public:
     IntegerConstant(int value);
   public:
     virtual int value()
     {
      return value1;
     }    
     void print();  
   
     int value1;

};

class HexConstant:public LiteralExpr{
   public:
     HexConstant(char* value);

   public:
     virtual char* value()
     {
      return value1;
     }
     
     void print();  
   
     char* value1;

};

class FloatConstant:public LiteralExpr{
   public:
     FloatConstant(float value);

   public:
     virtual float value()
     {
      return value1;
     }
     void print();  
   
     float value1;

};

class BooleanConstant:public LiteralExpr{
   public:
     BooleanConstant(bool value);

   public:
     virtual bool value()
     {
      return value1;
     }

     
     void print();  
   
     bool value1;

};


class Integer_Type:public Type{
   public:
     Integer_Type();

   public:
    
     
     void print();  
   
     

};

class Bool_Type:public Type{
   public:
     Bool_Type();
   public:
     void print();  
   
};

class Void_Type:public Type{
   public:
     Void_Type();

   public:   
     void print();  
   
};


