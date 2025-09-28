#pragma once
#include <string>

#include "type/ir_type.h"

class ClassType {
public:
  explicit ClassType(std::string type_name) : type_name_(std::move(type_name)) {}

  void AddElement(const std::string& name, const std::shared_ptr<IRType>& element_type) {
    types_[name] = std::make_pair(element_type, index_cnt++);
  }

  int GetElementIndex(const std::string& element_name) {
    return types_[element_name].second;
  }

  std::shared_ptr<IRType> GetElementType(const std::string& element_name) {
    return types_[element_name].first;
  }

  std::pair<std::shared_ptr<IRType>, int> GetElement(const std::string& element_name) {
    return types_[element_name];
  }

private:
  static int index_cnt;
  std::string type_name_;
  std::map<std::string, std::pair<std::shared_ptr<IRType>, int>> types_;
};
