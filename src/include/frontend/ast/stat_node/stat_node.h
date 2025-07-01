//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "frontend/ast/ASTNode.h"
#include "frontend/ast/visit_control.h"

class StatNode : public ASTNode {
public:
    StatNode() = delete;
    explicit StatNode(Position position) : ASTNode(position) {}

};
