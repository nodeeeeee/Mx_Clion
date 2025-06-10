//
// Created by zhang-kai on 6/6/25.
//

#pragma once
#include <memory>
#include <utility>
#include <vector>
#include "frontend/position.h"
class ASTNode {

    ASTNode(std::weak_ptr<ASTNode> parent, Position position) : position(position), parent(std::move(parent)) {}
    ASTNode(Position position) : position(position) {}

    virtual ~ASTNode() = default;
private:
    std::weak_ptr<ASTNode> parent;
    Position position;
};
