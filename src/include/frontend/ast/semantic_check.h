//
// Created by zhang-kai on 6/16/25.
//

#pragma once
#include "visit_control.h"
#include "util/scope.h"



class SemanticCheck : public VisitControl {
public:
  explicit SemanticCheck(std::shared_ptr<RootNode> root_node) : root_node(root_node) {
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
  void visit(std::shared_ptr<ForStatNode> node) final;
  void visit(std::shared_ptr<IfStatNode> node) final;
  void visit(std::shared_ptr<ReturnStatNode> node) final;
  void visit(std::shared_ptr<WhileStatNode> node) final;
  void visit(std::shared_ptr<LiteralNode> node) final;
  void visit(std::shared_ptr<TerminalNode> node) final;
  // void visit(std::shared_ptr<DefNode> node) override {}
  void visit(std::shared_ptr<IdNode> node) override {}
  void visit(std::shared_ptr<StatNode> node) override {}
  void visit(std::shared_ptr<RegularStatNode> node) override {}
  void visit(std::shared_ptr<ExprNode> node) override {}

  void createScope(const std::shared_ptr<ASTNode> &node);
  void exitScope();

private:
  std::shared_ptr<TypeType> k_string = std::make_shared<TypeType>(TypeType::PrimitiveType::kSTRING);
  std::shared_ptr<TypeType> k_int = std::make_shared<TypeType>(TypeType::PrimitiveType::kINT);
  std::shared_ptr<TypeType> k_bool = std::make_shared<TypeType>(TypeType::PrimitiveType::kBOOL);
};
