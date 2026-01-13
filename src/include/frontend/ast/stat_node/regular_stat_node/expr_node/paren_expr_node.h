//
// Created by zhang-kai on 7/17/25.
//

#pragma once
#include "expr_node.h"

class ParenExprNode : public ExprNode, public std::enable_shared_from_this<ParenExprNode> {
public:
  explicit ParenExprNode(std::shared_ptr<ExprNode> expr, Position position) : expr_(std::move(expr)), ExprNode(position) {
  }

  std::shared_ptr<ExprNode> getInnerExpr() const { return expr_; }
  void accept(VisitControl* visitor) override { visitor->visit(shared_from_this()); }

private:
  std::shared_ptr<ExprNode> expr_;
};
