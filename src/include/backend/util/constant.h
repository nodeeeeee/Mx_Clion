#pragma once
#include <string>
#include <utility>
#include <variant>

#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"
#include "type/ir_int_type.h"
#include "type/ir_type.h"
#include "type/type_getter.h"

class Constant {
public:
  explicit Constant(std::variant<int, bool, std::string> value) : value_(std::move(value)) {
    if (auto tmp = std::get_if<int>(&value_)) {
      type_ = std::make_shared<IRType>(IRType::kINT);
    } else if (auto tmp1 = std::get_if<bool>(&value_)) {
      type_ = std::make_shared<IRType>(IRType::kBOOL);
    } else if (auto tmp2 = std::get_if<std::string>(&value_)) {
      type_ = std::make_shared<IRType>(IRType::kSTRING);
    }
  }

  explicit Constant(const std::shared_ptr<LiteralNode>& literal_node) {
    value_ = literal_node->GetValue();
    if (auto tmp = std::get_if<int>(&value_)) {
      type_ = std::make_shared<IRType>(IRType::kINT);
    } else if (auto tmp1 = std::get_if<bool>(&value_)) {
      type_ = std::make_shared<IRType>(IRType::kBOOL);
    } else if (auto tmp2 = std::get_if<std::string>(&value_)) {
      type_ = std::make_shared<IRType>(IRType::kSTRING);
    }
  }

  [[nodiscard]] std::string ToString() const {
    if (*type_ == *TypeGetter::get_type(IRType::kINT)) {
      return std::to_string(std::get<int>(value_));
    } else if (*type_ == *TypeGetter::get_type(IRType::kBOOL)) {
      auto val = std::get<bool>(value_);
      if (val == true) return "1";
      else return "0";
    } else if (*type_ == *TypeGetter::get_type(IRType::kSTRING)) {
      return std::get<std::string>(value_);
    } else {
      throw std::runtime_error("Unknown type");
    }
  }

  [[nodiscard]] std::shared_ptr<IRType> GetConstType() const {
    return type_;
  }
private:
  std::shared_ptr<IRType> type_;
  std::variant<int, bool, std::string> value_;
};
