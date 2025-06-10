//
// Created by zhang-kai on 6/7/25.
//

#pragma once
#include <utility>

#include "frontend/ast/ASTNode.h"
#include "frontend/ast/def_node/def_node.h"

class VarDefNode : public DefNode {
private:
    std::string type_name;
    std::shared_ptr<ExprNode> expr_node;

public:
    VarDefNode() = delete;
    VarDefNode(std::string type_name, std::string ID, const Position& position, std::shared_ptr<Expr_Node> expr_node) : DefNode(std::move(ID), position),type_name(std::move(type_name)), expr_node(std::move(expr_node)){
    }
    VarDefNode(std::string type_name, std::string ID, const Position& position) : DefNode(std::move(ID), position), type_name(std::move(type_name)){
    }
};
