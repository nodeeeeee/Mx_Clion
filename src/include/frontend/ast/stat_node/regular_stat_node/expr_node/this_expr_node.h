//
// Created by zhang-kai on 6/28/25.
//

#pragma once
#include "expr_node.h"

class ThisExprNode : public ExprNode, public std::enable_shared_from_this<ThisExprNode> {
public:
  explicit ThisExprNode(Position position) : ExprNode(position) {
  }

  void accept(VisitControl* visitor) override { visitor->visit(shared_from_this()); }
};
