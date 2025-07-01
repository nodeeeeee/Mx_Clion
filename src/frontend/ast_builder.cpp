//
// Created by zhang-kai on 6/5/25.
// I will not trace the parent node in the construction phase due to heavy workload. I will traverse the tree once to record them later.
#include "frontend/ast_builder.h"

#include <format>

#include "frontend/ast/root_node.h"
#include <variant>
#include <ranges>
#include "frontend/ast/all_ast_nodes.h"
#include "frontend/ast/ASTNode.h"
#include "parser/MxParser.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/binary_expr_node.h"
// #include "../include/frontend/ast/def_node/main_func_node.h"
// #include "frontend/ast/def_node/func_def_node.h"
// #include "frontend/ast/def_node/var_def_node.h"
// #include "frontend/ast/def_node/class_def_node.h"
// #include "frontend/ast/def_node/class_func_def_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/assign_stat_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/block_node.h"
// #include "../include/frontend/ast/stat_node/regular_stat_node/expr_node/format_string_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/for_stat_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/unary_expr_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/if_stat_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/return_stat_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/while_stat_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/array_const_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/dot_expr_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/func_call_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/index_expr_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/init_array_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/init_object_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/null_expr_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/ternary_expr_node.h"
// #include "../include/frontend/ast/stat_node/regular_stat_node/expr_node/id_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/this_expr_node.h"
// #include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"
// #include "frontend/ast/terminal_node/terminal_node.h"


std::any ASTBuilder::visitProg(MxParser::ProgContext* ctx) {
  std::vector<std::shared_ptr<DefNode>> def_nodes;
  for (const auto& var_def_context : ctx->varDef()) {
    auto ret = std::any_cast<std::vector<std::shared_ptr<DefNode>>>(var_def_context->accept(this));
    for (const auto& ret_vardef : ret) {
      def_nodes.push_back(ret_vardef);
    }
  }
  for (const auto& func_def_context : ctx->funcDef()) {
    auto ret = std::any_cast<std::shared_ptr<FuncDefNode>>(func_def_context->accept(this));
    def_nodes.push_back(ret);
  }
  for (const auto& class_def_context : ctx->classDef()) {
    auto ret = std::any_cast<std::shared_ptr<ClassDefNode>>(class_def_context->accept(this));
    def_nodes.push_back(ret);
  }
  auto main_node = std::any_cast<std::shared_ptr<MainFuncNode>>(
    ctx->mainFunc()->accept(this));
  //MainDefNode \in FuncDefNode \in DefNode
  def_nodes.push_back(main_node);
  return std::make_shared<RootNode>(std::move(def_nodes), Position(ctx));
}

std::any ASTBuilder::visitVarDef(MxParser::VarDefContext* ctx) {
  /* since one vardef can be split into multiple, we will return back vector<VarDefNode>
   */
  auto type = std::make_shared<TypeType>(ctx->type());
  //pruning type node, we don't need it.
  std::vector<std::shared_ptr<VarDefNode>> var_defs;
  auto exprs = ctx->expr();
  // auto exprs = std::any_cast<std::vector<std::shared_ptr<MxParser::ExprContext>>>(ctx->expr());

  int expr_cnt = 0;
  for (const auto& varId : ctx->ID()) {
    if (expr_cnt < exprs.size() && varId->getSourceInterval().b + 2 == exprs.at(expr_cnt)->getSourceInterval().a) {
      auto id_node = std::make_shared<IdNode>(std::move(type), varId);
      auto ret = std::any_cast<std::shared_ptr<ExprNode>>(exprs[expr_cnt]->accept(this));
      var_defs.push_back(std::make_shared<VarDefNode>(std::move(id_node), Position(ctx),
                                                      std::move(ret)));
    } else {
      auto id_node = std::make_shared<IdNode>(std::move(type), varId);
      var_defs.push_back(std::make_shared<VarDefNode>(std::move(id_node), Position(ctx)));
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
  auto varIds = std::any_cast<std::vector<antlr4::tree::TerminalNode*>>(ctx->ID());
  auto return_type = std::make_shared<TypeType>(type_names.front());
  //when visitType, we return string
  int varId_cnt = 1;
  for (const auto& type_name : type_names | std::views::drop(1)) {
    auto type = std::make_shared<TypeType>(type_name);
    auto id_node = std::make_shared<IdNode>(std::move(type), varIds.at(varId_cnt++));
    var_defs.push_back(std::make_shared<VarDefNode>(id_node,
                                                    Position(ctx)));
  }
  auto return_id_node = std::make_shared<IdNode>(std::move(return_type), varIds.at(0));
  auto func_block = std::any_cast<std::shared_ptr<BlockNode>>(ctx->block()->accept(this));
  return std::make_shared<FuncDefNode>(std::move(return_id_node), std::move(var_defs),
                                       std::move(func_block), Position(ctx));
}

std::any ASTBuilder::visitClassDef(MxParser::ClassDefContext* ctx) {
  auto ID = std::make_shared<IdNode>(ctx->ID()->getSymbol()->getText(), Position(ctx));
  std::vector<std::shared_ptr<StatNode>> def_nodes;
  for (const auto& var_def_context : ctx->varDef()) {
    auto ret = std::any_cast<std::vector<std::shared_ptr<VarDefNode>>>(var_def_context->accept(this));
    for (const auto& ret_vardef : ret) {
      def_nodes.push_back(ret_vardef);
    }
  }
  for (const auto& func_def_context : ctx->funcDef()) {
    auto ret = std::any_cast<std::shared_ptr<FuncDefNode>>(func_def_context->accept(this));
    def_nodes.push_back(ret);
  }
  for (const auto& class_def_context : ctx->classDef()) {
    auto ret = std::any_cast<std::shared_ptr<ClassDefNode>>(class_def_context->accept(this));
    def_nodes.push_back(ret);
  }
  for (const auto& class_func_def_context : ctx->classFuncDef()) {
    auto ret = std::any_cast<std::shared_ptr<ClassFuncDefNode>>(class_func_def_context->accept(this));
    def_nodes.push_back(ret);
  }
  auto block_node = std::make_shared<BlockNode>(def_nodes, Position(ctx));
  return std::make_shared<ClassDefNode>(std::move(block_node), std::move(ID), Position(ctx));
}

std::any ASTBuilder::visitMainFunc(MxParser::MainFuncContext* ctx) {
  auto block_node = std::any_cast<std::shared_ptr<BlockNode>>(ctx->block()->accept(this));
  return std::make_shared<MainFuncNode>(block_node, Position(ctx));
}

std::any ASTBuilder::visitBinaryExpr(MxParser::BinaryExprContext* ctx) {
  auto expr_nodes = std::any_cast<std::vector<std::shared_ptr<
    ExprNode>>>(ctx->expr());
  std::shared_ptr<ExprNode> lhs = expr_nodes.at(0);
  std::shared_ptr<ExprNode> rhs = expr_nodes.at(1);
  BinaryExprNode::BinaryOp op;
  if (ctx->MUL()) {
    op = BinaryExprNode::BinaryOp::kMUL;
  } else if (ctx->DIV()) {
    op = BinaryExprNode::BinaryOp::kDIV;
  } else if (ctx->MOD()) {
    op = BinaryExprNode::BinaryOp::kMOD;
  } else if (ctx->ADD()) {
    op = BinaryExprNode::BinaryOp::kADD;
  } else if (ctx->SUB()) {
    op = BinaryExprNode::BinaryOp::kSUB;
  } else if (ctx->SRL()) {
    op = BinaryExprNode::BinaryOp::kSRL;
  } else if (ctx->SLL()) {
    op = BinaryExprNode::BinaryOp::kSLL;
  } else if (ctx->BT()) {
    op = BinaryExprNode::BinaryOp::kBT;
  } else if (ctx->LT()) {
    op = BinaryExprNode::BinaryOp::kLT;
  } else if (ctx->BEQ()) {
    op = BinaryExprNode::BinaryOp::kBEQ;
  } else if (ctx->LEQ()) {
    op = BinaryExprNode::BinaryOp::kLEQ;
  } else if (ctx->ET()) {
    op = BinaryExprNode::BinaryOp::kET;
  } else if (ctx->NET()) {
    op = BinaryExprNode::BinaryOp::kNET;
  } else if (ctx->AND()) {
    op = BinaryExprNode::BinaryOp::kAND;
  } else if (ctx->XOR()) {
    op = BinaryExprNode::BinaryOp::kXOR;
  } else if (ctx->OR()) {
    op = BinaryExprNode::BinaryOp::kOR;
  } else if (ctx->AND_AND()) {
    op = BinaryExprNode::BinaryOp::kAND_AND;
  } else if (ctx->OR_OR()) {
    op = BinaryExprNode::BinaryOp::kOR_OR;
  }
  return std::shared_ptr<ExprNode>(new BinaryExprNode(op, std::move(lhs), std::move(rhs), Position(ctx)));
}

std::any ASTBuilder::visitUnaryExpr(MxParser::UnaryExprContext* ctx) {
  auto expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr()->accept(this));
  UnaryExprNode::UnaryOp op;
  if (ctx->PLUS_PLUS()) {
    if (ctx->PLUS_PLUS()->getSymbol()->getTokenIndex() < ctx->expr()->getStart()->getTokenIndex()) {
      op = UnaryExprNode::UnaryOp::kPRE_PP;
    } else {
      op = UnaryExprNode::UnaryOp::kPOST_PP;
    }
  } else if (ctx->MINUS_MINUS()) {
    if (ctx->MINUS_MINUS()->getSymbol()->getTokenIndex() < ctx->expr()->getStart()->getTokenIndex()) {
      op = UnaryExprNode::UnaryOp::kPRE_MM;
    } else {
      op = UnaryExprNode::UnaryOp::kPOST_MM;
    }
  } else if (ctx->WAVE()) {
    op = UnaryExprNode::UnaryOp::kWAVE;
  } else if (ctx->EXCLAIMER()) {
    op = UnaryExprNode::UnaryOp::kEXCLAIMER;
  } else if (ctx->ADD()) {
    op = UnaryExprNode::UnaryOp::kADD;
  } else if (ctx->SUB()) {
    op = UnaryExprNode::UnaryOp::kSUB;
  }
  return std::shared_ptr<ExprNode>(new UnaryExprNode(op, std::move(expr_node), Position(ctx)));
}

std::any ASTBuilder::visitIfStat(MxParser::IfStatContext* ctx) {
  auto predicate = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr()->accept(this));
  auto then_stat = std::any_cast<std::shared_ptr<StatNode>>(
    ctx->regularStat(0)->accept(this));
  std::shared_ptr<BlockNode> then_block;
  if (auto block_node = std::dynamic_pointer_cast<BlockNode>(then_stat)) {
    then_block = std::move(block_node);
  } else {
    then_block = std::make_shared<BlockNode>(then_stat, Position(ctx));
  }
  if (ctx->ELSE()) {
    auto else_stat = std::any_cast<std::shared_ptr<StatNode>>(
      ctx->regularStat(1)->accept(this));
    std::shared_ptr<BlockNode> else_block;
    if (auto block_node = std::dynamic_pointer_cast<BlockNode>(else_stat)) {
      else_block = std::move(block_node);
    } else {
      else_block = std::make_shared<BlockNode>(else_stat, Position(ctx));
    }
    return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_block), std::move(else_block),
                                        Position(ctx));
  } else {
    return std::make_shared<IfStatNode>(std::move(predicate), std::move(then_block), Position(ctx));
  }
}

std::any ASTBuilder::visitTernaryExpr(MxParser::TernaryExprContext* ctx) {
  auto predicate = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(this));
  auto then_expr = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(this));
  auto else_expr = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(2)->accept(this));
  return std::shared_ptr<ExprNode>(new TernaryExprNode(std::move(predicate), std::move(then_expr), std::move(else_expr),
                                           Position(ctx)));
}

std::any ASTBuilder::visitArrayConst(MxParser::ArrayConstContext* ctx) {
  if (ctx->LITERAL(0)) {
    auto elements = ctx->LITERAL();
    std::vector<std::shared_ptr<LiteralNode>> literals;
    for (const auto& element : elements) {
      literals.push_back(std::any_cast<std::shared_ptr<LiteralNode>>(visitLiteral(element->getSymbol())));
    }
    return std::shared_ptr<ExprNode>(new ArrayConstNode(std::move(literals), Position(ctx)));
  } else if (ctx->arrayConst(0)) {
    std::vector<std::shared_ptr<ArrayConstNode>> elements;
    for (const auto& element : ctx->arrayConst()) {
      elements.push_back(std::any_cast<std::shared_ptr<ArrayConstNode>>(element->accept(this)));
    }
    return std::shared_ptr<ExprNode>(new ArrayConstNode(std::move(elements), Position(ctx)));
  } else {
    return std::shared_ptr<ExprNode>(new ArrayConstNode(Position(ctx)));
  }
}

std::any ASTBuilder::visitDotExpr(MxParser::DotExprContext* ctx) {
  auto lhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(this));
  auto rhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(this));
  return std::shared_ptr<ExprNode>(new DotExprNode(lhs, rhs, Position(ctx)));
}

std::any ASTBuilder::visitLiteralExpr(MxParser::LiteralExprContext* ctx) {
  return visitLiteral(ctx->LITERAL()->getSymbol());
}

std::any ASTBuilder::visitInitArray(MxParser::InitArrayContext* ctx) {
  std::shared_ptr<TypeType> type = std::make_shared<TypeType>(ctx->type());
  std::vector<std::shared_ptr<ExprNode>> ranges;
  auto exprs = ctx->expr();
  size_t range_cnt = 0;
  for (const auto& square_bracket : ctx->LEFT_SQUARE_BRACKET()) {
    if (square_bracket->getSourceInterval().a + 1 == exprs.at(range_cnt)->getSourceInterval().a) {
      range_cnt++;
      ranges.push_back(std::any_cast<std::shared_ptr<ExprNode>>(exprs.at(range_cnt)->accept(this)));
    } else {
      ranges.push_back(nullptr);
    }
  }

  if (ctx->arrayConst()) {
    auto default_array = std::any_cast<std::shared_ptr<ArrayConstNode>>(ctx->arrayConst()->accept(this));
    return std::shared_ptr<ExprNode>(new InitArrayNode(type, ranges, default_array, Position(ctx)));
  }
  return std::shared_ptr<ExprNode>(new InitArrayNode(type, ranges, Position(ctx)));
}

std::any ASTBuilder::visitIndexExpr(MxParser::IndexExprContext* ctx) {
  auto base = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(this));
  auto index = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(this));
  return std::shared_ptr<ExprNode>(new IndexExprNode(base, index, Position(ctx)));
}

std::any ASTBuilder:: visitLiteral(antlr4::Token* token) {
  return std::shared_ptr<ExprNode>(new LiteralNode(token));
}

std::any ASTBuilder::visitParenExpr(MxParser::ParenExprContext* ctx) {
  // I compressed the tree by deleting the ParenExprNode.
  if (ctx->expr()) {
    return std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr()->accept(this));
  } else {
    std::shared_ptr<ExprNode> ret = std::make_shared<NullExprNode>(Position(ctx));
    return ret;
  }
}

std::any ASTBuilder::visitClassFuncDef(MxParser::ClassFuncDefContext* ctx) {
  auto func_name = ctx->ID()->getSymbol()->getText();
  auto ID = std::make_shared<IdNode>(std::make_shared<TypeType>(TypeType::SpecialCode::NoType), ctx->ID());
  auto func_block = std::any_cast<std::shared_ptr<BlockNode>>(ctx->block()->accept(this));
  return std::make_shared<ClassFuncDefNode>(std::move(ID), std::move(func_block), Position(ctx));
}

std::any ASTBuilder::visitAssignStat(MxParser::AssignStatContext* ctx) {
  auto lhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(0)->accept(this));
  auto rhs = std::any_cast<std::shared_ptr<ExprNode>>(ctx->expr(1)->accept(this));
  return std::shared_ptr<StatNode>(new AssignStatNode(std::move(lhs), std::move(rhs), Position(ctx)));
}

std::any ASTBuilder::visitBlock(MxParser::BlockContext* ctx) {
  auto statements = ctx->stat();
  std::vector<std::shared_ptr<StatNode>> stat_nodes;
  for (const auto& statement : statements) {
    stat_nodes.push_back(std::any_cast<std::shared_ptr<StatNode>>(statement->accept(this)));
  }
  return std::make_shared<BlockNode>(std::move(stat_nodes), Position(ctx));
}

std::any ASTBuilder::visitForStat(MxParser::ForStatContext* ctx) {
  const auto initial_var_def = ctx->initialVarDef;
  const auto initial_assign_stat = ctx->initialAssignStat;
  const auto initial_expr = ctx->initialExpr;
  const auto update_assign_stat = ctx->updateAssignStat;
  const auto update_expr = ctx->updateExpr;

  auto for_cond_expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->forCondExpr->accept(this));
  auto initial_var_def_node = initial_var_def == nullptr
                                ? nullptr
                                : std::any_cast<std::shared_ptr<VarDefNode>>(ctx->varDef()->accept(this));
  auto update_assign_stat_node = update_assign_stat == nullptr
                                   ? nullptr
                                   : std::any_cast<std::shared_ptr<AssignStatNode>>(
                                     ctx->updateAssignStat->accept(this));
  auto update_expr_node = update_expr == nullptr
                            ? nullptr
                            : std::any_cast<std::shared_ptr<ExprNode>>(ctx->updateExpr->accept(this));
  auto initial_assign_stat_node = initial_assign_stat == nullptr
                                    ? nullptr
                                    : std::any_cast<std::shared_ptr<AssignStatNode>>(
                                      ctx->initialAssignStat->accept(this));
  auto initial_expr_node = initial_expr == nullptr
                             ? nullptr
                             : std::any_cast<std::shared_ptr<ExprNode>>(ctx->initialExpr->accept(this));
  auto regular_stat_node = std::any_cast<std::shared_ptr<StatNode>>(ctx->regularStat()->accept(this));
  std::shared_ptr<BlockNode> block;
  if (auto tmp_block = std::dynamic_pointer_cast<BlockNode>(regular_stat_node)) {
    block = tmp_block;
  } else {
    block = std::make_shared<BlockNode>(std::move(regular_stat_node), Position(ctx));
  }
  if (initial_var_def_node != nullptr) {
    if (update_assign_stat_node != nullptr) {
      return std::shared_ptr<StatNode>(new ForStatNode(initial_var_def_node, for_cond_expr_node, update_assign_stat_node,
                                           std::move(block), Position(ctx)));
    } else {
      return std::shared_ptr<StatNode>(new ForStatNode(initial_var_def_node, for_cond_expr_node, update_expr_node, std::move(block),
                                           Position(ctx)));
    }
  } else if (initial_assign_stat_node != nullptr) {
    if (update_assign_stat_node != nullptr) {
      return std::shared_ptr<StatNode>(new ForStatNode(initial_assign_stat_node, for_cond_expr_node, update_assign_stat_node,
                                           std::move(block), Position(ctx)));
    } else {
      return std::shared_ptr<StatNode>(new ForStatNode(initial_assign_stat_node, for_cond_expr_node, update_expr_node,
                                           std::move(block), Position(ctx)));
    }
  } else {
    if (update_assign_stat_node != nullptr) {
      return std::shared_ptr<StatNode>(new ForStatNode(initial_expr_node, for_cond_expr_node, update_assign_stat_node,
                                           std::move(block), Position(ctx)));
    } else {
      return std::shared_ptr<StatNode>(new ForStatNode(initial_expr_node, for_cond_expr_node, update_expr_node, std::move(block),
                                           Position(ctx)));
    }
  }
}

std::any ASTBuilder::visitWhileStat(MxParser::WhileStatContext* ctx) {
  auto while_cond_expr_node = std::any_cast<std::shared_ptr<ExprNode>>(ctx->whileCondExpr->accept(this));
  auto while_body_node = std::any_cast<std::shared_ptr<StatNode>>(ctx->regularStat()->accept(this));
  if (auto block = std::dynamic_pointer_cast<BlockNode>(while_body_node)) {
    return std::make_shared<WhileStatNode>(std::move(while_cond_expr_node), std::move(block), Position(ctx));
  } else {
    auto wrapped_block = std::make_shared<BlockNode>(std::move(while_body_node), Position(ctx));
    return std::shared_ptr<StatNode>(new WhileStatNode(std::move(while_cond_expr_node), std::move(wrapped_block), Position(ctx)));
  }
}

std::any ASTBuilder::visitReturnStat(MxParser::ReturnStatContext* ctx) {
  if (const auto return_expr = ctx->expr()) {
    auto return_tmp = return_expr->accept(this);
    auto return_expr_node = std::any_cast<std::shared_ptr<ExprNode>>(return_expr->accept(this));
    return std::shared_ptr<StatNode>(new ReturnStatNode(std::move(return_expr_node), Position(ctx)));
  } else if (const auto return_func_call = ctx->funcCall()) {
    auto return_func_call_node = std::any_cast<std::shared_ptr<FuncCallNode>>(return_func_call->accept(this));
    return std::shared_ptr<StatNode>(new ReturnStatNode(std::move(return_func_call_node), Position(ctx)));
  } else {
    return std::shared_ptr<StatNode>(new ReturnStatNode(Position(ctx)));
  }
}

std::any ASTBuilder::visitContinue(MxParser::ContinueContext* ctx) {
  return std::make_shared<TerminalNode>(TerminalNode::TerminalType::kCONTINUE, Position(ctx));
}

std::any ASTBuilder::visitBreak(MxParser::BreakContext* ctx) {
  return std::make_shared<TerminalNode>(TerminalNode::TerminalType::kBREAK, Position(ctx));
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
    exprs.push_back(std::any_cast<std::shared_ptr<ExprNode>>(element->accept(this)));
  }
  if (format_string_elements.at(0)->getSourceInterval().a < expr_elements.at(0)->getSourceInterval().a) {
    return std::shared_ptr<ExprNode>(new FormatStringNode(std::move(strings), std::move(exprs), true, Position(ctx)));
  } else {
    return std::shared_ptr<ExprNode>(new FormatStringNode(std::move(strings), std::move(exprs), false, Position(ctx)));
  }
}

std::any ASTBuilder::visitThisExpr(MxParser::ThisExprContext* ctx) {
  return std::shared_ptr<ExprNode>(new ThisExprNode(Position(ctx)));
}

std::any ASTBuilder::visitFuncCall(MxParser::FuncCallContext* ctx) {
  std::string func_name = ctx->ID()->getSymbol()->getText();
  std::vector<std::shared_ptr<ExprNode>> args;
  auto exprs = ctx->expr();
  for (auto expr : exprs) {
    args.push_back(std::any_cast<std::shared_ptr<ExprNode>>(expr->accept(this)));
  }
  return std::shared_ptr<ExprNode>(new FuncCallNode(std::move(func_name), args, Position(ctx)));
}

std::any ASTBuilder::visitInitObject(MxParser::InitObjectContext* ctx) {
  auto type_node = std::make_shared<TypeType>(ctx->type());
  return std::shared_ptr<ExprNode>(new InitObjectNode(std::move(type_node), Position(ctx)));
}

// std::any ASTBuilder::visitExprStat(MxParser::ExprContext *ctx) {
//   auto expr_node =
//   auto ret = ctx->accept(this);
//   return std::shared_ptr<StatNode>()
// }

std::any ASTBuilder::visitIdExpr(MxParser::IdExprContext* ctx) {
  return visitID(ctx->ID()->getSymbol());
}


std::any ASTBuilder::visitID(antlr4::Token* id) {
  auto id_node = id->getText();
  return std::shared_ptr<ExprNode>(new IdNode(std::move(id_node), Position(id)));
}
