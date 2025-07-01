grammar Mx;
@lexer::members {
    bool isID = true;
    bool start = true;
}
prog : (classDef ';' | varDef ';' | funcDef)* mainFunc (classDef ';' | varDef ';' | funcDef)* EOF;

mainFunc : INT MAIN '(' ')' block;

stat :  regularStat
     | specialStat;

specialStat : funcDef                   #funcdefstat
            | classFuncDef              #classfuncdefstat
            | classDef                  #classdefstat
            ;

regularStat : expr ';'                  #exprstat
            | varDef ';'                #vardefstat
            | ifStat                    #ifstat
            | assignStat ';'            #assignstat
            | block                     #blockstat
            | forStat                   #forstat
            | whileStat                 #whilestat
            | returnStat ';'            #returnstat
            | continue ';'              #continuestat
            | break ';'                 #breakstat
            | ';'                       #nullstat
            ;

varDef : type ID (EQUAL expr)? (',' ID (EQUAL expr)?)*;

//arrayDef : type('['INT?']')+ ID ('=' (arrayConst | initArray | ID ))?;

funcDef : type ID '(' (type ID (',' type ID)*)? ')' block;

classFuncDef : ID '('')' block;   //must split, or it will take '()' as a whole in the whole program.

classDef : CLASS ID '{' (varDef ';' | funcDef | classFuncDef | classDef ';')* '}';

ifStat : IF '(' (ifExpr = expr)? ')' regularStat (ELSE regularStat)?;

assignStat : expr EQUAL expr;

//arrayAssignStat : ID ('['expr']')* '=' expr; //int[][] a; a[0] = new int[0];

block : '{' stat*? '}';

forStat : FOR '(' (initialVarDef = varDef | initialAssignStat = assignStat | initialExpr = expr)? ';' (forCondExpr = expr)? ';' (updateAssignStat = assignStat | updateExpr = expr)? ')' regularStat;

whileStat : WHILE '(' whileCondExpr = expr ')' regularStat;

returnStat : RETURN (expr | funcCall)?;

continue : CONTINUE;

break : BREAK;

expr : '(' expr? ')'                                                    #parenExpr
     | expr '[' expr ']'                                               #indexExpr
     | arrayConst                                                       #arrayExpr
     | funcCall                                                         #funcCallExpr
     | expr '.' expr                                                    #dotExpr
     | expr (PLUS_PLUS | MINUS_MINUS)                                   #unaryExpr
     | (PLUS_PLUS | MINUS_MINUS) expr                                   #unaryExpr
     | (WAVE | EXCLAIMER) expr                                          #unaryExpr
     | expr ('*' | '/' | '%') expr                                      #binaryExpr
     | ('+' | '-') expr                                                 #unaryExpr
     | expr ('+' | '-') expr                                            #binaryExpr
     | expr (SRL | SLL) expr                                            #binaryExpr
     | expr (BT | LT | BEQ | LEQ) expr                                  #binaryExpr
     | expr (ET | NET) expr                                             #binaryExpr
     | expr AND expr                                                    #binaryExpr
     | expr XOR expr                                                    #binaryExpr
     | expr OR expr                                                     #binaryExpr
     | expr AND_AND expr                                                #binaryExpr
     | expr OR_OR expr                                                  #binaryExpr
     | expr '?' expr ':' expr                                           #ternaryExpr
     | initArray                                                        #initArrayExpr
     | initObject                                                       #initObjectExpr
     | formatString                                                     #formatStringExpr
     | THIS                                                             #thisExpr
     | LITERAL                                                          #literalExpr
     | ID                                                               #idExpr
     ;

formatString : FORMAT_STRING_STARTER (FORMAT_STRING_ELEMENT | (DOLLAR expr DOLLAR))* QUOTATION;


funcCall : ID '(' (expr (',' expr)*)? ')';

arrayConst : '{' (LITERAL (',' LITERAL)*)? '}'
           | '{' arrayConst (',' arrayConst)* '}';

initArray : NEW type ('['expr']')+('[' ']')*
          | NEW type ('[' ']')+ arrayConst;

initObject : NEW type ('('')')?;

type : INT | BOOLEAN | STR | VOID
     | ID     //since in ID can represent a type of class, and we can find no way to put type as lexer when it includes ID. So we decide to make it a parser
     | type '['']';


//INIT_ARRAY : 'new' type ('['INT']')+;    this makes whitespace and int jointly being type.
//WS only skips for parser

LITERAL : INTEGER
        | STRING
        | BOOL
        | NULL;


SL_COMMENT : '//' .*? ('\n'|EOF) -> skip;
ML_COMMENT : '/*' .*? '*/' -> skip;
DOCS_COMMENT : '/**' .*? '*/' -> skip;
//FORMAL_STRING : 'f' STRING;  //I need to guarantee that the inner $$ are executed as well.
FORMAT_STRING_ELEMENT : {!isID && start}? ('\\n' | '\\\\' | '\\"' | '$$' | [ !#%-[\]-~])+ ;
STRING : '"' ('\\n' | '\\\\' | '\\"' | [ !#-[\]-~])* '"';
FORMAT_STRING_STARTER : 'f"'{isID = !isID; start = true;};
QUOTATION : '"'{isID = !isID; start = false;};
CLASS : 'class';
FOR : 'for';
WHILE : 'while';
IF : 'if';
ELSE : 'else';
INT : 'int';
BOOLEAN : 'bool';
STR : 'string';
VOID : 'void';
MAIN : 'main';
RETURN : 'return';
CONTINUE: 'continue';
BREAK: 'break';
NEW : 'new';
NULL : 'null';
BOOL : 'true' | 'false';
THIS : 'this';
WS : [ \t\r\n]+ -> skip;
ID : LETTER(LETTER | NUMBER | '_')*;

DOLLAR : '$'{isID = !isID;};



INTEGER : '0' | [1-9]NUMBER*;  // if add +- before it, it will always recognize x+1 as x(ID) +1(INT) in lexer, which is not what we want.
LETTER : [a-zA-Z];
NUMBER : [0-9];
EQUAL : '=';
ADD : '+';
SUB : '-';
MUL : '*';
DIV : '/';
LEFT_PARENTHESIS : '(';
RIGHT_PARENTHESIS : ')';
LEFT_CURLY_BRACKET : '{';
RIGHT_CURLY_BRACKET : '}';
LEFT_SQUARE_BRACKET : '[';
RIGHT_SQUARE_BRACKET : ']';

PLUS_PLUS : '++';
MINUS_MINUS : '--';
MOD : '%';
SRL : '>>';
SLL : '<<';
BT : '>';
LT : '<';
BEQ : '>=';
LEQ : '<=';
ET : '==';
NET : '!=';
AND : '&';
XOR : '^';
OR : '|';
AND_AND : '&&';
OR_OR : '||';
QUESTION : '?';
SEMI_COLON : ';';
COLON : ':';
DOT : '.';
COMMA : ',';
WAVE : '~';
EXCLAIMER : '!';

//in this phase we don't have to hard-code the pre-defined functions because they can still be recognized as functions correctly