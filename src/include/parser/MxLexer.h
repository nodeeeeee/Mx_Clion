
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  MxLexer : public antlr4::Lexer {
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

