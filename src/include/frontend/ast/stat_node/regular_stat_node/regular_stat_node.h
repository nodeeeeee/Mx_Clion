//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/ASTNode.h"
#include "frontend/ast/stat_node/stat_node.h"

class RegularStatNode : public StatNode {
public:
    RegularStatNode() = delete;
    explicit RegularStatNode(Position position) : StatNode(position) {
    }
    virtual ~RegularStatNode() = default;
};
