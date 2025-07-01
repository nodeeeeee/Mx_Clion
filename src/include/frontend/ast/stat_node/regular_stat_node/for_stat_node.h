//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class ExprNode;
class AssignStatNode;
class VarDefNode;

class ForStatNode : public StatNode, public std::enable_shared_from_this<ForStatNode> {
public:
    ForStatNode() = delete;
    ForStatNode(std::shared_ptr<VarDefNode> initial_var_def_node,std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<AssignStatNode> update_assign_stat_node, std::shared_ptr<BlockNode> block_node, Position position) : initial_var_def_nodes(std::move(initial_var_def_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_assign_stat_node(std::move(update_assign_stat_node)), block_node(std::move(block_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<AssignStatNode> initial_assign_stat_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<AssignStatNode> update_assign_stat_node, std::shared_ptr<BlockNode> block_node, Position position) : initial_assign_stat_node(std::move(initial_assign_stat_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_assign_stat_node(std::move(update_assign_stat_node)),block_node(std::move(block_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<ExprNode> initial_expr_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<AssignStatNode> update_assign_stat_node, std::shared_ptr<BlockNode> block_node, Position position) : initial_expr_node(std::move(initial_expr_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_assign_stat_node(std::move(update_assign_stat_node)), block_node(std::move(block_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<VarDefNode> initial_var_def_node,std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<ExprNode> update_expr_node, std::shared_ptr<BlockNode> block_node, Position position) : initial_var_def_nodes(std::move(initial_var_def_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_expr_node(std::move(update_expr_node)), block_node(std::move(block_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<AssignStatNode> initial_assign_stat_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<ExprNode> update_expr_node, std::shared_ptr<BlockNode> block_node, Position position) : initial_assign_stat_node(std::move(initial_assign_stat_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_expr_node(std::move(update_expr_node)), block_node(std::move(block_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<ExprNode> initial_expr_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<ExprNode> update_expr_node, std::shared_ptr<BlockNode> block_node, Position position) : initial_expr_node(std::move(initial_expr_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_expr_node(std::move(update_expr_node)), block_node(std::move(block_node)), StatNode(position) {}

    const std::shared_ptr<VarDefNode> &getInitialVarDefNode() {return initial_var_def_nodes;}
    const std::shared_ptr<AssignStatNode> &getUpdateAssignStatNode() {return update_assign_stat_node;}
    const std::shared_ptr<BlockNode> &getBlockNode() {return block_node;}
    const std::shared_ptr<ExprNode> &getForCondExprNode() {return for_cond_expr_node;}
    const std::shared_ptr<ExprNode> &getUpdateExprNode() {return update_expr_node;}
    const std::shared_ptr<ExprNode> &getInitialExprNode() {return initial_expr_node;}
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}

private:
    std::shared_ptr<VarDefNode> initial_var_def_nodes;
    std::shared_ptr<AssignStatNode> update_assign_stat_node;
    std::shared_ptr<ExprNode> update_expr_node;
    std::shared_ptr<AssignStatNode> initial_assign_stat_node;
    std::shared_ptr<ExprNode> initial_expr_node;
    std::shared_ptr<ExprNode> for_cond_expr_node;
    std::shared_ptr<BlockNode> block_node;
};
