//
// Created by zhang-kai on 6/5/25.
// I will not trace the parent node in the construction phase due to heavy workload. I will traverse the tree once to record them later.
#include "frontend/ast_builder.h"

#include <format>

#include "frontend/ast/root_node.h"
#include <variant>
#include <ranges>

#include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"
#include "../include/frontend/ast/def_node/main_func_node.h"
#include "frontend/ast/def_node/func_def_node.h"
#include "frontend/ast/def_node/var_def_node.h"
#include "frontend/ast/def_node/class_def_node.h"
#include "frontend/ast/def_node/class_func_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/assign_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/block_node.h"
#include "../include/frontend/ast/stat_node/regular_stat_node/expr_node/format_string_node.h"
#include "frontend/ast/stat_node/regular_stat_node/for_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/if_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/return_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/while_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/array_const_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/dot_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/func_call_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/index_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/init_array_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/init_object_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/null_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/type_node.h"
#include "frontend/ast/terminal_node/id_node.h"
#include "frontend/ast/terminal_node/literal_node.h"


std::any ASTBuilder::visitProg(MxParser::ProgContext* ctx) {
    std::vector<std::shared_ptr<DefNode>> def_nodes;
    for (const auto& var_def_context : ctx->varDef()) {
        auto ret = std::any_cast<std::vector<std::shared_ptr<DefNode>>>(var_def_context->accept(&ast_builder));
        for (const auto& ret_vardef : ret) {
            def_nodes.push_back(ret_vardef);
        }
    }
    for (const auto& func_def_context : ctx->funcDef()) {
        auto ret = std::any_cast<std::shared_ptr<DefNode>>(func_def_context->accept(&ast_builder));
        def_nodes.push_back(ret);
    }
    for (const auto& class_def_context : ctx->classDef()) {
        auto ret = std::any_cast<std::shared_ptr<DefNode>>(class_def_context->accept(&ast_builder));
        def_nodes.push_back(ret);
    }
    std::shared_ptr<MainFuncNode> main_node = std::any_cast<std::shared_ptr<MainFuncNode>>(
        ctx->mainFunc()->accept(&ast_builder));
    //MainDefNode \in FuncDefNode \in DefNode
    def_nodes.push_back(main_node);
    return std::make_shared<RootNode>(std::move(def_nodes), Position(ctx));
}

std::any ASTBuilder::visitVarDef(MxParser::VarDefContext* ctx) {
    /* since one vardef can be split into multiple, we will return back vector<VarDefNode>
     */
    auto type_node = std::any_cast<std::shared_ptr<TypeNode>>(ctx->type()->accept(&ast_builder));
    //pruning type node, we don't need it.
    std::vector<std::shared_ptr<VarDefNode>> var_defs;
    std::vector<std::shared_ptr<MxParser::ExprContext>> exprs = std::any_cast<std::vector<std::shared_ptr<
        MxParser::ExprContext>>>(ctx->expr());

    int expr_cnt = 0;
    for (const auto& varId : ctx->ID()) {
        if (varId->getSourceInterval().b + 2 == exprs.at(expr_cnt)->getSourceInterval().a) {
            auto ret = std::any_cast<std::shared_ptr<ExprNode>>(exprs[expr_cnt]->accept(&ast_builder));
            var_defs.push_back(std::make_shared<VarDefNode>(std::move(type_node),
                                                            std::move(varId->getSymbol()->getText()), Position(ctx),
                                                            std::move(ret)));
        } else {
            var_defs.push_back(std::make_shared<VarDefNode>(std::move(type_node),
                                                            std::move(varId->getSymbol()->getText()), Position(ctx)));
        }
    }
    return var_defs;
}

std::any ASTBuilder::visitFuncDef(MxParser::FuncDefContext* ctx) {
    /* type, name
     * multiple var_def
     * block
     */
    std::vector<std::shared_ptr<VarDefNode>> var_defs;
    auto type_names = ctx->type();
    auto varIds = std::any_cast<std::vector<std::shared_ptr<antlr4::tree::TerminalNode>>>(ctx->ID());
    auto return_type = std::any_cast<std::string>(type_names.front()->accept(&ast_builder));
    //when visitType, we return string
    int varId_cnt = 1;
    for (const auto& type_name : type_names | std::views::drop(1)) {
        auto type_node = std::any_cast<std::shared_ptr<TypeNode>>(type_name->accept(&ast_builder));
        var_defs.push_back(std::make_shared<VarDefNode>(std::move(type_node),
                                                         std::move(varIds.at(varId_cnt++)->getSymbol()->getText()),
                                                         Position(ctx)));
    }
    std::string ID = varIds.at(0)->getSymbol()->getText();
    auto func_block = std::any_cast<std::shared_ptr<BlockNode>>(ctx->block()->accept(&ast_builder));
    return std::make_shared<FuncDefNode>(std::move(return_type), std::move(ID), std::move(var_defs),
                                         std::move(func_block), Position(ctx));
}

std::any ASTBuilder::visitClassDef(MxParser::ClassDefContext* ctx) {
    std::string ID = ctx->ID()->getSymbol()->getText();
    std::vector<std::shared_ptr<DefNode>> def_nodes;
    for (const auto& var_def_context : ctx->varDef()) {
        auto ret = std::any_cast<std::vector<std::shared_ptr<DefNode>>>(var_def_context->accept(&ast_builder));
        for (const auto& ret_vardef : ret) {
            def_nodes.push_back(ret_vardef);
        }
    }
    for (const auto& func_def_context : ctx->funcDef()) {
        auto ret = std::any_cast<std::shared_ptr<DefNode>>(func_def_context->accept(&ast_builder));
        def_nodes.push_back(ret);
    }
    for (const auto& class_def_context : ctx->classDef()) {
        auto ret = std::any_cast<std::shared_ptr<DefNode>>(class_def_context->accept(&ast_builder));
        def_nodes.push_back(ret);
    }
    for (const auto& class_func_def_context : ctx->classFuncDef()) {
        auto ret = std::any_cast<std::shared_ptr<DefNode>>(class_func_def_context->accept(&ast_builder));
        def_nodes.push_back(ret);
    }
    return std::make_shared<ClassDefNode>(std::move(def_nodes), std::move(ID), Position(ctx));
}

std::any ASTBuilder::visitMainFunc(MxParser::MainFuncContext* ctx) {
    auto block_node = std::any_cast<std::shared_ptr<BlockNode>>(ctx->block()->accept(&ast_builder));
    return std::make_shared<MainFuncNode>(block_node, Position(ctx));
}

std::any ASTBuilder::visitBinaryExpr(MxParser::BinaryExprContext* ctx) {
    std::vector<std::shared_ptr<ExprNode>> expr_nodes = std::any_cast<std::vector<std::shared_ptr<
        ExprNode>>>(ctx->expr());
    std::shared_ptr<ExprNode> lhs = expr_nodes.at(0);
    std::shared_ptr<ExprNode> rhs = expr_nodes.at(1);
    std::string op;
    if (ctx->MUL()) {
        op = "mul";
    } else if (ctx->DIV()) {
        op = "div";
    } else if (ctx->MOD()) {
        op = "mod";
    } else if (ctx->ADD()) {
        op = "add";
    } else if (ctx->SUB()) {
        op = "sub";
    } else if (ctx->SRL()) {
        op = "srl";
    } else if (ctx->SLL()) {
        op = "sll";
    } else if (ctx->BT()) {
        op = "bt";
    } else if (ctx->LT()) {
        op = "lt";
    } else if (ctx->BEQ()) {
        op = "beq";
    } else if (ctx->LEQ()) {
        op = "leq";
    } else if (ctx->ET()) {
        op = "et";
    } else if (ctx->NET()) {
        op = "net";
    } else if (ctx->AND()) {
        op = "and";
    } else if (ctx->XOR()) {
        op = "xor";
    } else if (ctx->OR()) {
        op = "or";
    } else if (ctx->AND_AND()) {
        op = "and_and";
    } else if (ctx->OR_OR()) {
        op = "or_or";
    }
    return std::make_shared<BinaryExprNode>(std::move(op), std::move(lhs), std::move(rhs), Position(ctx));
}

std::any ASTBuilder::visitUnaryExpr(MxParser::UnaryExprContext* ctx) {
    std::shared_ptr<ExprNode> expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr()->accept(&ast_builder));
    std::string op;
    if (ctx->PLUS_PLUS()) {
        op = "plus_plus";
    } else if (ctx->MINUS_MINUS()) {
        op = "minus_minus";
    } else if (ctx->WAVE()) {
        op = "wave";
    } else if (ctx->EXCLAIMER()) {
        op = "exclaimer";
    } else if (ctx->ADD()) {
        op = "add";
    } else if (ctx->SUB()) {
        op = "sub";
    }
    return std::make_shared<UnaryExprNode>(std::move(op), std::move(expr_node), Position(ctx));
}

std::any ASTBuilder::visitIfStat(MxParser::IfStatContext* ctx) {
    std::shared_ptr<ExprNode> predicate = std::any_cast<std::shared_ptr<ExprNode>>(ctx->ifExpr()->accept(&ast_builder));
    std::shared_ptr<RegularStatNode> then_stat = std::any_cast<std::shared_ptr<RegularStatNode>>(
        ctx->regularStat(0)->accept(&ast_builder));
    if (ctx->ELSE()) {
        std::shared_ptr<RegularStatNode> else_stat = std::any_cast<std::shared_ptr<RegularStatNode>>(
            ctx->regularStat(1)->accept(&ast_builder));
        return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_stat), std::move(else_stat),
                                            Position(ctx));
    } else {
        return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_stat), Position(ctx));
    }
}

std::any ASTBuilder::visitTernaryExpr(MxParser::TernaryExprContext* ctx) {
    std::shared_ptr<ExprNode> predicate = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(&ast_builder));
    std::shared_ptr<ExprNode> then_expr = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(&ast_builder));
    std::shared_ptr<ExprNode> else_expr = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(2)->accept(&ast_builder));
    return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_expr), std::move(else_expr),
                                        Position(ctx));
}

std::any ASTBuilder::visitArrayConst(MxParser::ArrayConstContext* ctx) {
    if (ctx->LITERAL(0)) {
        auto elements = ctx->LITERAL();
        std::vector<std::shared_ptr<LiteralNode>> literals;
        for (const auto& element : elements) {
            literals.push_back(std::any_cast<std::shared_ptr<LiteralNode>>(visitLiteral(element->getSymbol())));
        }
        return std::make_shared<ArrayConstNode>(std::move(literals), Position(ctx));
    } else if (ctx->arrayConst(0)) {
        std::vector<std::shared_ptr<ArrayConstNode>> elements;
        for (const auto& element : ctx->arrayConst()) {
            elements.push_back(std::any_cast<std::shared_ptr<ArrayConstNode>>(element->accept(&ast_builder)));
        }
        return std::make_shared<ArrayConstNode>(std::move(elements), Position(ctx));
    } else {
        return std::make_shared<ArrayConstNode>(Position(ctx));
    }
}

std::any ASTBuilder::visitDotExpr(MxParser::DotExprContext* ctx) {
    std::shared_ptr<ExprNode> lhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(&ast_builder));
    std::shared_ptr<ExprNode> rhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(&ast_builder));
    return std::make_shared<DotExprNode>(lhs, rhs, Position(ctx));
}

std::any ASTBuilder::visitLiteralExpr(MxParser::LiteralExprContext* ctx) {
    return visitLiteral(ctx->LITERAL()->getSymbol());
}

std::any ASTBuilder::visitInitArray(MxParser::InitArrayContext* ctx) {
    std::shared_ptr<TypeNode> type_node = std::any_cast<std::shared_ptr<TypeNode>>(
        ctx->type()->accept(&ast_builder));
    std::vector<std::shared_ptr<ExprNode>> ranges;
    auto exprs = ctx->expr();
    size_t range_cnt = 0;
    for (const auto& square_bracket : ctx->LEFT_SQUARE_BRACKET()) {
        if (square_bracket->getSourceInterval().a + 1 == exprs.at(range_cnt)->getSourceInterval().a) {
            range_cnt++;
            ranges.push_back(std::any_cast<std::shared_ptr<ExprNode>>(exprs.at(range_cnt)->accept(&ast_builder)));
        } else {
            ranges.push_back(nullptr);
        }
    }
    return std::make_shared<InitArrayNode>(type_node, ranges, Position(ctx));
}

std::any ASTBuilder::visitIndexExpr(MxParser::IndexExprContext* ctx) {
    std::vector<std::shared_ptr<ExprNode>> indices;
    for (const auto& expr_node : ctx->expr()) {
        indices.push_back(std::any_cast<std::shared_ptr<ExprNode>>(expr_node->accept(&ast_builder)));
    }
    return std::make_shared<IndexExprNode>(indices, Position(ctx));
}

std::any ASTBuilder::visitLiteral(antlr4::Token* token) {
    return std::make_shared<LiteralNode>(token);
}

std::any ASTBuilder::visitParenExpr(MxParser::ParenExprContext* ctx) {
    // I compressed the tree by deleting the ParenExprNode.
    if (ctx->expr()) {
        return std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr()->accept(&ast_builder));
    } else {
        std::shared_ptr<ExprNode> ret = std::make_shared<NullExprNode>(Position(ctx));
        return ret;
    }
}

std::any ASTBuilder::visitClassFuncDef(MxParser::ClassFuncDefContext* ctx) {
    std::string ID = ctx->ID()->getSymbol()->getText();
    auto func_block = std::any_cast<std::shared_ptr<BlockNode>>(ctx->block()->accept(&ast_builder));
    return std::make_shared<ClassFuncDefNode>(std::move(ID), std::move(func_block), Position(ctx));
}

std::any ASTBuilder::visitAssignStat(MxParser::AssignStatContext* ctx) {
    std::shared_ptr<ExprNode> lhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(&ast_builder));
    std::shared_ptr<ExprNode> rhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(&ast_builder));
    return std::make_shared<AssignStatNode>(std::move(lhs), std::move(rhs), Position(ctx));
}

std::any ASTBuilder::visitBlock(MxParser::BlockContext* ctx) {
    std::vector<std::shared_ptr<MxParser::StatContext>> statements = std::any_cast<std::vector<std::shared_ptr<MxParser::StatContext>>>(ctx->stat());
    std::vector<std::shared_ptr<StatNode>> stat_nodes;
    for (const auto& statement : statements) {
        stat_nodes.push_back(std::any_cast<std::shared_ptr<StatNode>>(statement->accept(&ast_builder)));
    }
    return std::make_shared<BlockNode>(std::move(stat_nodes), Position(ctx));
}

std::any ASTBuilder::visitForStat(MxParser::ForStatContext* ctx) {
    const auto initial_var_def = ctx->initialVarDef;
    const auto initial_assign_stat = ctx->initialAssignStat;
    const auto initial_expr = ctx->initialExpr;
    const auto update_assign_stat = ctx->updateAssignStat;
    const auto update_expr = ctx->updateExpr;

    auto for_cond_expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->forCondExpr->accept(&ast_builder));
    auto initial_var_def_node = initial_var_def == nullptr ? nullptr : std::any_cast<std::shared_ptr<VarDefNode>>(ctx->varDef()->accept(&ast_builder));
    auto update_assign_stat_node = update_assign_stat == nullptr ? nullptr : std::any_cast<std::shared_ptr<AssignStatNode>>(ctx->updateAssignStat->accept(&ast_builder));
    auto update_expr_node = update_expr == nullptr ? nullptr : std::any_cast<std::shared_ptr<ExprNode>>(ctx->updateExpr->accept(&ast_builder));
    auto initial_assign_stat_node = initial_assign_stat == nullptr ? nullptr : std::any_cast<std::shared_ptr<AssignStatNode>>(ctx->initialAssignStat->accept(&ast_builder));
    auto initial_expr_node = update_expr == nullptr ? nullptr : std::any_cast<std::shared_ptr<ExprNode>>(ctx->initialExpr->accept(&ast_builder));

    auto regular_stat_node = std::any_cast<std::shared_ptr<RegularStatNode>>(ctx->regularStat()->accept(&ast_builder));
    return std::make_shared<ForStatNode>(initial_var_def_node != nullptr ? std::move(initial_var_def_node) : initial_assign_stat_node == nullptr ? std::move(initial_assign_stat_node) : std::move(initial_expr_node),
                                            for_cond_expr_node,
                                            update_assign_stat_node != nullptr ? std::move(update_assign_stat_node) : std::move(update_expr_node),
                                            std::move(regular_stat_node), Position(ctx));
}

std::any ASTBuilder::visitWhileStat(MxParser::WhileStatContext* ctx) {
    auto while_cond_expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->whileCondExpr()->accept(&ast_builder));
    auto while_body_node = std::any_cast<std::shared_ptr<RegularStatNode>>(ctx->regularStat()->accept(&ast_builder));
    return std::make_shared<WhileStatNode>(std::move(while_cond_expr_node), std::move(while_body_node), Position(ctx));
}

std::any ASTBuilder::visitReturnStat(MxParser::ReturnStatContext* ctx) {
    if (const auto return_expr = ctx->expr()) {
        auto return_expr_node = std::any_cast<std::shared_ptr<ExprNode>>(return_expr->accept(&ast_builder));
        return std::make_shared<ReturnStatNode>(std::move(return_expr_node), Position(ctx));
    } else if (const auto return_func_call = ctx->funcCall()) {
        auto return_func_call_node = std::any_cast<std::shared_ptr<FuncCallNode>>(return_func_call->accept(&ast_builder));
        return std::make_shared<ReturnStatNode>(std::move(return_func_call_node), Position(ctx));
    } else {
        return std::make_shared<RegularStatNode>(Position(ctx));
    }

}

std::any ASTBuilder::visitContinue(MxParser::ContinueContext* ctx) {
    return std::make_shared<TerminalNode>("continue", Position(ctx));
}

std::any ASTBuilder::visitBreak(MxParser::BreakContext* ctx) {
    return std::make_shared<TerminalNode>("break", Position(ctx));
}

std::any ASTBuilder::visitFormatString(MxParser::FormatStringContext* ctx) {
    std::vector<std::shared_ptr<LiteralNode>> strings;
    std::vector<std::shared_ptr<ExprNode>> exprs;
    auto format_string_elements = ctx->FORMAT_STRING_ELEMENT();
    for (const auto& element : format_string_elements) {
        strings.push_back(std::any_cast<std::shared_ptr<LiteralNode>>(visitLiteral(element->getSymbol())));
    }
    auto expr_elements = ctx->expr();
    for (const auto& element : expr_elements) {
        exprs.push_back(std::any_cast<std::shared_ptr<ExprNode>>(element->accept(&ast_builder)));
    }
    if (format_string_elements.at(0)->getSourceInterval().a < expr_elements.at(0)->getSourceInterval().a) {
        return std::make_shared<FormatStringNode> (std::move(strings), std::move(exprs), true, Position(ctx));
    } else {
        return std::make_shared<FormatStringNode> (std::move(strings), std::move(exprs), false, Position(ctx));
    }
}

std::any ASTBuilder::visitThisExpr(MxParser::ThisExprContext* ctx) {
    return std::make_shared<TerminalNode>("this", Position(ctx));
}

std::any ASTBuilder::visitFuncCall(MxParser::FuncCallContext* ctx) {
    std::string func_name = ctx->ID()->getSymbol()->getText();
    return std::make_shared<FuncCallNode>(std::move(func_name), Position(ctx));
}

std::any ASTBuilder::visitInitObject(MxParser::InitObjectContext* ctx) {
    auto type_node = std::any_cast<std::shared_ptr<TypeNode>>(ctx->type()->accept(&ast_builder));
    return std::make_shared<InitObjectNode>(std::move(type_node), Position(ctx));
}

std::any ASTBuilder::visitType(MxParser::TypeContext* ctx) {
    if (ctx->INT()) {
        return std::make_shared<TypeNode>("int", Position(ctx));
    } else if (ctx->BOOLEAN()) {
        return std::make_shared<TypeNode>("bool", Position(ctx));
    } else if (ctx->STR()) {
        return std::make_shared<TypeNode>("string", Position(ctx));
    } else if (ctx->VOID()) {
        return std::make_shared<TypeNode>("void", Position(ctx));
    } else if (auto id_type = ctx->ID()) {
        return std::make_shared<TypeNode>(std::any_cast<std::shared_ptr<IdNode>>(ASTBuilder::visitID(id_type->getSymbol())), Position(ctx));
    } else {
        auto type_node = std::any_cast<std::shared_ptr<TypeNode>>(type_type->accept(&ast_builder));
        return std::make_shared<TypeNode>(std::move(type_node), Position(ctx));
    }
}

std::any ASTBuilder::visitID(antlr4::Token* id) {
    auto id_node = id->getText();
    return std::make_shared<IdNode>(std::move(id_node), Position(id));
}
