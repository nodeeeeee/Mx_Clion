//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "expr_node/expr_node.h"
#include "frontend/ast/stat_node/stat_node.h"

class AssignStatNode : public StatNode {
public:
    AssignStatNode() = delete;
    AssignStatNode(std::shared_ptr<ExprNode> lhs, std::shared_ptr<ExprNode> rhs, Position position) : lhs(std::move(lhs)), rhs(std::move(rhs)), StatNode(position) {}
    const std::shared_ptr<ExprNode> &getLhs() {return lhs;}
    const std::shared_ptr<ExprNode> &getRhs() {return rhs;}

private:
    std::shared_ptr<ExprNode> lhs;
    std::shared_ptr<ExprNode> rhs;
};
