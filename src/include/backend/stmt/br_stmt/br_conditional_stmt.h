//
// Created by zhang-kai on 10/21/25.
//

#pragma once
#include <utility>

#include "backend/stmt/binary_stmt.h"

class BrConditionalStmt : public Stmt{
 /**
  * conditional branching
  */
public:
  BrConditionalStmt(std::variant <int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> br_reg, std::string true_label, std::string false_label) : br_reg_(std::move(br_reg)), true_label_(std::move(true_label)), false_label_(std::move(false_label)) {

  }
  [[nodiscard]] std::string commit() const {
    return "br " + VariantRep::variant_rep(br_reg_) + ", label %" + true_label_ + ", label %" + false_label_;
  }

  [[nodiscard]] std::string GetTrueLabel() const {
    return true_label_;
  }

  [[nodiscard]] std::string GetFalseLabel() const {
    return false_label_;
  }

  [[nodiscard]] std::variant <int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> GetBrReg() const {
    return br_reg_;
  }
private:
  std::variant <int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> br_reg_;
  std::string true_label_;
  std::string false_label_;
};
