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
    if (!types_.contains(element_name)) {
      return -1;
    }
    return types_[element_name].second;
  }

  std::shared_ptr<IRType> GetElementType(const std::string& element_name) {
    if (!types_.contains(element_name)) {
      return nullptr;
    }
    return types_[element_name].first;
  }

  std::pair<std::shared_ptr<IRType>, int> GetElement(const std::string& element_name) {
    if (!types_.contains(element_name)) {
      return std::pair<std::shared_ptr<IRType>, int>(nullptr, -1);
    }
    return types_[element_name];
  }

  [[nodiscard]] int GetClassSize() const {
    return index_cnt;
  }
  std::string commit() {
    std::string str = "%class." + type_name_ + " = type { ";
    bool first = true;
    for (const auto& element : types_) {
      if (!first) str += ", ";
      first = false;
      str += element.second.first->toString();
    }
    str += " }";
    return str;
  }
private:
  int index_cnt = 0;
  std::string type_name_;
  std::map<std::string, std::pair<std::shared_ptr<IRType>, int>> types_;
};
