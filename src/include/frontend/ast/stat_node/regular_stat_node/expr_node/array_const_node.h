//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class ArrayConstNode : public ExprNode {
private:
    std::vector<std::shared_ptr<LiteralNode>> literal_elements;
    std::vector<std::shared_ptr<ArrayConstNode>> array_elements;
public:
    ArrayConstNode() = delete;
    ArrayConstNode(std::vector<std::shared_ptr<ArrayConstNode>> array_elements, Position position) : array_elements(std::move(array_elements)), ExprNode(position) {}
    ArrayConstNode(std::vector<std::shared_ptr<LiteralNode>> literal_elements, Position position) : literal_elements(std::move(literal_elements)), ExprNode(position) {}
    explicit ArrayConstNode(Position position) : ExprNode(position) {}
};
