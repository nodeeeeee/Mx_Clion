//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class DotExprNode : public ExprNode {
private:
    std::shared_ptr<ExprNode> lhs;
    std::shared_ptr<ExprNode> rhs;
public:
    DotExprNode() = delete;
    DotExprNode(std::shared_ptr<ExprNode> lhs, std::shared_ptr<ExprNode> rhs, Position position) : lhs(std::move(lhs)), rhs(std::move(rhs)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}
    std::shared_ptr<ExprNode> getLhs() {return lhs;}
    std::shared_ptr<ExprNode> getRhs() {return rhs;}
};
