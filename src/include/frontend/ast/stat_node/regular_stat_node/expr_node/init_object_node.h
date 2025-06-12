//
// Created by zhang-kai on 6/12/25.
//

#pragma once
#include "expr_node.h"

class TypeNode;

class InitObjectNode : public ExprNode {
private:
    std::shared_ptr<TypeNode> type_node;
public:
    InitObjectNode() = delete;
    InitObjectNode(std::shared_ptr<TypeNode> type_node, Position position) : type_node(std::move(type_node)), ExprNode(position) {}
};
