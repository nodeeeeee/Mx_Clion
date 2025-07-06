//
// Created by zhang-kai on 6/15/25.
//

#pragma once
#include "function.h"
#include "frontend/ast/stat_node/regular_stat_node/expr_node/id_node.h"
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

class Scope : public std::enable_shared_from_this<Scope> {
public:
  Scope() : parent(nullptr) {};
  Scope(const std::shared_ptr<Scope>& parent, std::shared_ptr<ASTNode> scope_owner) : parent(parent), scope_owner(std::move(scope_owner)) {}
  Scope(const std::shared_ptr<Scope>& parent) : parent(parent), scope_owner(nullptr) {}
  virtual ~Scope() = default;
  void declare(const std::shared_ptr<DefNode>& def_node);
  void declare(const std::shared_ptr<Function>& func);
  const std::shared_ptr<Function> & findFunc(std::string func_name);
  const std::shared_ptr<TypeType> findVar(std::string var_name);
  void setVarType(std::string var_name, std::shared_ptr<TypeType> var_type);
  const std::shared_ptr<Scope> & findClass(std::string class_name);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<FuncDefNode> func);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<ClassFuncDefNode> class_func);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<MainFuncNode> main_func);
  std::shared_ptr<Function> makeFunction(std::shared_ptr<TypeType> return_type, std::vector<std::shared_ptr<TypeType>> param_type, std::string func_name);
  std::shared_ptr<Scope> makeClass(std::shared_ptr<ClassDefNode> class_def_node);
  const std::shared_ptr<ASTNode> &getScopeOwner() {return scope_owner;}
  void addChildScope(std::shared_ptr<Scope> scope);
  const std::shared_ptr<Scope> & getParent();
  const std::shared_ptr<Scope> temp_scope;
protected:
  std::map<std::string, std::shared_ptr<TypeType>> vars;
  std::map<std::string, std::shared_ptr<Function>> functions;
  std::map<std::string, std::shared_ptr<Scope>> classes;
  std::vector<std::shared_ptr<Scope>> children;
  std::shared_ptr<Scope> parent;
  std::shared_ptr<ASTNode> scope_owner;
};



class GlobalScope : public Scope {
public:
  GlobalScope(std::shared_ptr<RootNode> root_node) : Scope(nullptr, root_node) {
    auto void_ = std::make_shared<TypeType>(TypeType::PrimitiveType::kVOID);
  auto bool_ = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
  auto int_ = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  auto string_ = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
  auto print_func = std::make_shared<Function>(void_, std::vector<std::shared_ptr<TypeType>>{string_}, "print");
  functions.emplace("print", print_func);
  auto println_func = std::make_shared<Function>(void_, std::vector<std::shared_ptr<TypeType>>{string_}, "println");
  functions.emplace("println", println_func);
  auto printInt_func = std::make_shared<Function>(void_, std::vector<std::shared_ptr<TypeType>>{int_}, "printInt");
  functions.emplace("printInt", printInt_func);
  auto printlnInt_func = std::make_shared<Function>(void_, std::vector<std::shared_ptr<TypeType>>{int_}, "printlnInt");
  functions.emplace("printlnInt", printlnInt_func);
  auto getString_func = std::make_shared<Function>(string_, std::vector<std::shared_ptr<TypeType>>{}, "getString");
  functions.emplace("getString", getString_func);
  auto getInt_func = std::make_shared<Function>(int_, std::vector<std::shared_ptr<TypeType>>{}, "getInt");
  functions.emplace("getInt", getInt_func);
  auto toString_func = std::make_shared<Function>(string_, std::vector<std::shared_ptr<TypeType>>{int_}, "toString");
  functions.emplace("toString", toString_func);

  auto string_class_scope = std::make_shared<Scope>(*this);
  this->addChildScope(string_class_scope);
  auto length_func = std::make_shared<Function>(int_, std::vector<std::shared_ptr<TypeType>>{}, "length");
  auto subString_func = std::make_shared<Function>(string_, std::vector<std::shared_ptr<TypeType>>{int_, int_}, "subString");
  auto parseInt_func = std::make_shared<Function>(int_, std::vector<std::shared_ptr<TypeType>>{}, "parseInt");
  auto ord_func = std::make_shared<Function>(int_, std::vector<std::shared_ptr<TypeType>>{int_}, "ord");
  string_class_scope->declare(length_func);
  string_class_scope->declare(subString_func);
  string_class_scope->declare(parseInt_func);
  string_class_scope->declare(ord_func);
  }
};

