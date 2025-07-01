//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include "expr_node.h"
#include "frontend/ast/type/type_type.h"

class ArrayConstNode : public ExprNode, public std::enable_shared_from_this<ArrayConstNode> {
private:
  std::vector<std::shared_ptr<LiteralNode>> literal_elements;
  std::vector<std::shared_ptr<ArrayConstNode>> array_elements;
  std::shared_ptr<TypeType> array_type;
public:
  ArrayConstNode() = delete;

  ArrayConstNode(std::vector<std::shared_ptr<ArrayConstNode>> array_elements, Position position) :
    array_elements(std::move(array_elements)), ExprNode(position) {
    // array_type = preCheck(std::shared_ptr<ArrayConstNode>{this});
  }

  ArrayConstNode(std::vector<std::shared_ptr<LiteralNode>> literal_elements, Position position) :
    literal_elements(std::move(literal_elements)), ExprNode(position) {
    // array_type = preCheck(std::shared_ptr<ArrayConstNode>{this});
  }

  void determineArrayType() {
    array_type = preCheck(std::shared_ptr<ArrayConstNode>(this));
  }

  explicit ArrayConstNode(Position position) : ExprNode(position) {
  }

  std::shared_ptr<TypeType> preCheck(const std::shared_ptr<ArrayConstNode>& current_array) {
    if (!current_array->literal_elements.empty()) {
      auto ref = current_array->literal_elements.front()->getLiteralType();
      bool all_same = std::all_of(current_array->literal_elements.begin() + 1, current_array->literal_elements.end(),
                                  [&](const std::shared_ptr<LiteralNode>& e) { return e->getLiteralType() == ref; });
      if (!all_same) {
        throw std::runtime_error("array const type mismatch");
      } else {
        return std::make_shared<TypeType>(ref, 0);
      }
    } else if (!current_array->array_elements.empty()) {
      auto ref = preCheck(current_array->array_elements.front());
      bool all_same = std::all_of(current_array->array_elements.begin() + 1, current_array->array_elements.end(),
        [&](const std::shared_ptr<ArrayConstNode>& e) {return preCheck(e) == ref;});
      if (!all_same) {
        throw std::runtime_error("array const type mismatch");
      } else {
        return std::make_shared<TypeType>(ref, 1);
      }
    } else {
      return std::make_shared<TypeType>(TypeType::SpecialCode::NoType);
    }
  }

  //check type consistency within the array, and check how many layers are there in an array
  void accept(VisitControl* visitor) override { visitor->visit(shared_from_this()); }
};
