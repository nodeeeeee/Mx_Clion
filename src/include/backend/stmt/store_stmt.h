#include <utility>

#pragma once

class StoreStmt : public Stmt {
public:
  StoreStmt() = default;
  StoreStmt(std::variant<int, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> value, std::shared_ptr<Register> addr) : value_(std::move(value)), addr_(std::move(addr)) {}

  [[nodiscard]]std::string commit() const override {
    if (std::holds_alternative<std::shared_ptr<Register>>(value_)) {
      auto value_reg = std::get<std::shared_ptr<Register>>(value_);
      return "store " + value_reg->GetType()->toString() + " " + value_reg->GetIndex() + ", ptr " + addr_->GetIndex();
    } else if (std::holds_alternative<std::shared_ptr<LiteralNode>>(value_)) {
      auto value_literal = std::get<std::shared_ptr<LiteralNode>>(value_);
      return "store " + value_literal->getLiteralIRType()->toString() + " " + value_literal->ToString() + ", ptr " + addr_->GetIndex();
    }
  }
private:
  std::variant<int, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> value_;
  std::shared_ptr<Register> addr_;
};