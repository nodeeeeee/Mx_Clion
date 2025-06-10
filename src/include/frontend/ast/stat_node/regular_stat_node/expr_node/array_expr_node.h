//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class ArrayExprNode : public ExprNode {
private:
    std::vector<std::shared_ptr<ExprNode>> elements;

public:
    ArrayExprNode() = delete;
    ArrayExprNode(std::vector<std::shared_ptr<ExprNode>> elements, Position position) : elements(std::move(elements)), ExprNode(position) {};
