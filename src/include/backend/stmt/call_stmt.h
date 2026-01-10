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
  CallStmt(const std::shared_ptr<IRFunction>& func, const std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>>& params) : func_(func), params_(params) {
  }
  [[nodiscard]] std::string commit() const override {
    std::string str;
    if (dest_reg_ != nullptr) {
      str += dest_reg_->GetIndex() + " = ";
    }
    str += "call " + func_->GetReturnType()->toString() + " @";
    str += func_->GetName() + "(";
    bool first = true;
    for (auto &param : params_) {
      if  (!first) str += ", ";
      first = false;
      str += VariantRep::variant_rep(param);
    }
    str += ")";
    return str;
  }

  [[nodiscard]] std::shared_ptr<IRFunction> GetFunc() {
    return func_;
  }

  [[nodiscard]] std::shared_ptr<Register> GetDestRegister() {
    return dest_reg_;
  }

  [[nodiscard]] std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> GetParams() {
    return params_;
  }
private:
  std::shared_ptr<IRFunction> func_;
  std::shared_ptr<Register> dest_reg_;
  std::vector<std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>>> params_;
};
