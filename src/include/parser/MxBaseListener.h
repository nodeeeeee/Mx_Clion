
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "MxListener.h"


/**
 * This class provides an empty implementation of MxListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MxBaseListener : public MxListener {
public:

  virtual void enterProg(MxParser::ProgContext * /*ctx*/) override { }
  virtual void exitProg(MxParser::ProgContext * /*ctx*/) override { }

  virtual void enterMainFunc(MxParser::MainFuncContext * /*ctx*/) override { }
  virtual void exitMainFunc(MxParser::MainFuncContext * /*ctx*/) override { }

  virtual void enterStat(MxParser::StatContext * /*ctx*/) override { }
  virtual void exitStat(MxParser::StatContext * /*ctx*/) override { }

  virtual void enterSpecialStat(MxParser::SpecialStatContext * /*ctx*/) override { }
  virtual void exitSpecialStat(MxParser::SpecialStatContext * /*ctx*/) override { }

  virtual void enterRegularStat(MxParser::RegularStatContext * /*ctx*/) override { }
  virtual void exitRegularStat(MxParser::RegularStatContext * /*ctx*/) override { }

  virtual void enterVarDef(MxParser::VarDefContext * /*ctx*/) override { }
  virtual void exitVarDef(MxParser::VarDefContext * /*ctx*/) override { }

  virtual void enterFuncDef(MxParser::FuncDefContext * /*ctx*/) override { }
  virtual void exitFuncDef(MxParser::FuncDefContext * /*ctx*/) override { }

  virtual void enterClassFuncDef(MxParser::ClassFuncDefContext * /*ctx*/) override { }
  virtual void exitClassFuncDef(MxParser::ClassFuncDefContext * /*ctx*/) override { }

  virtual void enterClassDef(MxParser::ClassDefContext * /*ctx*/) override { }
  virtual void exitClassDef(MxParser::ClassDefContext * /*ctx*/) override { }

  virtual void enterIfStat(MxParser::IfStatContext * /*ctx*/) override { }
  virtual void exitIfStat(MxParser::IfStatContext * /*ctx*/) override { }

  virtual void enterAssignStat(MxParser::AssignStatContext * /*ctx*/) override { }
  virtual void exitAssignStat(MxParser::AssignStatContext * /*ctx*/) override { }

  virtual void enterBlock(MxParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(MxParser::BlockContext * /*ctx*/) override { }

  virtual void enterForStat(MxParser::ForStatContext * /*ctx*/) override { }
  virtual void exitForStat(MxParser::ForStatContext * /*ctx*/) override { }

  virtual void enterWhileStat(MxParser::WhileStatContext * /*ctx*/) override { }
  virtual void exitWhileStat(MxParser::WhileStatContext * /*ctx*/) override { }

  virtual void enterReturnStat(MxParser::ReturnStatContext * /*ctx*/) override { }
  virtual void exitReturnStat(MxParser::ReturnStatContext * /*ctx*/) override { }

  virtual void enterContinue(MxParser::ContinueContext * /*ctx*/) override { }
  virtual void exitContinue(MxParser::ContinueContext * /*ctx*/) override { }

  virtual void enterBreak(MxParser::BreakContext * /*ctx*/) override { }
  virtual void exitBreak(MxParser::BreakContext * /*ctx*/) override { }

  virtual void enterInitObjectExpr(MxParser::InitObjectExprContext * /*ctx*/) override { }
  virtual void exitInitObjectExpr(MxParser::InitObjectExprContext * /*ctx*/) override { }

  virtual void enterThisExpr(MxParser::ThisExprContext * /*ctx*/) override { }
  virtual void exitThisExpr(MxParser::ThisExprContext * /*ctx*/) override { }

  virtual void enterDotExpr(MxParser::DotExprContext * /*ctx*/) override { }
  virtual void exitDotExpr(MxParser::DotExprContext * /*ctx*/) override { }

  virtual void enterArrayExpr(MxParser::ArrayExprContext * /*ctx*/) override { }
  virtual void exitArrayExpr(MxParser::ArrayExprContext * /*ctx*/) override { }

  virtual void enterBinaryExpr(MxParser::BinaryExprContext * /*ctx*/) override { }
  virtual void exitBinaryExpr(MxParser::BinaryExprContext * /*ctx*/) override { }

  virtual void enterFuncCallExpr(MxParser::FuncCallExprContext * /*ctx*/) override { }
  virtual void exitFuncCallExpr(MxParser::FuncCallExprContext * /*ctx*/) override { }

  virtual void enterParenExpr(MxParser::ParenExprContext * /*ctx*/) override { }
  virtual void exitParenExpr(MxParser::ParenExprContext * /*ctx*/) override { }

  virtual void enterIndexExpr(MxParser::IndexExprContext * /*ctx*/) override { }
  virtual void exitIndexExpr(MxParser::IndexExprContext * /*ctx*/) override { }

  virtual void enterUnaryExpr(MxParser::UnaryExprContext * /*ctx*/) override { }
  virtual void exitUnaryExpr(MxParser::UnaryExprContext * /*ctx*/) override { }

  virtual void enterTernaryExpr(MxParser::TernaryExprContext * /*ctx*/) override { }
  virtual void exitTernaryExpr(MxParser::TernaryExprContext * /*ctx*/) override { }

  virtual void enterLiteralExpr(MxParser::LiteralExprContext * /*ctx*/) override { }
  virtual void exitLiteralExpr(MxParser::LiteralExprContext * /*ctx*/) override { }

  virtual void enterInitArrayExpr(MxParser::InitArrayExprContext * /*ctx*/) override { }
  virtual void exitInitArrayExpr(MxParser::InitArrayExprContext * /*ctx*/) override { }

  virtual void enterFormatStringExpr(MxParser::FormatStringExprContext * /*ctx*/) override { }
  virtual void exitFormatStringExpr(MxParser::FormatStringExprContext * /*ctx*/) override { }

  virtual void enterIdExpr(MxParser::IdExprContext * /*ctx*/) override { }
  virtual void exitIdExpr(MxParser::IdExprContext * /*ctx*/) override { }

  virtual void enterFormatString(MxParser::FormatStringContext * /*ctx*/) override { }
  virtual void exitFormatString(MxParser::FormatStringContext * /*ctx*/) override { }

  virtual void enterFuncCall(MxParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(MxParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterArrayConst(MxParser::ArrayConstContext * /*ctx*/) override { }
  virtual void exitArrayConst(MxParser::ArrayConstContext * /*ctx*/) override { }

  virtual void enterInitArray(MxParser::InitArrayContext * /*ctx*/) override { }
  virtual void exitInitArray(MxParser::InitArrayContext * /*ctx*/) override { }

  virtual void enterInitObject(MxParser::InitObjectContext * /*ctx*/) override { }
  virtual void exitInitObject(MxParser::InitObjectContext * /*ctx*/) override { }

  virtual void enterType(MxParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(MxParser::TypeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

