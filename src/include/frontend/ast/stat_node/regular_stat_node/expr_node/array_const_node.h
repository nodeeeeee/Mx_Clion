//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"

class ArrayConstNode : public ExprNode {
private:
    std::vector<std::shared_ptr<LiteralNode>> literal_elements;
    std::vector<std::shared_ptr<ArrayConstNode>> array_elements;
public:
    ArrayConstNode() = delete;
    ArrayConstNode(std::vector<std::shared_ptr<ArrayConstNode>> array_elements, Position position) : array_elements(std::move(array_elements)), ExprNode(position) {
        preCheck(std::shared_ptr<ArrayConstNode>{this});
    }
    ArrayConstNode(std::vector<std::shared_ptr<LiteralNode>> literal_elements, Position position) : literal_elements(std::move(literal_elements)), ExprNode(position) {}
    explicit ArrayConstNode(Position position) : ExprNode(position) {}
    std::shared_ptr<TypeType> preCheck(std::shared_ptr<ArrayConstNode> current_array) {
        if (current_array->literal_elements.size() != 0) {
            if (!current_array->) {
                auto ref = vec.front().field;
                bool all_same = std::all_of(vec.begin(), vec.end(),
                                            [&](const MyType& e){ return e.field == ref; });
                // all_same 为 true 则所有元素的 field 都等于 vec.front().field
            }
        } else if (current_array->array_elements.size() != 0) {

        } else {
            return std::make_shared<TypeType::SpecialCode::NoType>;
        }
    }
    //check type consistency within the array, and check how many layers are there in an array
    void accept(VisitControl *visitor) {visitor->visit(this);}

};
