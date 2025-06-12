//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class TypeNode;

class InitArrayNode : public ExprNode {
private:
    std::vector<std::shared_ptr<ExprNode>> range_node;
    std::shared_ptr<TypeNode> type_node;
public:
    InitArrayNode() = delete;
    InitArrayNode(std::shared_ptr<TypeNode> type_node, std::vector<std::shared_ptr<ExprNode>> range_node, Position position)
        :  type_node(std::move(type_node)),range_node(std::move(range_node)), ExprNode(position) {}
};
