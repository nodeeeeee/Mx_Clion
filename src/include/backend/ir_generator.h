//
// Created by zhang-kai on 6/16/25.
//

#pragma once
#include "frontend/ast/visit_control.h"
#include "frontend/ast/type/type_type.h"
#include "util/class_type.h"
#include "util/ir_function.h"
#include "util/scope.h"



class IRGenerator : public VisitControl {
public:
  explicit IRGenerator(std::shared_ptr<RootNode> root_node) : root_node(root_node) {
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
  void visit(std::shared_ptr<InitArrayNode> node) final;
  void visit(std::shared_ptr<InitObjectNode> node) final;
  void visit(std::shared_ptr<NullExprNode> node) final;
  void visit(std::shared_ptr<UnaryExprNode> node) final;
  void visit(std::shared_ptr<TernaryExprNode> node) final;
  void visit(std::shared_ptr<AssignStatNode> node) final;
  void visit(std::shared_ptr<BlockNode> node) final;
  void visit(std::shared_ptr<BlockStatNode> node) final; // this is for raw blocks.
  void visit(std::shared_ptr<ForStatNode> node) final;
  void visit(std::shared_ptr<IfStatNode> node) final;
  void visit(std::shared_ptr<ReturnStatNode> node) final;
  void visit(std::shared_ptr<WhileStatNode> node) final;
  void visit(std::shared_ptr<LiteralNode> node) final;
  void visit(std::shared_ptr<TerminalNode> node) final;
  void visit(std::shared_ptr<ThisExprNode> node) final;
  void visit(std::shared_ptr<ParenExprNode> node) final;
  void visit(std::shared_ptr<IdNode> node) override{}
  void visit(std::shared_ptr<StatNode> node) override {}
  void visit(std::shared_ptr<RegularStatNode> node) override {}
  void visit(std::shared_ptr<ExprNode> node) override {}

  void InitFuncParam(std::shared_ptr<FuncDefNode> node) final;
  std::string FetchExprReg(std::shared_ptr<ExprNode> expr);
  void CreateString(std::shared_ptr<LiteralNode> string_literal);
  std::shared_ptr<Register> ToRightVal(std::shared_ptr<Register> reg);
  std::shared_ptr<Register> FindRegister(const std::string& var_name);

private:
  std::vector<std::shared_ptr<ClassType>> types_;
  std::vector<std::shared_ptr<IRFunction>> funcs_;
  std::shared_ptr<IRFunction> current_func_;
  std::shared_ptr<ClassType> current_class_type_;
  std::shared_ptr<Block> current_basic_block_;
  std::shared_ptr<IRScope> current_scope_;
  std::shared_ptr<IRGlobalScope> global_scope_ = std::make_shared<IRGlobalScope>();

  std::shared_ptr<TypeType> k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  std::shared_ptr<TypeType> k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
  std::shared_ptr<TypeType> k_string = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);


};
