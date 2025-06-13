//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "def_node.h"

class ClassFuncDefNode : public DefNode {
private:
    std::shared_ptr<BlockNode> block_node;
public:
    ClassFuncDefNode() = delete;
    ClassFuncDefNode(std::shared_ptr<IdNode> ID, std::shared_ptr<BlockNode> block_node, Position position) : block_node(std::move(block_node)), DefNode(std::move(ID), position) {};
};
