#include <utility>

#pragma once

class StoreStmt : public Stmt {
public:
  StoreStmt() = default;
  StoreStmt(std::shared_ptr<Register> value, std::shared_ptr<Register> addr) : value_(std::move(value)), addr_(std::move(addr)) {}

  std::string commit() {
    return "store " + value_->GetType()->toString() + " " + value_->GetIndex() + ", ptr " + addr_->GetIndex();
  }
private:
  std::shared_ptr<Register> value_;
  std::shared_ptr<Register> addr_;
};