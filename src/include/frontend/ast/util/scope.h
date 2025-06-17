//
// Created by zhang-kai on 6/15/25.
//

#pragma once
#include <vector>

#include "../def_node/def_node.h"
#include "../terminal_node/id_node.h"
#include "frontend/ast/root_node.h"
/* This class will manage all functions, types, vars...
 * We will declare builtin methods here.
 * by hardcoding a class for string (we will make string a special type)
*/


class TempScope;
class Function;
class MainFuncNode;
class ClassFuncDefNode;
class ClassDefNode;
class FuncDefNode;
class VarDefNode;

class Scope {
public:
  Scope() : parent(nullptr) {};
  Scope(const std::shared_ptr<Scope>& parent, std::shared_ptr<ASTNode> scope_owner) : parent(parent), scope_owner(std::move(scope_owner)) {}
  virtual ~Scope() = default;
  void declare(const std::shared_ptr<DefNode>& def_node);
  void Scope::declare(const std::shared_ptr<Function>& func);
  const std::shared_ptr<Function> & findFunc(std::string func_name);
  const bool findVar(std::string var_name);
  const std::shared_ptr<Scope> & getClass(std::string class_name);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<FuncDefNode> func);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<ClassFuncDefNode> class_func);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<MainFuncNode> main_func);
  std::shared_ptr<Function> makeFunction(TypeType return_type, std::vector<std::shared_ptr<TypeType>> param_type, std::string func_name);
  std::shared_ptr<Scope> makeClass(std::shared_ptr<ClassDefNode> class_def_node);
  void addChildScope(std::shared_ptr<Scope> scope);
  const std::shared_ptr<Scope> & getParent();
  const std::shared_ptr<Scope> temp_scope;
protected:
  std::map<std::string, bool> vars;
  std::map<std::string, std::shared_ptr<Function>> functions;
  std::map<std::string, std::shared_ptr<Scope>> classes;
  std::vector<std::shared_ptr<Scope>> children;
  std::shared_ptr<Scope> parent;
  std::shared_ptr<TempScope> tmp_scope = std::make_shared<TempScope>();
  std::shared_ptr<ASTNode> scope_owner;
};

class GlobalScope : public Scope {

public:
  GlobalScope(std::shared_ptr<RootNode> root_node) : Scope(nullptr, root_node) {}
};

class TempScope : public Scope {
public:
  TempScope();
};
