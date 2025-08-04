#pragma once
#include <string>

#include "type/ir_type.h"

class ClassType {
public:
  ClassType(std::string type_name, std::vector<std::shared_ptr<IRType>> types) : type_name_(std::move(type_name)), types_(std::move(types)) {}
private:
  std::string type_name_;
  std::vector<std::shared_ptr<IRType>> types_;
};
