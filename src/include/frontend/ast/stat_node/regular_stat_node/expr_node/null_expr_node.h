//
// Created by zhang-kai on 6/11/25.
//
#pragma once
#include "expr_node.h"

class NullExprNode : public ExprNode {
public:
    NullExprNode() = delete;
    NullExprNode(Position position) : ExprNode(position) {}
};
