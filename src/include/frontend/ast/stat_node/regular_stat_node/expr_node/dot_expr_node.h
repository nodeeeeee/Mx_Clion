//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class DotExprNode : public ExprNode {
private:
    std::shared_ptr<ExprNode> lhs_expr;
    std::shared_ptr<ExprNode> rhs;
public:
    DotExprNode() = delete;
    DotExprNode(std::shared_ptr<ExprNode> lhs_expr, std::shared_ptr<ExprNode> rhs, Position position) : lhs_expr(std::move(lhs_expr)), rhs(std::move(rhs)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
