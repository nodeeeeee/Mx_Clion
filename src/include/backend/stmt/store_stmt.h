#include <utility>

#pragma once

class StoreStmt : public Stmt {
public:
  StoreStmt() = default;
  StoreStmt(std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> value, std::shared_ptr<Register> addr) : value_(std::move(value)), addr_(std::move(addr)) {
    assert(!VariantRep::variant_rep(value_).empty());
  }

  [[nodiscard]]std::string commit() const override {
    // if (std::holds_alternative<std::shared_ptr<Register>>(value_)) {
    //   auto value_reg = std::get<std::shared_ptr<Register>>(value_);
    //   return "store " + value_reg->GetType()->toString() + " " + value_reg->GetIndex() + ", " + addr_->GetIndexWithType();
    // } else if (std::holds_alternative<std::shared_ptr<LiteralNode>>(value_)) {
    //   auto value_literal = std::get<std::shared_ptr<LiteralNode>>(value_);
    //   return "store " + value_literal->getLiteralIRType()->toString() + " " + value_literal->ToString() + ", " + addr_->GetIndexWithType();
    // } else if (std::holds_alternative<int>(value_)) {
    //   auto value_int = std::get<int>(value_);
    //   return "store i32 " + std::to_string(value_int) + ", " + addr_->GetIndexWithType();
    // } else if (std::holds_alternative<bool>(value_)) {
    //   auto value_bool = std::get<bool>(value_);
    //   return "store i1 " + std::to_string(value_bool) + ", " + addr_->GetIndexWithType();
    // }
    return "store " + VariantRep::variant_rep(value_) + ", " + addr_->GetIndexWithType();
  }

  [[nodiscard]] std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> GetValue() {
    return value_;
  }

  [[nodiscard]] std::shared_ptr<Register> GetAddr() {
    return addr_;
  }
private:
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> value_;
  std::shared_ptr<Register> addr_;
};