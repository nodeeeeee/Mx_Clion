grammar MxStandard;

@lexer::members {
    int formatMode = 0;
    boolean exprMode = false;
    int bracketDepth = 0;
}

program
    : (classDef | funcDef | varDef)* mainFunc (classDef | funcDef | varDef)* EOF
    ;

mainFunc
    : Int Main '(' ')' suite
    ;

classDef
    : Class classIdentifier=Identifier '{' classStmt* '}' ';'
    ;

classStmt
    : memberType=type Identifier (',' Identifier)* ';'                                               # memberDefStmt
    | classIdentifier=Identifier '(' ')' suite                                                       # constructorDefStmt
    | returnType=type funcName=Identifier '(' (type Identifier (',' type Identifier)*)? ')' suite    # funcDefStmt
    ;

funcDef
    : returnType=type funcName=Identifier
      '(' (type Identifier (',' type Identifier)*)? ')' suite
    ;

varDef
    : type Identifier ('=' expression)? (',' Identifier ('=' expression)?)* ';'
    ;

statement
    : type Identifier ('=' expression)? (',' Identifier ('=' expression)?)* ';' # varDefStmt
    | suite                                                                     # suiteStmt
    | expression ';'                                                            # exprStmt
    | If '(' expression ')' trueStmt=statement (Else falseStmt=statement)?      # ifStmt
    | While '(' expression ')' statement                                        # whileStmt
    | For '(' initializeStmt=statement (conditionExpr=expression)? ';'
      (stepExpr=expression)? ')' statement                                      # forStmt
    | Return (returnExpr=expression)? ';'                                       # returnStmt
    | Break ';'                                                                 # breakStmt
    | Continue ';'                                                              # continueStmt
    | ';'                                                                       # emptyStmt
    ;

expression
    : '(' expression ')'                                                    # parenExpr
    | primary                                                               # atomicExpr
    | 'f"' (FormatStringLiteral | '$' expression '$')* Quotation            # formatExpr
    | expression (Increment | Decrement)                                    # unaryExpr
    | funcName=Identifier '(' arguments? ')'                                # funcCallExpr
    | classVar=expression '.' funcName=Identifier '(' arguments? ')'        # funcCallExpr
    | expression ('[' index=expression ']')+                                # subscriptExpr
    | expression '.' Identifier                                             # memberExpr
    | <assoc=right> (Increment | Decrement) expression                      # unaryExpr
    | <assoc=right> (Add | Sub) expression                                  # unaryExpr
    | <assoc=right> (NotLogic | Not) expression                             # unaryExpr
    | expression (Mul | Div | Mod) expression                               # binaryExpr
    | expression (Add | Sub) expression                                     # binaryExpr
    | expression (ShiftLeft | ShiftRight) expression                        # binaryExpr
    | expression (Less | LessEqual | Greater | GreaterEqual) expression     # binaryExpr
    | expression (Equal | UnEqual) expression                               # binaryExpr
    | expression And expression                                             # binaryExpr
    | expression Xor expression                                             # binaryExpr
    | expression Or expression                                              # binaryExpr
    | expression AndLogic expression                                        # binaryExpr
    | expression OrLogic expression                                         # binaryExpr
    | <assoc=right> expression '?' expression ':' expression                # tenaryExpr
    | expression Assign expression                                          # assignExpr
    ;

suite
    : '{' statement* '}'
    ;

arguments
    : expression (',' expression)*
    ;

primary
    : literal                                    # literalPrimary
    | Identifier                                 # varPrimary
    | This                                       # thisPrimary
    | New type ('[' expression ']')+ ('[' ']')*  # newPrimary
    | New type ('[' ']')+ array                  # newPrimary
    | New type ('('')')?                         # newPrimary
    ;

array
    : '{' '}'
    | '{' array (',' array)* '}'
    | '{' literal (',' literal)* '}'
    ;

literal
    : DecimalNumber     # decimalLiteral
    | True              # boolLiteral
    | False             # boolLiteral
    | StringLiteral     # stringLiteral
    | Null              # nullLiteral
    | array             # arrayLiteral
    ;

type
    : Int
    | Bool
    | String
    | Identifier
    | Void
    | (Int | Bool | String | Identifier) ('[' ']')+
    ;

// Format quatations and Quotations
FormatQuatation
    : 'f"'
    {
        formatMode++;
        exprMode = false;
    }
    ;
Quotation
    : {formatMode > 0 && !exprMode}? '"'
    {
        formatMode--;
        if (formatMode > 0) {
            exprMode = true;
        }
    }
    ;
// Constants and Literals
True : 'true';
False : 'false';
DecimalNumber
    : [1-9][0-9]*
    | '0'
    ;
StringLiteral
    : {formatMode == 0 || exprMode}? '"'('\\n' | '\\\\' | '\\"' | [ !#-[\]-~])*'"'
    ;
FormatStringLiteral
    : {formatMode > 0 && !exprMode}? ('\\n' | '\\\\' | '\\"' | '$$' | [ !#%-[\]-~])+
    ;
Null : 'null';
// Reserved Words
New : 'new';
Class : 'class';
This : 'this';
If : 'if';
Else : 'else';
For : 'for';
While : 'while';
Break : 'break';
Continue : 'continue';
Return : 'return';
Main : { bracketDepth == 0 }? 'main';
// Types and Identifiers
Bool : 'bool';
Int : 'int';
Void : 'void';
String : 'string';
Identifier : [A-Za-z][A-Za-z_0-9]*;
// Arithmetic Operators
Add : '+';
Sub : '-';
Mul : '*';
Div : '/';
Mod : '%';
// Compare Operators
Less : '<';
LessEqual : '<=';
Greater : '>';
GreaterEqual : '>=';
Equal : '==';
UnEqual : '!=';
// Logic Operators
AndLogic : '&&';
OrLogic : '||';
NotLogic : '!';
// Bitwise Operators
ShiftRight : '>>';
ShiftLeft : '<<';
And : '&';
Or : '|';
Xor : '^';
Not : '~';
// Assign Operators
Assign : '=';
// Increment and Decrement
Increment : '++';
Decrement : '--';
// Member Access Operator
Dot : '.';
// Parens, Branckets and Braces
LeftParen : '(';
RightParen : ')';
LeftBracket : '[';
RightBracket : ']';
LeftBrace : '{'
          { ++bracketDepth; }
          ;
RightBrace : '}'
           { --bracketDepth; }
           ;
// Other Symbols
Dollar
    : '$'
    { exprMode = !exprMode; }
    ;
Question : '?';
Colon : ':';
Semicolon : ';';
Comma : ',';
// Whitespace
Whitespace : [ \n\r\t] -> skip;
// Comments
LineComment : '//' ~[\n\r]* -> skip;
BlockComment : '/*' .*? '*/' -> skip;