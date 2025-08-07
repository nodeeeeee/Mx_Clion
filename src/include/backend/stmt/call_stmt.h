//
// Created by zhang-kai on 8/7/25.
//

#pragma once
#include <string>
#include <utility>

#include "backend/util/ir_function.h"
#include "backend/util/register.h"


class CallStmt {
public:
  CallStmt(const std::shared_ptr<IRFunction>& func, std::shared_ptr<Register> dest_reg, std::vector<std::shared_ptr<Register>> registers) : func_(func), dest_reg_(std::move(dest_reg)), registers_(std::move(registers)) {
  }
  std::string commit() {
    return dest_reg_->GetIndex() + " call " + func_->GetReturnType()->toString()
  }
private:
  std::shared_ptr<IRFunction> func_;
  std::shared_ptr<Register> dest_reg_;
  std::vector<std::shared_ptr<Register>> registers_;
};
