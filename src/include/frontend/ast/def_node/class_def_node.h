//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/def_node/def_node.h"

class ClassDefNode : public DefNode {
private:
    std::vector<std::shared_ptr<DefNode>> def_nodes;
public:
    ClassDefNode(std::vector<std::shared_ptr<DefNode>> def_nodes, std::shared_ptr<IdNode> ID, Position pos) : def_nodes(std::move(def_nodes)), DefNode(std::move(ID), pos) {}
};