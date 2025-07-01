
// Generated from Mx.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "MxParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MxParser.
 */
class  MxVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MxParser.
   */
    virtual std::any visitProg(MxParser::ProgContext *context) = 0;

    virtual std::any visitMainFunc(MxParser::MainFuncContext *context) = 0;

    virtual std::any visitStat(MxParser::StatContext *context) = 0;

    virtual std::any visitFuncdefstat(MxParser::FuncdefstatContext *context) = 0;

    virtual std::any visitClassfuncdefstat(MxParser::ClassfuncdefstatContext *context) = 0;

    virtual std::any visitClassdefstat(MxParser::ClassdefstatContext *context) = 0;

    virtual std::any visitExprstat(MxParser::ExprstatContext *context) = 0;

    virtual std::any visitVardefstat(MxParser::VardefstatContext *context) = 0;

    virtual std::any visitIfstat(MxParser::IfstatContext *context) = 0;

    virtual std::any visitAssignstat(MxParser::AssignstatContext *context) = 0;

    virtual std::any visitBlockstat(MxParser::BlockstatContext *context) = 0;

    virtual std::any visitForstat(MxParser::ForstatContext *context) = 0;

    virtual std::any visitWhilestat(MxParser::WhilestatContext *context) = 0;

    virtual std::any visitReturnstat(MxParser::ReturnstatContext *context) = 0;

    virtual std::any visitContinuestat(MxParser::ContinuestatContext *context) = 0;

    virtual std::any visitBreakstat(MxParser::BreakstatContext *context) = 0;

    virtual std::any visitNullstat(MxParser::NullstatContext *context) = 0;

    virtual std::any visitVarDef(MxParser::VarDefContext *context) = 0;

    virtual std::any visitFuncDef(MxParser::FuncDefContext *context) = 0;

    virtual std::any visitClassFuncDef(MxParser::ClassFuncDefContext *context) = 0;

    virtual std::any visitClassDef(MxParser::ClassDefContext *context) = 0;

    virtual std::any visitIfStat(MxParser::IfStatContext *context) = 0;

    virtual std::any visitAssignStat(MxParser::AssignStatContext *context) = 0;

    virtual std::any visitBlock(MxParser::BlockContext *context) = 0;

    virtual std::any visitForStat(MxParser::ForStatContext *context) = 0;

    virtual std::any visitWhileStat(MxParser::WhileStatContext *context) = 0;

    virtual std::any visitReturnStat(MxParser::ReturnStatContext *context) = 0;

    virtual std::any visitContinue(MxParser::ContinueContext *context) = 0;

    virtual std::any visitBreak(MxParser::BreakContext *context) = 0;

    virtual std::any visitInitObjectExpr(MxParser::InitObjectExprContext *context) = 0;

    virtual std::any visitThisExpr(MxParser::ThisExprContext *context) = 0;

    virtual std::any visitDotExpr(MxParser::DotExprContext *context) = 0;

    virtual std::any visitArrayExpr(MxParser::ArrayExprContext *context) = 0;

    virtual std::any visitBinaryExpr(MxParser::BinaryExprContext *context) = 0;

    virtual std::any visitFuncCallExpr(MxParser::FuncCallExprContext *context) = 0;

    virtual std::any visitParenExpr(MxParser::ParenExprContext *context) = 0;

    virtual std::any visitIndexExpr(MxParser::IndexExprContext *context) = 0;

    virtual std::any visitUnaryExpr(MxParser::UnaryExprContext *context) = 0;

    virtual std::any visitTernaryExpr(MxParser::TernaryExprContext *context) = 0;

    virtual std::any visitLiteralExpr(MxParser::LiteralExprContext *context) = 0;

    virtual std::any visitInitArrayExpr(MxParser::InitArrayExprContext *context) = 0;

    virtual std::any visitFormatStringExpr(MxParser::FormatStringExprContext *context) = 0;

    virtual std::any visitIdExpr(MxParser::IdExprContext *context) = 0;

    virtual std::any visitFormatString(MxParser::FormatStringContext *context) = 0;

    virtual std::any visitFuncCall(MxParser::FuncCallContext *context) = 0;

    virtual std::any visitArrayConst(MxParser::ArrayConstContext *context) = 0;

    virtual std::any visitInitArray(MxParser::InitArrayContext *context) = 0;

    virtual std::any visitInitObject(MxParser::InitObjectContext *context) = 0;

    virtual std::any visitType(MxParser::TypeContext *context) = 0;


};

