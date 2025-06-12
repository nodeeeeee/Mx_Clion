//
// Created by zhang-kai on 6/12/25.
//

#pragma once

#include "terminal_node.h"

class IdNode : public TerminalNode {
private:
    std::string id_name;
public:
    IdNode() = delete;
    IdNode(std::string id_name, Position position) : id_name(std::move(id_name)), TerminalNode("ID", position) {}
};
