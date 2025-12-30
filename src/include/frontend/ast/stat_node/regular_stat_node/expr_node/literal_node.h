//
// Created by zhang-kai on 6/10/25.
//

#pragma once
#include <optional>
#include <variant>

#include "expr_node.h"
#include "backend/util/type/ir_type.h"
#include "frontend/ast/type/type_type.h"
#include "frontend/ast/stat_node/def_node/class_def_node.h"
#include "parser/MxParser.h"

class LiteralNode : public ExprNode, public std::enable_shared_from_this<LiteralNode> {
public:
  LiteralNode() = delete;

  explicit LiteralNode(MxParser::LiteralContext* ctx) : ExprNode(Position(ctx)) {
    auto literal = ctx;
    if (auto integer_type = literal->INTEGER()) {
      auto token = integer_type->getSymbol();
      literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
      literal_irtype = std::make_shared<IRType>(literal_type);
      value_ = std::stoi(token->getText());
    } else if (auto bool_type = literal->BOOL()) {
      auto token = bool_type->getSymbol();
      literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
      literal_irtype = std::make_shared<IRType>(literal_type);
      value_ = token->getText() == "true" ? true : false;
    } else if (auto string_type = literal->STRING()) {
      auto token = string_type->getSymbol();
      literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
      literal_irtype = std::make_shared<IRType>(literal_type);
      value_ = token->getText();
    } else if (auto null_type = literal->NULL_()) {
      auto token = null_type->getSymbol();
      literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kNULL);
      literal_irtype = std::make_shared<IRType>(literal_type);
      value_ = "null";
      is_null = true;
    }
  }

  explicit LiteralNode(antlr4::Token* token): ExprNode(Position(token)) {
    //only for format_string
    literal_type = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
    literal_irtype = std::make_shared<IRType>(literal_type);
    value_ = token->getText();
  }

  std::shared_ptr<TypeType> getLiteralType() { return literal_type; }
  bool isNull() const { return is_null; }
  void accept(VisitControl* visitor) { visitor->visit(shared_from_this()); }

  [[nodiscard]] std::shared_ptr<IRType> getLiteralIRType() { return literal_irtype; }

  [[nodiscard]] std::variant<int, bool, std::string> GetValue() const { return value_; }

  std::string ToString() const {
    if (auto int_value = std::get_if<int>(&value_)) {
      return std::to_string(*int_value);
    } else if (auto bool_value = std::get_if<bool>(&value_)) {
      return *bool_value ? "true" : "false";
    } else {
      auto string_value = std::get_if<std::string>(&value_);
      return *string_value;
    }
  }

  std::string ToStringWithType() const {
    if (std::holds_alternative<int>(value_)) {
      return "i32 " + ToString();
    } else if (std::holds_alternative<bool>(value_)) {
      return "i1 " + ToString();
    } else {
      throw std::runtime_error("types not int/bool is not allowed in ToStringWithType");
    }
  }

private:
  std::shared_ptr<TypeType> literal_type;
  std::shared_ptr<IRType> literal_irtype;
  bool is_null = false;

  std::variant<int, bool, std::string> value_;
};
