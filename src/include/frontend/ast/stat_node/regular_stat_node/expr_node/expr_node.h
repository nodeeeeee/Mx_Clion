//
// Created by zhang-kai on 6/9/25.
//
#pragma once
#include <utility>

#include "frontend/ast/stat_node/regular_stat_node/regular_stat_node.h"
#include "frontend/ast/type/type_type.h"

class ExprNode : public RegularStatNode {
public:
  ExprNode() = delete;

  explicit ExprNode(Position position) : RegularStatNode(position) {
  }



  void setExprType(std::shared_ptr<TypeType> expr_type) {
    this->expr_type = std::move(expr_type);
  }

  void setPrvalue(bool prvalue_) {
    prvalue = prvalue_;
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

  const bool isPrvalue() const {
    return prvalue;
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
  bool prvalue = true;
};
