//
// Created by zhang-kai on 6/12/25.
//

#pragma once
#include "expr_node.h"

class IdNode;

class TypeNode : public ExprNode {
private:
    std::string predefined_type_name;
    std::shared_ptr<IdNode> customized_type_name = nullptr;
    std::shared_ptr<TypeNode> array_type = nullptr;
public:
    TypeNode() = delete;
    TypeNode(std::shared_ptr<IdNode> customized_type_name, Position position) : customized_type_name(std::move(customized_type_name)), ExprNode(position) {}
    TypeNode(std::shared_ptr<TypeNode> array_type, Position position) : array_type(std::move(array_type)), ExprNode(position) {}
    TypeNode(std::string predefined_type_name, Position position) : predefined_type_name(std::move(predefined_type_name)), ExprNode(position) {}
};
