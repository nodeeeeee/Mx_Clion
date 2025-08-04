#pragma once
#include <string>
#include <utility>

#include "type/ir_type.h"

class Register {
public:
  Register(std::string name, std::shared_ptr<IRType> type, bool is_global = false) : name_(std::move(name)), type_(std::move(type)), is_global_(is_global) {}
  [[nodiscard]] bool IsGlobal() const {return is_global_;}
  std::shared_ptr<IRType> GetType() {return type_;}
  std::string GetName() {return name_;}

private:
  bool is_global_;
  std::shared_ptr<IRType> type_;
  std::string name_;
};
