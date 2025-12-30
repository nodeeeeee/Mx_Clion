#pragma once
#include <memory>
#include <string>
#include <variant>

#include "backend/util/register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"

class VariantRep {
public:
  static std::string variant_rep(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> var) {
    auto k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
    auto k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
    if (std::holds_alternative<int>(var)) {
      int var_int = std::get<int>(var);
      return "i32 " + std::to_string(var_int);
    } else if (std::holds_alternative<bool>(var)) {
      bool var_bool = std::get<bool>(var);
      return "i1 " + std::to_string(var_bool);
    } else if (std::holds_alternative<std::shared_ptr<LiteralNode>>(var)) {
      std::shared_ptr<LiteralNode> var_literal = std::get<std::shared_ptr<LiteralNode>>(var);
      return var_literal->getLiteralIRType()->toString() + " " + var_literal->ToString();
    } else if (std::holds_alternative<std::shared_ptr<Register>>(var)) {
      auto var_reg = std::get<std::shared_ptr<Register>>(var);
      return var_reg->GetIndexWithType();
    } else {
      throw std::runtime_error("Invalid variant type");
    }
  }
};