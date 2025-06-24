//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/visit_control.h"
#include "frontend/ast/def_node/def_node.h"

class BlockNode;

class ClassDefNode : public DefNode {
private:
    std::shared_ptr<BlockNode> block_node;
public:
    const std::shared_ptr<BlockNode>& GetBlockNode() { return block_node; }
    void accept(VisitControl *visitor) final {visitor->visit(this);}
    ClassDefNode(std::shared_ptr<BlockNode>, std::shared_ptr<IdNode> ID, Position pos) : block_node(std::move(block_node)), DefNode(std::move(ID), DefType::kClass, pos) {}
};
