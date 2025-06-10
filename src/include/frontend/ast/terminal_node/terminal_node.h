//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "frontend/ast/ASTNode.h"

class TerminalNode : public ASTNode {
private:
    std::string node_type;
public:
    TerminalNode(std::string node_type, Position position) : node_type(std::move(node_type)), ASTNode(position) {}
};
