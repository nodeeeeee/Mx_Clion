#pragma once
#include <string>

#include "type/ir_type.h"

class ClassType {
public:
  explicit ClassType(std::string type_name) : type_name_(std::move(type_name)) {}

  void AddElement(const std::shared_ptr<IRType>& element_type) {
    types_.push_back(element_type);
  }

private:
  std::string type_name_;
  std::vector<std::shared_ptr<IRType>> types_;
};
