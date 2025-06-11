//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class RegularStatNode;
class ExprNode;

class WhileStatNode : public StatNode {
private:
    std::shared_ptr<ExprNode> while_cond_expr_node;
    std::shared_ptr<RegularStatNode> while_body_node;
public:
    WhileStatNode() = delete;
    WhileStatNode(std::shared_ptr<ExprNode> while_cond_expr_node, std::shared_ptr<RegularStatNode> while_body_node, Position position) : while_cond_expr_node(std::move(while_cond_expr_node)), while_body_node(std::move(while_body_node)), StatNode(position) {}
};
