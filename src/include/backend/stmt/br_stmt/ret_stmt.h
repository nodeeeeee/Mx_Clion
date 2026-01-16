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
    // is_void = true;
    ret_str = "void";
  }
  explicit ReturnStmt(std::shared_ptr<IRType> ret_type) {
    ret_str = ret_type->toString() + " " + ret_type->DefaultValue();
  }
  [[nodiscard]] std::string commit() const {
    // if (is_void) {
    //   return "ret void";
    // }

    std::string ret = "ret ";
    if (!ret_str.empty()) {
      ret += ret_str;
      return ret;
    }
    if (std::holds_alternative<int>(ret_val_)) {
      ret += VariantRep::variant_rep(ret_val_);
    } else if (std::holds_alternative<bool>(ret_val_)) {
      ret += VariantRep::variant_rep(ret_val_);
    } else if (std::holds_alternative<std::shared_ptr<LiteralNode>>(ret_val_)) {
      ret += VariantRep::variant_rep(ret_val_);
    } else if (std::holds_alternative<std::shared_ptr<Register>>(ret_val_)) {
      ret += VariantRep::variant_rep(ret_val_);
    }
    return ret;
    // return "ret " + VariantRep::variant_rep(ret_val_);
  }

  [[nodiscard]] std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> GetRetVal() {
    return ret_val_;
  }

  std::set<std::shared_ptr<Register>> GetUse() {
    std::set<std::shared_ptr<Register>> use_reg;
    if (std::holds_alternative<std::shared_ptr<Register>>(ret_val_)) {
      use_reg.emplace(std::get<std::shared_ptr<Register>>(ret_val_));
    }
    return use_reg;
  }
  std::set<std::shared_ptr<Register>> GetDef() {
    return {};
  }

private:
  bool is_void = false;
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> ret_val_;
  std::string ret_str;
};
