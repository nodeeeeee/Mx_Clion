//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "expr_node.h"

class BinaryExprNode : public ExprNode {
private:
    std::string op;
    std::shared_ptr<ExprNode> lhs;
    std::shared_ptr<ExprNode> rhs;
public:
    BinaryExprNode() = delete;
    BinaryExprNode(std::string op, std::shared_ptr<ExprNode> lhs, std::shared_ptr<ExprNode> rhs, Position position) : op(std::move(op)), lhs(std::move(lhs)), rhs(std::move(rhs)), ExprNode(position) {}
};
