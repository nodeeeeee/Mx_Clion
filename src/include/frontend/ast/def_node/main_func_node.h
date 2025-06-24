//
// Created by zhang-kai on 6/9/25.
//

#pragma once
#include "../ASTNode.h"
#include "frontend/ast/terminal_node/id_node.h"
#include "frontend/ast/type/type_type.h"

class BlockNode;

class MainFuncNode : public DefNode {
private:
    std::shared_ptr<BlockNode> body;
public:
    MainFuncNode() = delete;
    MainFuncNode(std::shared_ptr<BlockNode> body, Position position) : body(std::move(body)), DefNode(std::make_shared<IdNode>(std::make_shared<TypeType>(0), "main", position), DefType::kFunc, position) {}
    const std::shared_ptr<BlockNode> getBody() const { return body; }
    void accept(VisitControl *visitor) {visitor->visit(this);}
};
