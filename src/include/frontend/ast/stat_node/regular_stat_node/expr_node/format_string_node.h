//
// Created by zhang-kai on 6/12/25.
//
#pragma once

class ExprNode;
class LiteralNode;

class FormatStringNode : public ExprNode, public std::enable_shared_from_this<FormatStringNode> {
private:
    std::vector<std::shared_ptr<LiteralNode>> literal_nodes; //strings
    std::vector<std::shared_ptr<ExprNode>> expr_nodes;
    bool literal_first;
public:
    FormatStringNode() = delete;
    FormatStringNode(std::vector<std::shared_ptr<LiteralNode>> literal_nodes, std::vector<std::shared_ptr<ExprNode>> expr_nodes, bool literal_first, Position position)
        : literal_nodes(std::move(literal_nodes)), expr_nodes(std::move(expr_nodes)), literal_first(literal_first), ExprNode(position){}
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}
    std::vector<std::shared_ptr<LiteralNode>>& getLiteralNodes() { return literal_nodes; }
    std::vector<std::shared_ptr<ExprNode>>& getExprNodes() { return expr_nodes; }
};
