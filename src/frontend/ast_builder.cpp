//
// Created by zhang-kai on 6/5/25.
// I will not trace the parent node in the construction phase due to heavy workload. I will traverse the tree once to record them later.
#include "frontend/ast_builder.h"
#include "frontend/ast/root_node.h"
#include <variant>
#include <ranges>

#include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"
#include "frontend/ast/main_func_node.h"
#include "frontend/ast/def_node/func_def_node.h"
#include "frontend/ast/def_node/var_def_node.h"
#include "frontend/ast/def_node/class_def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h"
#include "frontend/ast/stat_node/regular_stat_node/if_stat_node.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/array_expr_node.h"


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
    std::shared_ptr<MainDefNode> main_node = std::any_cast<std::make_shared<MainDefNode>>(ctx->mainFunc()->accept(&ast_builder));
    //MainDefNode \in FuncDefNode \in DefNode
    def_nodes.push_back(main_node);
    return std::make_shared<RootNode> (std::move(def_nodes), Position(ctx));
}

std::any ASTBuilder::visitVarDef(MxParser::VarDefContext* ctx) {
    /* since one vardef can be split into multiple, we will return back vector<VarDefNode>
     */
    auto type_name = std::any_cast<std::string>(ctx->type()->accept(&ast_builder)); //pruning type node, we don't need it.
    std::vector<std::shared_ptr<VarDefNode>> var_defs;
    std::vector<std::shared_ptr<MxParser::ExprContext>> exprs = std::any_cast<std::vector<std::shared_ptr<MxParser::ExprContext>>>(ctx->expr());

    int expr_cnt = 0;
    for (const auto& varId : ctx->ID()) {
        if (varId->getSourceInterval().b + 2 == exprs.at(expr_cnt)->getSourceInterval().a) {
            auto ret = std::any_cast<std::shared_ptr<ExprNode>>(exprs[expr_cnt]->accept(&ast_builder));
            var_defs.push_back(std::make_shared<VarDefNode>(std::move(type_name), std::move(varId->getSymbol()->getText()), Position(ctx), std::move(ret)));
        } else {
            var_defs.push_back(std::make_shared<VarDefNode>(std::move(type_name), std::move(varId->getSymbol()->getText()), Position(ctx)));
        }
    }
    return var_defs;
}
std::any ASTBuilder::visitFuncDef(MxParser::FuncDefContext* ctx) {
    /* type, name
     * multiple var_def
     * block
     */
    std::vector<std::shared_ptr<VarDefNode*>> var_defs;
    auto type_names = std::any_cast<std::vector<MxParser::TypeContext*>>(ctx->type());
    auto varIds = std::any_cast<std::vector<std::shared_ptr<antlr4::tree::TerminalNode>>>(ctx->ID());
    auto return_type = std::any_cast<std::string>(type_names.front()->accept(&ast_builder));   //when visitType, we return string
    int varId_cnt = 1;
    for (const auto &type_name : type_names | std::views::drop(1)) {
        var_defs.push_back(std::make_shared<VarDefNode*>(std::move(type_name->accept(&ast_builder)), std::move(varIds.at(varId_cnt++)->getSymbol()->getText()), Position(ctx)));
    }
    std::string ID = varIds.at(0)->getSymbol()->getText();
    auto func_block = std::any_cast<std::make_shared<BlockNode>>(ctx -> block() -> accept(&ast_builder));
    return std::make_shared<FuncDefNode>(std::move(return_type), std::move(ID), std::move(var_defs), std::move(func_block), Position(ctx));
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
    for (const auto & class_func_def_context : ctx -> classFuncDef()) {
        auto ret = std::any_cast<std::shared_ptr<DefNode>>(class_func_def_context->accept(&ast_builder));
        def_nodes.push_back(ret);
    }
    return std::make_shared<ClassDefNode>(std::move(def_nodes), std::move(ID), Position(ctx));
}

std::any ASTBuilder::visitMainFunc(MxParser::MainFuncContext* ctx) {
    std::shared_ptr<BlockNode> block_node = ctx->block()->accept(&ast_builder);
    return std::make_shared<MainFuncNode>(block_node, Position(ctx));
}

std::any ASTBuilder::visitBinaryExpr(MxParser::BinaryExprContext* ctx) {
    std::vector<std::shared_ptr<ExprNode>> expr_nodes = std::any_cast<std::vector<std::shared_ptr<ExprNode>>>(ctx->expr());
    std::shared_ptr<ExprNode> lhs = expr_nodes.at(0);
    std::shared_ptr<ExprNode> rhs = expr_nodes.at(1);
    std::string op;
    if (ctx -> MUL()) {
        op = "mul";
    } else if (ctx -> DIV()) {
        op = "div";
    } else if (ctx -> MOD()) {
        op = "mod";
    } else if (ctx -> ADD()) {
        op = "add";
    } else if (ctx -> SUB()) {
        op = "sub";
    } else if (ctx -> SRL()) {
        op = "srl";
    } else if (ctx -> SLL()) {
        op = "sll";
    } else if (ctx -> BT()) {
        op = "bt";
    } else if (ctx -> LT()) {
        op = "lt";
    } else if (ctx -> BEQ()) {
        op = "beq";
    } else if (ctx -> LEQ()) {
        op = "leq";
    } else if (ctx -> ET()) {
        op = "et";
    } else if (ctx -> NET()) {
        op = "net";
    } else if (ctx -> AND()) {
        op = "and";
    } else if (ctx -> XOR()) {
        op = "xor";
    } else if (ctx -> OR()) {
        op = "or";
    } else if (ctx -> AND_AND()) {
        op = "and_and";
    } else if (ctx -> OR_OR()) {
        op = "or_or";
    }
    return std::make_shared<BinaryExprNode>(std::move(op), std::move(lhs), std::move(rhs), Position(ctx));
}
std::any ASTBuilder::visitUnaryExpr(MxParser::UnaryExprContext* ctx) {
    std::shared_ptr<ExprNode>expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr()->accept(&ast_builder));
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
    std::shared_ptr<RegularStatNode> then_stat = std::any_cast<std::shared_ptr<RegularStatNode>>(ctx->regularStat(0)->accept(&ast_builder));
    if (ctx->ELSE()) {
        std::shared_ptr<RegularStatNode> else_stat = std::any_cast<std::shared_ptr<RegularStatNode>>(ctx->regularStat(1)->accept(&ast_builder));
        return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_stat), std::move(else_stat), Position(ctx));
    } else {
        return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_stat), Position(ctx));
    }
}

std::any ASTBuilder::visitTernaryExpr(MxParser::TernaryExprContext* ctx) {
    std::shared_ptr<ExprNode> predicate = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(&ast_builder));
    std::shared_ptr<ExprNode> then_expr = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(&ast_builder));
    std::shared_ptr<ExprNode> else_expr = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(2)->accept(&ast_builder));
    return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_expr), std::move(else_expr), Position(ctx));
}

std::any ASTBuilder::visitArrayExpr(MxParser::ArrayExprContext* ctx) {
    if (ctx->arrayConst()->LITERAL(0)) {
        std::vector<antlr4::tree::TerminalNode> = ctx->arrayConst()->LITERAL();

        std::transform(ctx->arrayConst()->LITERAL());
        std::shared_ptr<LiteralNode> literals = std::any_cast<std::shared_ptr<LiteralNode>>(ctx->arrayConst()->LITERAL());
        std::make_shared<ArrayExprNode>(ctx->arrayConst()->LITERAL());
    } else if (ctx->arrayConst()->arrayConst(0)) {
        return std::make_shared<ArrayExprNode>(ctx->arrayConst()->accept())
    } else {
        return std::
    }
}

std::any ASTBuilder visitLiteral(antlr4::tree::TerminalNode) {

}