
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  MxLexer : public antlr4::Lexer {
public:
  enum {
    LITERAL = 1, SL_COMMENT = 2, ML_COMMENT = 3, DOCS_COMMENT = 4, FORMAT_STRING_ELEMENT = 5, 
    STRING = 6, FORMAT_STRING_STARTER = 7, QUOTATION = 8, CLASS = 9, FOR = 10, 
    WHILE = 11, IF = 12, ELSE = 13, INT = 14, BOOLEAN = 15, STR = 16, VOID = 17, 
    MAIN = 18, RETURN = 19, CONTINUE = 20, BREAK = 21, NEW = 22, NULL_ = 23, 
    BOOL = 24, THIS = 25, WS = 26, ID = 27, DOLLAR = 28, INTEGER = 29, LETTER = 30, 
    NUMBER = 31, EQUAL = 32, ADD = 33, SUB = 34, MUL = 35, DIV = 36, LEFT_PARENTHESIS = 37, 
    RIGHT_PARENTHESIS = 38, LEFT_CURLY_BRACKET = 39, RIGHT_CURLY_BRACKET = 40, 
    LEFT_SQUARE_BRACKET = 41, RIGHT_SQUARE_BRACKET = 42, PLUS_PLUS = 43, 
    MINUS_MINUS = 44, MOD = 45, SRL = 46, SLL = 47, BT = 48, LT = 49, BEQ = 50, 
    LEQ = 51, ET = 52, NET = 53, AND = 54, XOR = 55, OR = 56, AND_AND = 57, 
    OR_OR = 58, QUESTION = 59, SEMI_COLON = 60, COLON = 61, DOT = 62, COMMA = 63, 
    WAVE = 64, EXCLAIMER = 65
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

