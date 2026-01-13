//
// Created by zhang-kai on 8/7/25.
//
#pragma once
#include "stmt.h"

#include <utility>
#include "backend/util/register.h"

class LoadStmt : public Stmt {
public:
  LoadStmt(std::shared_ptr<Register> dest_reg, std::shared_ptr<Register> addr_reg) : dest_reg_(std::move(dest_reg)), addr_reg_(std::move(addr_reg)) {
  }

  [[nodiscard]]std::string commit() const override{
    if (*dest_reg_->GetType() == *std::make_shared<IRType>(IRType::BasicType::kVOID)) {
      return "";
    }
    return dest_reg_->GetIndex() + " = load " + dest_reg_->GetType()->toString() + ", ptr " + addr_reg_->GetIndex();
  }

  [[nodiscard]] std::shared_ptr<Register> GetDestReg() {
    return dest_reg_;
  }

  [[nodiscard]] std::shared_ptr<Register> GetAddrReg() {
    return addr_reg_;
  }

private:
  std::shared_ptr<Register> dest_reg_;
  std::shared_ptr<Register> addr_reg_;

};