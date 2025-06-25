//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "expr_node.h"

class BinaryExprNode : public ExprNode {

public:
    enum class BinaryOp : int {
        kMUL, kDIV, kMOD, kADD, kSUB,kSRL, kSLL, kBT, kLT, kBEQ, kLEQ, kET, kNET, kAND, kXOR, kOR, kAND_AND, kOR_OR
};
    BinaryExprNode() = delete;
    BinaryExprNode(BinaryOp op, std::shared_ptr<ExprNode> lhs, std::shared_ptr<ExprNode> rhs, Position position) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}
    std::shared_ptr<ExprNode> getLhs() {return lhs;}
    std::shared_ptr<ExprNode> getRhs() {return rhs;}
    // const ... = Div();
    BinaryOp getOp() {return op;}
private:
    BinaryOp op;
    std::shared_ptr<ExprNode> lhs;
    std::shared_ptr<ExprNode> rhs;
};

//开enum