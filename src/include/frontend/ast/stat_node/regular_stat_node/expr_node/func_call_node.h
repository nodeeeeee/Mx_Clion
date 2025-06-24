//
// Created by zhang-kai on 6/12/25.
//

#pragma once
#include "expr_node.h"

class FuncCallNode : public ExprNode {
private:
    std::string func_name;
public:
    FuncCallNode() = delete;
    FuncCallNode(std::string func_name, Position position) : func_name(std::move(func_name)), ExprNode(position) {};
    void accept(VisitControl *visitor) {visitor->visit(this);}

};