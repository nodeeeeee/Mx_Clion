//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "regular_stat_node.h"
#include "frontend/ast_builder.h"
#include "frontend/ast/expr_node/expr_node.h"

class IfStatNode : public RegularStatNode {
private:
    std::shared_ptr<ExprNode> predicate;
    std::shared_ptr<RegularStatNode> then_stat;
    std::shared_ptr<RegularStatNode> else_stat = nullptr;
public:
    IfStatNode() = delete;
    IfStatNode(std::shared_ptr<ExprNode> predicate, std::shared_ptr<RegularStatNode> then_stat, std::shared_ptr<RegularStatNode> else_stat, Position position)
        : predicate(std::move(predicate)), then_stat(std::move(then_stat)), else_stat(std::move(else_stat)), RegularStatNode(position) {};
    IfStatNode(std::shared_ptr<ExprNode> predicate, std::shared_ptr<RegularStatNode> then_stat, Position position)
        : predicate(std::move(predicate)), then_stat(std::move(then_stat)), else_stat(std::move(position)) {};
};
