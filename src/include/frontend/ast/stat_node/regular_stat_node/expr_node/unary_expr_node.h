//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "expr_node.h"

class UnaryExprNode : public ExprNode {
public:
    enum class UnaryOp : int {
        kPLUS_PLUS, kMINUS_MINUS, kWAVE, kEXCLAIMER, kADD, kSUB
    };
    UnaryExprNode() = delete;
    UnaryExprNode(UnaryOp op, std::shared_ptr<ExprNode> expr, Position position) : op(std::move(op)), expr(std::move(expr)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}

private:

    std::shared_ptr<ExprNode> expr;
};
