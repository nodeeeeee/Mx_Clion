//
// Created by zhang-kai on 6/28/25.
//

#pragma once
#include "expr_node.h"

class ThisExprNode : public ExprNode {
public:
  explicit ThisExprNode(Position position) : ExprNode(position) {}
};
