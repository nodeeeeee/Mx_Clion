//
// Created by zhang-kai on 6/16/25.
//

#pragma once
#include "expr_node.h"

class TernaryExprNode : public ExprNode {
public:
  TernaryExprNode() = delete;
  TernaryExprNode(std::shared_ptr<ExprNode> predicate_node, std::shared_ptr<ExprNode> then_expr_node, std::shared_ptr<ExprNode> else_expr_node, Position position) :
  predicate_node(std::move(predicate_node)), then_expr_node(std::move(then_expr_node)), else_expr_node(std::move(else_expr_node)), ExprNode(position) {}
  void accept(VisitControl *visitor) {visitor->visit(this);}

private:
  std::shared_ptr<ExprNode> predicate_node;
  std::shared_ptr<ExprNode> then_expr_node;
  std::shared_ptr<ExprNode> else_expr_node;
};
