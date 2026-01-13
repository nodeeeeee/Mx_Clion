//
// Created by zhang-kai on 6/12/25.
//

#pragma once

#include "expr_node.h"
#include "frontend/ast/type/type_type.h"

class IdNode : public ExprNode, public std::enable_shared_from_this<IdNode> {
public:
    IdNode() = delete;
    IdNode(std::string id_name, Position position) : id_name(std::move(id_name)), ExprNode(position) {
        setPrvalue(false);
    }
    IdNode(std::shared_ptr<TypeType> type, std::string id_name, Position position) : type(std::move(type)), id_name(std::move(id_name)), ExprNode(position) {
        setPrvalue(false);
    }
    IdNode(std::shared_ptr<TypeType> type, antlr4::tree::TerminalNode *ID) : type(std::move(type)), id_name(ID->getSymbol()->getText()), ExprNode(Position(ID->getSymbol())) {
        setPrvalue(false);
    }
    std::string &getIdName() { return id_name; }
    std::shared_ptr<TypeType> getType() { return type; }
    void accept(VisitControl *visitor) override { visitor->visit(shared_from_this()); }

private:
    std::string id_name;
    std::shared_ptr<TypeType> type;
};
