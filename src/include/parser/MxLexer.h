
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  MxLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, LITERAL = 3, SL_COMMENT = 4, ML_COMMENT = 5, DOCS_COMMENT = 6, 
    FORMAT_STRING_ELEMENT = 7, STRING = 8, FORMAT_STRING_STARTER = 9, QUOTATION = 10, 
    CLASS = 11, FOR = 12, WHILE = 13, IF = 14, ELSE = 15, INT = 16, BOOLEAN = 17, 
    STR = 18, VOID = 19, MAIN = 20, RETURN = 21, CONTINUE = 22, BREAK = 23, 
    NEW = 24, NULL_ = 25, BOOL = 26, THIS = 27, WS = 28, ID = 29, DOLLAR = 30, 
    INTEGER = 31, LETTER = 32, NUMBER = 33, EQUAL = 34, ADD = 35, SUB = 36, 
    MUL = 37, DIV = 38, LEFT_PARENTHESIS = 39, RIGHT_PARENTHESIS = 40, LEFT_CURLY_BRACKET = 41, 
    RIGHT_CURLY_BRACKET = 42, PLUS_PLUS = 43, MINUS_MINUS = 44, MOD = 45, 
    SRL = 46, SLL = 47, BT = 48, LT = 49, BEQ = 50, LEQ = 51, ET = 52, NET = 53, 
    AND = 54, XOR = 55, OR = 56, AND_AND = 57, OR_OR = 58, QUESTION = 59, 
    SEMI_COLON = 60, COLON = 61, DOT = 62, COMMA = 63, WAVE = 64, EXCLAIMER = 65
  };

  explicit MxLexer(antlr4::CharStream *input);

  ~MxLexer() override;


      bool isID = true;
      bool start = true;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  void action(antlr4::RuleContext *context, size_t ruleIndex, size_t actionIndex) override;

  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.
  void FORMAT_STRING_STARTERAction(antlr4::RuleContext *context, size_t actionIndex);
  void QUOTATIONAction(antlr4::RuleContext *context, size_t actionIndex);
  void DOLLARAction(antlr4::RuleContext *context, size_t actionIndex);

  // Individual semantic predicate functions triggered by sempred() above.
  bool FORMAT_STRING_ELEMENTSempred(antlr4::RuleContext *_localctx, size_t predicateIndex);

};

