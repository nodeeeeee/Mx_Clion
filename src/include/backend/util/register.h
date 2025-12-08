#pragma once
#include <string>
#include <utility>

#include "type/ir_type.h"

class Register {
public:
  Register(int index, std::shared_ptr<IRType> type, bool is_global = false) : index_(index), type_(std::move(type)), is_global_(is_global) {}
  Register(std::string name, std::shared_ptr<IRType> type, bool is_global) : name_(std::move(name)), index_(index), type_(std::move(type)) {
    assert(is_global == true);
    is_global_ = is_global;
  }
  [[nodiscard]] bool IsGlobal() const {return is_global_;}
  std::shared_ptr<IRType> GetType() {return type_;}
  std::string GetName() {return name_;}
  [[nodiscard]] std::string GetIndex() const {return "%" + std::to_string(index_);}
  [[nodiscard]] std::string GetIndexWithType() {
    return GetType()->toString() + " " + GetIndex();
  }
private:
  bool is_global_;
  std::shared_ptr<IRType> type_;
  std::string name_;
  int index_;
};
