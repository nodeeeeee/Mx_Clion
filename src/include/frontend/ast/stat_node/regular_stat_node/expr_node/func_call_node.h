//
// Created by zhang-kai on 6/12/25.
//

#pragma once
#include "expr_node.h"

class FuncCallNode : public ExprNode, public std::enable_shared_from_this<FuncCallNode> {
private:
    std::string func_name;
    std::vector<std::shared_ptr<ExprNode>> args;
public:
    FuncCallNode() = delete;
    FuncCallNode(std::string func_name, std::vector<std::shared_ptr<ExprNode>> args, Position position) : func_name(std::move(func_name)), args(std::move(args)), ExprNode(position) {};
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}
    const std::string &getName() {return func_name;}
    const std::vector<std::shared_ptr<ExprNode>> &getArgs() {return args;}
};