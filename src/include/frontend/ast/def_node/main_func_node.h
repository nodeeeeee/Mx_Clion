//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "../ASTNode.h"

class BlockNode;

class MainFuncNode : public DefNode {
private:
    std::shared_ptr<BlockNode> body;
public:
    MainFuncNode() = delete;
    MainFuncNode(std::shared_ptr<BlockNode> body, Position position) : body(std::move(body)), DefNode("main", position) {}
};
