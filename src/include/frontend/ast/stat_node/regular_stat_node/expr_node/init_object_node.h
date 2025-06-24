//
// Created by zhang-kai on 6/12/25.
//

#pragma once
#include "expr_node.h"

class TypeNode;

class InitObjectNode : public ExprNode {
private:
    std::shared_ptr<TypeType> type;
public:
    InitObjectNode() = delete;
    InitObjectNode(std::shared_ptr<TypeType> type, Position position) : type(std::move(type)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
