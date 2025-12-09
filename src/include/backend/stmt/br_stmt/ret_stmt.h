//
// Created by zhang-kai on 10/21/25.
//

#pragma once
#include <memory>
#include <utility>

#include "backend/stmt/stmt.h"
#include "backend/stmt/variant_rep.h"
#include "backend/util/register.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/literal_node.h"

class ReturnStmt : public Stmt{
public:
  explicit ReturnStmt(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> ret_val) : ret_val_(std::move(ret_val)) {
  }
  explicit ReturnStmt() {
    is_void = true;
  }
  [[nodiscard]] std::string commit() const {
    if (is_void) {
      return "ret void";
    }
    return "ret " + VariantRep::variant_rep(ret_val_);
  }

private:
  bool is_void = false;
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> ret_val_;
};
