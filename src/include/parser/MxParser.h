
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  MxParser : public antlr4::Parser {
public:
  enum {
    SL_COMMENT = 1, ML_COMMENT = 2, DOCS_COMMENT = 3, FORMAT_STRING_ELEMENT = 4, 
    STRING = 5, FORMAT_STRING_STARTER = 6, QUOTATION = 7, CLASS = 8, FOR = 9, 
    WHILE = 10, IF = 11, ELSE = 12, INT = 13, BOOLEAN = 14, STR = 15, VOID = 16, 
    MAIN = 17, RETURN = 18, CONTINUE = 19, BREAK = 20, NEW = 21, NULL_ = 22, 
    BOOL = 23, THIS = 24, WS = 25, ID = 26, DOLLAR = 27, INTEGER = 28, LETTER = 29, 
    NUMBER = 30, EQUAL = 31, ADD = 32, SUB = 33, MUL = 34, DIV = 35, LEFT_PARENTHESIS = 36, 
    RIGHT_PARENTHESIS = 37, LEFT_CURLY_BRACKET = 38, RIGHT_CURLY_BRACKET = 39, 
    LEFT_SQUARE_BRACKET = 40, RIGHT_SQUARE_BRACKET = 41, PLUS_PLUS = 42, 
    MINUS_MINUS = 43, MOD = 44, SRL = 45, SLL = 46, BT = 47, LT = 48, BEQ = 49, 
    LEQ = 50, ET = 51, NET = 52, AND = 53, XOR = 54, OR = 55, AND_AND = 56, 
    OR_OR = 57, QUESTION = 58, SEMI_COLON = 59, COLON = 60, DOT = 61, COMMA = 62, 
    WAVE = 63, EXCLAIMER = 64
  };

  enum {
    RuleProg = 0, RuleMainFunc = 1, RuleStat = 2, RuleSpecialStat = 3, RuleRegularStat = 4, 
    RuleVarDef = 5, RuleFuncDef = 6, RuleClassFuncDef = 7, RuleClassDef = 8, 
    RuleIfStat = 9, RuleAssignStat = 10, RuleBlock = 11, RuleForStat = 12, 
    RuleWhileStat = 13, RuleReturnStat = 14, RuleContinue = 15, RuleBreak = 16, 
    RuleExpr = 17, RuleFormatString = 18, RuleFuncCall = 19, RuleArrayConst = 20, 
    RuleInitArray = 21, RuleInitObject = 22, RuleType = 23, RuleLiteral = 24
  };

  explicit MxParser(antlr4::TokenStream *input);

  MxParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MxParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgContext;
  class MainFuncContext;
  class StatContext;
  class SpecialStatContext;
  class RegularStatContext;
  class VarDefContext;
  class FuncDefContext;
  class ClassFuncDefContext;
  class ClassDefContext;
  class IfStatContext;
  class AssignStatContext;
  class BlockContext;
  class ForStatContext;
  class WhileStatContext;
  class ReturnStatContext;
  class ContinueContext;
  class BreakContext;
  class ExprContext;
  class FormatStringContext;
  class FuncCallContext;
  class ArrayConstContext;
  class InitArrayContext;
  class InitObjectContext;
  class TypeContext;
  class LiteralContext; 

  class  ProgContext : public antlr4::ParserRuleContext {
  public:
    ProgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MainFuncContext *mainFunc();
    antlr4::tree::TerminalNode *EOF();
    std::vector<ClassDefContext *> classDef();
    ClassDefContext* classDef(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI_COLON();
    antlr4::tree::TerminalNode* SEMI_COLON(size_t i);
    std::vector<VarDefContext *> varDef();
    VarDefContext* varDef(size_t i);
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgContext* prog();

  class  MainFuncContext : public antlr4::ParserRuleContext {
  public:
    MainFuncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *MAIN();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MainFuncContext* mainFunc();

  class  StatContext : public antlr4::ParserRuleContext {
  public:
    StatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RegularStatContext *regularStat();
    SpecialStatContext *specialStat();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatContext* stat();

  class  SpecialStatContext : public antlr4::ParserRuleContext {
  public:
    SpecialStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FuncDefContext *funcDef();
    ClassFuncDefContext *classFuncDef();
    ClassDefContext *classDef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecialStatContext* specialStat();

  class  RegularStatContext : public antlr4::ParserRuleContext {
  public:
    RegularStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RegularStatContext() = default;
    void copyFrom(RegularStatContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IfstatContext : public RegularStatContext {
  public:
    IfstatContext(RegularStatContext *ctx);

    IfStatContext *ifStat();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprstatContext : public RegularStatContext {
  public:
    ExprstatContext(RegularStatContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReturnstatContext : public RegularStatContext {
  public:
    ReturnstatContext(RegularStatContext *ctx);

    ReturnStatContext *returnStat();
    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NullstatContext : public RegularStatContext {
  public:
    NullstatContext(RegularStatContext *ctx);

    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VardefstatContext : public RegularStatContext {
  public:
    VardefstatContext(RegularStatContext *ctx);

    VarDefContext *varDef();
    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ContinuestatContext : public RegularStatContext {
  public:
    ContinuestatContext(RegularStatContext *ctx);

    ContinueContext *continue_();
    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignstatContext : public RegularStatContext {
  public:
    AssignstatContext(RegularStatContext *ctx);

    AssignStatContext *assignStat();
    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhilestatContext : public RegularStatContext {
  public:
    WhilestatContext(RegularStatContext *ctx);

    WhileStatContext *whileStat();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BreakstatContext : public RegularStatContext {
  public:
    BreakstatContext(RegularStatContext *ctx);

    BreakContext *break_();
    antlr4::tree::TerminalNode *SEMI_COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockstatContext : public RegularStatContext {
  public:
    BlockstatContext(RegularStatContext *ctx);

    BlockContext *block();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ForstatContext : public RegularStatContext {
  public:
    ForstatContext(RegularStatContext *ctx);

    ForStatContext *forStat();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  RegularStatContext* regularStat();

  class  VarDefContext : public antlr4::ParserRuleContext {
  public:
    VarDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQUAL();
    antlr4::tree::TerminalNode* EQUAL(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDefContext* varDef();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    BlockContext *block();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefContext* funcDef();

  class  ClassFuncDefContext : public antlr4::ParserRuleContext {
  public:
    ClassFuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassFuncDefContext* classFuncDef();

  class  ClassDefContext : public antlr4::ParserRuleContext {
  public:
    ClassDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CLASS();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LEFT_CURLY_BRACKET();
    antlr4::tree::TerminalNode *RIGHT_CURLY_BRACKET();
    std::vector<VarDefContext *> varDef();
    VarDefContext* varDef(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI_COLON();
    antlr4::tree::TerminalNode* SEMI_COLON(size_t i);
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);
    std::vector<ClassFuncDefContext *> classFuncDef();
    ClassFuncDefContext* classFuncDef(size_t i);
    std::vector<ClassDefContext *> classDef();
    ClassDefContext* classDef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ClassDefContext* classDef();

  class  IfStatContext : public antlr4::ParserRuleContext {
  public:
    MxParser::ExprContext *ifExpr = nullptr;
    IfStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    std::vector<RegularStatContext *> regularStat();
    RegularStatContext* regularStat(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfStatContext* ifStat();

  class  AssignStatContext : public antlr4::ParserRuleContext {
  public:
    AssignStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *EQUAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignStatContext* assignStat();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT_CURLY_BRACKET();
    antlr4::tree::TerminalNode *RIGHT_CURLY_BRACKET();
    std::vector<StatContext *> stat();
    StatContext* stat(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  ForStatContext : public antlr4::ParserRuleContext {
  public:
    MxParser::VarDefContext *initialVarDef = nullptr;
    MxParser::AssignStatContext *initialAssignStat = nullptr;
    MxParser::ExprContext *initialExpr = nullptr;
    MxParser::ExprContext *forCondExpr = nullptr;
    MxParser::AssignStatContext *updateAssignStat = nullptr;
    MxParser::ExprContext *updateExpr = nullptr;
    ForStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    std::vector<antlr4::tree::TerminalNode *> SEMI_COLON();
    antlr4::tree::TerminalNode* SEMI_COLON(size_t i);
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    RegularStatContext *regularStat();
    VarDefContext *varDef();
    std::vector<AssignStatContext *> assignStat();
    AssignStatContext* assignStat(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForStatContext* forStat();

  class  WhileStatContext : public antlr4::ParserRuleContext {
  public:
    MxParser::ExprContext *whileCondExpr = nullptr;
    WhileStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    RegularStatContext *regularStat();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileStatContext* whileStat();

  class  ReturnStatContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();
    FuncCallContext *funcCall();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatContext* returnStat();

  class  ContinueContext : public antlr4::ParserRuleContext {
  public:
    ContinueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueContext* continue_();

  class  BreakContext : public antlr4::ParserRuleContext {
  public:
    BreakContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakContext* break_();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  InitObjectExprContext : public ExprContext {
  public:
    InitObjectExprContext(ExprContext *ctx);

    InitObjectContext *initObject();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ThisExprContext : public ExprContext {
  public:
    ThisExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *THIS();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DotExprContext : public ExprContext {
  public:
    DotExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *DOT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayExprContext : public ExprContext {
  public:
    ArrayExprContext(ExprContext *ctx);

    ArrayConstContext *arrayConst();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryExprContext : public ExprContext {
  public:
    BinaryExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *MUL();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();
    antlr4::tree::TerminalNode *SRL();
    antlr4::tree::TerminalNode *SLL();
    antlr4::tree::TerminalNode *BT();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *BEQ();
    antlr4::tree::TerminalNode *LEQ();
    antlr4::tree::TerminalNode *ET();
    antlr4::tree::TerminalNode *NET();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *XOR();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *AND_AND();
    antlr4::tree::TerminalNode *OR_OR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FuncCallExprContext : public ExprContext {
  public:
    FuncCallExprContext(ExprContext *ctx);

    FuncCallContext *funcCall();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenExprContext : public ExprContext {
  public:
    ParenExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IndexExprContext : public ExprContext {
  public:
    IndexExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *LEFT_SQUARE_BRACKET();
    antlr4::tree::TerminalNode *RIGHT_SQUARE_BRACKET();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryExprContext : public ExprContext {
  public:
    UnaryExprContext(ExprContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *PLUS_PLUS();
    antlr4::tree::TerminalNode *MINUS_MINUS();
    antlr4::tree::TerminalNode *WAVE();
    antlr4::tree::TerminalNode *EXCLAIMER();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *SUB();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TernaryExprContext : public ExprContext {
  public:
    TernaryExprContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *COLON();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralExprContext : public ExprContext {
  public:
    LiteralExprContext(ExprContext *ctx);

    LiteralContext *literal();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InitArrayExprContext : public ExprContext {
  public:
    InitArrayExprContext(ExprContext *ctx);

    InitArrayContext *initArray();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FormatStringExprContext : public ExprContext {
  public:
    FormatStringExprContext(ExprContext *ctx);

    FormatStringContext *formatString();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdExprContext : public ExprContext {
  public:
    IdExprContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  FormatStringContext : public antlr4::ParserRuleContext {
  public:
    FormatStringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FORMAT_STRING_STARTER();
    antlr4::tree::TerminalNode *QUOTATION();
    std::vector<antlr4::tree::TerminalNode *> FORMAT_STRING_ELEMENT();
    antlr4::tree::TerminalNode* FORMAT_STRING_ELEMENT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOLLAR();
    antlr4::tree::TerminalNode* DOLLAR(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FormatStringContext* formatString();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncCallContext* funcCall();

  class  ArrayConstContext : public antlr4::ParserRuleContext {
  public:
    ArrayConstContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEFT_CURLY_BRACKET();
    antlr4::tree::TerminalNode *RIGHT_CURLY_BRACKET();
    std::vector<LiteralContext *> literal();
    LiteralContext* literal(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    std::vector<ArrayConstContext *> arrayConst();
    ArrayConstContext* arrayConst(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayConstContext* arrayConst();

  class  InitArrayContext : public antlr4::ParserRuleContext {
  public:
    InitArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEW();
    TypeContext *type();
    std::vector<antlr4::tree::TerminalNode *> LEFT_SQUARE_BRACKET();
    antlr4::tree::TerminalNode* LEFT_SQUARE_BRACKET(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RIGHT_SQUARE_BRACKET();
    antlr4::tree::TerminalNode* RIGHT_SQUARE_BRACKET(size_t i);
    ArrayConstContext *arrayConst();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitArrayContext* initArray();

  class  InitObjectContext : public antlr4::ParserRuleContext {
  public:
    InitObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NEW();
    TypeContext *type();
    antlr4::tree::TerminalNode *LEFT_PARENTHESIS();
    antlr4::tree::TerminalNode *RIGHT_PARENTHESIS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitObjectContext* initObject();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *BOOLEAN();
    antlr4::tree::TerminalNode *STR();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *ID();
    TypeContext *type();
    antlr4::tree::TerminalNode *LEFT_SQUARE_BRACKET();
    antlr4::tree::TerminalNode *RIGHT_SQUARE_BRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();
  TypeContext* type(int precedence);
  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *NULL_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);
  bool typeSempred(TypeContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

