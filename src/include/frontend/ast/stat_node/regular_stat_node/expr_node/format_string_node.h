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
    std::vector<std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<ExprNode>>> nodes_;
    bool literal_first;
public:
    FormatStringNode() = delete;
    FormatStringNode(std::vector<std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<ExprNode>>> nodes, bool literal_first, Position position)
        : nodes_(nodes), literal_first(literal_first), ExprNode(position) {
        for (const auto& node : nodes) {
            if (holds_alternative<LiteralNode>(node)) {
                literal_nodes.push_back(std::get<std::shared_ptr<LiteralNode>>(node));
            } else {
                expr_nodes.push_back(std::get<std::shared_ptr<ExprNode>>(node));
            }
        }
    }
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this()); }

    std::vector<std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<ExprNode>>> get_all_nodes() const {return nodes_;}
    std::vector<std::shared_ptr<LiteralNode>>& getLiteralNodes() { return literal_nodes; }
    std::vector<std::shared_ptr<ExprNode>>& getExprNodes() { return expr_nodes; }
};
