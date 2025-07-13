
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "MxVisitor.h"


/**
 * This class provides an empty implementation of MxVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MxBaseVisitor : public MxVisitor {
public:

  virtual std::any visitProg(MxParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMainFunc(MxParser::MainFuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStat(MxParser::StatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSpecialStat(MxParser::SpecialStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprstat(MxParser::ExprstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVardefstat(MxParser::VardefstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfstat(MxParser::IfstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignstat(MxParser::AssignstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockstat(MxParser::BlockstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForstat(MxParser::ForstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhilestat(MxParser::WhilestatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnstat(MxParser::ReturnstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinuestat(MxParser::ContinuestatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakstat(MxParser::BreakstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullstat(MxParser::NullstatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(MxParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(MxParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassFuncDef(MxParser::ClassFuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassDef(MxParser::ClassDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStat(MxParser::IfStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStat(MxParser::AssignStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(MxParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStat(MxParser::ForStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStat(MxParser::WhileStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStat(MxParser::ReturnStatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinue(MxParser::ContinueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreak(MxParser::BreakContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitObjectExpr(MxParser::InitObjectExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThisExpr(MxParser::ThisExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDotExpr(MxParser::DotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayExpr(MxParser::ArrayExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBinaryExpr(MxParser::BinaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCallExpr(MxParser::FuncCallExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(MxParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexExpr(MxParser::IndexExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(MxParser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTernaryExpr(MxParser::TernaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpr(MxParser::LiteralExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitArrayExpr(MxParser::InitArrayExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormatStringExpr(MxParser::FormatStringExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdExpr(MxParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFormatString(MxParser::FormatStringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCall(MxParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayConst(MxParser::ArrayConstContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitArray(MxParser::InitArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitObject(MxParser::InitObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(MxParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(MxParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

