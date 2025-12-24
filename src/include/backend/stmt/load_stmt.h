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
    return dest_reg_->GetIndex() + " = load " + dest_reg_->GetType()->toString() + ", ptr " + addr_reg_->GetIndex() + ", align " + dest_reg_->GetType()->GetAlign();
  }

private:
  std::shared_ptr<Register> dest_reg_;
  std::shared_ptr<Register> addr_reg_;

};