//
// Created by zhang-kai on 8/24/25.
//

#pragma once
#include <memory>
#include <utility>
#include <variant>

#include "stmt.h"
#include "backend/util/register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"

class BinaryStmt : public Stmt {
public:
  enum class BinaryOp : int {
    kMUL, kDIV, kMOD, kADD, kSUB,kSRL, kSLL, kBT, kLT, kBEQ, kLEQ, kET, kNET, kAND, kXOR, kOR, kAND_AND, kOR_OR
  };
  BinaryStmt(BinaryOp op, std::variant <std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>lhs, std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> rhs, std::shared_ptr<Register> dest)
    : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)), dest_(std::move(dest)){
  }

  std::string commit() {
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
      case BinaryOp::kBT:
        op_str = "sgt";
        break;
      case BinaryOp::kLT:
        op_str = "slt";
        break;
      case BinaryOp::kBEQ:
        op_str = "sge";
        break;
      case BinaryOp::kLEQ:
        op_str = "sle";
        break;
      case BinaryOp::kET:
        op_str = "eq";
        break;
      case BinaryOp::kNET:
        op_str = "ne";
        break;
      case BinaryOp::kAND:
        op_str = "and";
        break;
      case BinaryOp::kOR:
        op_str = "or";
        break;
      case BinaryOp::kAND_AND:
        op_str = "and";
        //short circuit evaluation optimization
        break;
      case BinaryOp::kOR_OR:
        op_str = "or";
        //short circuit evaluation optimization
        break;
      case default:
        throw std::runtime_error("Unknown binary operator");
    }
  }

private:
  BinaryOp op_;
  std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> lhs_;
  std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> rhs_;
  std::shared_ptr<Register> dest_;
};
