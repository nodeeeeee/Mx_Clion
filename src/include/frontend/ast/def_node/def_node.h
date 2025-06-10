//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/ASTNode.h"
class DefNode : public ASTNode {
private:
    std::string ID;
public:
    DefNode () = delete;
    explicit DefNode (std::string ID, Position pos) : ASTNode(pos), ID(std::move(ID)) {}
};