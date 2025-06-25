//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include "frontend/ast/stat_node/regular_stat_node/regular_stat_node.h"

class ExprNode : public RegularStatNode {
public:
  ExprNode() = delete;

  explicit ExprNode(Position position) : RegularStatNode(position) {
  }

  void accept(VisitControl* visitor) { visitor->visit(this); }

  void setExprType(std::shared_ptr<TypeType> expr_type) {
    this->expr_type = expr_type;
  }

  std::shared_ptr<TypeType> getExprType() {
    return expr_type;
  }

  const bool isAssignable() const {
    return assignable;
  }

  const bool isValid() const {
    return valid;
  }



  void setAssignable(bool assignable_) {
    assignable = assignable_;
  }

  void setValid(bool valid_) {
    valid = valid_;
  }

private:
  std::shared_ptr<TypeType> expr_type = nullptr;
  bool assignable = true;
  bool valid = true;

};
