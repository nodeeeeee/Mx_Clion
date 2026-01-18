//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "expr_node.h"

class BinaryExprNode : public ExprNode, public std::enable_shared_from_this<BinaryExprNode> {

public:
    enum class BinaryOp : int {
        kMUL, kDIV, kMOD, kADD, kSUB,kSRL, kSLL, kBT, kLT, kBEQ, kLEQ, kET, kNET, kAND, kXOR, kOR, kAND_AND, kOR_OR
};
    BinaryExprNode() = delete;
    BinaryExprNode(BinaryOp op, std::shared_ptr<ExprNode> lhs, std::shared_ptr<ExprNode> rhs, Position position) : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)), ExprNode(position) {}
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}
    std::shared_ptr<ExprNode> getLhs() {return lhs;}
    std::shared_ptr<ExprNode> getRhs() {return rhs;}
    // const ... = Div();
    BinaryOp getOp() {return op;}

    void AddPreAllocatedReg(std::shared_ptr<Register> reg) {
        pre_allocated_reg.emplace_back(reg);
    }

    std::shared_ptr<Register> GetPreAllocatedReg() {
        return pre_allocated_reg[pre_alloc_reg_counter++];
    }
private:
    BinaryOp op;
    std::shared_ptr<ExprNode> lhs;
    std::shared_ptr<ExprNode> rhs;
    std::vector<std::shared_ptr<Register>> pre_allocated_reg;
    int pre_alloc_reg_counter = 0;
};

//开enum