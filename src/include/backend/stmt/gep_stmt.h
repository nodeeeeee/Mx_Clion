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

class GEPStmt : public Stmt {
public:
  GEPStmt(std::shared_ptr<Register> dest_ptr, std::shared_ptr<Register> base_ptr, std::vector<std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices) : dest_ptr_(std::move(dest_ptr)), base_ptr_(std::move(base_ptr)), indices_(std::move(indices)) {
  }

  std::string commit() {
    return dest_ptr_->GetIndex() + " = getelementptr inbounds " + base_ptr_->
  }
private:
  std::shared_ptr<Register> dest_ptr_;
  std::shared_ptr<Register> base_ptr_;  // pointee-type can be retrieved from base_ptr
  std::vector<std::variant<std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> indices_;
};
