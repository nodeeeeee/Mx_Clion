//
// Created by zhang-kai on 8/24/25.
//

#pragma once
#include <memory>
#include <utility>
#include <variant>

#include "stmt.h"
#include "variant_rep.h"
#include "backend/util/register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"

class BinaryStmt : public Stmt {
public:
  enum class BinaryOp : int {
    kMUL, kDIV, kMOD, kADD, kSUB,kSRL, kSLL, kAND, kXOR, kOR
  };
  BinaryStmt(BinaryOp op, std::variant <int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>lhs, std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> rhs, std::shared_ptr<Register> dest)
    : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)), dest_(std::move(dest)){
  }

  [[nodiscard]] std::string commit() const override {
    std::string op_str;
    switch (op_) {
      case BinaryOp::kMUL:
        op_str = "mul";
        break;
      case BinaryOp::kDIV:
        op_str = "sdiv";
        break;
      case BinaryOp::kMOD:
        op_str = "srem";
        break;
      case BinaryOp::kADD:
        op_str = "add";
        break;
      case BinaryOp::kSUB:
        op_str = "sub";
        break;
      case BinaryOp::kSRL:
        op_str = "lshr";
        break;
      case BinaryOp::kSLL:
        op_str = "shl";
        break;
      case BinaryOp::kAND:
        op_str = "and";
        break;
      case BinaryOp::kOR:
        op_str = "or";
        break;
      default:
        throw std::runtime_error("Unknown binary operator");
    }

    return dest_->GetIndex() + " = " + op_str + " " + VariantRep::variant_rep(lhs_) + ", " + VariantRep::variant_rep(rhs_);
  }

private:
  BinaryOp op_;
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> lhs_;
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> rhs_;
  std::shared_ptr<Register> dest_;
};
