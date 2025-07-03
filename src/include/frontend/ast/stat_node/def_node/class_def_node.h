//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "def_node.h"
#include "frontend/ast/visit_control.h"
// modify
class ClassDefNode : public DefNode, public std::enable_shared_from_this<ClassDefNode> {
private:
    std::shared_ptr<BlockNode> block_node;
public:
    const std::shared_ptr<BlockNode>& getBlockNode() { return block_node; }
    void accept(VisitControl *visitor) final {visitor->visit(shared_from_this());}
    ClassDefNode(std::shared_ptr<BlockNode>, std::shared_ptr<IdNode> ID, Position pos) : block_node(std::move(block_node)), DefNode(std::move(ID), DefNode::DefType::kClass, pos) {}
};