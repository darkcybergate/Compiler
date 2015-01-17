#include <iostream>
#include <list>
#include <cstring>
#include <cstdio>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/ADT/APInt.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/TypeBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <cctype>
#include <map>
#include <string>
#include <vector>

using namespace llvm;

using namespace std;

extern Value *ErrorV(const char *Str);



static AllocaInst *CreateEntryBlockAlloca(Function *main_function, char *variable_name, char *type,int ln) 
{
  IRBuilder<> builder(&main_function->getEntryBlock(),main_function->getEntryBlock().begin());
    if(!strcmp(type,"int")) 
    {
      return builder.CreateAlloca(Type::getInt64Ty(getGlobalContext()), 0,variable_name);
    }
    else if(!strcmp(type,"bool"))
    {
      return builder.CreateAlloca(Type::getInt1Ty(getGlobalContext()), 0,
                           variable_name);
    }
    else if(!strcmp(type,"char"))
    {
      return builder.CreateAlloca(Type::getInt8Ty(getGlobalContext()), ConstantInt::get(getGlobalContext(),APInt(8,ln)),
                           variable_name);
    }
}


static Module *TheModule;
static IRBuilder<> Builder(getGlobalContext());
static std::map<string, Value*> NamedValues;
static vector<BasicBlock *> ForBB;
static vector<BasicBlock *> ForBB2;
static legacy::FunctionPassManager  *function_pass_manager;


class AstNode
{
public:
  virtual void print();
  virtual Value *Codegen()
  {
  }
  
   virtual  char * return_name()
  {
    char *temp;
    temp=(char *)malloc(sizeof(char)*4);
    temp[0]='a';
    temp[1]='s';
    temp[2]='t';
    temp[3]='\0';
    return temp;
  }
  virtual int dimensions()
  {
    return 0;
  }
};

struct eqstr
{
  bool operator()( char* s1, char* s2) 
  {
    return strcmp(s1, s2) == 0;
  }
};


class ClassChild:public AstNode 
{
public:
  ClassChild(char*name, list<AstNode*> *class_members);

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
  virtual Value* Codegen()
  {

     LLVMInitializeNativeTarget();
    LLVMContext &Start_Context = getGlobalContext();
    static Module Temp("Starting LLVM Generation",Start_Context);
    TheModule = &Temp;
    legacy::FunctionPassManager OurFPM(TheModule);
    OurFPM.doInitialization();
    function_pass_manager = &OurFPM;
  
    list<AstNode *>::iterator it1;
     printf("entered class\n");
    for(it1=class_members1->begin();it1!=class_members1->end();it1++)
    {
      (*it1)->Codegen(); 
    }
    function_pass_manager = 0;
    TheModule->dump();
  }

  list<AstNode*> *class_members1;
  char *name1;
};


class Stmt:public AstNode
{
public:  
  Stmt() {}
  virtual void print() = 0;
  virtual Value *Codegen()
  {

  }
}; 

class Expr
{
public:
 Expr(){
  int a=2;
  int b=2;
  }
  virtual void print()=0;
  virtual Value *Codegen()
  {
  };
   virtual int type1()
  {
      return 0;
  }
    virtual char* string_value()
     {
        char *temp;
    temp=(char *)malloc(sizeof(char)*3);
    temp[0]='i';
    temp[1]='d';
    temp[2]='\0';
        return temp;
     }
     virtual char* id()
     {
      char *temp;
    temp=(char *)malloc(sizeof(char)*3);
    temp[0]='i';
    temp[1]='d';
    temp[2]='\0';
        return temp;
     }


};



class Var_type 
{
public:
  Var_type() {};
  char *my_type()
     {
        char *temp;
    temp=(char *)malloc(sizeof(char)*4);
    temp[0]='i';
    temp[1]='n';
    temp[2]='t';
    temp[3]='\0';
    return temp;
     }
  virtual void print() = 0;
};

class Integer_Type:public Var_type
{
   public:
     Integer_Type();
   public:
     void print();
     virtual Value * Codegen()
     {
        return ConstantInt::get(getGlobalContext(),APInt(64,1));
     }
     char *my_type()
     {
       char *temp;
    temp=(char *)malloc(sizeof(char)*4);
    temp[0]='i';
    temp[1]='n';
    temp[2]='t';
    temp[3]='\0';
    return temp;
     }
};

class Bool_Type:public Var_type
{
   public:
     Bool_Type();
   public:
     void print();
     char * my_type()
     {
      char *temp;
    temp=(char *)malloc(sizeof(char)*5);
    temp[0]='b';
    temp[1]='o';
    temp[2]='o';
    temp[3]='l';
    temp[4]='\0';
    return temp;
     }
     virtual Value * Codegen()
     {
          return ConstantInt::get(getGlobalContext(),APInt(1,1));
     }
   
};

class Void_Type:public Var_type
{
   public:
     Void_Type();

   public:   
     void print();  
      char *my_type()
     {
      char *temp;
    temp=(char *)malloc(sizeof(char)*5);
    temp[0]='v';
    temp[1]='o';
    temp[2]='i';
    temp[3]='d';
    temp[4]='\0';
    return temp;
     }
     virtual Value * Codegen()
     {
        return ConstantInt::get(getGlobalContext(),APInt(32,1));
     }
};

class FieldChild:public AstNode
{
public:
  FieldChild( char *name,Var_type* type,int dimensions);


public:
  virtual Var_type *type()
  {
    return type1;
  }
  virtual char * return_name()
  {
    return name1;
  }
  virtual void print();
  virtual int dimensions()
  {
    return dimensions1;
  }
  virtual Value *Codegen()
  {

  }
  char *name1;
  Var_type *type1;
  int dimensions1;
};

class MethodChild:public AstNode
{
public:
  MethodChild(char *name, Var_type *return_type, list<FieldChild *> *formal_params,Stmt *method_body);
public:
  void CreateArgumentAllocas(Function *my_function,vector<char*> store_name,vector<char *> arg_type)
  {
    Function::arg_iterator function_iterator = my_function->arg_begin();
    for(unsigned Idx = 0 , e = arg_type.size();Idx!=e;++Idx,++function_iterator)
    {
      Value *store = CreateEntryBlockAlloca(my_function,store_name[Idx],arg_type[Idx],1);
      Builder.CreateStore(function_iterator,store);
      NamedValues[store_name[Idx]] = store;
    }
  }
  virtual Function *Codegen()
  {
    vector<Type *> argument(formal_params1->size());
    int count=0;
    vector<char *> store_variable_name;
    vector <char *> arg_type;
    Type *temp;
    list<FieldChild*>::iterator it1=formal_params1->begin();
    printf("entry %d\n",argument.size());
    while(it1!=formal_params1->end())
    {
      printf("method entry\n");
      
      if(strcmp(((*it1)->type())->my_type(),"int")==0)
      {
        printf("%s\n",((*it1)->type())->my_type());
        temp=Type::getInt64Ty(getGlobalContext());
        arg_type.push_back("int");
        argument[count]=temp;
        count++;
        store_variable_name.push_back((*it1)->return_name());
      }
      else if(strcmp((*it1)->type()->my_type(),"bool")==0)
      {
        temp=Type::getInt1Ty(getGlobalContext());
        argument[count]=temp;
        arg_type.push_back("bool");
        count++;
        store_variable_name.push_back((*it1)->return_name());
      }
      else if(strcmp((*it1)->type()->my_type(),"void")==0)
      {
        temp=Type::getInt64Ty(getGlobalContext());
        argument[count]=temp;
        arg_type.push_back("void");
        count++;
        store_variable_name.push_back((*it1)->return_name());
      }
      it1++;
    }
    ArrayRef< Type* > reference(argument);
    FunctionType *FT;
    printf("entry %d\n",argument.size());
    if(strcmp(return_type1->my_type(),"int")==0)
    {
        printf("int entry\n");
        FT = FunctionType::get(Type::getInt64Ty(getGlobalContext()),reference, false);
        printf("int error\n");
    }
    else if(strcmp(return_type1->my_type(),"bool")==0)
    {
       FT = FunctionType::get(Type::getInt1Ty(getGlobalContext()),reference, false);
    }
    else if(strcmp(return_type1->my_type(),"void")==0)
    {
      FT = FunctionType::get(Type::getVoidTy(getGlobalContext()),reference, false);
    }
    printf("entry\n");
    Function *F = Function::Create(FT, Function::ExternalLinkage, name1, TheModule);
    if (F->getName() != name1) 
    {
        // Delete the one we just made and get the existing one.
      F->eraseFromParent();
      F = TheModule->getFunction(name1);
      if (!F->empty())
      {
          ErrorV("redefinition of function");
          return 0;
      }
      if (F->arg_size() != argument.size()) 
      {
          ErrorV("redefinition of function with different # args");
          return 0;
      } 
    }
    
      unsigned Idx = 0;
      for (Function::arg_iterator AI = F->arg_begin(); Idx != argument.size();++AI, ++Idx) 
      {
          AI->setName(store_variable_name[Idx]);
      }
      Function *TheFunction = F;
      if (TheFunction == 0)
      {
        return 0;
      }
      BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
      Builder.SetInsertPoint(BB);
     CreateArgumentAllocas(F,store_variable_name,arg_type);
        (method_body1)->Codegen();
        printf("Before Function Verified \n");
     //  verifyFunction(*TheFunction);
        printf("After Function Verified\n");
      return TheFunction;
}

 
  virtual Var_type *return_type()
  {
    return return_type1;
  }
  virtual list<FieldChild*> *formal_params()
  {
    return formal_params1;
  }
  virtual Stmt *method_body()
  {
    return method_body1;
  }
  virtual  char * return_name()
  {
    return name1;
  }
  virtual void set_return_type(Var_type *return_type)
  {
    return_type1=return_type;
  }
  virtual void set_formal_params(list<FieldChild*> *formal_params)
  {
    formal_params1=formal_params;
  }
  virtual void set_method_body(Stmt *method_body)
  {
    method_body1=method_body;
  }
  virtual void print();

  char *name1;
  Var_type *return_type1;
  list<FieldChild*> *formal_params1;
  Stmt* method_body1;
};


  
class VariableChild:public AstNode
{
public:
  VariableChild( char*name, Var_type* type, int dimensions);

public:
  virtual Var_type *type()
  {
    return type1;
  }
  virtual char * return_name()
  {
    return name1;
  }
  virtual int dimensions()
  {
    return dimensions1;
  }
  virtual void set_type(Var_type *t)
  {
    type1=t;
  }
  virtual void print();
  virtual Value *Codegen()
  {

  }
  char *name1;
  Var_type *type1;
  int dimensions1;
};







typedef enum 
{
  ADD, SUB, MUL, DIV, EQ, NEQ, LT, LEQ, GT, GEQ, AND, OR , MOD
}Binary_Operator;

typedef enum 
{
  NEG, UMINUS
} UnaryOperator;


typedef enum {EQUAL,PLUS_EQUAL,MINUS_EQUAL} AssignOperator;

class LiteralExpr:public Expr
{
public:
  LiteralExpr() {};
  virtual void print() = 0;
};

class NullExpr:public LiteralExpr
{
   public:
     NullExpr();
   public:
     void print();
     virtual Value* Codegen()
     {
        return Constant::getNullValue(Type::getInt64Ty(getGlobalContext()));
     }  
};


class ImpExpr:public Expr
{
public:
  ImpExpr(Expr *expr);
public:
  virtual Value* Codegen()
  {
    return expr1->Codegen();
  }
  void print();
  Expr *expr1;
};

class StringConstant:public LiteralExpr
{
   public:
     StringConstant(char* value);
   public:
     virtual char* string_value()
     {
        return value1;
     }
     virtual Value *Codegen()
     {
        Value *init_val = NamedValues[value1];
        return Builder.CreateLoad(init_val, value1);
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
  virtual Value *Codegen()
  {
  }
  char* value1;
};

class IdExpr:public Expr
{
   public:
     IdExpr(char* id);
   public:
     virtual char* id()
     {
      return id1;
     }
      virtual int type1()
  {
      return 2;
  }
     virtual Value *Codegen()
     {
      Value *store = NamedValues[id1];
      return Builder.CreateLoad(store, id1);
     }
     void print();  
   
     char* id1;

};


class LocationExpr:public Expr
{
public:
  LocationExpr(char *id,Expr *expr);
public:
  virtual char *id()
  {
    return id1;
  }
  virtual Expr *expr()
  {
    return expr1;
  }
  virtual int type1()
  {
      return 1;
  }
  virtual Value *Codegen()
  {
    char *o=id1;
    Value *V=NamedValues[o];
    if(V==0)
    {
      ErrorV("No Variable found");
    }
    Value *VA = expr1->Codegen();
    vector <Value*> tmp;
    tmp.push_back(ConstantInt::get(getGlobalContext(), APInt(64,0)));
    tmp.push_back(VA);
    V=Builder.CreateGEP(V,tmp);
    return Builder.CreateLoad(V,o);
  }
  void print();

  char *id1;
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
    virtual Value *Codegen()
    {
      printf("location entered\n");
      char *l;
      l=lhs1->id();
      cout<<NamedValues[l]<<endl;
      Value *store = NamedValues[l];
      if((lhs1->type1())==1)
      {
        Value *VA = (lhs1->Codegen());
        vector <Value*> tmp;
        tmp.push_back(ConstantInt::get(getGlobalContext(), APInt(64,0)));
        tmp.push_back(VA);
        store=Builder.CreateGEP(store,tmp);

      }
      printf("1::: %s\n",l);
     
      Value *current_variable = Builder.CreateLoad(store, l);
      printf("%s\n",l);
      Value *next_variable,*update_variable;

      next_variable=rhs1->Codegen();
      update_variable=next_variable;
      switch(op()) 
      {
          case EQUAL:               
              Builder.CreateStore(next_variable, store);    
              break;
          case PLUS_EQUAL:
              next_variable=Builder.CreateAdd(current_variable , update_variable, "nextvar");
              Builder.CreateStore(next_variable, store);
              break;
          case MINUS_EQUAL:    
              next_variable=Builder.CreateSub(current_variable , update_variable, "nextvar");
              Builder.CreateStore(next_variable, store);
              break;
      }
      return Constant::getNullValue(Type::getInt64Ty(getGlobalContext()));
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
    virtual Value *Codegen()
    {
        Value *condition_value=expr1->Codegen();
        if(condition_value==0)
        {
          return 0;
        }
        condition_value=Builder.CreateICmpNE(condition_value,ConstantInt::get(getGlobalContext(), APInt(1,0)),"ifcond");
        Function *function = Builder.GetInsertBlock()->getParent();
        BasicBlock *then_basic_block = BasicBlock::Create(getGlobalContext(), "then", function);
        BasicBlock *else_basic_block = BasicBlock::Create(getGlobalContext(), "else");
        BasicBlock *merge_basic_block = BasicBlock::Create(getGlobalContext(), "ifcont");
        Builder.CreateCondBr(condition_value, then_basic_block, else_basic_block);
        Builder.SetInsertPoint(then_basic_block);
        Value *then_value = thenpart1->Codegen();
        if (then_value == 0)
        {
          return 0;
        }
        Builder.CreateBr(merge_basic_block);
        then_basic_block = Builder.GetInsertBlock();
        Value *ElseV;
        function->getBasicBlockList().push_back(else_basic_block);
        Builder.SetInsertPoint(else_basic_block);
        if(elsepart1!=NULL)
        {
          ElseV = elsepart1->Codegen();
        }
        else
        {
          Expr * exp1=new NullExpr();
          ElseV = exp1->Codegen();
        }
        if (ElseV == 0)
        {
          return 0;
        }
        Builder.CreateBr(merge_basic_block);
        else_basic_block = Builder.GetInsertBlock();
        function->getBasicBlockList().push_back(merge_basic_block);
        Builder.SetInsertPoint(merge_basic_block);
        PHINode *PN = Builder.CreatePHI(Type::getInt64Ty(getGlobalContext()), 2,"iftmp");
        PN->addIncoming(then_value, then_basic_block);
        PN->addIncoming(ElseV, else_basic_block);
        return PN;
    }        
     void print(); 
   
     Expr* expr1;
     Stmt* thenpart1;
     Stmt* elsepart1;

};

class CallOutInvocation:public LiteralExpr
{
public:
  CallOutInvocation(char* str,list <Expr *>* expr);
public:
  virtual char* str()
  {
    return str1;
  }
  virtual list <Expr *>* expr()
  {
    return expr1;
  }
  virtual Value *Codegen()
  {
    printf("callout enter\n");
    vector<Expr*> args2;
        list<Expr *>::iterator it1=(*expr1).begin();
        while(it1!=(*expr1).end())
        {
          args2.push_back(*it1);
          it1++;
        }
        printf("%s\n",str1);
        char str2[20];
        int count=0;
        for(int i=1;i<(strlen(str1)-1);i++)
        {
          str2[count]=str1[i];
          count++;
        }
        str2[count]='\0';
        str1=str2;
        Function *caller_function = TheModule->getFunction(str1);
        if (caller_function == 0)
        {
            return ErrorV("Unknown function referenced");
        }
        if (caller_function->arg_size() != args2.size())
        {
            return ErrorV("Incorrect number arguments passed");
        }
        vector<Value *> argument_val;
        unsigned i=0,e=0;
        for (i = 0, e = args2.size(); i != e; ++i)
        {
            argument_val.push_back(args2[i]->Codegen());
            if (argument_val.back() == 0) 
            {
              return 0;
            }
        }
        return Builder.CreateCall(caller_function, argument_val, "calltmp");

/*

     list<Expr *>::iterator i;
    for(i=expr1->begin();i!=expr1->end();i++)
    {
      (*i)->Codegen(); 
    }
*/
  }
  void print();

  char *str1;
  list <Expr *> *expr1;
};




class ForStmt:public Stmt
{
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
    virtual Value* Codegen()
    {
      printf("Entterd for statement without segment fault\n");

      Function *temp_function = Builder.GetInsertBlock()->getParent();
      ForBB.push_back(Builder.GetInsertBlock());
      char temp[] = "int";
      Value *store = CreateEntryBlockAlloca(temp_function, init1->string_value(),temp,1);
      printf("Gave space to variables without segment fault\n");
      Value *begin_val = condition1->Codegen();

      if(begin_val == 0) 
      {
        return 0;
      }
      printf("hello1\n");
      Builder.CreateStore(begin_val, store);
      BasicBlock *loop_basic_block = BasicBlock::Create(getGlobalContext(), "loop", temp_function);
      BasicBlock *update_basic_block = BasicBlock::Create(getGlobalContext(),"updateCond", temp_function);
      ForBB2.push_back(update_basic_block);
      Builder.CreateBr(loop_basic_block);
      Builder.SetInsertPoint(loop_basic_block);
      Value *init_value = NamedValues[init1->string_value()];
      NamedValues[init1->string_value()] = store;
      printf("hello\n");
      if(body1->Codegen() == 0)
      {
        return 0;
      }
 
      Value *update_val = ConstantInt::get(getGlobalContext(),APInt(64,1));


      Value *ending_condition = update1->Codegen();
      if(ending_condition == 0) 
      {
        return ending_condition;
      }

     
      Builder.CreateBr(update_basic_block);
      Builder.SetInsertPoint(update_basic_block);
      
      Value *current_variable = Builder.CreateLoad(store, init1->string_value());
      Value *next_variable = Builder.CreateAdd(current_variable, update_val, "nextvar");
      Builder.CreateStore(next_variable, store);
      ending_condition = Builder.CreateICmpNE(ending_condition,ConstantInt::get(getGlobalContext(),APInt(64,0)),"loopcond");
      BasicBlock *after_basic_block = BasicBlock::Create(getGlobalContext(),"afterloop", temp_function);
      Builder.CreateCondBr(ending_condition,loop_basic_block,after_basic_block);
      Builder.SetInsertPoint(after_basic_block);
      ForBB.pop_back();
      ForBB2.pop_back();
      if(init_value)
      {
        NamedValues[init1->string_value()] = init_value;
      }
      else
      {
        NamedValues.erase(init1->string_value());
      }
      return Constant::getNullValue(Type::getInt64Ty(getGlobalContext()));
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
     virtual Value* Codegen()
     {
        printf("Entered Return Part\n");
       return Builder.CreateRet(expr1->Codegen());
    }
     void print();  
   
     Expr* expr1;

};

class BlockStmt:public Stmt
{
   public:
     BlockStmt(list<Stmt*>* stmt_list);
   public:
     virtual list<Stmt*>* stmt_list()
     {
      return stmt_list1;
     }
     virtual Value * Codegen()
     {
        list<Stmt *>::iterator it1;
      for(it1=stmt_list1->begin();it1!=stmt_list1->end();it1++)
     {
       printf("Function called this\n");
       (*it1)->Codegen(); 
     }
    return Constant::getNullValue(Type::getInt64Ty(getGlobalContext()));   
     }
     
     void print();  
   
     list<Stmt*>* stmt_list1;

};

class GlobalDeclStmt:public Stmt
{
   public:
     GlobalDeclStmt(Var_type* type, list<AstNode*>* var_list);
   public:
     virtual list<AstNode*>* var_list()
     {
      return var_list1;
     }
     virtual Var_type* get_type()
     {
      return type1;
     }
     void print();
     virtual Value *Codegen()
      {
        Value* arg1;
        Type* temp_var;
        list<AstNode*>::iterator i;
        for(i=var_list1->begin();i!=(var_list1->end());i++)
        {
  //        Value *Alloca = CreateEntryBlockAlloca(F,(*i)->return_name(),type1->my_type(),1);
          printf("%s\n",(*i)->return_name());
           //dt=ArrayType::get(Type::getInt1Ty(getGlobalContext()),dimension);
          if(!strcmp(type1->my_type(),"bool"))
          { 
            if(((*i)->dimensions())==0)
            {
               arg1=new GlobalVariable(*TheModule,Type::getInt1Ty(getGlobalContext()),false,GlobalVariable::InternalLinkage,nullptr,(*i)->return_name());
            }
            else
            {
               temp_var=ArrayType::get(Type::getInt1Ty(getGlobalContext()),((*i)->dimensions()));
               arg1=new GlobalVariable(*TheModule,temp_var,false,GlobalVariable::InternalLinkage,nullptr,(*i)->return_name());
            }
          }
          else if(!strcmp(type1->my_type(),"int"))
          { 
            if(((*i)->dimensions())==0)
            {
               arg1=new GlobalVariable(*TheModule,Type::getInt64Ty(getGlobalContext()),false,GlobalVariable::InternalLinkage,ConstantInt::get(getGlobalContext(),APInt(64,0)),(*i)->return_name());
            }
            else
            {
               vector <uint64_t> arr((*i)->dimensions(),0);
               ArrayRef<uint64_t> reference(arr);
               cout<<((*i)->dimensions())<<endl;
               temp_var=ArrayType::get(Type::getInt64Ty(getGlobalContext()),((*i)->dimensions()));
               arg1=new GlobalVariable(*TheModule,temp_var,false,GlobalVariable::InternalLinkage,ConstantDataArray::get(getGlobalContext(),reference),(*i)->return_name());
            }
          }
          NamedValues[(*i)->return_name()] = arg1;
        }

      }
      

     list<AstNode*>* var_list1;
     Var_type *type1;
};


class DeclStmt:public Stmt
{
   public:
     DeclStmt(Var_type* type, list<AstNode*>* var_list);
   public:
     virtual list<AstNode*>* var_list()
     {
      return var_list1;
     }
     virtual Var_type* get_type()
     {
      return type1;
     }
     void print();  
     virtual Value *Codegen()
    {
      printf("declstmt ent\n");
      Function *F = Builder.GetInsertBlock()->getParent();
      list<AstNode *>::iterator i;
      char temp[] = "int";
      char temp2[]="bool";
      Value *Alloca;
      for(i=var_list1->begin();i!=(var_list1->end());i++)
      {
  //        Value *Alloca = CreateEntryBlockAlloca(F,(*i)->return_name(),type1->my_type(),1);
        printf("%s\n",(*i)->return_name());
           
          if(!strcmp(type1->my_type(),"bool"))
          { 
            Alloca = CreateEntryBlockAlloca(F,(*i)->return_name(),temp2,1);
            Builder.CreateStore(ConstantInt::get(getGlobalContext(),APInt(1,0)),Alloca);
          }
          else if(!strcmp(type1->my_type(),"int"))
          { 
            Alloca = CreateEntryBlockAlloca(F,(*i)->return_name(),temp,1);
            Builder.CreateStore(ConstantInt::get(getGlobalContext(),APInt(64,0)),Alloca);
          }
          NamedValues[(*i)->return_name()] = Alloca;
      }

    }
     list<AstNode*>* var_list1;
     Var_type *type1;
};

class ExprStmt:public Stmt
{
   public:
     ExprStmt(Expr* expr);
   public:
     virtual Expr* expr()
     {
       return expr1;
     }
     virtual Value* Codegen()
     {
      return expr1->Codegen();
     }
     void print();
     Expr* expr1;
};

class BreakStmt:public Stmt
{
   public:
     BreakStmt();
     virtual Value *Codegen()
     {
        Value *value=Builder.CreateBr(ForBB.back());
        ForBB.pop_back();
        return value;
     }
   public:     
     void print();
};

class ContinueStmt:public Stmt
{
   public:
     ContinueStmt();
   public:
     void print();
     virtual Value* Codegen()
     {
        cout<<ForBB2.size()<<endl;
        Value *value=Builder.CreateBr(ForBB2.back());
        ForBB2.pop_back();
        return value;
     }
};


class BinaryExpr:public Expr
{
   public:
     BinaryExpr(Binary_Operator binary_operator,Expr* lhs,Expr* rhs);


   public:
     virtual Binary_Operator binary_operator()
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
   Value *Codegen() 
     {
        printf("entered binary expr\n");
        Value *L = lhs1->Codegen();
        Value *R = rhs1->Codegen();
        if (L == 0 || R == 0) 
        {
          return 0;
        }
        if(binary_operator1==ADD)
        {
          return Builder.CreateAdd(L,R,"add_tmp");
        }
        else if(binary_operator1==SUB)
        {
          return Builder.CreateSub(L,R,"sub_tmp");
        }
        else if(binary_operator1==MUL)
        {
          return Builder.CreateMul(L,R,"mul_tmp");
        }
        else if(binary_operator1==DIV)
        {
          return Builder.CreateSDiv(L,R,"div_tmp");
        }
        else if(binary_operator1==MOD)
        {
          return Builder.CreateSRem(L,R,"mod_tmp");
        }
        else if(binary_operator1==EQ)
        {
          return Builder.CreateICmpEQ(L,R,"eq_tmp");
        }
        else if(binary_operator1==NEQ)
        {
          return Builder.CreateICmpEQ(L,R,"not_eq_tmp");
        }
        else if(binary_operator1==LT)
        {
          return Builder.CreateICmpSLT(L,R,"less_than_tmp");
        }
        else if(binary_operator1==LEQ)
        {
          return Builder.CreateICmpSLE(L,R,"less_than_eq_tmp");
        }
        else if(binary_operator1==GT)
        {
          return Builder.CreateICmpSGT(L,R,"greater_than_tmp");
        }
        else if(binary_operator1==GEQ)
        {
          return Builder.CreateICmpSGE(L,R,"greater_than_eq_tmp");
        }
        else if(binary_operator1==AND)
        {
          return Builder.CreateAnd(L,R,"and_tmp");
        }
        else if(binary_operator1==OR)
        {
          return Builder.CreateOr(L,R,"or_tmp");
        }
        else
        {
          return ErrorV("invalid binary operator");
        }
      }      
     void print();  
   
     Binary_Operator binary_operator1;
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
    virtual Value *Codegen()
    {
      Value *Left = lhs1->Codegen();
      Value *Right = rhs1->Codegen();

    }
     void print();
   
     Expr* lhs1;
     Expr* rhs1;

};




class MethodInvocation:public Expr
{
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
     virtual Value *Codegen()
     {
        vector<Expr *> args2;
        list<Expr *>::iterator it1=(*args1).begin();
        while(it1!=(*args1).end())
        {
          args2.push_back(*it1);
          it1++;
        }
        printf("base::%s\n", base1->string_value());
        Function *called_function = TheModule->getFunction(base1->string_value());
        if (called_function == 0)
        {
            return ErrorV("Function Not available in main Module");
        }
        if (called_function->arg_size() != args2.size())
        {
            return ErrorV("Incorrect number arguments passed");
        }
        std::vector<Value*> argument_val;
        unsigned i=0,e=0;
        for (i = 0, e = args2.size(); i != e; ++i)
        {
            argument_val.push_back(args2[i]->Codegen());
            if (argument_val.back() == 0) 
            {
              return 0;
            }
        }
        return Builder.CreateCall(called_function, argument_val, "calltmp");
     }         
     void print();  
   
     Expr* base1;
     list<Expr*>* args1;
     

};

class UnaryExpr:public Expr
{
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
     Value *Codegen() 
     {
        Value *val=arg1->Codegen();
        if(unary_operator1==NEG)
        {
          return Builder.CreateNeg(val,"neg_tmp");
        }
        else if(unary_operator1==UMINUS)
        {
          return Builder.CreateNot(val,"uminus_tmp");
        }
        
      }       
   
     UnaryOperator unary_operator1;
     Expr* arg1;

};






class IntegerConstant:public LiteralExpr
{
   public:
     IntegerConstant(int value);
   public:
     virtual int value()
     {
      return value1;
     }
     virtual Value *Codegen()
     {
      printf("entered int const\n");
      return ConstantInt::get(getGlobalContext(),APInt(64,value1));
  //    return ConstantFP::get(getGlobalContext(), APFloat((float)value1));
     }
     void print();  
   
     int value1;

};

class HexConstant:public LiteralExpr
{
   public:
     HexConstant(char* value);

   public:
     virtual char* value()
     {
      return value1;
     }
     
     void print();  
      virtual Value* Codegen()
      {
        return ConstantInt::get(getGlobalContext(),APInt(8,strtol(value1+2,NULL,16)));
      }
     char* value1;

};

class FloatConstant:public LiteralExpr
{
   public:
     FloatConstant(float value);

   public:
     virtual float value()
     {
      return value1;
     }
     void print();
     virtual Value *Codegen()
     {
      return ConstantFP::get(getGlobalContext(), APFloat(value1));
     }
   
     float value1;

};

class BooleanConstant:public LiteralExpr
{
   public:
     BooleanConstant(bool value);

   public:
     virtual bool value()
     {
      return value1;
     }
     virtual Value *Codegen()
     {
       return ConstantInt::get(getGlobalContext(),APInt(1,value1));
//     return ConstantFP::get(getGlobalContext(), APFloat((float)value1));
     }
     
     void print();  
   
     bool value1;

};




