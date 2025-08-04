#pragma once
#include <map>
#include <memory>

#include "type/ir_type.h"

class Scope : public std::enable_shared_from_this<Scope> {
public:
  Scope() : parent_(nullptr) {
  }
  int GetIndex(const std::string& var_name) {
    try {
      return index_[var_name];
    } catch (const std::exception &e) {
      throw std::runtime_error("var not found exception");
    }
  }
  void declare(const std::string& var_name) {
    index_[var_name] = ++index_counter_;
  }
private:
  std::shared_ptr<Scope> parent_;
  std::map<std::string, int> index_;
  std::map<std::string, IRType> vars_;
  int index_counter_ = 0;
};
