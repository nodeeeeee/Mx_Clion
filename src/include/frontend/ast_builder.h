#pragma once
#include "parser/MxBaseVisitor.h"
#include "parser/MxParser.h"


class ASTBuilder : public MxBaseVisitor
{
    ASTBuilder ast_builder;
    std::any visitProg(MxParser::ProgContext *ctx) override;
    std::any visitMainFunc(MxParser::MainFuncContext *ctx) override;
    std::any visitStat(MxParser::StatContext *ctx) override;
    std::any visitSpecialStat(MxParser::SpecialStatContext *ctx) override;
    std::any visitRegularStat(MxParser::RegularStatContext *ctx) override;
    std::any visitVarDef(MxParser::VarDefContext *ctx) override;
    std::any visitFuncDef(MxParser::FuncDefContext *ctx) override;
    std::any visitClassFuncDef(MxParser::ClassDefContext *ctx) override;
    std::any visitClassDef(MxParser::ClassDefContext *ctx) override;
    std::any visitIfStat(MxParser::IfStatContext *ctx) override;
    std::any visitAssignStat(MxParser::ArrayConstContext *ctx) override;
    std::any visitBlock(MxParser::BlockContext *ctx) override;
    std::any visitForStat(MxParser::ForStatContext *ctx) override;
    std::any visitWhileStat(MxParser::WhileStatContext *ctx0) override;
    std::any visitReturnStat(MxParser::ReturnStatContext *ctx) override;
    std::any visitContinue(MxParser::ContinueContext *ctx) override;
    std::any visitBreak(MxParser::BreakContext *ctx) override;
    std::any visitUnaryExpr(MxParser::UnaryExprContext *ctx) override;
    std::any visitBinaryExpr(MxParser::BinaryExprContext *ctx) override;
    std::any visitTernaryExpr(MxParser::TernaryExprContext* context) override;
    std::any visitArrayExpr(MxParser::ArrayExprContext* context) override;
    std::any visitDotExpr(MxParser::DotExprContext* context) override;
    std::any visitLiteralExpr(MxParser::LiteralExprContext* ctx) override;
    std::any visitInitArrayExpr(MxParser::InitArrayExprContext* ctx) override;
    std::any visitFormatStringExpr(MxParser::FormatStringExprContext* ctx) override;
    std::any visitIdExpr(MxParser::IdExprContext* ctx) override;
    std::any visitParenExpr(MxParser::ParenExprContext* ctx) override;
    std::any visitThisExpr(MxParser::ThisExprContext* ctx) override;
    std::any visitFormatString(MxParser::FormatStringContext *ctx) override;
    std::any visitUpdate(MxParser::UpdateContext *ctx) override;
    std::any visitFuncCall(MxParser::FuncCallContext *ctx) override;
    std::any visitArrayConst(MxParser::ArrayConstContext *ctx) override;
    std::any visitInitArray(MxParser::IfStatContext *ctx) override;
    std::any visitInitObject(MxParser::StatContext *ctx) override;
    std::any visitTypeContext(MxParser::TypeContext *ctx) override;
};
