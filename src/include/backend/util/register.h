#pragma once
#include <string>
#include <utility>

#include "type/ir_type.h"

class Register {
public:
  Register(int index, std::shared_ptr<IRType> type, bool is_global = false) : index_(index), type_(std::move(type)), is_global_(is_global) {}
  Register(std::string name, std::shared_ptr<IRType> type, bool is_global) : name_(std::move(name)), type_(std::move(type)) {
    assert(is_global == true);
    is_global_ = is_global;
  }
  [[nodiscard]] bool IsGlobal() const {return is_global_;}
  std::shared_ptr<IRType> GetType() {return type_;}
  std::string GetName() {return is_global_ ? name_.value() : GetIndex();}
  [[nodiscard]] std::string GetIndex() const {return is_global_ ? "@" + name_.value() : "%" + std::to_string(index_.value());}
  [[nodiscard]] std::string GetIndexWithType() {
    // if (index_.has_value()) {
    //   return GetType()->toString() + " " + GetIndex();
    // } else {
    //   return GetType()->toString() + " " GetName();
    // }
    return GetType()->toString() + " " + GetIndex();
  }
  // std::string GetOutputRep() {return is_global_ ? "%" + name_.value() : GetIndex();}

  [[nodiscard]] int GetIndexNum() const {return index_.value();}

private:
  bool is_global_ = false;
  std::shared_ptr<IRType> type_;
  std::optional<std::string> name_;
  std::optional<int> index_;
};
