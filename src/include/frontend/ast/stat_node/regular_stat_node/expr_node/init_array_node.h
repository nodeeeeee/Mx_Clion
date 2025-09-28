//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class TypeType;
class TypeNode;

class InitArrayNode : public ExprNode, public std::enable_shared_from_this<InitArrayNode> {
private:
    std::vector<std::shared_ptr<ExprNode>> range_node;
    std::shared_ptr<TypeType> type;
    std::shared_ptr<ArrayConstNode> default_array = nullptr;
public:
    InitArrayNode() = delete;
    InitArrayNode(std::shared_ptr<TypeType> type, std::vector<std::shared_ptr<ExprNode>> range_node, Position position)
        :  type(std::move(type)),range_node(std::move(range_node)), ExprNode(position) {}
    InitArrayNode(std::shared_ptr<TypeType> type, std::vector<std::shared_ptr<ExprNode>> range_node, std::shared_ptr<ArrayConstNode> default_array, Position position) :
    type(std::move(type)), range_node(std::move(range_node)), default_array(std::move(default_array)), ExprNode(position) {}
    const std::vector<std::shared_ptr<ExprNode>>& getRangeNode() { return range_node; }
    const std::shared_ptr<TypeType>& getType() { return type; }
    const std::shared_ptr<ArrayConstNode> getDefaultArray() { return default_array; }
    void accept(VisitControl *visitor) override {visitor->visit(shared_from_this());}
    [[nodiscard]] std::string GetTypeForInit() {
        std::string ret;
        for (int i = 0; i < range_node.size(); i++) {
            std::shared_ptr<LiteralNode> range_literal = std::dynamic_pointer_cast<LiteralNode>(range_node[i]);
            ret += "[" + range_literal->ToString() + " x ";
        }
        ret += "i32";
        for (int i = 0; i < range_node.size(); i++) {
            ret += "]";
        }
        return ret;
    }
    [[nodiscard]] std::string GetArrayConstForInit() {
        std::string ret;
        ret += "[";
        for (int i = 0; i < range_node.size(); i++) {
            std::shared_ptr<LiteralNode> range_literal = std::dynamic_pointer_cast<LiteralNode>(range_node[i]);
            ret += "i32 " + range_literal->ToString() + ", ";
        }
        ret += "]";
    }
};
