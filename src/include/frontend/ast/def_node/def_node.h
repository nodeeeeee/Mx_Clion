//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/ASTNode.h"
class IdNode;

class DefNode : public ASTNode {
private:
    std::shared_ptr<IdNode>id_node;
public:
    DefNode () = delete;
    explicit DefNode (std::shared_ptr<IdNode>id_node, Position pos) : ASTNode(pos), id_node(std::move(id_node)) {}
};
