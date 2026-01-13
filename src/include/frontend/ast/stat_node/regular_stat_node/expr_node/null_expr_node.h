//
// Created by zhang-kai on 6/11/25.
//
#pragma once
#include "expr_node.h"

class NullExprNode : public ExprNode, public std::enable_shared_from_this<NullExprNode> {
/** used as an helper signal that marks nothing is involved in the expression
 */
public:
    NullExprNode() = delete;
    NullExprNode(Position position) : ExprNode(position) {}
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}

};
