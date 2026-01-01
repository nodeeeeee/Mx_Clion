#pragma once
#include <memory>
#include <utility>

#include "backend/util/register.h"
#include "backend/util/type/ir_type.h"


class AllocaStmt : public Stmt {
public:
  AllocaStmt() = default;
  explicit AllocaStmt(std::shared_ptr<Register> reg) : register_(std::move(reg)) {}
  [[nodiscard]] std::string commit() const override {
    return register_->GetIndex() + " = alloca " + register_->GetType()->ElementToString();
  }
private:
  std::shared_ptr<Register> register_;
};
