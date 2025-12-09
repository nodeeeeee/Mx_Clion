//
// Created by zhang-kai on 6/11/25.
//

#pragma once
#include "regular_stat_node.h"

class FuncCallNode;
class ExprNode;

class ReturnStatNode : public RegularStatNode, public std::enable_shared_from_this<ReturnStatNode> {
public:

    ReturnStatNode() = delete;
    ReturnStatNode(std::shared_ptr<ExprNode> return_expr_node, Position position) : return_expr_node(std::move(return_expr_node)), RegularStatNode(position) {}
    ReturnStatNode(std::shared_ptr<FuncCallNode> return_func_call_node, Position position) : return_func_call_node(std::move(return_func_call_node)), RegularStatNode(position) {}
    explicit ReturnStatNode(Position position) : RegularStatNode(position) {}
    [[nodiscard]] const std::shared_ptr<ExprNode>& getReturnExpr() const { return return_expr_node; }
    [[nodiscard]] const std::shared_ptr<FuncCallNode>& getFuncCall() const { return return_func_call_node; }
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}
private:
    std::shared_ptr<ExprNode> return_expr_node = nullptr;
    std::shared_ptr<FuncCallNode> return_func_call_node = nullptr;
};
