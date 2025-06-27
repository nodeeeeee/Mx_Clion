//
// Created by zhang-kai on 6/11/25.
//
#pragma once
#include "expr_node.h"

class NullExprNode : public ExprNode {
/** used as an helper signal that marks nothing is involved in the expression
 */
public:
    NullExprNode() = delete;
    NullExprNode(Position position) : ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
