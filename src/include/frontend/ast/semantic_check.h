//
// Created by zhang-kai on 6/16/25.
//

#pragma once
#include "visit_control.h"
#include "util/scope.h"
#include "root_node.h"
#include "frontend/global_scope_extractor.h"

class Scope;

class SemanticCheck : public VisitControl {
public:
  SemanticCheck(std::shared_ptr<RootNode> root_node) : root_node(std::move(root_node)) {}
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
  void visit(std::shared_ptr<AssignStatNode> node) final;
  void visit(std::shared_ptr<BlockNode> node) final;
  void visit(std::shared_ptr<ForStatNode> node) final;
  void visit(std::shared_ptr<IfStatNode> node) final;
  void visit(std::shared_ptr<ReturnStatNode> node) final;
  void visit(std::shared_ptr<WhileStatNode> node) final;
  void visit(std::shared_ptr<IdNode> node) final;
  void visit(std::shared_ptr<LiteralNode> node) final;
  void visit(std::shared_ptr<TerminalNode> node) final;
  void visit(std::shared_ptr<RootNode> node) final;
  void createScope(const std::shared_ptr<ASTNode> &node) final;
  void exitScope() final;

private:
  auto k_string = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
  auto k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  auto k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
};
