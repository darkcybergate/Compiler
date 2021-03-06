/*
 * Program → class ID ‘{‘ FieldDeclList  MethodDeclList  ‘}’
 * FieldDeclList → FieldDecl | FieldDeclList FieldDecl 
 * MethodDeclList → MethodDecl | MethodDeclList MethodDecl
 * FieldDecl → Type VariableList ';'
 * VariableList → Variable | VariableList Variable
 * Variable → ID | ID '[' integer_literal ']' 
 * Type → int | float | boolean  
 * MethodDecl → Type ID '(' ')' Block | Type ID '(' ParameterDeclList ')' Block
 * MethodDecl → void ID '(' ')' Block | void ID '(' ParameterDeclList ')' Block
 * ParameterDeclList → ParameterDecl | ParameterDeclList ',' ParameterDecl
 * ParameterDecl → Type ID | Type ID '[' ']'
 * Block → '{' FieldDeclList StatementList '}'
 * StatementList → Statement | StatementList Statement
 * Statement → Location '=' Expr | MethodCall | if '(' Expr ')' Block  
 * Statement → if '(' Expr ')' Block else Block | while '(' Expr ')' Block | return Expr ';'
 * Statement → break ';' | continue ';' | Block
 * MethodCall → ID '(' ExprList ')' | callout '(' string_literal CallOutArgList ')'
 * CallOutArgList → CallOutArg | CallOutArgList ',' CallOutArg
 * CallOutArg → Expr | string_literal  
 * ExprList → Expr | ExprList Expr         
 * Expr		→	Expr Binop Expr | − Expr   | ! Expr | ( Expr )
 * Expr		→	integer_literal  
 * Expr		→	boolean_literal
 * Expr		→	float_literal
 * Binop		→   Arithop | Relop | Eqop | Condop
 * Arithop	→   + | − | * | / | % | << | >> 
 * Relop		→   < | > | <= | >=
 * Eqop		→   == | !=
 * Condop		→   && | ||
 */

import java.util.*;


abstract class ASTnode{ }

abstract class ASTExpression extends ASTnode { }

/*
 * We can make FieldDeclList part of the AST and process it later. 
 * Or we can directly note the information given by the FieldDeclList 
 * in the Symbol Table.
 * Program → class ID ‘{‘ FieldDeclList  MethodDeclList  ‘}’ { Program.node = new ASTProgram(ID.value, MethodDeclList.node)}
 */
class ASTProgram extends ASTnode {
	
	public ASTProgram(String id, ArrayList<ASTMethodDecl> mdl)
	{
		id_ = id;
		mdl_ = mdl;
	}
	public String getId()
	{
		return id_;
	}
	public ArrayList<ASTMethodDecl> getMethodDeclList()
	{
		return mdl_;
	}
	private String id_;
	private ArrayList<ASTMethodDecl> mdl_;
}

class ASTLocation extends ASTnode {
	
}

abstract class ASTStatement extends ASTnode {
	
}

/*
 * Block → '{' { push(currEnv); currEnv = new Env(currEnv); } FieldDeclList StatementList { currEnv = pop(); 
 *                                                                                      Block.node = new ASTBlockStatement(StatementList.node);} '}'  
 */

class ASTBlockStatement extends ASTStatement{
	
	public ASTBlockStatement(ArrayList<ASTStatement> stmtlist){
		stmtlist_ = stmtlist;		
	}
	private ArrayList<ASTStatement> stmtlist_;
}

/*
 * StatementList → Statement {StatementList.node = new ArrayList<ASTStatement>(); 
 * 								StatementList.node.add(Statement.node)}  
 * StatementList_1 → StatementList_2 Statement  {StatementList_1.node = StatementList_2.node;
 * 												StatementList_1.add(Statement.node); }
 */

/*
 * Statement → Location '=' Expr { Statement.node = newASTAssignmentStatement(Location.node, Expr.node);}
 */
class ASTAssignmentStatement extends ASTStatement {
	public ASTAssignmentStatement(ASTLocation loc, ASTExpression expr) {
		loc_ = loc;
		expr_ = expr;
	}
	
	private ASTLocation loc_;
	private ASTExpression expr_;
}

abstract class ASTMethodCallStatement extends ASTStatement {
	
}

/*
 *  Statement → MethodCall { Statement.node = MethodCall.node }
 *  MethodCall → ID '(' ExprList ')' { Symbol method = currEnv.get(ID); 
 *                                     MethodCall.node = new MethodCallStatement1(method,ExprList.node)} 
 *  MethodCall → callout '(' string_literal CallOutArgList ')' {  YOU FILL IT }
 *  ExprList → Expr  {ExprList.node = new ArrayList<ASTExpression>();
 *                               ExprList.node.add(Expr.node); }
 *  ExprList_1 → ExprList_2 Expr { ExprList_2.node.add(Expr.node);
 *                                 ExprList_1.node = ExprList_2.node; }
 */
class ASTMethodCallStatement1 extends ASTMethodCallStatement {
	public ASTMethodCallStatement1(Symbol method, ArrayList<ASTExpression> exprlist){
		method_ = method;
		exprlist_ = exprlist; 
	}
	Symbol method_; 
	ArrayList<ASTExpression> exprlist_;
}

class ASTMethodCallStatement2 extends ASTMethodCallStatement {
	/* you fill it */
}

class ASTIfStatement extends ASTStatement {
	/* you fill it */
}

/*
 * Statement → if '(' Expr ')' Block_1 else Block_2 {Statement.node = new ASTIfThenElseStatement(Expr.node,
 * 																				Block_1.node, Block_2.node) } 
 */
class ASTIfThenElseStatement extends ASTStatement {
	public ASTIfThenElseStatement(ASTExpression expr, ASTBlockStatement ifblock, ASTBlockStatement elseblock) {
		expr_ = expr;
		ifblock_ = ifblock;
		elseblock_ = elseblock;	
	}
	ASTExpression expr_; 
	ASTBlockStatement ifblock_; 
	ASTBlockStatement elseblock_;
}

class ASTWhileStatement extends ASTStatement {
	
}

class ASTReturnStatement extends ASTStatement {
	
} 

class ASTBreakStatement extends ASTStatement {
	
}

class ASTContinueStatement extends ASTStatement {
	
}

/*
 * Statement → Block { Statement.node = Block.node }
 */
class ASTBlockStatement extends ASTStatement {
	
}

/*
 * MethodDeclList → MethodDecl  {MethodDeclList.node = new ArrayList<ASTMethodDecl>();
 *                               MethodDeclList.node.add(MethodDecl.node); }
 * MethodDeclList_1 → MethodDeclList_2 MethodDecl { MethodDeclList_2.node.add(MethodDecl.node);
 *                                                  MethodDeclList_1.node = MethodDeclList_1.node; }
 */
class ASTMethodDecl extends ASTnode {
	
}

/* Expr   →  integer_literal  {  Expr.node = new ASTIntegerLiteralExpression( integral_literal.value);} */
class ASTIntegerLiteralExpression extends ASTExpression {
	public ASTIntegerLiteralExpression(int value) {
		value_ = value;
    }
	public void setValue(int value) {
		value_ = value; 
	}
	private int value_;	
}

/* Expr   →  float_literal  {  Expr.node = new ASTFloatLiteralExpression( float_literal.value);} */
class ASTFloatLiteralExpression extends ASTExpression {
	public ASTFloatLiteralExpression(float value) {
		value_ = value;
    }
	public void setValue(int value) {
		value_ = value; 
	}
	private float value_;	
}

/* Expr   →  boolean_literal  {  Expr.node = new ASTBooleanLiteralExpression(boolean_literal.value);} */
class ASTBooleanLiteralExpression extends ASTExpression {
	public ASTBooleanLiteralExpression(boolean value) {
		value_ = value;
    }
	public void setValue(boolean value) {
		value_ = value; 
	}
	private boolean value_;	
}
/* 
 * Expr_1 → Expr_2 + Expr_3	{ Expr_1.node = new ASTBinaryOperatorExpression(Expr_2.node, Expr_3.node, "+");}
 * Expr_1 → Expr_2 - Expr_3	{ Expr_1.node = new ASTBinaryOperatorExpression(Expr_2.node, Expr_3.node, "-");}
 * Expr_1 → Expr_2 * Expr_3	{ Expr_1.node = new ASTBinaryOperatorExpression(Expr_2.node, Expr_3.node, "*");}
 * .............Fill the rest of the SDT by yourself.............
 * Expr_1 → ( Expr_2 ) { Expr_1.node = Expr_2.node }
 */
class ASTBinaryOperatorExpression extends ASTExpression {
	public static final int ERROR = 0;
	public static final int PLUS = 1;
	public static final int MINUS = 2;
	public static final int MULTIPLY = 3;
	public static final int DIVIDE = 4;
	public static final int REMINDER = 5;
	public static final int LSHIFT = 6;
	public static final int RSHIFT = 7;
	public static final int LT = 8;
	public static final int GT = 9;
	public static final int LEQ = 10;
	public static final int GEQ = 11;
	public static final int EQ = 12;
	public static final int NEQ = 13;
	public static final int CAND = 14;
	public static final int  COR = 15;
	public ASTBinaryOperatorExpression(ASTExpression left, ASTExpression right, String operator) {
		left_ = left;
		right_ = right;
		if(operator.compareTo("+")== 0){
			operator_ = PLUS;
		}
		else if(operator.compareTo("-")== 0){
			operator_ = MINUS;
		}
		else if(operator.compareTo("*")== 0){
			operator_ = MULTIPLY;
		}
		else if(operator.compareTo("/")== 0){
			operator_ = DIVIDE;
		}
		else if(operator.compareTo("%")== 0){
			operator_ = REMINDER;
		}
		else if(operator.compareTo("<<")== 0){
			operator_ = LSHIFT;
		}
		else if(operator.compareTo(">>")== 0){
			operator_ = RSHIFT;
		}
		else if(operator.compareTo("<")== 0){
			operator_ = LT;
		}
		else if(operator.compareTo(">")== 0){
			operator_ = GT;
		}
		else if(operator.compareTo("<=")== 0){
			operator_ = LEQ;
		}
		else if(operator.compareTo(">=")== 0){
			operator_ = GEQ;
		}
		else if(operator.compareTo("==")== 0){
			operator_ = EQ;
		}
		else if(operator.compareTo("!=")== 0){
			operator_ = NEQ;
		}
		else if(operator.compareTo("&&")== 0){
			operator_ = CAND;
		}
		else if(operator.compareTo("||")== 0){
			operator_ = COR;
		}
		else {
			operator_ = ERROR;
		}
	}

	public ASTExpression left(){ 
		return left_; 
	}
	public ASTExpression right(){ 
		return right_; 
	}
	public int operator() { return operator_; }
	private ASTExpression left_;
	private ASTExpression right_;
	private int operator_;
}

/*
 * Expr_1	→  − Expr_2 { Expr_1.node = new ASTUnaryOperatorExpression(Expr_2, "-"); } 
 * Expr_1	→ ! Expr_2 { Expr_1.node = new ASTUnaryOperatorExpression(Expr_2, "-"); }
 * Expr_1	→  ( Expr_2 ) { Expr_1.node = Expr_2.node }  
 */

class ASTUnaryOperatorExpression extends ASTExpression {
	public static final int ERROR = 0;
	public static final int UMINUS = 1;
	public static final int NEGATE = 2;
	public ASTUnaryOperatorExpression(ASTExpression expr, String operator) {
		expr_ = expr;
		if(operator.compareTo("-")== 0){
			operator_ = UMINUS;
		}
		else if(operator.compareTo("!")== 0){
			operator_ = NEGATE;
		}
		else {
			operator_ = ERROR;
		}
	}

	public ASTExpression expr(){ 
		return expr_; 
	}	
	public int operator() { return operator_; }
	private ASTExpression expr_;	
	private int operator_;
}

class Symbol {
	int dummyentry;
}

/*
 * SDT Scheme for handling Field Declations - Version 1
 * FieldDeclList → FieldDecl    {  } 
 * FieldDeclList → FieldDeclList FieldDecl  {  } 
 * FieldDecl → Type VariableList ';' { } 
 * VariableList → Variable { }
 * VariableList → VariableList Variable { }
 * Variable → ID { Symbol sym = new Symbol(ID, type); currEnv.put(ID, sym);} 
 * Variable → ID '[' integer_literal ']'{ Symbol sym = new Symbol(ID, type, integer_literal); currEnv.put(ID, sym);} }  
 * Type → int { type = INT  } //type is a global variable 
 * Type → float { type = FLOAT  } //type is a global variable  boolean
 * Type → boolean { type = BOOLEAN  }
 */

/*
 * SDT Scheme for handling Field Declations - Version 2
 * FieldDeclList → FieldDecl    {  } 
 * FieldDeclList → FieldDeclList FieldDecl  {  } 
 * FieldDecl → Type VariableList ';' { annotateSymbolTable(Type.type, VariableList.node);} 
 * VariableList → Variable { VariableList.node = Variable.node; }
 * VariableList_1 → VariableList_2 Variable { VariableList_1.node = VariableList_2.node; VariableList_1.node.add(Variable.node);}
 * Variable → ID { Symbol sym = new Symbol(ID); currEnv.put(ID, sym); Variable.node = new ArrayList<Symbol>(); Variable.node.add(sym);} 
 * Variable → ID '[' integer_literal ']'{ Symbol sym = new Symbol(ID, integer_literal); currEnv.put(ID, sym);} Variable.node = new ArrayList<Symbol>(); Variable.node.add(sym);}  
 * Type → int { Type.type = INT  } /
 * Type → float { Type.type = FLOAT  } //type is a global variable  boolean
 * Type → boolean { Type.type = BOOLEAN  }
 */


/*
 * Symbol Table
 */
class Env {
	private Hashtable table;
	protected Env prev;
	
	public Env(Env p) {
		table = new Hashtable(); 
		prev = p;
	}
	
	public void put(String s, Symbol sym) {
		table.put(s, sym);
	}

	public Symbol get(String s) {
		for( Env e = this; e != null; e = e.prev ) {
			Symbol found = (Symbol)(e.table.get(s));
			if ( found != null ) return found;
		}
		return null;
	}
}
