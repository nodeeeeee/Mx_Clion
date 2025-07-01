//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class IndexExprNode : public ExprNode, public std::enable_shared_from_this<IndexExprNode> {
private:
    std::shared_ptr<ExprNode> index;
    std::shared_ptr<ExprNode> base;
public:
    IndexExprNode() = delete;
    IndexExprNode(std::shared_ptr<ExprNode> base, std::shared_ptr<ExprNode> index, Position position) : index(std::move(index)), base(std::move(base)), ExprNode(position) {}
    std::shared_ptr<ExprNode> getIndex() {return index;}
    std::shared_ptr<ExprNode> getBase() {return base;}
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}

};
