//
// Created by zhang-kai on 6/12/25.
//

#pragma once

#include "terminal_node.h"
#include "frontend/ast/type/type_type.h"

class IdNode : public TerminalNode {
private:
    std::string id_name;
    std::shared_ptr<TypeType> type;
public:
    IdNode() = delete;
    IdNode(std::string id_name, Position position) : id_name(std::move(id_name)), TerminalNode(TerminalType::kID, position) {}
    IdNode(std::shared_ptr<TypeType> type, std::string id_name, Position position) : type(std::move(type)), id_name(std::move(id_name)), TerminalNode(TerminalType::kID, position) {}
    IdNode(std::shared_ptr<TypeType> type, antlr4::tree::TerminalNode *ID) : type(std::move(type)), id_name(ID->getSymbol()->getText()), TerminalNode(TerminalType::kID, Position(ID->getSymbol())) {}
};
