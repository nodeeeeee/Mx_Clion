//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class IndexExprNode : public ExprNode {
private:
    std::vector<std::shared_ptr<ExprNode>> indices;
public:
    IndexExprNode() = delete;
    IndexExprNode(std::vector<std::shared_ptr<ExprNode>> indices, Position position) : indices(std::move(indices)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
