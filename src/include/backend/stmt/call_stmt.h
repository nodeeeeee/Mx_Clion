//
// Created by zhang-kai on 8/7/25.
//

#pragma once
#include <string>
#include <utility>

#include "backend/util/ir_function.h"
#include "backend/util/register.h"


class CallStmt : public Stmt {
public:
  CallStmt(const std::shared_ptr<IRFunction>& func, std::shared_ptr<Register> dest_reg, const std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>>& params) : func_(func), dest_reg_(std::move(dest_reg)), params_(params) {
  }
  [[nodiscard]] std::string commit() const override {
    std::string str =  dest_reg_->GetIndex() + " call " + func_->GetReturnType()->toString() + func_->GetName() + "(";
    bool first = true;
    for (auto &param : params_) {
      if  (!first) str += ", ";
      first = false;
      str += VariantRep::variant_rep(param);
    }
    str += ")";
    return str;
  }
private:
  std::shared_ptr<IRFunction> func_;
  std::shared_ptr<Register> dest_reg_;
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params_;
};
