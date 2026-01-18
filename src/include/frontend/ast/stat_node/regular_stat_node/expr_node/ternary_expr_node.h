//
// Created by zhang-kai on 6/16/25.
//

#pragma once
#include "expr_node.h"

class TernaryExprNode : public ExprNode, public std::enable_shared_from_this<TernaryExprNode> {
public:
  TernaryExprNode() = delete;
  TernaryExprNode(std::shared_ptr<ExprNode> predicate_node, std::shared_ptr<ExprNode> then_expr_node, std::shared_ptr<ExprNode> else_expr_node, Position position) :
  predicate_node(std::move(predicate_node)), then_expr_node(std::move(then_expr_node)), else_expr_node(std::move(else_expr_node)), ExprNode(position) {}
  std::shared_ptr<ExprNode> getPredicateNode() { return predicate_node; }
  std::shared_ptr<ExprNode> getThenExprNode() { return then_expr_node; }
  std::shared_ptr<ExprNode> getElseExprNode() { return else_expr_node; }
  void accept(VisitControl* visitor) override {
    visitor->visit(shared_from_this());
  }
  void AddPreAllocatedReg(std::shared_ptr<Register> reg) {
    pre_allocated_reg.emplace_back(reg);
  }

  std::shared_ptr<Register> GetPreAllocatedReg() {
    return pre_allocated_reg[pre_alloc_reg_counter++];
  }
private:
  std::shared_ptr<ExprNode> predicate_node;
  std::shared_ptr<ExprNode> then_expr_node;
  std::shared_ptr<ExprNode> else_expr_node;
  std::vector<std::shared_ptr<Register>> pre_allocated_reg;
  int pre_alloc_reg_counter = 0;
};
