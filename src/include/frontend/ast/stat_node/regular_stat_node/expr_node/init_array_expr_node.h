//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class InitArrayExprNode : public ExprNode {
private:
    std::vector<std::shared_ptr<ExprNode>> range_node;
    std::shared_ptr<TypeNode> type_node;
public:
    InitArrayExprNode() = delete;
    InitArrayExprNode(std::vector<std::shared_ptr<ExprNode>> range_node,std::shared_ptr<TypeNode> type_node, Position position)
        : range_node(std::move(range_node)), type_node(std::move(type_node)), ExprNode(position) {}
};
