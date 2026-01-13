#pragma once

#include "frontend/ast/type/type_type.h"
//
// Created by zhang-kai on 6/16/25.
//
class Function {
public:
  Function() = delete;
  Function(std::shared_ptr<TypeType> return_type, std::vector<std::shared_ptr<TypeType>> param_types, std::string func_name) : return_type(std::move(return_type)), param_types(std::move(param_types)), func_name(std::move(func_name)) {}
  const std::shared_ptr<TypeType> &getReturnType() const { return return_type; }
  const std::vector<std::shared_ptr<TypeType>> &getParamTypes() const { return param_types; }
  const std::string &getFuncName() const { return func_name; }
private:
  std::shared_ptr<TypeType> return_type;
  std::vector<std::shared_ptr<TypeType>> param_types;
  std::string func_name;
};
