//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "frontend/ast/stat_node/stat_node.h"

class BlockNode : public StatNode {
private:
    std::vector<std::shared_ptr<StatNode>> stat_nodes;
public:
    BlockNode() = delete;
    BlockNode(std::vector<std::shared_ptr<StatNode>> stat_nodes, Position position) : stat_nodes(std::move(stat_nodes)), StatNode(position) {};
};