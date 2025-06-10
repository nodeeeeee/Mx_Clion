//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "expr_node.h"

class UnaryExprNode : public ExprNode {
private:
    std::string op;
    std::shared_ptr<ExprNode> expr;
public:
    UnaryExprNode() = delete;
    UnaryExprNode(std::string op, std::shared_ptr<ExprNode> expr, Position position) : op(std::move(op)), expr(std::move(expr)), ExprNode(position) {}
};
