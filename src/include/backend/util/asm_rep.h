//
// Created by zhangkai on 2026/1/10.
//

#pragma once
#include <memory>
#include <variant>

#include "physical_register.h"
#include "register.h"
#include "backend/stmt/variant_rep.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"


class AsmRep {
public:
  AsmRep(std::variant<int, PhysicalRegister> rep) : rep_(rep) {
  }

  AsmRep(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> ir_rep) {
    if (std::holds_alternative<int>(ir_rep)) {
      rep_ = std::get<int>(ir_rep);
    } else if (std::holds_alternative<bool>(ir_rep)) {
      rep_ = (int)std::get<bool>(ir_rep);
    } else if (std::holds_alternative<std::shared_ptr<LiteralNode>>(ir_rep)) {
      auto rep_literal = std::get<std::shared_ptr<LiteralNode>>(ir_rep);
      rep_ = rep_literal->GetAsmValue();
    } else if (std::holds_alternative<std::shared_ptr<Register>>(ir_rep)) {
      throw std::runtime_error("should not be a Register");
    }
  }

  std::string PrintRep() {
    if (std::holds_alternative<int>(rep_)) {
      return std::to_string(std::get<int>(rep_));
    } else {
      return std::get<PhysicalRegister>(rep_).GetName();
    }
  }

  int GetRepVal() {
    if (std::holds_alternative<int>(rep_)) {
      return std::get<int>(rep_);
    } else {
      throw std::runtime_error("should be a int");
    }
  }
  private:
  std::variant<int, PhysicalRegister> rep_;
};
