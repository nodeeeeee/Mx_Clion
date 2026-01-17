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
    if (*register_->GetType() == *std::make_shared<IRType>(IRType::BasicType::kVOID, 1)) { // ternary expression, retain a void memory space.
      return "";
    }
    return register_->GetIndex() + " = alloca " + register_->GetType()->ElementToString();
  }
  [[nodiscard]] std::shared_ptr<Register> GetReg() const {
    return register_;
  }

  std::set<std::shared_ptr<Register>> GetUse() {
    return {};
  }
  std::set<std::shared_ptr<Register>> GetDef() {
    return {register_};
  }

private:
  std::shared_ptr<Register> register_;

};
