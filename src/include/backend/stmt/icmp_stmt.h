//
// Created by zhang-kai on 10/21/25.
//

#pragma once
#include <memory>
#include <utility>
#include <variant>

#include "stmt.h"
#include "variant_rep.h"
#include "backend/util/register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"

class IcmpStmt : public Stmt {
public:
  enum class IcmpOp : int {
    kBT, kLT, kBEQ, kLEQ, kET, kNET
  };
  IcmpStmt(IcmpOp op, std::variant <int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>lhs, std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> rhs, std::shared_ptr<Register> dest)
    : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)), dest_(std::move(dest)){
  }

  [[nodiscard]]std::string commit() const override {
    std::string op_str;
    switch (op_) {
      case IcmpOp::kBT:
        op_str = "sgt";
        break;
      case IcmpOp::kLT:
        op_str = "slt";
        break;
      case IcmpOp::kBEQ:
        op_str = "sge";
        break;
      case IcmpOp::kLEQ:
        op_str = "sle";
        break;
      case IcmpOp::kET:
        op_str = "eq";
        break;
      case IcmpOp::kNET:
        op_str = "ne";
        break;
      default:
        throw std::runtime_error("Unknown binary operator");
    }
    return dest_->GetIndex() + " = icmp " + op_str + " " + VariantRep::variant_rep(lhs_) + ", " + VariantRep::variant_val_only(rhs_);
  }

  [[nodiscard]] IcmpOp GetOp() {
    return op_;
  }

  [[nodiscard]] std::shared_ptr<Register> GetDestReg() {
    return dest_;
  }

  [[nodiscard]] std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> GetLhs() {
    return lhs_;
  }

  [[nodiscard]] std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> GetRhs() {
    return rhs_;
  }
  std::set<std::shared_ptr<Register>> GetUse() {
    std::set<std::shared_ptr<Register>> use_reg;
    if (std::holds_alternative<std::shared_ptr<Register>>(lhs_)) {
      use_reg.emplace(std::get<std::shared_ptr<Register>>(lhs_));
    }
    if (std::holds_alternative<std::shared_ptr<Register>>(rhs_)) {
      use_reg.emplace(std::get<std::shared_ptr<Register>>(rhs_));
    }
    return use_reg;
  }

  std::set<std::shared_ptr<Register>> GetDef() {
    std::set<std::shared_ptr<Register>> def_reg;
    return {dest_};
  }
private:
  IcmpOp op_;
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> lhs_;
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> rhs_;
  std::shared_ptr<Register> dest_;
};
