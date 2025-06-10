//
// Created by zhang-kai on 6/6/25.
//
#pragma once
#include "ASTNode.h"
#include "def_node/def_node.h"

class RootNode : public ASTNode {
private:
    std::vector<std::shared_ptr<DefNode>> def_nodes;
    std::shared_ptr<MainNode> main_node;

public:
    RootNode() = delete;
    RootNode(std::vector<std::shared_ptr<DefNode>> def_nodes, const Position& position) : def_nodes(std::move(def_nodes)) {
        ASTNode(NULL, position);
    };

};
