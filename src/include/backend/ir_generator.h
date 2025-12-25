//
// Created by zhang-kai on 6/16/25.
//

#pragma once
#include <variant>

#include "frontend/ast/visit_control.h"
#include "frontend/ast/type/type_type.h"
#include "util/class_type.h"
#include "util/ir_function.h"
#include "util/scope.h"
#include "util/type/ir_type.h"


class IRGenerator : public VisitControl {
public:
  explicit IRGenerator(std::shared_ptr<RootNode> root_node) : root_node(root_node) {
    // init functions
    auto print_function_ = std::make_shared<IRFunction>("print", std::vector{k_ir_string}, k_ir_void, true);
    funcs_["print"] = print_function_;
    auto println_function = std::make_shared<IRFunction>("println", std::vector{k_ir_string}, k_ir_void, true);
    funcs_["println"] = println_function;
    auto printInt_function = std::make_shared<IRFunction>("printInt", std::vector{k_ir_int}, k_ir_void, true);
    funcs_["printInt"] = printInt_function;
    auto printlnInt_function = std::make_shared<IRFunction>("printlnInt", std::vector{k_ir_int}, k_ir_void, true);
    funcs_["printlnInt"] = printlnInt_function;
    auto getString_function = std::make_shared<IRFunction>("getString", std::vector<std::shared_ptr<IRType>>{}, k_ir_void, true);
    funcs_["getString"] = getString_function;
    auto getInt_function = std::make_shared<IRFunction>("getInt", std::vector<std::shared_ptr<IRType>>{}, k_ir_void, true);
    funcs_["getInt"] = getInt_function;
    auto toString_function = std::make_shared<IRFunction>("toString", std::vector{k_ir_int}, k_ir_string, true);
    funcs_["toString"] = toString_function;

    //String@length
    auto string_length_function = std::make_shared<IRFunction>("String_length", std::vector{k_ir_string}, k_ir_int, true);
    funcs_["String@length"] = string_length_function;
    //String@substring
    auto string_substring_function = std::make_shared<IRFunction>("String_substring", std::vector{k_ir_string, k_ir_int, k_ir_int}, k_ir_string, true);
    funcs_["String@substring"] = string_substring_function;
    //String@parseInt
    auto string_parseInt_function = std::make_shared<IRFunction>("String_parseInt", std::vector{k_ir_string}, k_ir_int, true);
    funcs_["String@parseInt"] = string_parseInt_function;
    //string@ord
    auto string_ord_function = std::make_shared<IRFunction>("String_ord", std::vector{k_ir_string, k_ir_int}, k_ir_int, true);
    funcs_["String@ord"] = string_ord_function;
    //Array@size
    auto array_size_function = std::make_shared<IRFunction>("Array_size", std::vector{k_ir_void_star}, k_ir_int, true);
    funcs_["Array@size"] = array_size_function;
    //Array@alloc
    auto array_alloc_function = std::make_shared<IRFunction>("ArrayAlloc", std::vector{k_ir_int}, k_ir_void_star, true);  //there might be some problem about dimension
    funcs_["ArrayAlloc"] = array_alloc_function;
    //builtin_strcat
    auto strcat_function = std::make_shared<IRFunction>("builtin_strcat", std::vector{k_ir_string, k_ir_string}, k_ir_string, true);
    funcs_["builtin_strcat"] = strcat_function;
    auto malloc_function = std::make_shared<IRFunction>("builtin_malloc", std::vector<std::shared_ptr<IRType>>{k_ir_int}, k_ir_void_star, true);
    funcs_["builtin_malloc"] = malloc_function;

    visit(root_node);
  }
  std::shared_ptr<RootNode> root_node;
  std::shared_ptr<Scope> current_scope = std::make_shared<GlobalScope>(root_node);
  void visit(std::shared_ptr<RootNode> node) final;
  void visit(std::shared_ptr<ClassFuncDefNode> node) final;
  void visit(std::shared_ptr<ClassDefNode> node) final;
  void visit(std::shared_ptr<FuncDefNode> node) final;
  void visit(std::shared_ptr<MainFuncNode> node) final;
  void visit(std::shared_ptr<VarDefNode> node) final;
  void visit(std::shared_ptr<ArrayConstNode> node) final;
  void visit(std::shared_ptr<BinaryExprNode> node) final;
  void visit(std::shared_ptr<DotExprNode> node) final;
  void visit(std::shared_ptr<FormatStringNode> node) final;
  void visit(std::shared_ptr<FuncCallNode> node) final;
  void visit(std::shared_ptr<IndexExprNode> node) final;
  void visit(std::shared_ptr<InitArrayNode> node) {throw std::runtime_error("Not implemented");}// included in VarDef, no need.
  void visit(std::shared_ptr<InitObjectNode> node) {throw std::runtime_error("Not implemented");};
  void visit(std::shared_ptr<NullExprNode> node) {throw std::runtime_error("Not implemented");};
  void visit(std::shared_ptr<UnaryExprNode> node) final;
  void visit(std::shared_ptr<TernaryExprNode> node) final;
  void visit(std::shared_ptr<AssignStatNode> node) final;
  void visit(std::shared_ptr<BlockNode> node) final;
  void visit(std::shared_ptr<BlockStatNode> node) final; // this is for raw blocks.
  void visit(std::shared_ptr<ForStatNode> node) final;
  void visit(std::shared_ptr<IfStatNode> node) final;
  void visit(std::shared_ptr<ReturnStatNode> node) final;
  void visit(std::shared_ptr<WhileStatNode> node) final;
  void visit(std::shared_ptr<LiteralNode> node) final; // this should be implemented, creating a register for this literal
  void visit(std::shared_ptr<TerminalNode> node) final;
  void visit(std::shared_ptr<ThisExprNode> node) final;
  void visit(std::shared_ptr<ParenExprNode> node) final;
  void visit(std::shared_ptr<IdNode> node) final;
  void visit(std::shared_ptr<StatNode> node) override {}
  void visit(std::shared_ptr<RegularStatNode> node) override {}
  void visit(std::shared_ptr<ExprNode> node) override {}

  void InitFuncParam(std::shared_ptr<FuncDefNode> node);
  std::variant<int, bool, std::shared_ptr<LiteralNode>, std::shared_ptr<Register>> FetchExprReg(std::shared_ptr<ExprNode> expr);
  std::shared_ptr<Register> CreateString(std::shared_ptr<LiteralNode> string_literal);
  std::shared_ptr<Register> ToRightVal(std::shared_ptr<Register> reg);
  std::shared_ptr<Register> FindRegister(const std::string& var_name);
  std::shared_ptr<IRFunction> FindFunction(const std::string& func_name);
  std::pair<std::shared_ptr<IRType>, int> GetElementInStruct(std::string type_name, std::string field_name);
  void InitializeArray(std::shared_ptr<Register> base, std::shared_ptr<ArrayConstNode> array_const);
  std::shared_ptr<ClassType> GetClassType(const std::string& type_name);

private:
  std::map<std::string, std::shared_ptr<ClassType>> types_;
  // std::vector<std::shared_ptr<IRFunction>> funcs_;
  std::map<std::string, std::shared_ptr<IRFunction>> funcs_; //a global vector that stores all functions defined
  std::shared_ptr<IRFunction> current_func_;
  std::shared_ptr<ClassType> current_class_type_;
  std::shared_ptr<Block> current_basic_block_;
  std::shared_ptr<IRScope> current_scope_;
  std::shared_ptr<IRGlobalScope> global_scope_ = std::make_shared<IRGlobalScope>();

  std::shared_ptr<TypeType> k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  std::shared_ptr<TypeType> k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
  std::shared_ptr<TypeType> k_string = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
  std::shared_ptr<TypeType> k_void = std::make_shared<TypeType>(TypeType::PrimitiveType::kVOID);
  std::shared_ptr<IRType> k_ir_int = std::make_shared<IRType>(k_int);
  std::shared_ptr<IRType> k_ir_bool = std::make_shared<IRType>(k_bool);
  std::shared_ptr<IRType> k_ir_string = std::make_shared<IRType>(k_string, 1);
  std::shared_ptr<IRType> k_ir_void = std::make_shared<IRType>(k_void);
  std::shared_ptr<IRType> k_ir_void_star = std::make_shared<IRType>(k_void, 1);



};


//all variants support int, LiteralNode, Registers