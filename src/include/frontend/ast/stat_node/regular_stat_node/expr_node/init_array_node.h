//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class TypeType;
class TypeNode;

class InitArrayNode : public ExprNode {
private:
    std::vector<std::shared_ptr<ExprNode>> range_node;
    std::shared_ptr<TypeType> type;
public:
    InitArrayNode() = delete;
    InitArrayNode(std::shared_ptr<TypeType> type, std::vector<std::shared_ptr<ExprNode>> range_node, Position position)
        :  type(std::move(type)),range_node(std::move(range_node)), ExprNode(position) {}
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
