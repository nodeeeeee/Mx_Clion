//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class RegularStatNode;
class ExprNode;

class WhileStatNode : public StatNode {

public:
    WhileStatNode() = delete;
    WhileStatNode(std::shared_ptr<ExprNode> while_cond_expr_node, std::shared_ptr<BlockNode> block_node, Position position) : while_cond_expr_node(std::move(while_cond_expr_node)), block_node(std::move(block_node)), StatNode(position) {}
    [[nodiscard]] const std::shared_ptr<ExprNode> &getWhileCondExprNode() {return while_cond_expr_node;}
    [[nodiscard]] const std::shared_ptr<BlockNode> &getBlockNode() const {return block_node;}
    void accept(VisitControl *visitor) {visitor->visit(this);}

private:
    std::shared_ptr<ExprNode> while_cond_expr_node;
    std::shared_ptr<BlockNode> block_node;
};
