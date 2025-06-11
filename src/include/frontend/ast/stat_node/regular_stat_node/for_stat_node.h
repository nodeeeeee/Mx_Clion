//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class ExprNode;
class AssignStatNode;
class VarDefNode;

class ForStatNode : public StatNode {
private:
    std::shared_ptr<VarDefNode> initial_var_def_nodes;
    std::shared_ptr<AssignStatNode> update_assign_stat_node;
    std::shared_ptr<ExprNode> update_expr_node;
    std::shared_ptr<AssignStatNode> initial_assign_stat_node;
    std::shared_ptr<ExprNode> initial_expr_node;
    std::shared_ptr<ExprNode> for_cond_expr_node;
    std::shared_ptr<RegularStatNode> regular_stat_node;
public:
    ForStatNode() = delete;
    ForStatNode(std::shared_ptr<VarDefNode> initial_var_def_node,std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<AssignStatNode> update_assign_stat_node, std::shared_ptr<RegularStatNode> regular_stat_node, Position position) : initial_var_def_nodes(std::move(initial_var_def_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_assign_stat_node(std::move(update_assign_stat_node)), regular_stat_node(std::move(regular_stat_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<AssignStatNode> initial_assign_stat_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<AssignStatNode> update_assign_stat_node, std::shared_ptr<RegularStatNode> regular_stat_node, Position position) : initial_assign_stat_node(std::move(initial_assign_stat_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_assign_stat_node(std::move(update_assign_stat_node)),regular_stat_node(std::move(regular_stat_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<ExprNode> initial_expr_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<AssignStatNode> update_assign_stat_node, std::shared_ptr<RegularStatNode> regular_stat_node, Position position) : initial_expr_node(std::move(initial_expr_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_assign_stat_node(std::move(update_assign_stat_node)), regular_stat_node(std::move(regular_stat_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<VarDefNode> initial_var_def_node,std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<ExprNode> update_expr_node, std::shared_ptr<RegularStatNode> regular_stat_node, Position position) : initial_var_def_nodes(std::move(initial_var_def_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_expr_node(std::move(update_expr_node)), regular_stat_node(std::move(regular_stat_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<AssignStatNode> initial_assign_stat_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<ExprNode> update_expr_node, std::shared_ptr<RegularStatNode> regular_stat_node, Position position) : initial_assign_stat_node(std::move(initial_assign_stat_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_expr_node(std::move(update_expr_node)), regular_stat_node(std::move(regular_stat_node)), StatNode(position) {}
    ForStatNode(std::shared_ptr<ExprNode> initial_expr_node, std::shared_ptr<ExprNode> for_cond_expr_node, std::shared_ptr<ExprNode> update_expr_node, std::shared_ptr<RegularStatNode> regular_stat_node, Position position) : initial_expr_node(std::move(initial_expr_node)), for_cond_expr_node(std::move(for_cond_expr_node)), update_expr_node(std::move(update_expr_node)), regular_stat_node(std::move(regular_stat_node)), StatNode(position) {}
};
