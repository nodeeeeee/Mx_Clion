
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "MxParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by MxParser.
 */
class  MxListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProg(MxParser::ProgContext *ctx) = 0;
  virtual void exitProg(MxParser::ProgContext *ctx) = 0;

  virtual void enterMainFunc(MxParser::MainFuncContext *ctx) = 0;
  virtual void exitMainFunc(MxParser::MainFuncContext *ctx) = 0;

  virtual void enterStat(MxParser::StatContext *ctx) = 0;
  virtual void exitStat(MxParser::StatContext *ctx) = 0;

  virtual void enterFuncdefstat(MxParser::FuncdefstatContext *ctx) = 0;
  virtual void exitFuncdefstat(MxParser::FuncdefstatContext *ctx) = 0;

  virtual void enterClassfuncdefstat(MxParser::ClassfuncdefstatContext *ctx) = 0;
  virtual void exitClassfuncdefstat(MxParser::ClassfuncdefstatContext *ctx) = 0;

  virtual void enterClassdefstat(MxParser::ClassdefstatContext *ctx) = 0;
  virtual void exitClassdefstat(MxParser::ClassdefstatContext *ctx) = 0;

  virtual void enterExprstat(MxParser::ExprstatContext *ctx) = 0;
  virtual void exitExprstat(MxParser::ExprstatContext *ctx) = 0;

  virtual void enterVardefstat(MxParser::VardefstatContext *ctx) = 0;
  virtual void exitVardefstat(MxParser::VardefstatContext *ctx) = 0;

  virtual void enterIfstat(MxParser::IfstatContext *ctx) = 0;
  virtual void exitIfstat(MxParser::IfstatContext *ctx) = 0;

  virtual void enterAssignstat(MxParser::AssignstatContext *ctx) = 0;
  virtual void exitAssignstat(MxParser::AssignstatContext *ctx) = 0;

  virtual void enterBlockstat(MxParser::BlockstatContext *ctx) = 0;
  virtual void exitBlockstat(MxParser::BlockstatContext *ctx) = 0;

  virtual void enterForstat(MxParser::ForstatContext *ctx) = 0;
  virtual void exitForstat(MxParser::ForstatContext *ctx) = 0;

  virtual void enterWhilestat(MxParser::WhilestatContext *ctx) = 0;
  virtual void exitWhilestat(MxParser::WhilestatContext *ctx) = 0;

  virtual void enterReturnstat(MxParser::ReturnstatContext *ctx) = 0;
  virtual void exitReturnstat(MxParser::ReturnstatContext *ctx) = 0;

  virtual void enterContinuestat(MxParser::ContinuestatContext *ctx) = 0;
  virtual void exitContinuestat(MxParser::ContinuestatContext *ctx) = 0;

  virtual void enterBreakstat(MxParser::BreakstatContext *ctx) = 0;
  virtual void exitBreakstat(MxParser::BreakstatContext *ctx) = 0;

  virtual void enterNullstat(MxParser::NullstatContext *ctx) = 0;
  virtual void exitNullstat(MxParser::NullstatContext *ctx) = 0;

  virtual void enterVarDef(MxParser::VarDefContext *ctx) = 0;
  virtual void exitVarDef(MxParser::VarDefContext *ctx) = 0;

  virtual void enterFuncDef(MxParser::FuncDefContext *ctx) = 0;
  virtual void exitFuncDef(MxParser::FuncDefContext *ctx) = 0;

  virtual void enterClassFuncDef(MxParser::ClassFuncDefContext *ctx) = 0;
  virtual void exitClassFuncDef(MxParser::ClassFuncDefContext *ctx) = 0;

  virtual void enterClassDef(MxParser::ClassDefContext *ctx) = 0;
  virtual void exitClassDef(MxParser::ClassDefContext *ctx) = 0;

  virtual void enterIfStat(MxParser::IfStatContext *ctx) = 0;
  virtual void exitIfStat(MxParser::IfStatContext *ctx) = 0;

  virtual void enterAssignStat(MxParser::AssignStatContext *ctx) = 0;
  virtual void exitAssignStat(MxParser::AssignStatContext *ctx) = 0;

  virtual void enterBlock(MxParser::BlockContext *ctx) = 0;
  virtual void exitBlock(MxParser::BlockContext *ctx) = 0;

  virtual void enterForStat(MxParser::ForStatContext *ctx) = 0;
  virtual void exitForStat(MxParser::ForStatContext *ctx) = 0;

  virtual void enterWhileStat(MxParser::WhileStatContext *ctx) = 0;
  virtual void exitWhileStat(MxParser::WhileStatContext *ctx) = 0;

  virtual void enterReturnStat(MxParser::ReturnStatContext *ctx) = 0;
  virtual void exitReturnStat(MxParser::ReturnStatContext *ctx) = 0;

  virtual void enterContinue(MxParser::ContinueContext *ctx) = 0;
  virtual void exitContinue(MxParser::ContinueContext *ctx) = 0;

  virtual void enterBreak(MxParser::BreakContext *ctx) = 0;
  virtual void exitBreak(MxParser::BreakContext *ctx) = 0;

  virtual void enterInitObjectExpr(MxParser::InitObjectExprContext *ctx) = 0;
  virtual void exitInitObjectExpr(MxParser::InitObjectExprContext *ctx) = 0;

  virtual void enterThisExpr(MxParser::ThisExprContext *ctx) = 0;
  virtual void exitThisExpr(MxParser::ThisExprContext *ctx) = 0;

  virtual void enterDotExpr(MxParser::DotExprContext *ctx) = 0;
  virtual void exitDotExpr(MxParser::DotExprContext *ctx) = 0;

  virtual void enterArrayExpr(MxParser::ArrayExprContext *ctx) = 0;
  virtual void exitArrayExpr(MxParser::ArrayExprContext *ctx) = 0;

  virtual void enterBinaryExpr(MxParser::BinaryExprContext *ctx) = 0;
  virtual void exitBinaryExpr(MxParser::BinaryExprContext *ctx) = 0;

  virtual void enterFuncCallExpr(MxParser::FuncCallExprContext *ctx) = 0;
  virtual void exitFuncCallExpr(MxParser::FuncCallExprContext *ctx) = 0;

  virtual void enterParenExpr(MxParser::ParenExprContext *ctx) = 0;
  virtual void exitParenExpr(MxParser::ParenExprContext *ctx) = 0;

  virtual void enterIndexExpr(MxParser::IndexExprContext *ctx) = 0;
  virtual void exitIndexExpr(MxParser::IndexExprContext *ctx) = 0;

  virtual void enterUnaryExpr(MxParser::UnaryExprContext *ctx) = 0;
  virtual void exitUnaryExpr(MxParser::UnaryExprContext *ctx) = 0;

  virtual void enterTernaryExpr(MxParser::TernaryExprContext *ctx) = 0;
  virtual void exitTernaryExpr(MxParser::TernaryExprContext *ctx) = 0;

  virtual void enterLiteralExpr(MxParser::LiteralExprContext *ctx) = 0;
  virtual void exitLiteralExpr(MxParser::LiteralExprContext *ctx) = 0;

  virtual void enterInitArrayExpr(MxParser::InitArrayExprContext *ctx) = 0;
  virtual void exitInitArrayExpr(MxParser::InitArrayExprContext *ctx) = 0;

  virtual void enterFormatStringExpr(MxParser::FormatStringExprContext *ctx) = 0;
  virtual void exitFormatStringExpr(MxParser::FormatStringExprContext *ctx) = 0;

  virtual void enterIdExpr(MxParser::IdExprContext *ctx) = 0;
  virtual void exitIdExpr(MxParser::IdExprContext *ctx) = 0;

  virtual void enterFormatString(MxParser::FormatStringContext *ctx) = 0;
  virtual void exitFormatString(MxParser::FormatStringContext *ctx) = 0;

  virtual void enterFuncCall(MxParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(MxParser::FuncCallContext *ctx) = 0;

  virtual void enterArrayConst(MxParser::ArrayConstContext *ctx) = 0;
  virtual void exitArrayConst(MxParser::ArrayConstContext *ctx) = 0;

  virtual void enterInitArray(MxParser::InitArrayContext *ctx) = 0;
  virtual void exitInitArray(MxParser::InitArrayContext *ctx) = 0;

  virtual void enterInitObject(MxParser::InitObjectContext *ctx) = 0;
  virtual void exitInitObject(MxParser::InitObjectContext *ctx) = 0;

  virtual void enterType(MxParser::TypeContext *ctx) = 0;
  virtual void exitType(MxParser::TypeContext *ctx) = 0;


};

