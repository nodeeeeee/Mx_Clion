//
// Created by zhang-kai on 10/21/25.
//

#pragma once
#include <utility>

#include "backend/stmt/binary_stmt.h"

class BrUnconditionalStmt : public Stmt{
  /**
   * conditional branching
   */
public:
  explicit BrUnconditionalStmt(std::string label) : label_(std::move(label)) {

  }
  [[nodiscard]] std::string commit() const {
    return "br label %" + label_;
  }
  std::variant <int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> br_reg_;
  std::string label_;
};
