//
// Created by zhang-kai on 6/12/25.
//

#pragma once
#include "expr_node.h"

class TypeNode;

class InitObjectNode : public ExprNode, public std::enable_shared_from_this<InitObjectNode> {
private:
    std::shared_ptr<TypeType> type;
public:
    InitObjectNode() = delete;
    InitObjectNode(std::shared_ptr<TypeType> type, Position position) : type(type), ExprNode(position) {
        setExprType(type);
    }
    [[nodiscard]] const std::shared_ptr<TypeType>& getType() const { return type; }
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}

};
