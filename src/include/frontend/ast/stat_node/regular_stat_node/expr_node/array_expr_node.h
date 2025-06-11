//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class ArrayExprNode : public ExprNode {
private:
    std::vector<std::shared_ptr<LiteralNode>> literal_elements;
    std::vector<std::shared_ptr<ArrayExprNode>> array_elements;
public:
    ArrayExprNode() = delete;
    ArrayExprNode(std::vector<std::shared_ptr<ArrayExprNode>> array_elements, Position position) : array_elements(std::move(array_elements)), ExprNode(position) {}
    ArrayExprNode(std::vector<std::shared_ptr<LiteralNode>> literal_elements, Position position) : literal_elements(std::move(literal_elements)), ExprNode(position) {}
    explicit ArrayExprNode(Position position) : ExprNode(position) {}
};
