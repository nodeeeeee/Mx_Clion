//
// Created by zhang-kai on 6/16/25.
//
#include "scope.h"
#include "frontend/ast/stat_node/def_node/class_def_node.h"
#include "frontend/ast/stat_node/def_node/class_func_def_node.h"
#include "frontend/ast/stat_node/def_node/func_def_node.h"
#include "frontend/ast/stat_node/def_node/main_func_node.h"
#include "frontend/ast/stat_node/def_node/def_node.h"
#include "frontend/ast/stat_node/regular_stat_node/block_node.h"
#include "frontend/ast/util/function.h"

void Scope::declare(const std::shared_ptr<DefNode>& def_node) {
  std::string decl_name = def_node->getIdNode()->getIdName();
  if (auto var_def = dynamic_pointer_cast<VarDefNode>(def_node)) {
    if (vars.contains(decl_name) || functions.contains(decl_name)) {
      throw std::runtime_error("repeated declaration");
    }
    vars[decl_name] = nullptr;
  } else if (auto func_def = dynamic_pointer_cast<FuncDefNode>(def_node)) {
    if (vars.contains(decl_name) || functions.contains(decl_name) || classes.contains(decl_name)) {
      throw std::runtime_error("repeated declaration");
    }
    functions[decl_name] = makeFunction(func_def);
  } else if (auto class_def = dynamic_pointer_cast<ClassDefNode>(def_node)) {
    if (classes.contains(decl_name)) {
      throw std::runtime_error("repeated declaration");
    }
    classes[decl_name] = temp_scope;
    classes[decl_name] = makeClass(class_def);
  } else if (auto main_def = dynamic_pointer_cast<MainFuncNode>(def_node)) {
    if (vars.contains(decl_name) || functions.contains(decl_name) || classes.contains(decl_name)) {
      throw std::runtime_error("repeated declaration");
    }
    functions[decl_name] = makeFunction(main_def);
  } else if (auto class_func_def = dynamic_pointer_cast<ClassFuncDefNode>(def_node)) {
    if (classes.contains(decl_name) || functions.contains(decl_name)) {
      throw std::runtime_error("repeated declaration");
    }
    functions[decl_name] = makeFunction(class_func_def);
  }
}

void Scope::declare(const std::shared_ptr<Function>& func) {
  functions[func->getFuncName()] = func;
}

std::shared_ptr<Function> Scope::makeFunction(std::shared_ptr<FuncDefNode> func) {
  auto return_type = func->getReturnType();
  auto param_var_defs = func->getVarDefs();
  std::vector<std::shared_ptr<TypeType>> param_type;
  for (const auto& param_var_def : param_var_defs) {
    param_type.push_back(param_var_def->getIdNode()->getType());
  }
  auto func_name = func->getIdNode()->getIdName();
  return std::make_shared<Function>(return_type, param_type, func_name);
}

std::shared_ptr<Function> Scope::makeFunction(std::shared_ptr<ClassFuncDefNode> class_func) {
  auto return_type = (class_func->getIdNode()->getType());
  std::vector<std::shared_ptr<TypeType>> param_type;
  auto func_name = class_func->getIdNode()->getIdName();
  return std::make_shared<Function>(return_type, param_type, func_name);
}

std::shared_ptr<Function> Scope::makeFunction(std::shared_ptr<MainFuncNode> main_func) {
  auto return_type = main_func->getIdNode()->getType();
  std::vector<std::shared_ptr<TypeType>> param_type;
  auto func_name = main_func->getIdNode()->getIdName();
  return std::make_shared<Function>(return_type, param_type, func_name);
}

std::shared_ptr<Function> Scope::makeFunction(std::shared_ptr<TypeType> return_type, std::vector<std::shared_ptr<TypeType>> param_type, std::string func_name) {
  return std::make_shared<Function>(return_type, param_type, func_name);
}

std::shared_ptr<Scope> Scope::makeClass(std::shared_ptr<ClassDefNode> class_def_node) {
  auto class_scope = std::make_shared<Scope>(*this);
  this->addChildScope(class_scope);
  auto stat_nodes = class_def_node->GetBlockNode()->getStatNodes();
  for (auto stat_node : stat_nodes) {
    if (auto def_node = std::dynamic_pointer_cast<DefNode>(stat_node)) {
      class_scope->declare(def_node);
    } else {
      throw std::runtime_error("cannot put statements other than def in a class");
    }
  }
  return class_scope;
}

void Scope::addChildScope(std::shared_ptr<Scope> scope) {
  children.push_back(scope);
}


const std::shared_ptr<TypeType> Scope::findVar(std::string var_name) {
  if (vars.contains(var_name)) {
    return vars[var_name];
  } else {
    if (this->getParent() != nullptr) {
        return this->getParent()->findVar(var_name);
    } else {
      throw std::runtime_error("var name not found" + var_name);
    }
  }
}

void Scope::setVarType(std::string var_name, std::shared_ptr<TypeType> var_type) {
  if (vars.contains(var_name)) {
    vars[var_name] = var_type;
  } else {
    throw std::runtime_error("var name not found" + var_name);
  }
}


const std::shared_ptr<Function>& Scope::findFunc(std::string func_name) {
  if (vars.contains(func_name)) {
    return functions[func_name];
  } else {
    if (this->getParent() != nullptr) {
      return this->getParent()->findFunc(func_name);
    } else {
      throw std::runtime_error("func name not found" + func_name);
    }
  }
}

const std::shared_ptr<Scope>& Scope::findClass(std::string class_name) {
  if (classes.contains(class_name)) {
    return classes[class_name];
  } else {
    if (this->getParent() != nullptr) {
      return this->getParent()->findClass(class_name);
    } else{
      throw std::runtime_error("class name not found" + class_name);
    }
  }
}

const std::shared_ptr<Scope>& Scope::getParent() { return parent; }

