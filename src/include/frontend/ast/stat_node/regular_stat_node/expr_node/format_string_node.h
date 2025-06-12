//
// Created by zhang-kai on 6/12/25.
//
#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class ExprNode;
class LiteralNode;

class FormatStringNode : public ExprNode {
private:
    std::vector<std::shared_ptr<LiteralNode>> literal_nodes;
    std::vector<std::shared_ptr<ExprNode>> expr_nodes;
    bool literal_first;
public:
    FormatStringNode() = delete;
    FormatStringNode(std::vector<std::shared_ptr<LiteralNode>> literal_nodes, std::vector<std::shared_ptr<ExprNode>> expr_nodes, bool literal_first, Position position)
        : literal_nodes(std::move(literal_nodes)), expr_nodes(std::move(expr_nodes)), literal_first(literal_first), ExprNode(position){}
};
