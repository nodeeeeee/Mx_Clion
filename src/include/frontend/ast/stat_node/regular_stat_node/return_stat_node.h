//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "regular_stat_node.h"
#include "frontend/ast/stat_node/stat_node.h"

class ExprNode;

class ReturnStatNode : public RegularStatNode {
private:
    std::shared_ptr<ExprNode> return_expr_node = nullptr;
    std::shared_ptr<FuncCallNode> return_func_call_node = nullptr;
public:
    ReturnStatNode() = delete;
    ReturnStatNode(std::shared_ptr<ExprNode> return_expr_node, Position position) : return_expr_node(std::move(return_expr_node)), RegularStatNode(position) {}
    ReturnStatNode(std::shared_ptr<FuncCallNode> return_func_call_node, Position position) : return_func_call_node(std::move(return_func_call_node)), RegularStatNode(position) {}
    explicit ReturnStatNode(Position position) : RegularStatNode(position) {}
};
