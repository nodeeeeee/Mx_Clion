//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "expr_node.h"

class UnaryExprNode : public ExprNode {
public:
    enum class UnaryOp : int {
        kPRE_PP, kPRE_MM, kPOST_PP, kPOST_MM, kWAVE, kEXCLAIMER, kADD, kSUB
    };
    UnaryExprNode() = delete;
    UnaryExprNode(UnaryOp op, std::shared_ptr<ExprNode> expr, Position position) : op(std::move(op)), expr(std::move(expr)), ExprNode(position) {}
    const UnaryOp &getOp() {return op;}
    const std::shared_ptr<ExprNode> &getExpr() {return expr;}
    void accept(VisitControl *visitor) {visitor->visit(this);}

private:
    UnaryOp op;
    std::shared_ptr<ExprNode> expr;
};
