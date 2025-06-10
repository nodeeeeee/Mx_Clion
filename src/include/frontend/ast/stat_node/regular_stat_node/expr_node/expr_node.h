//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/stat_node/regular_stat_node/regular_stat_node.h"

class ExprNode : public RegularStatNode {
public:
    ExprNode() = delete;
    explicit ExprNode(Position position) : ASTNode(position) {}

};
