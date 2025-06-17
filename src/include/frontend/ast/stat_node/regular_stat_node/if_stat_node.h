//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "regular_stat_node.h"
#include "frontend/ast_builder.h"
#include "expr_node/expr_node.h"

class IfStatNode : public RegularStatNode {

public:
    IfStatNode() = delete;
    IfStatNode(std::shared_ptr<ExprNode> predicate, std::shared_ptr<BlockNode> then_block, std::shared_ptr<BlockNode> else_block, Position position)
        : predicate(std::move(predicate)), then_block(std::move(then_block)), else_block(std::move(else_block)), RegularStatNode(position) {};
    IfStatNode(std::shared_ptr<ExprNode> predicate, std::shared_ptr<BlockNode> then_block, Position position)
        : predicate(std::move(predicate)), then_block(std::move(then_block)), RegularStatNode(position) {}
    const std::shared_ptr<ExprNode> &getPredicate() {return predicate;}
    const std::shared_ptr<BlockNode> &getThenBlock() {return then_block;}
    const std::shared_ptr<BlockNode> &getElseBlock() {return else_block;}
private:
    std::shared_ptr<ExprNode> predicate;
    std::shared_ptr<BlockNode> then_block;
    std::shared_ptr<BlockNode> else_block = nullptr;
};
